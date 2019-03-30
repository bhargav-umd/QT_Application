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
 * @file samppoints.cpp
 * @brief  Sample points handling data structure
 * @author Bhargav Dandamudi
 * @version 1
 * @date 2019-03-30
 */
#include "samppoints.h"

samppoints::samppoints() {
  n = 0;
  X = new double[n];
  Y = new double[n];
  for (int i = 0; i < n; i++) {
    X[i] = 0.;
    Y[i] = 0.;
  }
}

// Constructor with assignment of the field N
samppoints::samppoints(int N) {
  n = N;
  X = new double[n];
  Y = new double[n];

  for (int i = 0; i < n; i++) {
    X[i] = 0.;
    Y[i] = 0.;
  }
}

// Constructor with assignment of each field
samppoints::samppoints(int N, double samppointsX[], double samppointsY[]) {
  n = N;
  X = new double[n];
  Y = new double[n];

  for (int i = 0; i < n; i++) {
    X[i] = samppointsX[i];
    Y[i] = samppointsY[i];
  }
}

// function that computes the x- and y- sample means (the coordinates of the
// centeroid)

void samppoints::means(void) {
  meanX = 0.;
  meanY = 0.;

  for (int i = 0; i < n; i++) {
    meanX += X[i];
    meanY += Y[i];
  }
  meanX /= n;
  meanY /= n;
}

// function that centers the samppoints set (shifts the coordinates to the
// centeroid)

void samppoints::center(void) {
  double sX = 0., sY = 0.;
  int i;

  for (i = 0; i < n; i++) {
    sX += X[i];
    sY += Y[i];
  }
  sX /= n;
  sY /= n;

  for (i = 0; i < n; i++) {
    X[i] -= sX;
    Y[i] -= sY;
  }
  meanX = 0.;
  meanY = 0.;
}

// function that scales the coordinates (makes them of order one)

void samppoints::scale(void) {
  double sXX = 0., sYY = 0., scaling;
  int i;

  for (i = 0; i < n; i++) {
    sXX += X[i] * X[i];
    sYY += Y[i] * Y[i];
  }
  scaling = std::sqrt((sXX + sYY) / n / 2.0);

  for (i = 0; i < n; i++) {
    X[i] /= scaling;
    Y[i] /= scaling;
  }
}

// Printing function

void samppoints::print(void) {
  std::cout << std::endl
            << "The samppoints set has " << n
            << " points with coordinates :" << std::endl;

  for (int i = 0; i < n - 1; i++)
    std::cout << std::setprecision(7) << "(" << X[i] << "," << Y[i] << "), ";

  std::cout << "(" << X[n - 1] << "," << Y[n - 1] << ")\n";
}

// Destructor
// samppoints::~samppoints()
//{
//    delete[] X;
//    delete[] Y;
//}
//
//
// TODO: NEED TO DEBUG THE CRASH AFER GENERATING CIRCLE
