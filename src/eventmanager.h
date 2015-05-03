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

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <iostream>
#include <vector>
#include <QLabel>

#include "event.h"

class EventManager
{
public:
    /**
     * @brief EventManager new Object EventManager
     * @parm numFrames number of frames of the video/images to annotate
     */
    EventManager(const int &_numFrames);
    /**
     * @brief next return next event
     * @param speed frame speed
     * @param l label to modify
     */
    void next(const int &speed, QLabel *l);
    /**
     * @brief prev return previous event
     * @param speed frame speed
     * @param l label to modify
     */
    void prev(const int &speed, QLabel *l);
    /**
     * @brief getEvents return the set of events
     * @return return the set of events
     */
    inline std::vector<Event*> getEvents() const
    {
        return events;
    }
    /**
     * @brief startEvent start to annotate an abnormal event
     */
    inline void startEvent()
    {
        event = true;
    }
    /**
     * @brief endEvent end to annotate an abnormal event
     */
    inline void endEvent()
    {
        event = false;
    }
    /**
     * @brief draw draw the event in the current image
     * @param l label to modify
     */
    void draw(QLabel *l);
    /**
     * @brief setCurrentEvent set current frame to abnormal
     */
    inline void setCurrentEvent()
    {
        events[frameCounter - 1]->setAbnormal();
    }
    /**
     * @brief cancelCurrentEvent set current frame to normal
     */
    inline void cancelCurrentEvent()
    {
        events[frameCounter - 1]->setNormal();
    }
    /**
     * @brief setEvents set the vector events to _events
     * @param _events vector of events in input
     */
    void setEvents(const std::vector<Event*> &_events);
private:
    std::vector<Event*> events;
    bool event;
    int numFrames, frameCounter;
};

#endif // EVENTMANAGER_H
