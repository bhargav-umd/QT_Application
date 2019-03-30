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
 * @file part2.cpp
 * @brief
 * @author Bhargav Dandamudi
 * @version 1
 * @date 2019-03-30
 */
#include "part2.h"
#include "circle.h"
#include "samppoints.h"
#include "ui_part2.h"
/* ----------------------------------------------------------------*/
/**
 * @brief  Default constructor
 *
 * @param parent
 */
/* ----------------------------------------------------------------*/
Part2::Part2(QWidget *parent) : QMainWindow(parent), ui(new Ui::Part2) {
  ui->setupUi(this);
  this->setFixedSize(430, 520);
  this->setMouseTracking(true);
}

/* ----------------------------------------------------------------*/
/**
 * @brief  Default Destructor
 */
/* ----------------------------------------------------------------*/
Part2::~Part2() { delete ui; }

/* ----------------------------------------------------------------*/
/**
 * @brief  To draw the blocks on window and changing color of the block
 *          based upon the intersection, refreshes every instance
 *
 * @param event
 */
/* ----------------------------------------------------------------*/
void Part2::paintEvent(QPaintEvent *event) {
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
void Part2::resizeEvent(QResizeEvent *event) {
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
 * @brief  Capture mouse click events and store position of blocks selected
 *          by user
 *
 * @param event
 */
/* ----------------------------------------------------------------*/
void Part2::mousePressEvent(QMouseEvent *event) {
  if (are_all_points_selected == false) {
    QPainter painter{&pix_map};
    is_mouse_clicked = true;
    mouse_position = event->pos();
    center_x = mouse_position.x();
    center_y = mouse_position.y();
  }
}
/* ----------------------------------------------------------------*/
/**
 * @brief  whenever mouse is clicked, to select more points.
 *         Changes color to blue of selected blocks and changes color
 *         to gray if unselected.
 *
 * @param event
 */
/* ----------------------------------------------------------------*/
void Part2::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event);
  if (are_all_points_selected == false) {
    QPainter painter{&pix_map};
    painter.setRenderHint(QPainter::Antialiasing);

    int map_x_location = 10;
    int map_y_location = 10;

    // Iterating over all the blocks on map

    for (int i = 0; i < 20; ++i) {
      for (int j = 0; j < 20; ++j) {
        QRect block_rect(map_x_location, map_y_location, block_width,
                         block_height);

        // creating brush and pen to fill later depeding on selected
        // points
        QPen framepen;
        QBrush brush;
        bool result = block_rect.contains(center_x, center_y);
        if (result == true) {
          map_color[i][j] = !map_color[i][j];
        }

        bool myColor = map_color[i][j];
        if (myColor == false) {
          framepen.setColor("gray");
          brush.setColor("gray");
        } else {
          framepen.setColor("blue");
          brush.setColor("blue");
        }

        // fill colors based on selections
        brush.setStyle(Qt::SolidPattern);
        painter.fillRect(block_rect, brush);
        painter.setPen(framepen);
        painter.drawRect(block_rect);

        // iterate over all columns
        map_y_location = map_y_location + gap;
      }

      // updating rows and reseting column (i.e, map_y_location)
      map_x_location = map_x_location + gap;
      map_y_location = 10;
    }
    painter.fillRect(pix_map.rect(), Qt::white);
  }

  update();
}

/* ----------------------------------------------------------------*/
/**
 * @brief  To return circle radius and center based on calculations
 *
 * @param  samplepoints as selected by user
 *
 * @return vector containing center x y coordinates and radius
 */
/* ----------------------------------------------------------------*/
std::vector<double> Part2::CircleFitByKasa(samppoints &samppoints)
/*
      Circle fit to a given set of samppoints points (in 2D)

      This is an algebraic fit, disovered and rediscovered by many people.
      One of the earliest publications is due to Kasa:

      I. Kasa, "A curve fitting procedure and its error analysis",
      IEEE Trans. Inst. Meas., Vol. 25, pages 8-14, (1976)

      Input:  samppoints     - the class of samppoints (contains the given
   points):

          samppoints.n   - the number of samppoints points
          samppoints.X[] - the array of X-coordinates
          samppoints.Y[] - the array of Y-coordinates

     Output:
               circle - parameters of the fitting circle:

           circle[0] - the X-coordinate of the center of the fitting circle
           circle[1] - the Y-coordinate of the center of the fitting circle
           circle[2] - the radius of the fitting circle

     The method is based on the minimization of the function

                 F = sum [(x-a)^2 + (y-b)^2 - R^2]^2

*/
{
  int i;

  double Xi, Yi, Zi;
  double Mxy, Mxx, Myy, Mxz, Myz;
  double B, C, G11, G12, G22, D1, D2;

  circle circle;
  qDebug() << "circle.a" << circle.a;

  samppoints.means(); // Compute x- and y- sample means (via a function in
                      // the class "samppoints")

  //     computing moments

  Mxx = Myy = Mxy = Mxz = Myz = 0.;

  for (i = 0; i < samppoints.n; i++) {
    Xi = samppoints.X[i] - samppoints.meanX; //  centered x-coordinates
    Yi = samppoints.Y[i] - samppoints.meanY; //  centered y-coordinates
    Zi = Xi * Xi + Yi * Yi;

    Mxx += Xi * Xi;
    Myy += Yi * Yi;
    Mxy += Xi * Yi;
    Mxz += Xi * Zi;
    Myz += Yi * Zi;
  }

  Mxx /= samppoints.n;
  Myy /= samppoints.n;
  Mxy /= samppoints.n;
  Mxz /= samppoints.n;
  Myz /= samppoints.n;

  // solving system of equations by Cholesky factorization
  // Refer Paper for more clear idea

  G11 = sqrt(Mxx);
  G12 = Mxy / G11;
  G22 = sqrt(Myy - G12 * G12);

  D1 = Mxz / G11;
  D2 = (Myz - D1 * G12) / G22;
  //    computing paramters of the fitting circle

  C = D2 / G22 / 2.0;
  B = (D1 - G12 * C) / G11 / 2.0;

  // assembling the output

  circle.a = B + samppoints.meanX;
  circle.b = C + samppoints.meanY;
  circle.r = sqrt(B * B + C * C + Mxx + Myy);

  std::vector<double> circle_data;
  circle_data.push_back(circle.a);
  circle_data.push_back(circle.b);
  circle_data.push_back(circle.r);
  return circle_data;
}

