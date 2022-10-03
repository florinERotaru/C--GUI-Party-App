#pragma once
#include <wx/wx.h>
class MainFrame : public wxFrame
{
public:

	wxScrolledWindow* panel = nullptr;
	wxStatusBar* status = nullptr;
	MainFrame(const wxString& title);
	void StartButtonClicked(wxCommandEvent& evt);
	void StartParty();
	void ChooseMode();
	void SimpleVersion(wxCommandEvent& evt);
	void ExtendedVersion(wxCommandEvent& evt);
	void ClearPanelAndSizer(wxPanel* panel);
	void BackPressed(wxCommandEvent& evt);
	void DeleteParticipant(wxCommandEvent& evt);
};

