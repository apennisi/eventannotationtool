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

#ifndef BARMANAGER_H
#define BARMANAGER_H

#include <opencv2/opencv.hpp>
#include <QLabel>

#include "event.h"

/**
 * @file barmanager.h
 * @class BarManager
 * @brief The BarManager class
 */

class BarManager
{
public:
    /**
     * @brief BarManager create a new object BarManager
     * @param endFrame number of frames
     * @param barsize size of the bar
     * @param _arrow label to move during the interaction
     */
    BarManager(const int &endFrame, const cv::Size &_barsize,
               QLabel *_arrow);
    /**
     * @brief getBar return the bar
     * @return the bar image
     */
    inline cv::Mat getBar() const
    {
        return bigBar;
    }
    /**
     * @brief next move the arrow forward
     * @param speed
     */
    void next(const int &speed);
    /**
     * @brief prev move the arrow backward
     * @param speed
     */
    void prev(const int &speed);
    /**
     * @brief setAbnormal set an abnormal event into the bar
     */
    void setAbnormal()
    {
        abnormal = true;
    }
    /**
     * @brief setNormal set a normal event into the bar
     */
    void setNormal()
    {
        abnormal = false;
    }
    /**
     * @brief cancelEvent the current event
     */
    void cancelEvent();
    /**
     * @brief setEvents set the vector events
     * @param _events the input vector
     */
    void setEvents(const std::vector<Event*> &_events);
private:
    void drawBar();
    cv::Mat bar, cursor;
    cv::Mat bigBar, bigBarCopy;
    QLabel *arrow;
    int barW, barH;
    cv::Size barsize;
    int frameNumber;
    int ratio;
    int intervalCounter, cursorCounter;
    cv::Point barTl, arrowPos, startArrowPos;
    bool abnormal;
    std::vector<Event*> events;
};

#endif // BARMANAGER_H
