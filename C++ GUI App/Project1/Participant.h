#pragma once
#include <string>
class Participant
{
	std::string name;
	bool isDrinking;
	int exception_value;
	int share;
public:
	Participant()
	{
		isDrinking = 0;
		exception_value = 0;
		share = 0;
	}
	//getters
	std::string GetName() const
	{
		return name;
	};

	bool IsDrinking() const
	{
		return isDrinking;
	}

	int GetExcptVal() const
	{
		return exception_value;
	}

	int GetShare() const
	{
		return share;
	}

	//setters
	void SetName(const std::string input)
	{
		name = input;
	}

	void SetIsDrinking( )
	{
		isDrinking = 1;
	}
	void SetIsNotDrinking()
	{
		isDrinking = 0;
	}

	void SetShare(int input)
	{
		share = input;
	}
	void SetExceptVal(int input)
	{
		exception_value = input;
	}

};

