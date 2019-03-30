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

bool Part2::solveLeastSquaresCircleKasa(
    const std::vector<Eigen::Vector2d,
                      Eigen::aligned_allocator<Eigen::Vector2d>> &points,
    Eigen::Vector2d &midpoint, double &radius) {
  // REFERENCE:
  // https://github.com/DLuensch/Least-Squares-Circle-Fitting-Kasa-Method-.git
  // was used.
  /* ---------------------------------------------------------------------------
 * Revision			: 1.0
 * Modul				: Least Square Circle Kasa C++
 * Creation			: 10.01.2015
 * Recent changes	: 10.01.2015
 * ----------------------------------------------------------------------------
 * LOG:
 * ----------------------------------------------------------------------------
 * Author			: Dennis Luensch
 * Contact			: dennis.luensch@gmail.com
 *    ALl Copyrights for this part reserved to respective owner
 */

  int length = int(points.size());
  double x1;
  double x2;
  double x3;
  Eigen::MatrixXd AFill(3, length);
  Eigen::MatrixXd A(length, 3);
  Eigen::VectorXd AFirst(length);
  Eigen::VectorXd ASec(length);
  Eigen::VectorXd AFirstSquared(length);
  Eigen::VectorXd ASecSquared(length);
  Eigen::VectorXd ASquaredRes(length);
  Eigen::VectorXd b(length);
  Eigen::VectorXd c(3);
  bool ok = true;

  if (length > 1) {
    for (int i = 0; i < length; i++) {
      AFill(0, i) = points[i](0);
      AFill(1, i) = points[i](1);
      AFill(2, i) = 1;
    }

    A = AFill.transpose();

    for (int i = 0; i < length; i++) {
      AFirst(i) = A(i, 0);
      ASec(i) = A(i, 1);
    }

    for (int i = 0; i < length; i++) {
      AFirstSquared(i) = AFirst(i) * AFirst(i);
      ASecSquared(i) = ASec(i) * ASec(i);
    }

    b = AFirstSquared + ASecSquared;

    c = A.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b);

    x1 = c(0);
    midpoint(0) = x1 * 0.5;
    x2 = c(1);
    midpoint(1) = x2 * 0.5;
    x3 = c(2);
    radius = sqrt((x1 * x1 + x2 * x2) / 4 + x3);
  } else {
    ok = false;
  }

  return ok;
}

/* ----------------------------------------------------------------*/
/**
 * @brief  Generate Ellipse from the points when 1st push button is clicked
 */
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

void Part2::on_pushButton_2_clicked() {
  // if (is_user_done = false){
  QPainter painter{&pix_map};
  painter.setRenderHint(QPainter::Antialiasing);

  // vector to store the selected points
  std::vector<Eigen::Vector2d, Eigen::aligned_allocator<Eigen::Vector2d>>
      samplePoints;
  // midpoint of the fitted circle
  Eigen::Vector2d midpoint;
  double radius;
  bool ok;

  are_all_points_selected = true;
  int map_x_location = 10;
  int map_y_location = 10;

  // iterating  over all the blocks on map
  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < 20; ++j) {
      if (map_color[i][j] == true) {
        samplePoints.push_back(
            Eigen::Vector2d((map_x_location + (block_width / 2)),
                            (map_y_location + (block_height / 2))));
      }
      map_y_location = map_y_location + gap;
    }
    map_x_location = map_x_location + gap;
    map_y_location = 10;
  }

  // Using Kasa Fitting Algorithm to fit circle
  ok = solveLeastSquaresCircleKasa(samplePoints, midpoint, radius);
  if (ok) {
    QRect myRect(int(midpoint(0)) - int(radius), int(midpoint(1)) - int(radius),
                 int(radius) * 2, int(radius) * 2);
    // drawing the resultant circle
    painter.setPen({Qt::red, 1.2});
    painter.fillRect(pix_map.rect(), Qt::white);
    painter.drawEllipse(myRect);
    update();
  } else {
    qDebug() << "Not able to fit circle using Kasa algorithm, restart to "
                "select points ";
  }
}
