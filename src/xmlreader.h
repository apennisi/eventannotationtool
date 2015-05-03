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
 * \file xmlreader.h
 *
 * \class XmlReader
 *
 * \brief Class for managing xml files
 *
 **/

#ifndef XMLREADER_H
#define XMLREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <boost/tokenizer.hpp>

#include "eventmanager.h"

class XmlReader
{
public:
    /**
     * \brief Create a new object XmlReader
     *
     * \param name: file name
     *
     */
    XmlReader(const std::string &name);
    /**
     * \brief Return the rectangles read from the file
     *
     * \return return the rectangles read from the file
     *
     */
    inline std::vector<Event*> getEvents() const
    {
        return events;
    }
private:
    /**
     * \brief Read the file
     *
     * \param name: file name
     *
     */
    void read(const std::string &name);
    /**
     * \brief Parse a line
     *
     * \param line: line to parse
     *
     */
    bool parsingLine(const std::string &line);
    std::vector<Event*> events;
    std::map<std::string, int> xmlMap;
    bool frame;
};

#endif // XMLREADER_H
