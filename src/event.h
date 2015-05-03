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

#ifndef EVENT_H
#define EVENT_H

#include <opencv2/opencv.hpp>
#include <QLabel>
#include <QPainter>
#include <QPixmap>


class Event
{
public:
    /**
     * @brief Event new Object Event
     */
    Event();
    /**
     * @brief Event new Object Event
     * @param _abnormal set if the event is normal or abnormal
     */
    Event(const bool &_abnormal);
    /**
     * @brief setAbnormal set abnormal event
     */
    inline void setAbnormal()
    {
        abnormal = true;
    }
    /**
     * @brief setNormal set normal event
     */
    inline void setNormal()
    {
        abnormal = false;
    }

    /**
     * @brief getAbnormal return true if an abnormal event is detected
     * @return true if an abnormal event is detected
     */
    inline bool getAbnormal() const
    {
        return abnormal;
    }
    /**
     * @brief draw draw a circle representing the state normal/abnormal
     * @param img image to modify
     */
    void draw(QLabel *l);
private:
    bool abnormal;
};

#endif // EVENT_H
