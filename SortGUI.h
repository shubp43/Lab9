#if !defined SORTGUI_H
#define SORTGUI_H

#include "Plot.h"
#include "DrawPanel.h"
#include "CD.h"
using CSC2110::CD;
#include "Color.h"

class SortGUI : public wxFrame
{
   private:
      Plot* plot;
      CD** cds;
      CD** sorted_cds;
      int n_max;
      int increment;
	  
	  DrawPanel* sort_draw_panel;

      CD** randomCDs(int numToCreate, int numCharacters);
      bool busy;

   public:
      SortGUI(int w, int h, int n, int incr, Plot* plot);
      virtual ~SortGUI();

      void sort(int n_start, int n_end, int incr, int sortMethod, Color* color, int radius);
      void sort(CD** items, int numToSort, int sortMethod);
      void on_sort_button_click_event(wxCommandEvent& evt);
      void startSortPlotThread();
      void sortPlot();
	  void setDrawPanel(DrawPanel* draw_panel);
	  
	  DECLARE_EVENT_TABLE()
};

#endif
 
