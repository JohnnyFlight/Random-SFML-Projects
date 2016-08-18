#pragma once

#include "Domino.hpp"

#include <vector>

class DominoAI
{
public:
	DominoAI();

	enum Calculation { VerySimple, Simple, Complex };

	void opponentDrew();
	void playerDrew(Domino domino);

	void opponentPlayed(Domino domino);
	void playerPlayed(Domino domino);

	inline void setLeftEnd(unsigned end) { _leftExposedEnd = end; }
	inline void setRightEnd(unsigned end) { _rightExposedEnd = end; }

	Domino makePrediction();

private:
	void updateProbabilityTable();
	bool removeDomino(Domino domino);

	Calculation _calculation;

	unsigned _leftExposedEnd;
	unsigned _rightExposedEnd;

	unsigned _depth;

	//	Maybe add played dominos?
	//	Add number of "decks" used to prevent false positives

	std::vector<Domino> _unknown;
	std::vector<Domino> _playerHand;

	unsigned _opponentHandSize;
	unsigned _boneyardSize;
	std::vector<unsigned> _pipCount;

};