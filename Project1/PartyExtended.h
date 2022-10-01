#pragma once
#include <set>
#include "PartySimple.h"
#include "Participant.h"
class PartyExtended : public PartySimple
{
	static std::set<Participant*> Participants;
public:
	static void AddParticipant(Participant* participant);
	static void RemoveParticipant(Participant* participant);
	static std::set<Participant*> GetParticipants();
	static int ComputeNonDrinkers();
	static void CalculateExtended();
};

