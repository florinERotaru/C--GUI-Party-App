#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>


wxIMPLEMENT_APP(App);

bool App::OnInit()
{ 
	MainFrame* mainFrame = new MainFrame("C++ GUI - v1.1");
	//mainFrame->SetClientSize(800, 600);
	mainFrame->SetMinClientSize(wxSize(800, 600));
	mainFrame->Center();
	mainFrame->Show();
	return true;
}

//Finished on Septmeber 28th, 2022, 11.08 pm.