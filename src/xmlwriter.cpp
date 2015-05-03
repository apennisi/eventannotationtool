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


#include "xmlwriter.h"



XmlWriter::XmlWriter(const std::string &name,
                     const std::vector<Event*> &events)
{
    file.open(name.c_str());

    this->write(events);

    file.close();

}

void XmlWriter::write(const std::vector<Event*> &events)
{
    std::vector<Event*>::const_iterator it;

    file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
    file << "<dataset>" << std::endl;

    for(it = events.begin(); it != events.end(); ++it)
    {
        if((*it)->getAbnormal())
        {
            file << "\t<frame number=\"" << it - events.begin() << "\">" << std::endl;
            file << "\t\tABNORMAL" << std::endl;
            file << "\t</frame>" << std::endl;
        }
    }

    file << "</dataset>" << std::endl;
}