/* ----------------------------------------------------------------*/
/**
 * @brief  Generate Ellipse from the points when 1st push button is clicked
 */
// USING OPENCV ONLY FOR ELLIPSE !!!!!!!!!!!!!!!!!!!!!
/* ----------------------------------------------------------------*/
void Part2::on_pushButton1_clicked() {
  QPainter painter(&pix_map);
  painter.setRenderHint(QPainter::Antialiasing);

  // std::vector<std::vector<double>> sample_points;
  std::vector<cv::Point> sample_points;
  are_all_points_selected = true;
  int map_x_location = 10;
  int map_y_location = 10;

  // iterating over all the blocks
  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < 20; ++j) {
      if (map_color[i][j] == true) {
        cv::Point pt_;
        pt_.x = (map_x_location + (block_width / 2));
        pt_.y = (map_y_location + (block_height / 2));
        // storing all the selected points locations in a vector
        sample_points.push_back(pt_);
      }
      map_y_location = map_y_location + gap;
    }
    map_x_location = map_x_location + gap;
    map_y_location = 10;
  }
  // Using Opencv Library function to fit ellipse on selected points
  // limitation of selecting 5 points

  int size = int(sample_points.size());
  if (size >= 5) {
    cv::RotatedRect ellipse_rect = cv::fitEllipse(sample_points);
    cv::Point mid_point = ellipse_rect.center;
    int mid_x = mid_point.x;
    int mid_y = mid_point.y;
    int rect_width_ = int(ellipse_rect.size.width);
    int rect_height_ = int(ellipse_rect.size.height);

    // drawing ellipse found from the fitEllipse function
    QRect myRect(mid_x - rect_width_ / 2, mid_y - rect_height_ / 2, rect_width_,
                 rect_height_);
    //    qDebug() << "mid_x" << mid_x;
    //    qDebug() << "mid_y" << mid_y;

    painter.setPen({Qt::red, 1.2});
    painter.fillRect(pix_map.rect(), Qt::white);
    painter.drawEllipse(myRect);
  } else {
    qDebug() << "Need to select atleast 5 points, restart program to select";
  }
  update();
}

/* ----------------------------------------------------------------*/
/**
 * @brief  Circle generation when generate button is clicked
 */
/* ----------------------------------------------------------------*/
void Part2::on_pushButton_2_clicked() {
  // if (is_user_done = false){
  QPainter painter{&pix_map};
  painter.setRenderHint(QPainter::Antialiasing);

  // vector to store the selected points

  std::vector<double> midpoint;
  double radius;
  // bool ok;
  std::vector<cv::Point> circle_points;
  are_all_points_selected = true;
  int map_x_location = 10;
  int map_y_location = 10;

  // iterating  over all the blocks on map
  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < 20; ++j) {
      if (map_color[i][j] == true) {
        cv::Point pt_;
        pt_.x = (map_x_location + (block_width / 2));
        pt_.y = (map_y_location + (block_height / 2));
        // storing all the selected points locations in a vector
        circle_points.push_back(pt_);
      }
      map_y_location = map_y_location + gap;
    }
    map_x_location = map_x_location + gap;
    map_y_location = 10;
  }
  samppoints data;
  data.n = int(circle_points.size());

  // storing parameters to use the circle fit function
  for (std::vector<int>::size_type jj = 0; jj < circle_points.size(); jj++) {
    cv::Point cc = circle_points[jj];
    data.X[jj] = cc.x;
    data.Y[jj] = cc.y;
  }

  std::vector<double> circle_info = CircleFitByKasa(data);
  // qDebug() << circle_data.a << "x coordinate" ;

  radius = circle_info[2];

  // drawing circle based on circle parameters calculated above
  //
  QRect myRect(int(circle_info[0]) - int(radius), int(circle_info[1]) - int(radius),
               int(radius) * 2, int(radius) * 2);
  // drawing the resultant circle
  painter.setPen({Qt::red, 1.2});
  painter.fillRect(pix_map.rect(), Qt::white);
  painter.drawEllipse(myRect);
  update();
}
