#include "MainFrame.h"
#include "Participant.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <functional>
#include <wx/statline.h>
#include "PartySimple.h"
#include "PartyExtended.h"
#include <wx/grid.h>
#include <initializer_list>
MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	Center();
	Layout();
	panel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS| wxVSCROLL );
	auto Navigate = [](wxKeyEvent& evt)
	{
		if (evt.GetKeyCode() == 13)
		{
			wxPanel* window = (wxPanel*)evt.GetEventObject();
			window->Navigate();
		}
		else
			evt.Skip();
	};

	panel->Bind(wxEVT_CHAR_HOOK, Navigate);
	status = CreateStatusBar();
	status->PushStatusText("© 2022 - App Developed by Florin Rotaru");
	StartParty();

}
void MainFrame::StartButtonClicked(wxCommandEvent& evt)
{
	ClearPanelAndSizer(panel);
	ChooseMode();
}

void MainFrame::StartParty()
{
	wxButton* start_button = new wxButton(panel, wxID_ANY, "Start the Party!", wxDefaultPosition, wxSize(200, 70));
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->AddStretchSpacer(1);
	sizer->Add(
		start_button,
		0,
		wxALL | wxALIGN_CENTER,
		0);
	sizer->AddStretchSpacer(1);
	panel->SetSizerAndFit(sizer);
	start_button->Bind(wxEVT_BUTTON, &MainFrame::StartButtonClicked, this);

}

void MainFrame::ChooseMode()
{
	status->PushStatusText(_T("Mode Selection..."));
	wxButton* simple = new wxButton(panel, wxID_ANY, _T("Simple Mode"), wxDefaultPosition, wxSize(200, 70));
	wxButton* extended = new wxButton(panel, wxID_ANY, _T("Extended Mode"), wxDefaultPosition, wxSize(200, 70));
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->AddStretchSpacer(1);

	sizer->Add(
		simple,
		0,
		wxALL | wxALIGN_CENTER,
		5);

	sizer->Add(
		extended,
		0,
		wxALL | wxALIGN_CENTER,
		5);
	sizer->AddStretchSpacer(1);
	panel->SetSizer(sizer);
	panel->Layout();
	simple->Bind(wxEVT_BUTTON, &MainFrame::SimpleVersion, this);
	extended->Bind(wxEVT_BUTTON, &MainFrame::ExtendedVersion, this);
}

