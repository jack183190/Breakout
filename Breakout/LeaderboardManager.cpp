#include "LeaderboardManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>

static constexpr size_t LEADERBOARD_SIZE = 10;

LeaderboardManager::LeaderboardManager()
{
	load();
}

void LeaderboardManager::addScore(std::uint64_t score)
{
	// where does score rank
	// could do a binary search but we can't render lots of scores on screen so leaderboard size is small, not really worth it
	size_t insertIndex = LEADERBOARD_SIZE;
	for (size_t i = 0; i < LEADERBOARD_SIZE; ++i)
	{
		if (score <= _scores[i]) continue;
			insertIndex = i;
			break;
	}

	if (insertIndex >= LEADERBOARD_SIZE)
		return;

	// move everything else down
	for (size_t i = LEADERBOARD_SIZE - 1; i > insertIndex; --i)
		_scores[i] = _scores[i - 1];

	_scores[insertIndex] = score;

	save();
}

std::string LeaderboardManager::getScoresString()
{
	std::ostringstream ss;
	for (size_t i = 0; i < LEADERBOARD_SIZE; ++i)
	{
		if (_scores[i] == 0) break;
		ss << "#" << (i + 1) << " - " << _scores[i] << '\n';
	}
	return ss.str();
}

void LeaderboardManager::load()
{
	_scores.fill(0);

	std::ifstream in(SAVE_FILE);
	if (!in) {
		std::ofstream out(SAVE_FILE, std::ios::trunc); // create empty file, but we know there is nothing to load
		return;
	}

	std::string line;
	size_t i = 0;
	while (i < LEADERBOARD_SIZE && std::getline(in, line))
	{
		std::uint64_t val = 0;
		std::istringstream(line) >> val;
		_scores[i++] = val;
	}
}

void LeaderboardManager::save()
{
	std::ofstream out(SAVE_FILE, std::ios::trunc);
	if (!out) return;

	for (size_t i = 0; i < LEADERBOARD_SIZE && _scores[i] != 0; ++i)
		out << _scores[i] << '\n';
}
