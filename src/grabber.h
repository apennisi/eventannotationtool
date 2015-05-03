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
 * \file grabber.h
 *
 * \class Grabber
 *
 * \brief Class for grabbing images
 *
 **/

#ifndef GRABBER_H
#define GRABBER_H

#include <iostream>
#include <opencv2/opencv.hpp>

namespace grabber {
    class Grabber
    {
    public:
        /**
         * \brief Create a new object Grabber
         *
         */
        Grabber();
        /**
         * \brief Return the next image
         *
         * \return return the next image
         *
         */
        virtual cv::Mat next(const int &speed) = 0;
        /**
         * \brief Return the previous image
         *
         * \return return the previous image
         *
         */
        virtual cv::Mat prev(const int &speed) = 0;
        /**
         * \brief Load the images when an XML file is loaded
         *
         * \param _frame: number of images to load
         *
         */
        cv::Mat load(const int &_frame);
        /**
         * \brief Return the end of the images to analyse
         *
         * \return return the end of the images to analyse
         *
         */
        virtual int getEnd() = 0;
        /**
         * \brief Return current frame number
         *
         * \return return current frame number
         *
         */
        inline int getFrameNum()
        {
            return frameNumber;
        }
    protected:
        int frameNumber, end;
    };
}

#endif // GRABBER_H
