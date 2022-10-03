#include "PartySimple.h"
int PartySimple::total_expenses;
int PartySimple::alcohol_expenses;
int PartySimple::nr_of_participants;
int PartySimple::nr_of_nondrinkers;
int PartySimple::participants_share;
int PartySimple::nondrinkers_share;
PartySimple::PartySimple()
{
	total_expenses = 0;
	alcohol_expenses = 0;
	nr_of_participants = 0;
	nr_of_nondrinkers = 0;
	participants_share = 0;
	nondrinkers_share = 0;
}

int PartySimple::GetTotalExpenses()
{
	return total_expenses;
}

int PartySimple::GetAlcoholExpenses()
{
	return alcohol_expenses;
}

int PartySimple::GetNrOfParticipants()
{
	return nr_of_participants;
}

int PartySimple::GetNrOfNondrinkers()
{
	return nr_of_nondrinkers;
}

int PartySimple::GetParticipantsShare()
{
	return participants_share;
}

int PartySimple::GetNonDrinkersShare()
{
	return nondrinkers_share;
}

void PartySimple::SetTotalExpenses(int value)
{
	total_expenses=value;
}

void PartySimple::SetAlcoholExpenses(int value)
{
	alcohol_expenses=value;
}

void PartySimple::SetNrOfParticipants(int value)
{
	nr_of_participants = value;
}

void PartySimple::SetNrOfNondrinkers(int value)
{
	nr_of_nondrinkers=value;
}

void PartySimple::SetParticipantsShare(int value)
{
	participants_share=value;
}

void PartySimple::SetNonDrinkersShare(int value)
{
	nondrinkers_share=value;
}

void PartySimple::Calculate()
{
	SetParticipantsShare((total_expenses - alcohol_expenses) / nr_of_participants
		+ alcohol_expenses / (nr_of_participants - nr_of_nondrinkers));

	SetNonDrinkersShare((total_expenses - alcohol_expenses) / nr_of_participants);
}
