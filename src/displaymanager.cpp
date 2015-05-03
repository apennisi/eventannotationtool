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

#include <QImage>
#include <QPixmap>
#include "displaymanager.h"

DisplayManager::DisplayManager(QLabel *l)
    : label(l)
{

}


void DisplayManager::display(const cv::Mat &image)
{
    QImage *qImage = Mat2QImage(resize(image));
    QPixmap img = QPixmap::fromImage(*qImage);

    label->setPixmap(img);

    delete qImage;
}

cv::Mat DisplayManager::resize(const cv::Mat &image)
{
    cv::Mat frame = cv::Mat::zeros(cv::Size(label->width(), label->height()), CV_8UC3);

    if(image.rows < label->height() && image.cols < label->width())
    {
        image.copyTo(frame(cv::Rect(label->width()/2 - image.cols/2, label->height()/2 - image.rows/2,
                           image.cols, image.rows)));
    }
    else
    {
        float rw = float(image.cols) / float(label->width());
        float rh = float(image.rows) / float(label->height());

        if(rw > rh)
        {
            int width = label->width();
            int height = cvRound(image.rows / rw);

            cv::Mat tempImg;
            cv::resize(image, tempImg, cv::Size(width, height));

            tempImg.copyTo(frame(cv::Rect(0, label->height()/2 - tempImg.rows/2, width, height)));
        }
        else
        {
            int height = label->height();
            int width = cvRound(image.cols / rh);

            cv::Mat tempImg;
            cv::resize(image, tempImg, cv::Size(width, height));

            tempImg.copyTo(frame(cv::Rect(label->width()/2 - tempImg.cols/2, 0, width, height)));
        }
    }

    return frame;
}
