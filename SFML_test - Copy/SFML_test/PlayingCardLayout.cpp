#include "PlayingCardLayout.hpp"

#include <fstream>
#include <iostream>

namespace
{
	const std::string kCardToken = "Card";
	const std::string kDeckToken = "Deck";
	const std::string kPileToken = "Pile";

	const std::string kPositionToken = "Position";
	const std::string kFaceUpToken = "FaceUp";

	const std::string kAddToken = "add";
	const std::string kRemoveToken = "remove";
	const std::string kShuffleToken = "shuffle";
	const std::string kEndToken = "end";

	const std::string kPipToken = "Pip";

	const std::string kAceTokens[2] = { "Ace", "A" };
	const std::string kJackTokens[2] = { "Jack", "J" };
	const std::string kQueenTokens[2] = { "Queen", "Q" };
	const std::string kKingTokens[2] = { "King", "K" };

	const std::string kSuitToken = "Suit";

	const std::string kHeartToken = "Heart";
	const std::string kDiamondToken = "Diamond";
	const std::string kSpadeToken = "Spade";
	const std::string kClubToken = "Club";
	
	const std::string kTrueToken = "True";
	const std::string kFalseToken = "False";

	const std::string kLessToken = "<";
	const std::string kEqualToken = "=";
	const std::string kMoreToken = ">";

	const std::string kCommentToken = "//";
}

PlayingCardLayout::PlayingCardLayout()
{

}

void PlayingCardLayout::clear()
{
	_decks.clear();
	_piles.clear();
	_cards.clear();
}

void PlayingCardLayout::loadFromFile(std::string fileName)
{
	std::ifstream file(fileName, std::ifstream::in);
	
	std::vector<std::vector<std::string> > tokenLines;

	std::string line;
	while (std::getline(file, line))
	{
		std::vector<std::string> tokens;

		//	Getting tokens
		std::string tempToken;
		for (unsigned i = 0; i < line.size(); i++)
		{
			//	If char is space add temptoken to vector
			if (line[i] == ' ')
			{
				tokens.push_back(tempToken);
				tempToken.clear();
			}
			else
			{
				tempToken += line[i];
			}
		}

		//	Adding final temptoken to tokens
		tokens.push_back(tempToken);
		tokenLines.push_back(tokens);
	}

	file.close();

	//	Go through tokenised file and do appropriate work
	for (auto iter = tokenLines.begin(); iter != tokenLines.end(); iter++)
	{
		//	Check first token
		if (iter->empty() == false)
		{
			//	Handle appropriately
			if ((*iter)[0].compare(kCardToken) == 0)
			{
				handleCardToken(iter, tokenLines.end());
			}
			else if ((*iter)[0].compare(kDeckToken) == 0)
			{
				handleDeckToken(iter, tokenLines.end());
			}
			else if ((*iter)[0].compare(kPileToken) == 0)
			{
				handlePileToken(iter, tokenLines.end());
			}
		}

	}
}

void PlayingCardLayout::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	//	Draw decks
	for (unsigned i = 0; i < _decks.size(); i++)
	{
		_decks[i].draw(target, states);
	}

	//	Draw piles
	for (unsigned i = 0; i < _piles.size(); i++)
	{
		_piles[i].draw(target, states);
	}

	//	Draw cards
	for (auto iter = _cards.begin(); iter != _cards.end(); iter++)
	{
		iter->second.draw(target, states);
	}
}

