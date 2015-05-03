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

#include <string>

#include "xmlreader.h"


XmlReader::XmlReader(const std::string &name)
{

    frame = false;

    xmlMap.insert(std::pair<std::string, int>("<frame", 0));
    xmlMap.insert(std::pair<std::string, int>("</frame", 1));
    xmlMap.insert(std::pair<std::string, int>("number=", 2));
    xmlMap.insert(std::pair<std::string, int>("ABNORMAL", 3));

    this->read(name);
}

void XmlReader::read(const std::string &name)
{
    std::ifstream file(name.c_str());
    std::string line;

    while (std::getline(file, line))
    {
        line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
        this->parsingLine(line);
    }
}

bool XmlReader::parsingLine(const std::string &line)
{

    boost::char_separator<char> sep(" ");
    boost::tokenizer< boost::char_separator<char> > tok(line, sep);
    sep = boost::char_separator<char>("\"");
    cv::Point tl;
    for(boost::tokenizer< boost::char_separator<char> >::iterator it = tok.begin(); it != tok.end(); ++it)
    {
        boost::tokenizer< boost::char_separator<char> > tok_(*it, sep);
        for(boost::tokenizer< boost::char_separator<char> >::iterator it2=tok_.begin(); it2 != tok_.end(); ++it2)
        {
            std::string s(*it2);

            switch (xmlMap[s])
            {
                case 0:
                    frame = true;
                    break;
                case 1:
                    frame = false;
                    break;
                case 2:
                    if (frame)
                    {
                        int fnum = atoi((*(++it2)).c_str());
                        if(fnum - events.size() > 1)
                        {
                            for(int i = events.size(); i < fnum; ++i)
                            {
                                events.push_back(new Event(false));
                            }
                        }
                    }
                    break;
                case 3:
                    if(frame)
                    {
                        events.push_back(new Event(true));
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return true;
}
