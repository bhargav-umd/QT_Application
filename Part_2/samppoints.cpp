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
  this->n = 0;
  for (std::vector<int>::size_type i = 0; int(i) < n; i++) {
    this->X[i] = 0.;
    this->Y[i] = 0.;
  }
}

// Constructor with assignment of the field N
samppoints::samppoints(int N) {
  this->n = N;

  for (std::vector<int>::size_type i = 0; int(i) < n; i++) {
    this->X[i] = 0.;
    this->Y[i] = 0.;
  }
}

// Constructor with assignment of each field
samppoints::samppoints(int N, std::vector<double> samppointsX, std::vector<double> samppointsY) {
  n = N;

  for (std::vector<int>::size_type i = 0; int(i) < n; i++) {
    this->X.push_back(samppointsX[i]);
    this->Y.push_back(samppointsY[i]);
  }
}

// function that computes the x- and y- sample means (the coordinates of the
// centeroid)

void samppoints::means(void) {
  this->meanX = 0.;
  this->meanY = 0.;

  for (std::vector<int>::size_type i = 0; int(i) < n; i++) {
    this->meanX += this->X[i];
    this->meanY += this->Y[i];
  }
  this->meanX /= n;
  this->meanY /= n;
}

// function that centers the samppoints set (shifts the coordinates to the
// centeroid)

void samppoints::center(void) {
  double sX = 0., sY = 0.;
  // int i;

  for (std::vector<int>::size_type i = 0; int(i) < n; i++) {
    sX += this->X[i];
    sY += this->Y[i];
  }
  sX /= n;
  sY /= n;

  for (std::vector<int>::size_type i = 0; int(i) < n; i++) {
    this->X[i] -= sX;
   this->Y[i] -= sY;
  }
  this->meanX = 0.;
  this->meanY = 0.;
}

// function that scales the coordinates (makes them of order one)

void samppoints::scale(void) {
  double sXX = 0., sYY = 0., scaling;
  // int i;

  for (std::vector<int>::size_type i = 0; int(i) < n; i++) {
    sXX += this->X[i] * this->X[i];
    sYY += this->Y[i] * this->Y[i];
  }
  scaling = std::sqrt((sXX + sYY) / n / 2.0);

  for (std::vector<int>::size_type i = 0; int(i) < n; i++) {
    this->X[i] /= scaling;
    this->Y[i] /= scaling;
  }
}

// Printing function

//void samppoints::print(void) {
//  std::cout << std::endl
//            << "The samppoints set has " << n
//            << " points with coordinates :" << std::endl;

//  for (std::vector<int>::size_type i = 0; int(i) < n - 1; i++)
//    std::cout << std::setprecision(7) << "(" << X[i] << "," << Y[i] << "), ";

//  std::cout << "(" << X[n - 1] << "," << Y[n - 1] << ")\n";
//}

// Destructor
 samppoints::~samppoints()
{
//    delete X;
//    delete Y;
}

//
// TODO: NEED TO DEBUG THE CRASH AFER GENERATING CIRCLE
