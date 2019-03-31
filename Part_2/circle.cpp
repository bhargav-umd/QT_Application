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
 * @file circle.cpp
 * @brief  circle parameters to be calculated and initialised
 * @author Bhargav Dandamudi
 * @version 1
 * @date 2019-03-30
 */
#include "circle.h"

circle::circle() {
  a = 0.;
  b = 0.;
  r = 1.;

  /* a =x coordinate of circle center
   * b =y coordinate of circle center
   * c = radius;
  */
}

// Constructor with assignment of the circle parameters only

circle::circle(double aa, double bb, double rr) {
  this->a = aa;
  this->b = bb;
  this->r = rr;
}
