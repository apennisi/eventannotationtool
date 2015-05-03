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

#include "event.h"

Event::Event()
{
    abnormal = false;
}

Event::Event(const bool &_abnormal)
    : abnormal(_abnormal)
{

}

void Event::draw(QLabel *l)
{
    QPixmap myPix( QSize( l->width(), l->height()) );
    myPix.fill(QColor("transparent"));

    QPainter p(&myPix);
    (abnormal) ? p.setBrush(QBrush(Qt::red))
               : p.setBrush(QBrush(Qt::green));
    p.setRenderHint( QPainter::Antialiasing );
    p.drawEllipse(0, 0, l->width(), l->height());

    l->setPixmap(myPix);
}
