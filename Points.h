#if !defined (POINTS_H)
#define POINTS_H

#include "Point.h"
#include "ListArray.h"
using CSC2110::ListArray;

class Points
{

   private:
      ListArray<Point>* points;
      Color* color;
      int radius;
      double x_max_data;  //plot dimensions in data coordinates
      double y_max_data;

   public:
      Points(Color* color, int radius, double x_max, double y_max);
      virtual ~Points();
      void addPoint(Point* p);
      virtual void draw(wxDC& dc, int width, int height);
      virtual void mouseClicked(int x, int y);

};

#endif
