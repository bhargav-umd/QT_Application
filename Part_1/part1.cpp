/* Copyright (C)
 * 2019 - Bhargav Dandamudi
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the 'Software'), to deal in the Software without
 * restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so,subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED ''AS IS'', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM,OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
/**
 * @file part1.cpp
 * @brief  Definition of all the functions in part1 class
 * @author Bhargav Dandamudi
 * @version 1
 * @date 2019-03-29
 */
#include "part1.h"
#include "ui_part1.h"

/* ----------------------------------------------------------------*/
/**
 * @brief  Default constructor to fix size of the window
 *
 * @param parent
 */
/* ----------------------------------------------------------------*/
part1::part1(QWidget *parent) : QMainWindow(parent), ui(new Ui::part1) {
  ui->setupUi(this);
  this->setFixedSize(430, 500);
  this->setMouseTracking(true);
}

/* ----------------------------------------------------------------*/
/**
 * @brief  Default Destructor
 */
/* ----------------------------------------------------------------*/
part1::~part1() { delete ui; }

/* ----------------------------------------------------------------*/
/**
 * @brief  To draw the blocks on window and changing color of the block
 *          based upon the intersection, refereshes every instance
 *
 * @param event
 */
/* ----------------------------------------------------------------*/
void part1::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.drawPixmap(0, 0, pix_map);
  int map_x_location = 10;
  int map_y_location = 10;

  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < 20; ++j) {
      QRect block_rect(map_x_location, map_y_location, block_width,
                       block_height);

      // To change color from gray to blue if the path intesects any
      // blocks
      if (map_color[i][j] == false) {
        // make pen and brush to fill colors
        QPen framepen(Qt::gray);
        QBrush brush(Qt::gray, Qt::SolidPattern);
        painter.fillRect(block_rect, brush);
        painter.setPen(framepen);
      } else {
        // make pen and brush to fill colors
        QPen framepen(Qt::blue);
        QBrush brush(Qt::blue, Qt::SolidPattern);
        painter.fillRect(block_rect, brush);
        painter.setPen(framepen);
      }
      // draw respective color block
      painter.drawRect(block_rect);
      map_y_location = map_y_location + gap; // updating y to move in coloumns
    }
    // moving in x direction for all rows
    map_x_location = map_x_location + gap;
    // resetting y to start next row
    map_y_location = 10;
  }
}

/* ----------------------------------------------------------------*/
/**
 * @brief  The widget will be erased and receive a paint event immediately after
 * processing the resize event
 *
 * @param event
 */
/* ----------------------------------------------------------------*/
void part1::resizeEvent(QResizeEvent *event) {
  Q_UNUSED(event);
  auto newRect = pix_map.rect().united(rect());
  if (newRect == pix_map.rect())
    return;
  QPixmap newPixmap{newRect.size()};
  QPainter painter{&newPixmap};
  painter.fillRect(newPixmap.rect(), Qt::white);
  painter.drawPixmap(0, 0, pix_map);
  pix_map = newPixmap;
}

/* ----------------------------------------------------------------*/
/**
 * @brief  Capture mouse click events and store center of main circle
 *
 * @param event
 */
/* ----------------------------------------------------------------*/
void part1::mousePressEvent(QMouseEvent *event) {
  if (is_circle_drawn == false) {
    QPainter painter{&pix_map};
    is_mouse_clicked = true;
    mouse_position = event->pos();
    center_x = mouse_position.x();
    center_y = mouse_position.y();
  }
}
/* ----------------------------------------------------------------*/
/**
 * @brief show/draw circles as mouse is moved while updating radius
 *
 * @param event
 */
/* ----------------------------------------------------------------*/
void part1::mouseMoveEvent(QMouseEvent *event) {
  if (is_mouse_clicked == true && is_circle_drawn == false) {
    QPainter painter{&pix_map};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen({Qt::blue, 1.0});
    mouse_position = event->pos();
    int tempW = int(qFabs(mouse_position.x() - center_x));
    int tempH = int(qFabs(mouse_position.y() - center_y));
    if (tempW > tempH) {
      width = tempW;
      height = tempW;
    } else {
      width = tempH;
      height = tempH;
    }

    radius = width / 2;
    QRect myRect(center_x - (width / 2), center_y - (height / 2), width,
                 height);

    painter.fillRect(pix_map.rect(), Qt::white);
    // painter.drawRect(myRect);
    painter.drawEllipse(myRect);
    update();
  }
}

