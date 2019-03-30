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
 * @file samppoints.h
 * @brief  Data structure containing all the points with parameters
 *          stored for calculations
 * @author Bhargav Dandamudi
 * @version 1
 * @date 2019-03-30
 */
#ifndef SAMPPOINTS_H
#define SAMPPOINTS_H
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>

class samppoints {
public:
  int n;
  double *X; // dynamic array ,space is allocated in the constructors
  double *Y; // dynamic array space is allocated in the constructors
  double meanX, meanY;

  // constructors for the data class
  samppoints();
  samppoints(int N);
  samppoints(int N, double X[], double Y[]);

  // parameter calculation
  void means(void);
  void center(void);
  void scale(void);
  void print(void);

  // destructors
  // ~samppoints();
};

#endif // SAMPPOINTS_H
