#ifndef __GEOM_VECTOR_H_INCLUDED
#define __GEOM_VECTOR_H_INCLUDED
#pragma once

#include <cmath>

namespace gv {
  class geom_vector_t {
  public:
    double x; //coordinate x
    double y; //coordinate y

    //constructor
    geom_vector_t(double x0 = 0, double y0 = 0) {
      x = x0;
      y = y0;
    }

    //copy constructor
    geom_vector_t(const geom_vector_t& v) {
      x = v.x;
      y = v.y;
    }

    // = operator function
    geom_vector_t& operator=(const geom_vector_t& v) {
      x = v.x;
      y = v.y;

      return *this;
    }

    // + operator function
    geom_vector_t operator+(const geom_vector_t& v) const {
      return geom_vector_t(x + v.x, y + v.y);
    }

    // += operator function
    geom_vector_t& operator+=(const geom_vector_t& v) {
      x += v.x;
      y += v.y;

      return *this;
    }

    // - operator function
    geom_vector_t operator-(const geom_vector_t& v) const {
      return geom_vector_t(x - v.x, y - v.y);
    }

    // -= operator function
    geom_vector_t& operator-=(const geom_vector_t& v) {
      x -= v.x;
      y -= v.y;

      return *this;
    }

    // * operator function
    geom_vector_t operator*(double a) const {
      return geom_vector_t(x * a, y * a);
    }

    // *= operator function
    geom_vector_t& operator*=(double a) {
      x *= a;
      y *= a;

      return *this;
    }

    // / operator function
    geom_vector_t operator/(double a) const {
      return geom_vector_t(x / a, y / a);
    }

    // /= operator function
    geom_vector_t& operator/=(double a) {
      x /= a;
      y /= a;

      return *this;
    }

    //length of vector function
    double Len(void) const {
      return sqrt(x * x + y * y);
    }
  };
}

#endif //__GEOM_VECTOR_H_INCLUDED