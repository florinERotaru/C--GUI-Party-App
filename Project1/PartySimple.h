#pragma once
class PartySimple
{
protected:
	static int total_expenses;
	static int alcohol_expenses;
	static int nr_of_participants;
	static int nr_of_nondrinkers;
	static int participants_share;
	static int nondrinkers_share;
public:
	PartySimple();
	//getters
	static int GetTotalExpenses();
	static int GetAlcoholExpenses();
	static int GetNrOfParticipants();
	static int GetNrOfNondrinkers();
	static int GetParticipantsShare();
	static int GetNonDrinkersShare();
	//setters
	static void SetTotalExpenses(int value);
	static void SetAlcoholExpenses(int value);
	static void SetNrOfParticipants(int value);
	static void SetNrOfNondrinkers(int value);
	static void SetParticipantsShare(int value);
	static void SetNonDrinkersShare(int value);

	static void Calculate();

};

