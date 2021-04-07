#ifndef __TRACK_H_INCLUDED
#define __TRACK_H_INCLUDED
#pragma once

#include "geom_vector.h"

namespace tr {
  class track_t {
  public:
    gv::geom_vector_t coord;
    double r;
    double color;

    //constructor
    track_t(gv::geom_vector_t coord0 = (0, 0), double r0 = 0, double color0 = 0) {
      coord = coord0;
      r = r0;
      color = color0;
    }

    //copy constructor
    track_t(const track_t& t) {
      coord = t.coord;
      r = t.r;
      color = t.color;
    }

    // = operator function
    track_t& operator=(const track_t& t) {
      coord = t.coord;
      r = t.r;
      color = t.color;

      return *this;
    }

    // += operator function
    track_t& operator+=(const track_t& t) {
      coord += t.coord;
      r += t.r;
      color += t.color;

      return *this;
    }

    //increase value "r"
    track_t& rIncrease(double delta) {
      r += delta;

      return *this;
    }

    //increase value "color"
    track_t& colorIncrease(double delta) {
      color += delta;
      color = color < 0 ? 0 : color;
      color = color > 255 ? 255 : color;

      return *this;
    }
  };
}

#endif //__TRACK_H_INCLUDED