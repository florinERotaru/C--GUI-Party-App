#include "PartyExtended.h"

std::set<Participant*> PartyExtended::Participants;
void PartyExtended::AddParticipant(Participant* participant)
{
	Participants.insert(participant);
}

void PartyExtended::RemoveParticipant(Participant* participant)
{
	Participants.erase(participant);
}

std::set<Participant*> PartyExtended::GetParticipants()
{
	return Participants;
}

int PartyExtended::ComputeNonDrinkers()
{
	int p = 0;
	for (auto particip : PartyExtended::GetParticipants())
		if (!particip->IsDrinking())
			p++;
	PartyExtended::SetNrOfNondrinkers(p);
	return p;
}

void PartyExtended::CalculateExtended()
{

	int non_alc_expenses = total_expenses - alcohol_expenses;
	int nr_of_drinkers = nr_of_participants - nr_of_nondrinkers;
	int alc_share = (nr_of_drinkers == 0) ? 0 : alcohol_expenses / nr_of_drinkers;
	int budget_exceptions = 0; //sums all excp participant's shares
	int participants_with_exceptions = 0;
	
	for (auto participant : Participants)
	{
		if (participant->GetExcptVal() != 0)
		{
			participant->SetShare((non_alc_expenses - participant->GetExcptVal()) / nr_of_participants);
			budget_exceptions += participant->GetShare();
			if(participant->IsDrinking())
				participant->SetShare(participant->GetShare() + alc_share);

			participants_with_exceptions++;
		}
	}
	if (nr_of_participants == participants_with_exceptions)
		return; //we're done

	participants_share = (non_alc_expenses-budget_exceptions) / ((nr_of_participants - participants_with_exceptions)) + alc_share;
	nondrinkers_share = participants_share-alc_share;
	for (auto participant : Participants)
	{
		if (participant->GetExcptVal() == 0)
		{
			if (participant->IsDrinking())
				participant->SetShare(participants_share);
			else
				participant->SetShare(nondrinkers_share);
		}
	}

}
