#if !defined (POINT_H)
#define POINT_H

#include "Color.h"
#include "Circle.h"

class Point
{

   private:
      double x;
      double y;

   public:
     Point(double x, double y);
     virtual ~Point();
     double getX();
     double getY();
     void draw(wxDC& dc, Color* color, int radius, int width, int height, double x_max, double y_max);
};

#endif
