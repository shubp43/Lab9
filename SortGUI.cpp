#include "SortGUI.h"
#include "Sort.h"
#include "Random.h"
using CSC2110::Random;
#include "HighPerformanceCounter.h"
using CSC2110::HighPerformanceCounter;

#include <iostream>
using namespace std;

#include <windows.h>

BEGIN_EVENT_TABLE (SortGUI, wxFrame)
	EVT_BUTTON (wxID_HIGHEST + 1, SortGUI::on_sort_button_click_event) 
END_EVENT_TABLE() 

DWORD WINAPI SortPlotThread(LPVOID* parameters)
{
   SortGUI* sort_plot = (SortGUI*) (parameters[0]);
   sort_plot->sortPlot();
}

void SortGUI::startSortPlotThread()
{
   //start a new thread to solve the maze
   LPVOID* params = new LPVOID[1];
   params[0] = this;
   CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) SortPlotThread, params, 0, NULL);
}

void SortGUI::setDrawPanel(DrawPanel* draw_panel)
{
   sort_draw_panel = draw_panel;
}

void SortGUI::sortPlot()
{
   //start, end, increment, sort method, color for points, radius
   //1 = mergesort (red), 2 = quicksort (blue)
   sort(1, n_max, increment, 1, new Color(1, 0, 0), 5); //merge
   //sort(1, (int) (n_max*1.0/2.0), increment, 2, new Color(0, 0, 1), 5); //quick
   sort(1, (int) (n_max*1.0/2.0), increment, 3, new Color(0, 1, 0), 5); //selection
   sort(1, n_max, increment, 4, new Color(1, 0, 1), 5); //insertion binary
   // sort(1, n_max, increment, 5, new Color(1, 1, 0), 5); //heap
}

SortGUI::SortGUI(int width, int height, int n, int incr, Plot* p) : wxFrame((wxFrame *)NULL, -1,  wxT("Sort Plot"), wxPoint(500,300), wxSize(width,height))
{
   n_max = n;
   increment = incr;
   plot = p;

   cds = randomCDs(n_max, 5);  
   sorted_cds = Sort<CD>::mergeSort(cds, n_max, &CD::compare_items);

   busy = false;
}

SortGUI::~SortGUI()
{
   for (int i = 0; i < n_max; i++)
   {
      CD* cd = cds[i];
      delete cd;
   }
   delete[] cds;
   delete[] sorted_cds;
   delete plot;
}

void SortGUI::on_sort_button_click_event(wxCommandEvent& evt)
{
   if (!busy)
   {
      busy = true;
      startSortPlotThread();
   }
}

void SortGUI::sort(int n_start, int n_end, int incr, int sortMethod, Color* color, int radius)
{
   HighPerformanceCounter* hpc = HighPerformanceCounter::getHighPerformanceCounter();
   Points* points = new Points(color, radius, n_max, 200000);  //last parameter is microseconds for max y
   plot->addPoints(points);

   for (int i = n_start; i <= n_end; i += incr)
   {
      int numToSort = i;

      int start_time = hpc->getCurrentTimeInTicks();
      sort(cds, numToSort, sortMethod);
      int end_time = hpc->getCurrentTimeInTicks();

      double micro = hpc->getTimeDifferenceInMicroSeconds(start_time, end_time);
      Point* p = new Point(numToSort, (int) micro);
      points->addPoint(p);

      Refresh();
   }
}

void SortGUI::sort(CD** cds, int num_to_sort, int sort_method)
{
   CD** sorted;
   if (sort_method == 1)
   {
      sorted = Sort<CD>::mergeSort(cds, num_to_sort, &CD::compare_items);
   }
   else if (sort_method == 2)
   {
      //note use of sorted_cds, the worst case for quick sort
      sorted = Sort<CD>::quickSort(sorted_cds, num_to_sort, &CD::compare_items);
   }
   else if (sort_method == 3)
   {
      sorted = Sort<CD>::selectionSort(cds, num_to_sort, &CD::compare_items);
   }
   else if (sort_method == 4)
   {
      sorted = Sort<CD>::insertionBinarySort(cds, num_to_sort, &CD::compare_items);
   }
   else if (sort_method == 5)
   {
      // sorted = Sort<CD>::heapSort(cds, num_to_sort, &CD::compare_items);
   }

   delete[] sorted;
}

CD** SortGUI::randomCDs(int num_to_create, int num_characters)
{
   Random* rand = new Random();
   CD** cds = new CD*[num_to_create];

   for (int i = 0; i < num_to_create; i++)
   {
      char* title_char = new char[num_characters + 1];
      for (int j = 0; j < num_characters; j++)
      {
         char the_char;

         int temp = rand->getRandomInt(0, 35);

         if (temp < 10)  //digit
         {
            the_char = (char) (temp + 48);
         }
         else  //lower case character
         {
            the_char = (char) (temp + 87);
         }
         title_char[j] = the_char;
      }

      title_char[num_characters] = 0;  //need a null terminator
      String* title = new String(title_char);
      delete[] title_char;
      String* artist = new String("ABCDE");
      cds[i] = new CD(artist, title, 2004, 9, 9);
   }
   return cds;
}
