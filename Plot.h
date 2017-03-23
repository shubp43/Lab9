#if !defined (PLOT_H)
#define PLOT_H

#include "Points.h"
#include "Drawable.h"
#include "ListArray.h"
using CSC2110::ListArray;


class Plot : public Drawable
{
   private:
      ListArray<Points>* data;

   public:
      Plot();
      virtual ~Plot();

      void addPoints(Points* points);
      virtual void draw(wxDC& dc, int width, int height);
      virtual void mouseClicked(int x, int y);
};

#endif
