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

#ifndef MAINGUI_H
#define MAINGUI_H

#include <QWidget>
#include <opencv2/opencv.hpp>

#include "grabber.h"
#include "imagegrabber.h"
#include "videograbber.h"
#include "displaymanager.h"
#include "barmanager.h"
#include "eventmanager.h"

namespace Ui {
class MainGUI;
}

class MainGUI : public QWidget
{
    Q_OBJECT

public:
    explicit MainGUI(QWidget *parent = 0);
    ~MainGUI();

private:
    Ui::MainGUI *ui;
    grabber::Grabber *my_grabber;
    cv::Mat frame, bar;
    int imageWidth, imageHeight, barWidth, barHeight;
    DisplayManager *displayImage, *displayBar;
    BarManager *barManager;
    EventManager *eventManager;
    void activateButtons();
    bool images, video, interaction;
    bool enableEvent;

private slots:
    void open_video_file();
    void open_image_folder();
    void next(const int &speed);
    void prev(const int &speed);
    void startEvent();
    void save();
    void load();
    void stopEvent();
    void cancelEvent();
};

#endif // MAINGUI_H
