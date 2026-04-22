#pragma once

#include <string>

class Player
{
private:
	std::string p_name;
	int score = 0;
	bool hasEnteredGame = false;

public:
	Player()
	{

	}

	void SetName(const std::string& name)
	{
		p_name = name;
	}

	void AddScore(int value)
	{
		score += value;
	}

	void SetEnteredGame(bool entered)
	{
		hasEnteredGame = entered;
	}

	const std::string& GetName() const
	{
		return p_name;
	}
	int GetScore() const
	{
		return score;
	}

	bool HasEnteredGame() const
	{
		return hasEnteredGame;
	}
};