void MainFrame::SimpleVersion(wxCommandEvent& evt)
{
	ClearPanelAndSizer(panel);
	//left controls
	wxStaticBox* box = new wxStaticBox(panel, wxID_ANY, _T("Party Info"), wxDefaultPosition, wxSize(300, 300));
	wxStaticText* participants = new wxStaticText(box, wxID_ANY, _T("Number of Participants(total):"));
	wxSpinCtrl* input_participants = new wxSpinCtrl(box, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS| wxTE_PROCESS_ENTER, 0, 300);
	wxStaticText* nondrinkers = new wxStaticText(box, wxID_ANY, _T("Number of Non Drinkers:"));
	wxSpinCtrl* input_nondrinkers = new wxSpinCtrl(box, wxID_ANY, _T("0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 300);
	wxStaticText* expenses = new wxStaticText(box, wxID_ANY, _T("Total Expenses:"));
	wxSpinCtrlDouble* input_expenses = new wxSpinCtrlDouble(box, wxID_ANY, _T("0.0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 5000);
	wxStaticText* alcohol = new wxStaticText(box, wxID_ANY, _T("Alcohol Expenses:"));
	wxSpinCtrlDouble* input_alcohol = new wxSpinCtrlDouble(box, wxID_ANY, _T("0.0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 5000);
	//box sizer(left sizer):
	wxSizer* box_sizer = new wxBoxSizer(wxVERTICAL);
	box_sizer->AddStretchSpacer(1);
	box_sizer->Add(participants, 0, wxALL, 5);
	box_sizer->Add(input_participants, 0, wxALL | wxALIGN_CENTER, 5);
	box_sizer->AddStretchSpacer(1);
	box_sizer->Add(nondrinkers, 0, wxALL, 5);
	box_sizer->Add(input_nondrinkers, 0, wxALL | wxALIGN_CENTER, 5);
	box_sizer->AddStretchSpacer(1);
	box_sizer->Add(expenses, 0, wxALL, 5);
	box_sizer->Add(input_expenses, 0, wxALL | wxALIGN_CENTER, 5);
	box_sizer->AddStretchSpacer(1);
	box_sizer->Add(alcohol, 0, wxALL, 5);
	box_sizer->Add(input_alcohol, 0, wxALL | wxALIGN_CENTER, 5);
	box_sizer->AddStretchSpacer(1);
	box->SetSizer(box_sizer);
	//right controls:
	wxTextCtrl* drinkersPay = new wxTextCtrl(panel, wxID_ANY, _T(""),wxDefaultPosition, wxSize(200,-1), wxTE_READONLY);
	wxTextCtrl* nondrinkersPay = new wxTextCtrl(panel, wxID_ANY, _T(""), wxDefaultPosition, wxSize(200, -1), wxTE_READONLY);
	//right sizer:
	wxSizer* right_sizer = new wxBoxSizer(wxVERTICAL);
	right_sizer->AddStretchSpacer(1);
	right_sizer->Add(drinkersPay, 0, wxALL | wxALIGN_CENTER, 5);
	right_sizer->AddStretchSpacer(3);
	right_sizer->Add(nondrinkersPay, 0, wxALL | wxALIGN_CENTER, 5);
	right_sizer->AddStretchSpacer(1);
	//horizontal sizer
	wxSizer* horizontal_sizer = new wxBoxSizer(wxHORIZONTAL);
	horizontal_sizer->Add(box, 1, wxALL | wxSHAPED | wxALIGN_CENTER, 5);
	horizontal_sizer->Add(right_sizer, 1, wxALL | wxSHAPED | wxALIGN_CENTER, 5);
	//master sizer
	wxButton* calculate = new wxButton(panel, wxID_ANY, _T("Calculate"), wxDefaultPosition, wxSize(200, 70));
	wxButton* back = new wxButton(panel, wxID_ANY, _T("Back"), wxDefaultPosition, wxSize(100, 35));
	wxSizer* master_sizer = new wxBoxSizer(wxVERTICAL);
	master_sizer->Add(horizontal_sizer, 3, wxALL | wxSHAPED | wxALIGN_CENTER, 5);
	master_sizer->Add(calculate, 0, wxALL | wxALIGN_CENTER, 20);
	master_sizer->Add(0, 20, 0);
	master_sizer->Add(back, 0, wxALL | wxALIGN_CENTER, 20);
	panel->SetSizer(master_sizer);
	panel->Layout();
	status->PushStatusText("Awating data...");
	//navigation lambda
	 
	//lambda for the calculate button
	 auto CalculatePressed = [=](wxCommandEvent& evt)
	 {
		 nondrinkersPay->Clear();
		 drinkersPay->Clear();

		 PartySimple::SetTotalExpenses(input_expenses->GetValue());
		 PartySimple::SetAlcoholExpenses(input_alcohol->GetValue());
		 PartySimple::SetNrOfParticipants(input_participants->GetValue());
		 PartySimple::SetNrOfNondrinkers(input_nondrinkers->GetValue());

		 if (input_participants->GetValue() == 0
			 || input_participants->GetValue() < input_nondrinkers->GetValue())
		 {
			 nondrinkersPay->SetBackgroundColour(wxColour(wxNullColour));
			 drinkersPay->SetBackgroundColour(wxColour(wxNullColour));
			 nondrinkersPay->Refresh();
			 drinkersPay->Refresh();
			 status->PushStatusText("Invalid Data! Check Entered Number Of Participants");
			 status->SetBackgroundColour(wxColour(*wxRED));
			 status->Refresh();
			 return;
		 }

		 if (input_expenses->GetValue() < input_alcohol->GetValue())
		 {
			 status->PushStatusText("Invalid Data! Check Entered Expenses");
			 status->SetBackgroundColour(wxColour(*wxRED));
			 status->Refresh();
			 return;
		 }

		 PartySimple::Calculate();
		 status->PushStatusText("Check is Split!");
		 status->SetBackgroundColour(wxColour(*wxGREEN));
		 status->Refresh();
		 *nondrinkersPay << "Non Drinkers will pay " << PartySimple::GetNonDrinkersShare();
		 nondrinkersPay->SetBackgroundColour(wxColour(*wxGREEN));
		 *drinkersPay << "Drinkers will pay " << PartySimple::GetParticipantsShare();
		 drinkersPay->SetBackgroundColour(wxColour(*wxGREEN));
	 };
	//bindings:
	 calculate->Bind(wxEVT_BUTTON, CalculatePressed);
	 back->Bind(wxEVT_BUTTON, &MainFrame::BackPressed, this);
	
}

void MainFrame::ExtendedVersion(wxCommandEvent& evt)
{
	status->SetBackgroundColour(wxColour(wxNullColour));
	this->SetClientSize(wxSize(1200, 500));
	this->Center();
	this->Layout();
	ClearPanelAndSizer(panel);
	status->PushStatusText("Awating data...");
	//left panel
	wxScrolledWindow* panel_left = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxSize(600,300), wxWANTS_CHARS);
	panel_left->SetScrollbars(0, 5, 0, 0);	
	//left panel:sizer
	wxSizer* panel_left_sizer = new wxBoxSizer(wxVERTICAL);
	panel_left->SetSizer(panel_left_sizer);
	//right panel 
	wxPanel* panel_right = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);
	//right controls
	wxButton* Add = new wxButton(panel_right, wxID_ANY, _T("Add"), wxDefaultPosition, wxDefaultSize);
	wxButton* goBack = new wxButton(panel_right, wxID_ANY, _T("Back"), wxDefaultPosition, wxDefaultSize);
	wxButton* calculate = new wxButton(panel_right, wxID_ANY, _T("Calculate"), wxDefaultPosition, wxSize(150, 50));

	//right panel:sizer
	wxSizer* panel_right_sizer = new wxBoxSizer(wxVERTICAL);
	panel_right->SetSizer(panel_right_sizer);
	//box
	wxStaticBox* box = new wxStaticBox(panel_right, wxID_ANY, _T("Party Info"), wxDefaultPosition, wxSize(300, 300));
	wxStaticText* participants = new wxStaticText(box, wxID_ANY, _T("Number of Participants(total):"));
	wxTextCtrl* input_participants = new wxTextCtrl(box, wxID_ANY, _T("0"), wxDefaultPosition, wxSize(80, -1), wxTE_READONLY );
	wxStaticText* nondrinkers = new wxStaticText(box, wxID_ANY, _T("Number of Non Drinkers:"));
	wxTextCtrl* input_nondrinkers = new wxTextCtrl(box, wxID_ANY, _T("0"), wxDefaultPosition, wxSize(80, -1), wxTE_READONLY);
	wxStaticText* expenses = new wxStaticText(box, wxID_ANY, _T("Total Expenses:"));
	wxSpinCtrlDouble* input_expenses = new wxSpinCtrlDouble(box, wxID_ANY, _T("0.0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 5000);
	wxStaticText* alcohol = new wxStaticText(box, wxID_ANY, _T("Alcohol Expenses:"));
	wxSpinCtrlDouble* input_alcohol = new wxSpinCtrlDouble(box, wxID_ANY, _T("0.0"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 5000);
	//box sizer(right sizer):
	wxSizer* box_sizer = new wxBoxSizer(wxVERTICAL);
	box_sizer->AddStretchSpacer(1);
	box_sizer->Add(participants, 0, wxALL, 5);
	box_sizer->Add(input_participants, 0, wxALL | wxALIGN_CENTER, 5);
	box_sizer->AddStretchSpacer(1);
	box_sizer->Add(nondrinkers, 0, wxALL, 5);
	box_sizer->Add(input_nondrinkers, 0, wxALL | wxALIGN_CENTER, 5);
	box_sizer->AddStretchSpacer(1);
	box_sizer->Add(expenses, 0, wxALL, 5);
	box_sizer->Add(input_expenses, 0, wxALL | wxALIGN_CENTER, 5);
	box_sizer->AddStretchSpacer(1);
	box_sizer->Add(alcohol, 0, wxALL, 5);
	box_sizer->Add(input_alcohol, 0, wxALL | wxALIGN_CENTER, 5);
	box_sizer->AddStretchSpacer(1);
	box->SetSizer(box_sizer);
	
	//add on sizers
	panel_right_sizer->Add(Add, 0, wxALIGN_LEFT, 0);
	panel_right_sizer->Add(0, 15, 0);
	panel_right_sizer->Add(goBack, 0, wxALIGN_LEFT, 0);
	panel_right_sizer->Add(0, 15, 0);
	panel_right_sizer->Add(box, 0, wxALIGN_CENTER, 0);
	panel_right_sizer->Add(0, 15, 0);
	panel_right_sizer->Add(calculate, 0, wxALIGN_CENTER, 0);
	Layout();
	goBack->Bind(wxEVT_BUTTON, &MainFrame::BackPressed, this);
	auto ChangeParticipantsAndDrinkersNumber = [=](wxSizeEvent& evt)
	{
		input_participants->SetValue(wxString::Format(wxT("%i"), PartyExtended::GetNrOfParticipants()));
		input_nondrinkers->SetValue(wxString::Format(wxT("%i"), PartyExtended::ComputeNonDrinkers()));
	};
	panel_left->Bind(wxEVT_SIZE, ChangeParticipantsAndDrinkersNumber);
	auto appear = [=](wxCommandEvent& evt)
	{
		PartyExtended::SetNrOfParticipants(PartyExtended::GetNrOfParticipants() + 1);
		//new participant
		Participant* new_participant = new Participant;
		PartyExtended::AddParticipant(new_participant);
		//controls
		wxPanel* local_panel = new wxPanel(panel_left);
		wxSizer* local_sizer_horizontal = new wxBoxSizer(wxHORIZONTAL);
		wxTextCtrl* name = new wxTextCtrl(local_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(130, -1));
		name->SetHint("Participant Name...");
		wxString choices[] = { "Drinker", "Driver", "Party-Pooper" };
		wxComboBox* mode = new wxComboBox(local_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 3, choices);
		mode->SetHint("Mode");
		wxSpinCtrl* exception = new wxSpinCtrl(local_panel, wxID_ANY, _T("BudgetExcpt"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 0, 10000);
		//wxTextCtrl* exception = new wxTextCtrl(local_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(80, -1));
		//exception->SetHint("Budget Excpt...");
		wxButton* del = new wxButton(local_panel, wxID_ANY, _T("Delete"), wxDefaultPosition, wxDefaultSize);
		local_sizer_horizontal->Add(name);
		local_sizer_horizontal->Add(30, -1);
		local_sizer_horizontal->Add(mode);
		local_sizer_horizontal->Add(30, -1);
		local_sizer_horizontal->Add(exception);
		local_sizer_horizontal->Add(30, -1);
		local_sizer_horizontal->Add(del);

		wxSizer* local_sizer_vertical = new wxBoxSizer(wxVERTICAL);
		local_sizer_vertical->Add(local_sizer_horizontal);
		local_sizer_vertical->Add(-1, 30);
		/*
				|
				|
				V
		  panel_left_sizer
			 + panel
				|
				V
		  local_vertical
		  +->local horizontal
		  +->space
				|
				|
				|
				v
			result panel
		*/
		local_panel->SetSizer(local_sizer_vertical);
		panel_left_sizer->Add(local_panel);
		panel->Layout();
		//delete the controls
		del->Bind(wxEVT_BUTTON, &MainFrame::DeleteParticipant, this);
		//delete the participant
		del->Bind(wxEVT_BUTTON,
			[=](wxCommandEvent& evt)
			{
				PartyExtended::RemoveParticipant(new_participant);
				delete new_participant;
				evt.Skip();
			}
		);
		
		//bindings for participant info
		//name
		auto ChangeName = [=](wxCommandEvent& evt)
		{
			std::string strname = std::string(evt.GetString().mb_str());
			new_participant->SetName(strname);

		};
		name->Bind(wxEVT_TEXT, ChangeName);
		//drinks?
		auto setdrinker = [=](wxCommandEvent& evt)
		{
			if (evt.GetSelection() == 0)
			{
				new_participant->SetIsDrinking();
			}
			else
			{
				new_participant->SetIsNotDrinking();
			}
			
			input_nondrinkers->SetValue(wxString::Format(wxT("%i"), PartyExtended::ComputeNonDrinkers()));
		};
		mode->Bind(wxEVT_COMBOBOX, setdrinker);
		//exception

		auto setexception = [=](wxCommandEvent& evt)
		{
			new_participant->SetExceptVal(exception->GetValue());
		};
		exception->Bind(wxEVT_SPINCTRL, setexception);
	};

	
	Add->Bind(wxEVT_BUTTON, appear);
	//left sizer
	wxBoxSizer* left_sizer = new wxBoxSizer(wxVERTICAL);
	wxScrolledWindow* result_panel = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxSize(600, 200));
	result_panel->SetScrollbars(0, 5, 0, 0);
	//result panel sizer
	wxBoxSizer* result_panel_sizer = new wxBoxSizer(wxVERTICAL);
	left_sizer->Add(panel_left, 1, wxALL| wxSHAPED, 0);
	left_sizer->Add(result_panel, 1, wxALL| wxSHAPED, 0);
	result_panel->SetSizer(result_panel_sizer);
	wxBoxSizer* main_sizer = new wxBoxSizer(wxHORIZONTAL);
	main_sizer->Add(left_sizer, 1, wxALL | wxALIGN_CENTER | wxSHAPED, 50);
	main_sizer->Add(panel_right, 2, wxALL| wxSHAPED, 10);
	panel->SetSizer(main_sizer);
	panel->Layout();
	auto handleWarning=[=](const wxString message)
	{
		status->PushStatusText(message);
		status->SetBackgroundColour(*wxRED);
		status->Refresh();
	};
	auto Calculate = [=](wxCommandEvent& evt)
	{
		result_panel_sizer->Clear();
		for (auto wins : result_panel->GetChildren())
		{
			wins->Hide();
		}
		PartyExtended::SetTotalExpenses(input_expenses->GetValue());
		PartyExtended::SetAlcoholExpenses(input_alcohol->GetValue());
		//exception checks
		if ((PartyExtended::GetNrOfParticipants() - PartyExtended::GetNrOfNondrinkers()) > 0 && PartyExtended::GetAlcoholExpenses() == 0)
		{
			handleWarning("Invalid Data! There are Drinkers But No Alcohol Expenses!");
			return;
		}
		if ((PartyExtended::GetNrOfParticipants() - PartyExtended::GetNrOfNondrinkers()) == 0 && PartyExtended::GetAlcoholExpenses() > 0)
		{
			handleWarning("Invalid Data! There are no Drinkers But Non-Zero Alcohol Expenses!");
			return;
		}
		if (input_alcohol->GetValue() > input_expenses->GetValue())
		{
			handleWarning("Invalid Data! Check Entered Expenses!");
			return;
		}
		if (PartyExtended::GetParticipants().empty())
		{
			handleWarning("Invalid Data! ->  No Participants!");
			return;
		}
		for (auto participant : PartyExtended::GetParticipants())
			if (participant->GetName().empty())
			{
				handleWarning("Invalid Data! -> Incomplete Participant Names!");
				return;
			}
		for (auto participant : PartyExtended::GetParticipants())
			if (participant->GetExcptVal() > PartyExtended::GetTotalExpenses())
			{
				handleWarning("Invalid Data! -> Budget Exceptions may not exceed the total expenses. ");
				return;
			}		
		
		//tests passed
		//=========================
		PartyExtended::CalculateExtended();
	
		status->PushStatusText("The Check is Split");
		status->SetBackgroundColour(*wxGREEN);
		status->Refresh();
		wxStaticText* res = new wxStaticText(result_panel, wxID_ANY, _T("Results:"));
		result_panel_sizer->Add(res);
		result_panel_sizer->Add(0, 15, 0);
		for (auto participant : PartyExtended::GetParticipants())
		{
			if (participant->GetExcptVal() != 0)
			{
				std::string name = participant->GetName();
				std::string shr = std::to_string(participant->GetShare());
				std::string full = name + " will pay " + shr;
				wxString name2(name);
				wxStaticText* result = new wxStaticText(result_panel, wxID_ANY, full);
				result_panel_sizer->Add(result);
				result_panel_sizer->Add(0, 15, 0);
				result_panel->Layout();
				panel->Layout();
				result_panel->Fit();
			}
		}
		if ((PartyExtended::GetNrOfParticipants() - PartyExtended::GetNrOfNondrinkers()) != 0)
		{
			wxString drk_shr("DRINKERS WILL PAY: " + std::to_string(PartyExtended::GetParticipantsShare()));
			wxStaticText* drk_txt = new wxStaticText(result_panel, wxID_ANY, drk_shr);
			result_panel_sizer->Add(0, 15, 0);
			result_panel_sizer->Add(drk_txt);
		}
		if (PartyExtended::GetNrOfNondrinkers() != 0)
		{
			wxString nondrk_shr = ("NON DRINKERS WILL PAY: " + std::to_string(PartyExtended::GetNonDrinkersShare()));
			wxStaticText* nondrk_txt = new wxStaticText(result_panel, wxID_ANY, nondrk_shr);
			result_panel_sizer->Add(0, 15, 0);
			result_panel_sizer->Add(nondrk_txt);
		}
		
		result_panel->Layout();
		panel->Layout();
		result_panel->Fit();
		
	};
	calculate->Bind(wxEVT_BUTTON, Calculate);
}
void MainFrame::ClearPanelAndSizer(wxPanel* panel)
{
	panel->GetSizer()->Clear(true);
	panel->SetSizerAndFit(nullptr);
}

void MainFrame::BackPressed(wxCommandEvent& evt)
{
	ClearPanelAndSizer(panel);
	ChooseMode();
}

void MainFrame::DeleteParticipant(wxCommandEvent& evt)
{
	PartyExtended::SetNrOfParticipants(PartyExtended::GetNrOfParticipants() - 1);
	auto btn = (wxButton*)evt.GetEventObject();
	auto pnl = btn->GetParent()->GetParent();
	btn->GetParent()->Destroy();//pnl is panel_left
	pnl->GetParent()->Layout(); //will layout the main panel
}
