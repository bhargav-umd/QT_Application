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
 * @file circle.h
 * @brief  Circle data structure containing its properties as in 39-43 line
 * @author Bhargav Dandamudi
 * @version 1
 * @date 2019-03-30
 */
#ifndef CIRCLE_H
#define CIRCLE_H

class circle {
public:
  //    circle.a - the X-coordinate of the center of the fitting circle
  //    circle.b - the Y-coordinate of the center of the fitting circle
  //    circle.r - the radius of the fitting circle
  //    circle.s - the root mean square error (the estimate of sigma)
  //    circle.j - the total number of iterations

  double a, b, r, s, g, Gx, Gy;
  int i, j;

  // constructors
  circle();
  circle(double aa, double bb, double rr);

  // routines
  void print(void);
};

#endif // CIRCLE_H
