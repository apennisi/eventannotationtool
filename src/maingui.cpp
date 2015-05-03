/*
 *  EAT Event Annotation Tool
 *  Copyright 2015 Andrea Pennisi
 *
 *  This file is part of AT and it is distributed under the terms of the
 *  GNU Lesser General Public License (Lesser GPL)
 *
 *
 *
 *  EAT is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  EAT is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with EAT.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *  EAT has been written by Andrea Pennisi
 *
 *  Please, report suggestions/comments/bugs to
 *  andrea.pennisi@gmail.com
 *
 */

#include <QFileDialog>
#include <QSignalMapper>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <iostream>
#include <unistd.h>

#include "maingui.h"
#include "ui_maingui.h"
#include "xmlwriter.h"
#include "xmlreader.h"

MainGUI::MainGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainGUI)
{
    ui->setupUi(this);
    ui->image->setStyleSheet("background-color: black");
    ui->bar->setStyleSheet("background-color: rgb(0,0, 255)");
    ui->controls->setStyleSheet(QString::fromUtf8("QWidget#controls\n"
                                                "{\n"
                                                "    border-radius: 5px;\n"
                                                "    background-color: rgba(255, 255, 255, 70);\n"
                                                "}\n"
                                                ""));

    QPixmap pix("../images/arrow.png");
    ui->arrow->setPixmap(pix);
    ui->arrow->hide();

    ui->loadXML->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");
    ui->saveXML->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");

    ui->next->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");
    ui->nextSpeed->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");

    ui->prev->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");
    ui->prevSpeed->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");

    ui->startEvent->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");
    ui->endEvent->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");

    ui->cancelEvent->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");

    imageWidth = ui->image->width();
    imageHeight = ui->image->height();
    barWidth = ui->bar->width();
    barHeight = ui->bar->height();

    displayImage = new DisplayManager(ui->image);
    displayBar = new DisplayManager(ui->bar);

    my_grabber = NULL;

    images = video = interaction = false;

    connect(ui->folder_button , SIGNAL( clicked() ), this, SLOT( open_image_folder() ) );
    connect(ui->video_button , SIGNAL( clicked() ), this, SLOT( open_video_file() ) );

    barManager = NULL;
    eventManager = NULL;

    //Button Connection
    QSignalMapper* signalNext = new QSignalMapper (this) ;
    connect (ui->next, SIGNAL(clicked()), signalNext, SLOT(map())) ;
    connect (ui->nextSpeed, SIGNAL(clicked()), signalNext, SLOT(map())) ;

    signalNext->setMapping(ui->next, 1) ;
    signalNext-> setMapping(ui->nextSpeed, 10) ;

    connect (signalNext, SIGNAL(mapped(int)), this, SLOT(next(int))) ;

    QSignalMapper* signalPrev = new QSignalMapper (this) ;
    connect (ui->prev, SIGNAL(clicked()), signalPrev, SLOT(map())) ;
    connect (ui->prevSpeed, SIGNAL(clicked()), signalPrev, SLOT(map())) ;

    signalPrev->setMapping(ui->prev, 1) ;
    signalPrev->setMapping(ui->prevSpeed, 10) ;

    connect (signalPrev, SIGNAL(mapped(int)), this, SLOT(prev(int))) ;

    connect(ui->startEvent, SIGNAL(clicked()), this, SLOT(startEvent()) );
    connect(ui->endEvent, SIGNAL(clicked()), this, SLOT(stopEvent()) ) ;
    connect(ui->cancelEvent, SIGNAL(clicked()), this, SLOT(cancelEvent()) );

    connect(ui->saveXML, SIGNAL(clicked()), this, SLOT(save()) );
    connect(ui->loadXML, SIGNAL(clicked()), this, SLOT(load()) );

    enableEvent = false;
}

MainGUI::~MainGUI()
{
    delete ui;
    delete displayBar;
    delete displayImage;
    if(video)
    {
        delete dynamic_cast<grabber::VideoGrabber*>(my_grabber);
    }
    if(images)
    {
        delete dynamic_cast<grabber::ImageGrabber*>(my_grabber);
    }
}

