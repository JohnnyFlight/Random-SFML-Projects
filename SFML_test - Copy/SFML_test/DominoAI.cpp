#include "DominoAI.hpp"

#include "MathsUtility.hpp"
#include <stack>

//	Substitute error messages
#include <iostream>

namespace
{
	unsigned kMaxPipCount = 6;
}

DominoAI::DominoAI()
{
	//	Put full boneyard in _unknown
	for (unsigned i = 0; i <= kMaxPipCount; i++)
	{
		for (unsigned j = i; j <= kMaxPipCount; j++)
		{
			_unknown.push_back(Domino(i, j));
		}
	}

	_pipCount.assign(kMaxPipCount+1, 0U);
}

void DominoAI::opponentDrew()
{
	if (_boneyardSize > 0)
	{
		_boneyardSize--;
		_opponentHandSize++;
	}
	else
	{
		//	Throw error boneyard should be empty
		std::cout << "Boneyard is empty" << std::endl;
	}
}

void DominoAI::playerDrew(Domino domino)
{
	bool dominoInBoneyard = false;

	//	Remove domino from BY
	for (unsigned i = 0; i < _unknown.size(); i++)
	{
		if (_unknown[i] == domino)
		{
			std::swap(_unknown.begin()+i, _unknown.end()-1);
			_unknown.pop_back();

			dominoInBoneyard = true;
			break;
		}
	}

	//	Add domino to hand
	if (dominoInBoneyard == true)
	{
		_playerHand.push_back(domino);
		
		if (_boneyardSize > 0)
		{
			_boneyardSize--;
		}
		else
		{
			//	Throw error boneyard should be empty
			std::cout << "Boneyard is empty." << std::endl;
		}
	}
	else
	{
		//	Throw error domino not in boneyard
		std::cout << "Domino " << domino.left() << ", " << domino.right() << " not in boneyard." << std::endl;
	}
}

void DominoAI::opponentPlayed(Domino domino)
{
	if (_opponentHandSize > 0)
	{
		_opponentHandSize--;
	}
	else
	{
		//	Throw error opponent hand should be empty
		std::cout << "Opponent hand is empty." << std::endl;
	}
}

void DominoAI::playerPlayed(Domino domino)
{
	//	Check hand isn't empty
	if (_playerHand.size() == 0)
	{
		//	Throw error player hand should be empty
		std::cout << "Player hand is empty." << std::endl;
	}

	//	Check domino is in hand
	bool dominoInHand = false;

	for (unsigned i = 0; i < _playerHand.size(); i++)
	{
		if (_playerHand[i] == domino)
		{
			dominoInHand = true;
			std::swap(_playerHand[i], _playerHand.back());
			
			_playerHand.pop_back();
			break;
		}
	}

	if (dominoInHand == false)
	{
		//	Throw error domino not in hand
		std::cout << "Domino not in hand." << std::endl;
	}
}

Domino DominoAI::makePrediction()
{
	updateProbabilityTable();

	std::stack<unsigned> bestChoices;
	std::vector<unsigned> chosenPips;

	//	Check best probability
	//	See if suitable domino is in hand

	for (unsigned i = 0; i <= kMaxPipCount; i++)
	{
		unsigned highestPip = 0;
		unsigned highestPipCount = 0;

		for (unsigned j = 0; j <= kMaxPipCount; j++)
		{
			//	Check if greatest value
			if (_pipCount[j] >= highestPipCount)
			{
				//	Check not used
				bool used = false;
				for (unsigned k = 0; k < chosenPips.size(); k++)
				{
					if (j == chosenPips[k])
					{
						used = true;
						break;
					}
				}

				if (used == false)
				{
					highestPip = j;
					highestPipCount = _pipCount[j];
				}
			}
		}
		bestChoices.push(highestPip);
		chosenPips.push_back(highestPip);
	}

	Domino best;

	while (bestChoices.size() > 0)
	{
		bool optionFound = false;

		//	Check if suitable domino is in hand
		for (unsigned i = 0; i < _playerHand.size(); i++)
		{
			if (_playerHand[i].contains(bestChoices.top()))
			{
				//	Also check against exposed ends here
				//	Handle zero!

				best = _playerHand[i];
				optionFound = true;

				while (bestChoices.empty() == false)
				{
					bestChoices.pop();
				}
				break;
			}
		}
	}

	return best;
}

void DominoAI::updateProbabilityTable()
{
	//	Probability is of opponent having specific number in hand

	//	Set each element of pipCount to 0
	for (auto iter = _pipCount.begin(); iter != _pipCount.end(); iter++)
	{
		(*iter) = 0;
	}

	//	This is now hella optimised.

	//	For each unknown domino
	for (auto iter = _unknown.begin(); iter != _unknown.end(); iter++)
	{
		//	Increase pip count of left
		_pipCount[iter->left()]++;

		//	If not a double, also increase pip count of right
		if (iter->isDouble() == false)
		{
			_pipCount[iter->right()]++;
		}
	}
}

bool DominoAI::removeDomino(Domino domino)
{
	for (unsigned i = 0; i < _unknown.size(); i++)
	{
		if (_unknown[i] == domino)
		{
			std::swap(_unknown[i], _unknown.back());
			_unknown.pop_back();
			return true;
		}
	}

	return false;
}