/* ----------------------------------------------------------------*/
/**
 * @brief  As soon as mouse is released
 *          1. we use path to see which grids the circle intersects
 *          2. change color of those grids as in PaintEvent
 *          3. FInd the radius of large and small circle
 *          4. set the color of the circles
 *
 * @param event
 */
/* ----------------------------------------------------------------*/
void part1::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event);
  is_mouse_clicked = false;
  is_circle_drawn = true;
  QPainter painter{&pix_map};
  painter.setRenderHint(QPainter::Antialiasing);

  QRect myRect(center_x - (width / 2), center_y - (height / 2), width, height);
  int helpW = width - 1;
  int helpH = height - 1;
  QRect rect_temp(center_x - (helpW / 2), center_y - (helpH / 2), helpW, helpH);

  // making path of both the ellipse enclosing main circle
  QPainterPath path;
  path.addEllipse(myRect);
  path.addEllipse(rect_temp);
  QBrush fullbrush;
  fullbrush.setColor(Qt::yellow);
  painter.fillPath(path, fullbrush);

  int map_x_location = 10;
  int map_y_location = 10;
  int r_large = 0;   // initialising radius of large circle
  int r_small = 200; // initialising radius of the small circle
  int rtempsmall;    // temporarily storing small radius value
  int rtemplarge;    // temporarily storing large radius value

  qDebug() << "radius of the main circle: " << radius;

  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < 20; ++j) {
      QRect block_rect(map_x_location, map_y_location, block_width,
                       block_height);

      // storing intersection result
      bool result = path.intersects(block_rect);
      map_color[i][j] = result;
      // changing color based on result

      if (result == false) {
        QPen framepen(Qt::gray);
        QBrush brush(Qt::gray, Qt::SolidPattern);
        painter.fillRect(block_rect, brush);
        painter.setPen(framepen);
      } else {
        QPen framepen(Qt::blue);
        QBrush brush(Qt::blue, Qt::SolidPattern);
        painter.fillRect(block_rect, brush);
        painter.setPen(framepen);

        // storing the large/small radius based on location of grid
        rtemplarge =
            int(qSqrt(qPow(map_x_location + block_width - center_x, 2) +
                      qPow(map_y_location + block_height - center_y, 2)));
        rtempsmall = int(qSqrt(qPow(map_x_location - center_x, 2) +
                               qPow(map_y_location - center_y, 2)));

        /*  qDebug() << rtempsmall << ":rtempsmall"; */
        // qDebug() << rtemplarge << ":rtemplarge";
        // qDebug() << r_small << ":r_small";
        // qDebug() << r_large << ":rlarge";
        /* qDebug() << "##################"; */

        // finding maximum and minimum radius based on calculations
        // above
        if (rtemplarge > r_large) {
          r_large = rtemplarge;
        }
        if (rtempsmall < r_small) {
          r_small = rtempsmall;
        }
      }

      // going over all the columns in the same row
      painter.drawRect(block_rect);
      map_y_location = map_y_location + gap;
    }
    // updating rows and reseting column (i.e, map_y_location)
    map_x_location = map_x_location + gap;
    map_y_location = 10;
  }

  painter.setPen({Qt::red, 1.2});
  int maxW = 2 * r_large;
  int maxH = 2 * r_large;
  // drawing larger/outer circle
  QRect maxRect(center_x - (maxW / 2), center_y - (maxH / 2), maxW, maxH);
  painter.drawEllipse(maxRect);
  painter.setPen({Qt::red, 1.2});
  int minW = 2 * r_small;
  int minH = 2 * r_small;
  // drawing smaller/inner circle
  QRect minRect(center_x - (minW / 2), center_y - (minH / 2), minW, minH);
  painter.drawEllipse(minRect);

  update();
}