void MainGUI::activateButtons()
{
    ui->folder_button->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");
    ui->video_button->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");

    ui->loadXML->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");
    ui->saveXML->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");

    ui->next->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");
    ui->nextSpeed->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");

    ui->prev->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");
    ui->prevSpeed->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");

    ui->startEvent->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");

    ui->cancelEvent->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");
}

void MainGUI::open_video_file()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open Video File"),
                ".",
                tr("Video (*.avi *.mpg *.mkv *.mpeg *.mov);;") );

    if(filename != "")
    {
        if(my_grabber != NULL)
        {
            delete dynamic_cast<grabber::ImageGrabber*>(my_grabber);
        }

        my_grabber = new grabber::VideoGrabber(filename.toStdString());


        activateButtons();

        eventManager = new EventManager(my_grabber->getEnd());
        eventManager->next(1, ui->event);

        frame = my_grabber->next(1);

        displayImage->display(frame);

        barManager = new BarManager(my_grabber->getEnd(), cv::Size(ui->bar->width(), ui->bar->height()),
                                    ui->arrow);

        ui->arrow->show();

        displayBar->display(barManager->getBar());

        video = interaction = true;
    }
}

void MainGUI::open_image_folder()
{
    QString dirname = QFileDialog::getExistingDirectory(this,
                                                        tr("Choose the Image Directory"),
                                                        ".",
                                                        QFileDialog::ShowDirsOnly);
    if(dirname != "")
    {
        if(my_grabber != NULL)
        {
            delete static_cast<grabber::VideoGrabber*>(my_grabber);
        }

        my_grabber = new grabber::ImageGrabber(dirname.toStdString());

        activateButtons();

        eventManager = new EventManager(my_grabber->getEnd());
        eventManager->next(1, ui->event);

        frame = my_grabber->next(1);

        displayImage->display(frame);

        barManager = new BarManager(my_grabber->getEnd(), cv::Size(ui->bar->width(), ui->bar->height()),
                                    ui->arrow);

        ui->arrow->show();

        displayBar->display(barManager->getBar());

        images = interaction = true;
    }
}


void MainGUI::next(const int &speed)
{
    if(interaction)
    {
        frame = my_grabber->next(speed);
        barManager->next(speed);
        eventManager->next(speed, ui->event);
        displayImage->display(frame);
        displayBar->display(barManager->getBar());
    }
}

void MainGUI::prev(const int &speed)
{
    if(interaction)
    {
        frame = my_grabber->prev(speed);
        barManager->prev(speed);
        eventManager->prev(speed, ui->event);
        displayImage->display(frame);
        displayBar->display(barManager->getBar());
    }
}

void MainGUI::startEvent()
{
    if(interaction && !enableEvent)
    {
        eventManager->startEvent();
        eventManager->setCurrentEvent();
        eventManager->draw(ui->event);
        barManager->setAbnormal();
        ui->endEvent->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");
        ui->startEvent->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");
        enableEvent = true;
    }
}

void MainGUI::save()
{
    if(interaction)
    {
        QString filename = QFileDialog::getSaveFileName(
                    this,
                    tr("Save Document"),
                    QDir::currentPath(),
                    tr("Documents (*.xml)") );
        if( !filename.isNull() )
        {
            XmlWriter xmlWriter(filename.toStdString(),
                                eventManager->getEvents());
        }
    }
}

void MainGUI::load()
{
    if(interaction)
    {
        QString filename = QFileDialog::getOpenFileName(
                    this,
                    tr("Open XML File"),
                    ".",
                    tr("File (*.xml);;") );

        if(filename != "")
        {
            XmlReader *xmlReader = new XmlReader(filename.toStdString());
            eventManager->setEvents(xmlReader->getEvents());
            barManager->setEvents(xmlReader->getEvents());
            int speed = int(xmlReader->getEvents().size())  - 1;
            this->next(speed);
            delete xmlReader;
        }
    }

}

void MainGUI::stopEvent()
{
    if(interaction && enableEvent)
    {
        eventManager->endEvent();
        barManager->setNormal();
        ui->startEvent->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");
        ui->endEvent->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");
        enableEvent = false;
    }
}

void MainGUI::cancelEvent()
{
    if(interaction)
    {
        eventManager->cancelCurrentEvent();
        eventManager->draw(ui->event);
        barManager->cancelEvent();
        displayBar->display(barManager->getBar());
    }
}