void PlayingCardLayout::handleCardToken(std::vector<std::vector<std::string> >::iterator& iter, std::vector<std::vector<std::string> >::iterator& end)
{
	//	Create card object
	PlayingCardDrawable drawable;
	PlayingCard card;

	std::string name;

	//	Check line contains both card token and a name
	if (iter->size() >= 2)
	{
		name = (*iter)[1];

		//	Check name isn't already used
		if (_cards.find(name) != _cards.end())
		{
			//	Error card name already exists
		}
		//	Do same for decks and piles.
	}
	else
	{
		//	Error no name token present
	}

	while (iter != end)
	{
		if (iter->empty() == false)
		{
			//	Check end token
			if ((*iter)[0].compare(kEndToken) == 0)
			{
				//	Check card token
				if (iter->size() >= 2)
				{
					if ((*iter)[1].compare(kCardToken) == 0)
					{
						//	Add card to vector
						drawable.setCard(card);
						_cards.insert(std::pair<std::string, PlayingCardDrawable>(name, drawable));

						//	Exit function
						return;
					}
				}
			}
			//	Check Position token
			else if ((*iter)[0].compare(kPositionToken) == 0)
			{
				//	Check is line contains at least 3 tokens
				//	Should probably make consts of the lengths
				if (iter->size() >= 3)
				{
					//	Attempt to cast tokens 1 and 2 into floats
					float x = atof((*iter)[1].c_str());
					float y = atof((*iter)[2].c_str());

					drawable.setPosition(x, y);
				}
			}
			//	Check Pip token
			else if ((*iter)[0].compare(kPipToken) == 0)
			{
				//	Check if line contains second token
				if (iter->size() >= 2)
				{
					//	Check if pip token
					int pip = isValidPipToken(&(*iter)[1]);
					if (pip != -1)
					{
						std::cout << pip;
						card.setPip(pip);
					}
					else
					{
						pip = atoi((*iter)[1].c_str());
						if (pip > 0 && pip <= 13)
						{
							card.setPip(pip);
						}
						else
						{
							//	Throw error invalid pip value
						}
					}

				}
			}
			else if ((*iter)[0].compare(kSuitToken) == 0)
			{
				//	Check if line contains second token
				if (iter->size() >= 2)
				{
					PlayingCard::Suit suit = isValidSuitToken(&(*iter)[1]);
					if (suit != PlayingCard::Suit::None)
					{
						card.setSuit(suit);
					}
					else
					{
						//	Throw error invalid suit token
					}
				}
			}
			else if ((*iter)[0].compare(kFaceUpToken) == 0)
			{
				//	Check if line contains second token
				if (iter->size() >= 2)
				{
					if ((*iter)[1].compare(kTrueToken) == 0)
					{
						drawable.setOrientation(true);
					}
					else if ((*iter)[1].compare(kFalseToken) == 0)
					{
						drawable.setOrientation(false);
					}
					else
					{
						//	Invalid token
					}
				}
			}
			//	Check if not comment token
			else if ((*iter)[0].compare(kCommentToken) != 0)
			{
				//	Throw error invalid token
			}
		}
		iter++;
	}
}

void PlayingCardLayout::handleDeckToken(std::vector<std::vector<std::string> >::iterator& iter, std::vector<std::vector<std::string> >::iterator& end)
{

}

void PlayingCardLayout::handlePileToken(std::vector<std::vector<std::string> >::iterator& iter, std::vector<std::vector<std::string> >::iterator& end)
{

}

int PlayingCardLayout::isValidPipToken(std::string *token)
{
	//	Check AJQK tokens
	for (unsigned i = 0; i < 2; i++)
	{
		if (token->compare(kAceTokens[i]) == 0) return 1;
		if (token->compare(kJackTokens[i]) == 0) return 11;
		if (token->compare(kQueenTokens[i]) == 0) return 12;
		if (token->compare(kKingTokens[i]) == 0) return 13;
	}

	//	Return -1 otherwise
	return -1;
}

PlayingCard::Suit PlayingCardLayout::isValidSuitToken(std::string *token)
{
	if (token->compare(kHeartToken) == 0) return PlayingCard::Suit::Heart;
	if (token->compare(kDiamondToken) == 0) return PlayingCard::Suit::Diamond;
	if (token->compare(kSpadeToken) == 0) return PlayingCard::Suit::Spade;
	if (token->compare(kClubToken) == 0) return PlayingCard::Suit::Club;

	return PlayingCard::Suit::None;
}