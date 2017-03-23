#include "wx/wx.h"
#include "wx/sizer.h"

#include "SortGUI.h"
#include "Sort.h"

#include <iostream>
using namespace std;

#include <windows.h>
class SortApp: public wxApp
{
	public:
		bool OnInit();
};

IMPLEMENT_APP(SortApp)
 
bool SortApp::OnInit()
{
   	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	Plot* plot = new Plot();
    SortGUI* sort_frame = new SortGUI(640, 520, 8000, 100, plot);
 
 	DrawPanel* sort_display_panel = new DrawPanel(sort_frame, plot);
	sort_frame->setDrawPanel(sort_display_panel);
	
	wxButton* sort_button = new wxButton(sort_frame, wxID_HIGHEST + 1, wxT("Sort!"), wxPoint(25,375), wxSize(100, 25), 0);
	sort_button->SetBackgroundColour(*wxWHITE);
	
    sizer->Add(sort_display_panel, 9, wxEXPAND);
	sizer->Add(sort_button, 1, wxEXPAND);
 
    sort_frame->SetSizer(sizer);
    sort_frame->SetAutoLayout(true);
 
    sort_frame->Show();
    return true;
} 
