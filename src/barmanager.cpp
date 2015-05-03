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

#include "barmanager.h"

BarManager::BarManager(const int &endFrame, const cv::Size &_barsize, QLabel *_arrow)
    : arrow(_arrow), barsize(_barsize), frameNumber(endFrame)
{
    barW = barsize.width;
    barH = barsize.height;
    bigBar = cv::Mat(barsize, CV_8UC3, cv::Scalar(255, 0, 0));
    if(endFrame > barW)
    {
        while(endFrame % barW != 0)
        {
            barW--;
        }
        ratio = endFrame / barW;
    }
    else
    {
        ratio = 1;
        barW = endFrame;
    }

    cursor = cv::Mat::zeros(cv::Size(ratio, barH), CV_8UC3);

    bar = cv::Mat(cv::Size(barW, barH), CV_8UC3, cv::Scalar(0, 255, 0));
    cursor.copyTo(bar(cv::Rect(0, 0, cursor.cols, cursor.rows)));
    barTl = cv::Point((barsize.width - barW)/2, 0);

    bar.copyTo(bigBar(cv::Rect(barTl.x, barTl.y, barW, barH)));

    arrowPos = cv::Point(barTl.x + arrow->x()/2 + (ratio + 1), arrow->y());
    startArrowPos = arrowPos;
    arrow->move(QPoint(cvRound(arrowPos.x), arrowPos.y));
    intervalCounter = 0;
    abnormal = false;
    cursorCounter = 0;

    bigBarCopy = bigBar.clone();

    events.resize(barW);
}

void BarManager::next(const int &speed)
{
    if((intervalCounter + speed) / ratio < (barW - ratio) )
    {
        for(int i = 0; i < speed && intervalCounter < frameNumber; ++i)
        {
            intervalCounter++;
            if(abnormal)
            {
                events[cvRound(double(intervalCounter) / double(ratio)) + 1]->setAbnormal();
            }
        }
        arrowPos.x = startArrowPos.x + cvRound(double(intervalCounter) / double(ratio)) + 1;
        cursorCounter = cvRound(double(intervalCounter) / double(ratio)) + 1;
    }
    else
    {
        intervalCounter = frameNumber;
        arrowPos.x = startArrowPos.x + intervalCounter/ratio - ratio;
        cursorCounter = cvRound(double(intervalCounter) / double(ratio)) - ratio;
    }

    arrow->move(QPoint(cvRound(arrowPos.x), arrowPos.y));
    bar = cv::Scalar(0, 255, 0);
    drawBar();
    cursor.copyTo(bar(cv::Rect(cursorCounter,
                           0, cursor.cols, cursor.rows)));
    bar.copyTo(bigBar(cv::Rect(barTl.x, barTl.y, barW, barH)));
}

void BarManager::prev(const int &speed)
{
    if((intervalCounter - speed) / ratio > ratio )
    {
        for(int i = 0; i < speed && intervalCounter > 0; ++i)
        {
            intervalCounter--;
        }
        arrowPos.x = startArrowPos.x + cvRound(double(intervalCounter) / double(ratio)) + 1;
        cursorCounter = cvRound(double(intervalCounter) / double(ratio)) + 1;
    }
    else
    {
        intervalCounter = 0;
        arrowPos.x = startArrowPos.x;
        cursorCounter = 0;
    }

    arrow->move(QPoint(cvRound(arrowPos.x), arrowPos.y));
    bar = cv::Scalar(0, 255, 0);
    drawBar();
    cursor.copyTo(bar(cv::Rect(cursorCounter,
                           0, cursor.cols, cursor.rows)));
    bar.copyTo(bigBar(cv::Rect(barTl.x, barTl.y, barW, barH)));
}

void BarManager::cancelEvent()
{
    events[cursorCounter]->setNormal();
    bar = cv::Scalar(0, 255, 0);
    drawBar();
    cursor.copyTo(bar(cv::Rect(cursorCounter,
                           0, cursor.cols, cursor.rows)));
    bar.copyTo(bigBar(cv::Rect(barTl.x, barTl.y, barW, barH)));
}

void BarManager::setEvents(const std::vector<Event *> &_events)
{
    events.clear();
    std::vector<Event*>::const_iterator it;
    for(it = _events.begin(); it != _events.end(); ++it)
    {
        events.push_back(new Event((*it)->getAbnormal()));
    }
}

void BarManager::drawBar()
{
    for(size_t i = 0; i < events.size(); ++i)
    {
        if(events[i]->getAbnormal() == true)
        {
            cv::rectangle(bar, cv::Rect(i, 0, cursor.cols, cursor.rows),
                          cv::Scalar(0, 0, 255), -1);
        }
    }
}
