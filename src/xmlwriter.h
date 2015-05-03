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

/**
 * \file xmlwriter.h
 *
 * \class XmlWriter
 *
 * \brief Class for writing a file xml
 *
 **/

#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <iostream>
#include <fstream>

#include "event.h"

class XmlWriter
{
public:
    /**
     * \brief Create a new object XmlWriter
     *
     * \param name: file name
     * \param rectangles: rectangles to write into the file
     *
     */
    XmlWriter(const std::string &name,
              const std::vector<Event*> &events);
private:
    /**
     * \brief Write rectangles
     * 
     * \param rectangles: rectangles to write into the file
     *
     */
    void write(const std::vector<Event*> &events);
    std::ofstream file;
};


#endif // XMLWRITER_H
