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
 * @file part1.h
 * @brief  Header file for the application with all declarations/signatures
 * @author Bhargav Dandamudi
 * @version 1
 * @date 2019-03-29
 */
#ifndef PART1_H
#define PART1_H

#include <QApplication>
#include <QDebug>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QRubberBand>
#include <QTimer>
#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QtMath>

namespace Ui {
class part1;
}

/* ----------------------------------------------------------------*/
/**
 * @brief  Class for part 1 solution to draw circles around the grids
 */
/* ----------------------------------------------------------------*/
class part1 : public QMainWindow {
  Q_OBJECT

public:
  explicit part1(QWidget *parent = nullptr);
  ~part1() Q_DECL_OVERRIDE;

private:
  Ui::part1 *ui;

protected:
  /* ----------------------------------------------------------------*/
  /**
   * @brief  generates 20x20 blocks in a window
   *
   * @param event
   */
  /* ----------------------------------------------------------------*/
  virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

  /* ----------------------------------------------------------------*/
  /**
   * @brief widget will be erased and receive a paint event immediately after
   * processing the resize event
   *
   * @param event
   */
  /* ----------------------------------------------------------------*/
  virtual void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
  /* ----------------------------------------------------------------*/
  /**
   * @brief Overiding default function of clicking mouse left button
   *
   * @param event
   */
  /* ----------------------------------------------------------------*/
  virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  /* ----------------------------------------------------------------*/
  /**
   * @brief  To show circle of dyanamic radius as mouse is moving
   *
   * @param event
   */
  /* ----------------------------------------------------------------*/
  virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  /* ----------------------------------------------------------------*/
  /**
   * @brief  To draw additional circles corresponding to largest and smallest
   *        radius of the highlighted points
   *
   * @param event
   */
  /* ----------------------------------------------------------------*/
  virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

  int width, height;     // dimensions of Qrectangle to create respective circle
  int block_width = 10;  // individual small blocks width to make given pattern
  int block_height = 10; // individual small blocks height to make given pattern
  int gap = 20;          // gap between blocks

  bool is_mouse_clicked = false; // flag to check mouse click
  bool is_circle_drawn = false;  // flag to check if circle is drawn by user
  bool map_color[20][20] = {{false}}; // false means not intersecting
  QPoint mouse_position;              //(x, y)coordinate of mouse location
  QPixmap pix_map;                    // map to draw required circles
  int center_x, center_y, radius; // coordinates for circle's center and radius
};

#endif // PART1_H
