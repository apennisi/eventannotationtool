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


#include "qtcvtransform.h"
#include <dirent.h>
#include <iostream>
#include <vector>
#include <sstream>

QImage* Mat2QImage(const cv::Mat &img)
{
    int h = img.rows;
    int w = img.cols;
    QImage *qimg;

    int channels = img.channels();

    switch(channels) {
        case 1:
        case 3:
            qimg = new QImage(w, h, QImage::Format_RGB888);
            break;
        default:
            qimg = new QImage(w, h, QImage::Format_ARGB32);
    }

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            char r = 0, g = 0, b = 0;
            if(channels == 1) {
                r = (int)img.at<uchar>(i,j);
                g = (int)img.at<uchar>(i,j);
                b = (int)img.at<uchar>(i,j);
            } else if(channels == 3) {
                r = img.at<cv::Vec3b>(i,j)[2];
                g = img.at<cv::Vec3b>(i,j)[1];
                b = img.at<cv::Vec3b>(i,j)[0];
            }
            qimg->setPixel(j, i, qRgb(r, g, b));
        }
    }

    return qimg;
}


cv::Mat QImage2Mat(const QImage *qimg) {
    cv::Mat mat = cv::Mat(qimg->height(), qimg->width(), CV_8UC4, (uchar*)qimg->bits(), qimg->bytesPerLine());
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0,  1,1,  2,2 };
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );
    return mat2;
}
