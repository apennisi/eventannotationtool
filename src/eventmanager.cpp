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

#include "eventmanager.h"

EventManager::EventManager(const int &_numFrames)
    : numFrames(_numFrames)
{
    event = false;
    frameCounter = 0;
}

void EventManager::next(const int &speed, QLabel *l)
{
    if(frameCounter >= int(events.size()))
    {
        for(int i = 0; i < speed && frameCounter <= numFrames; ++i)
        {
            events.push_back(new Event(event));
            frameCounter++;
        }
    }
    else
    {
        for(int i = 0; i < speed && frameCounter <= numFrames; ++i)
        {
            frameCounter++;
        }
    }
    draw(l);
}

void EventManager::prev(const int &speed, QLabel *l)
{
    if(frameCounter >= 0)
    {
        for(int i = 0; i < speed && frameCounter > 0; ++i)
        {
            frameCounter--;
        }
    }
    else
    {
        frameCounter = 0;
    }
    draw(l);
}

void EventManager::draw(QLabel *l)
{
    (frameCounter == 0) ? events[frameCounter]->draw(l)
                        : events[frameCounter - 1]->draw(l);
}

void EventManager::setEvents(const std::vector<Event*> &_events)
{
    events.clear();
    std::vector<Event*>::const_iterator it;
    for(it = _events.begin(); it != _events.end(); ++it)
    {
        events.push_back(new Event((*it)->getAbnormal()));
    }
}
