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

#include "videograbber.h"

using namespace grabber;

VideoGrabber::VideoGrabber(const std::string &video_file)
    : video(video_file)
{
    cap = cv::VideoCapture(video);
    if(!cap.isOpened())
    {
        throw std::invalid_argument( "Invalid Video File Name" );
    }

    try
    {
        end = int(cap.get(CV_CAP_PROP_FRAME_COUNT));
    }
    catch(int ex)
    {
        std::cout << "Invalid End of File " << ex << std::endl;
        exit(-1);
    }


    frameNumber = -1;


}

VideoGrabber::~VideoGrabber()
{
    if(history.size() > 0)
    {
        for(int i = 0 ; i < int(history.size()); ++i)
        {
            delete history[i];
        }
    }
}


cv::Mat VideoGrabber::next(const int &speed)
{
    cv::Mat frame;
    if(end == int(history.size()))
    {
        if(frameNumber + speed >= end - 1)
        {
            frameNumber = end - 1;
        }
        else
        {
            frameNumber += speed;
        }
        frame = *(history[frameNumber]);
    }
    else
    {
        if(frameNumber >= int(history.size()) - 1)
        {
            for(int i = 0; i < speed && frameNumber < end; ++i)
            {
                if(!frame.empty())
                {
                    frame.release();
                }
                if(cap.read(frame))
                {

                    history.push_back(new cv::Mat(frame));
                    frameNumber++;
                }
            }
            if(frameNumber == int(history.size()) - 1)
            {
                frame = *(history[frameNumber]);
            }
        }
        else
        {
            frameNumber += speed;
            frame = *(history[frameNumber]);
        }
    }
    return frame;
}

cv::Mat VideoGrabber::prev(const int &speed)
{
    cv::Mat frame;
    if(frameNumber - speed >= 0)
    {
        frameNumber -= speed;
    }
    else
    {
        frameNumber = 0;
    }
    frame = *(history[frameNumber]);
    return frame;
}

int VideoGrabber::getEnd()
{
    return end;
}

void VideoGrabber::videoScrolling()
{
    cv::Mat frame;
    while (cap.read(frame))
    {
        history.push_back(new cv::Mat(frame.clone()));
    }

    end = history.size();
}
