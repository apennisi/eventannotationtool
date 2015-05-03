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
 * \file videograbber.h
 *
 * \class VideoGrabber
 *
 * \brief Class for grabbing images from a video
 *
 **/

#ifndef VIDEOGRABBER_H
#define VIDEOGRABBER_H

#include <opencv2/opencv.hpp>
#include <stdexcept>
#include "grabber.h"

namespace grabber {

    class VideoGrabber : public Grabber
    {
    public:
        /**
         * \brief Create a new object VideoGrabber
         *
         * \param video_file: the video filename
         *
         */
        VideoGrabber(const std::string &video_file);
        /**
         * \brief VideoGrabber Destructor
         *
         */
        ~VideoGrabber();
        /**
         * @brief next return the next speed image
         * @param speed the number of frame to skip
         * @return the speed image
         */
        cv::Mat next(const int &speed);
        /**
         * @brief prev return the previous speed image
         * @param speed the number of frame to skip
         * @return the speed image
         */
        cv::Mat prev(const int &speed);
        /**
         * \brief Return current frame number
         *
         * \return return current frame number
         *
         */
        int getEnd();
    private:
        std::string video;
        cv::VideoCapture cap;
        /**
          * \brief Scroll the entire video and collect the images
          *
          */
        void videoScrolling();
        std::vector<cv::Mat*> history;
    };

}

#endif // VIDEOGRABBER_H
