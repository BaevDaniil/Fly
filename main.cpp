#include <vector>
#include "geom_vector.h"
#include "track.h"
#include "labengine.h"

constexpr double TRACK_LENGTH = 1200;
constexpr double MIN_RADIUS = 1;
constexpr double MAX_RADIUS = 16;
constexpr double ACCELERATION = 0.01;
constexpr double MAX_V = 0.2;

using gv::geom_vector_t;
using tr::track_t;

int main() {
  geom_vector_t v, delta;
  int width, height;

  labparams_t params;
  params.height = 580;
  params.width = 1024;
  params.scale = 1;
  if (LabInitWith(&params)) {
    height = LabGetHeight();
    width = LabGetWidth();
    geom_vector_t point(width / 2, height / 2);
    geom_vector_t deltaV;
    std::vector<track_t> track;
    int sym;

    while (true) {
      sym = 0;

      if (LabInputKeyReady())
        sym = LabInputKey();

      LabClear();

      // handle pressing
      switch (sym) {
      case LABKEY_UP:
        deltaV = geom_vector_t(0, -ACCELERATION);
        break;
      case LABKEY_DOWN:
        deltaV = geom_vector_t(0, ACCELERATION);
        break;
      case LABKEY_LEFT:
        deltaV = geom_vector_t(-ACCELERATION, 0);
        break;
      case LABKEY_RIGHT:
        deltaV = geom_vector_t(ACCELERATION, 0);
        break;
      case ' ':
        deltaV = geom_vector_t(0, 0);
        v = geom_vector_t(0, 0);
        break;
      case LABKEY_ESC:
        LabTerm();
        exit(0);
        break;
      default:
        deltaV = geom_vector_t(-ACCELERATION * 0.001 * (v.x > 0 ? 1 : -1), -ACCELERATION * 0.001 * (v.y > 0 ? 1 : -1));
        break;
      }
      v += deltaV;
      if (v.Len() < 1e-3)
        v = geom_vector_t(0, 0);
      if ((v + deltaV).Len() > MAX_V) {
        v += deltaV;
        v = v / v.Len() * MAX_V;
      }
      else {
        v += deltaV;
      }
      // add trace element
      if (v.Len() != 0 && (delta.Len() / v.Len()) >= 20) {
        track.push_back(track_t(point, 1, 255));
        delta = geom_vector_t(0, 0);
      }

      point += v;
      delta += v;
      // handle going abroad
      if (point.x > width)
        v.x = -v.x;
        //point.x -= width;
      else if (point.x < 0)
        v.x = -v.x;
        //point.x += width;
      if (point.y > height)
        v.y = -v.y;
        //point.y -= height;
      else if (point.y < 0)
        v.y = -v.y;
        //point.y += height;

      LabSetColor(LABCOLOR_DARK_RED);
      LabDrawCircle(static_cast<int>(point.x), static_cast<int>(point.y), 2);
      // remove trace element
      if (!track.empty() && track.front().r >= MAX_RADIUS)
        track.erase(track.begin());
      //display the current picture
      double deltaR = (MAX_RADIUS - MIN_RADIUS) / TRACK_LENGTH;
      double deltaC = -255 / TRACK_LENGTH;
      for (auto& t : track) {
        LabSetColorRGB(0, 0, static_cast<int>(t.color));
        LabDrawCircle(static_cast<int>(t.coord.x), static_cast<int>(t.coord.y), static_cast<int>(t.r));
        t.rIncrease(deltaR);
        t.colorIncrease(deltaC);
      }
      LabDrawFlush();

    }
  }

  return 0;
}