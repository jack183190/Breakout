#pragma once

#include <array>
#include <string>

class LeaderboardManager
{
public:
	LeaderboardManager();

	void addScore(std::uint64_t score);

	// return a string containing score
	// #1 - 1237894
	// #2 - 239783
	// etc
	std::string getScoresString();

private:
	void load();
	void save();

private:
	static constexpr const char* SAVE_FILE = "leaderboard.dat";
	static constexpr size_t LEADERBOARD_SIZE = 5;

	std::array<std::uint64_t, LEADERBOARD_SIZE> _scores;

};

