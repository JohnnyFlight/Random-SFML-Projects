#include "Game.hpp"

#include <iostream>
#include <sstream>

#include <cmath>

#include "DeckGenerator.hpp"
#include "TileGenerator.hpp"
#include "TileNames.hpp"

namespace
{
	const float kRotateTargetRadius = 20.0f;

	const unsigned kCharacterSize = 24;

	const unsigned kFactionNumber = 5;

	const std::string kImageDirectory = "Images/";
	const std::string kImageExtension = ".png";

	const std::string kStartPhaseTutorialText = "Select a number of players.";
	const std::string kDrawPhaseTutorialText = "Click on the deck to draw a tile.";
	const std::string kDiscardPhaseTutorialText = "Click on a tile in your hand to discard it.\nMust have at most 2 tiles in hand.";
	const std::string kPlayPhaseTutorialText = "Click on a tile in your hand to play it.";
	const std::string kPlaceTilePhaseTutorialText = "Click on the board to place tile.";
	const std::string kRotateTilePhaseTutorialText = "Click one of the markers to rotate tile.";
	const std::string kChooseLocationPhaseTutorialText = "Click on the board to select tile.";
}

Game::Game(unsigned width, unsigned height, std::string title)
	: Application(width, height, title)
{
	//_board = Board(5, 5, 100.0f);
	_board = Board();

	loadAssets();

	initialise();
}

Game::~Game()
{
	_currentPlayer = 0;
	
	for (unsigned i = 0; i < _players.size(); i++)
	{
		delete _players[i];
	}

	_players.clear();
}

void Game::initialise()
{
	_phase = Phase::Start;

	_playerCounter = 0;

	//	Initialise tutorial text
	_tutorialText.setFont(_font);

	_tutorialText.setColor(sf::Color::White);
	_tutorialText.setCharacterSize(kCharacterSize);
	_tutorialText.setPosition(800.0f, 400.0f);

	updateTutorialText();

	//	Create start buttons
	HexTile twoPlayerButton = HexTile();

	HexTile threePlayerButton = HexTile();

	//	Apply textures
	twoPlayerButton.setTexture(_textures.getResource("Two Player"));
	threePlayerButton.setTexture(_textures.getResource("Three Player"));

	//	Move to appropriate locations
	twoPlayerButton.move(200.0f, 200.0f);
	threePlayerButton.move(400.0f, 200.0f);

	//	Push to array
	_playerSelectButtons.push_back(twoPlayerButton);
	_playerSelectButtons.push_back(threePlayerButton);

	for (unsigned i = 0; i < kFactionNumber; i++)
	{
		Button button(200.0f, 100.0f);
		button.setPosition(0.0f, 150.0f * i);
		_factionButtons.push_back(button);
	}

	_factionButtons[0].setTexture(_textures.getResource("outpost_button"));
	_factionButtons[1].setTexture(_textures.getResource("hegemony_button"));
	_factionButtons[2].setTexture(_textures.getResource("moloch_button"));
	_factionButtons[3].setTexture(_textures.getResource("doomsday_button"));
	_factionButtons[4].setTexture(_textures.getResource("borgo_button"));
}

void Game::initialiseGame()
{
	_phaseStack = std::stack<Phase>();

	_resolvingPlayTile = Tile::PlayType::Null;

	_currentPlayer = _players[_playerCounter];

	_tiles = std::vector<std::vector<HexTile> >(_board.getWidth());
	for (unsigned i = 0; i < _tiles.size(); i++)
	{
		_tiles[i] = std::vector<HexTile>(_board.getHeight(), HexTile());
	}

	for (unsigned i = 0; i < _tiles.size(); i++)
	{
		for (unsigned j = 0; j < _tiles[i].size(); j++)
		{
			float tileDistance = _tiles[i][j].getRadius() * 2.75f;
			_tiles[i][j].setPosition(i * tileDistance * 0.75f + _tiles[i][j].getRadius(), j * tileDistance * 0.7f + _tiles[i][j].getRadius());
			if (j%2) _tiles[i][j].move(tileDistance * 0.375f, 0.0f);
			_tiles[i][j].setTexture(_textures.getResource("Hex Default"));
		}
	}

	//	Initialise text
	_playerNumberDisplay.setFont(_font);
	_playerNumberDisplay.setCharacterSize(kCharacterSize);
	_playerNumberDisplay.move(850.0f, 450.0f);
	_playerNumberDisplay.setString("Player: ");
	
	_playerHealthDisplay.setFont(_font);
	_playerHealthDisplay.setCharacterSize(kCharacterSize);
	_playerHealthDisplay.move(850.0f, 500.0f);
	_playerHealthDisplay.setString("Player: ");

	_continueButton = Button(200, 100);
	_continueButton.setPosition(800.0f, 600.0f);
	_continueButton.setTexture(_textures.getResource("continue_button"));

	_drawContinueButton = false;
	_tilePlaced = false;

	_currentInitiative = -1;
	_continueBattlePhase = false;

	_drawRotateTargets = false;
	_rotateTargets = std::vector<HexTile>(6);
	
	for (unsigned i = 0; i < _rotateTargets.size(); i++)
	{
		_rotateTargets[i].setFillColor(sf::Color::Blue);
		_rotateTargets[i].setRadius(kRotateTargetRadius);
	}
}

bool Game::loadAssets()
{
	_textures = ResourceManager<sf::Texture>();

	sf::Texture *texture = new sf::Texture();
	
	if (!loadTexture("Hex Default")) return false;

	//	Loading Player Select tiles
	if (!loadTexture("Two Player")) return false;
	if (!loadTexture("Three Player")) return false;

	//	Loading faction select buttons
	if (!loadTexture("outpost_button")) return false;
	if (!loadTexture("hegemony_button")) return false;
	if (!loadTexture("moloch_button")) return false;
	if (!loadTexture("doomsday_button")) return false;
	if (!loadTexture("borgo_button")) return false;

	if (!loadTexture("continue_button")) return false;

	//	Loading Play tiles
	if (!loadTexture(TileNames::move())) return false;
	if (!loadTexture(TileNames::sniper())) return false;
	if (!loadTexture(TileNames::battle())) return false;
	if (!loadTexture(TileNames::airStrike())) return false;

	//	Load HeadQuarters
	if (!loadTexture(TileNames::outpostHQ())) return false;
	if (!loadTexture(TileNames::hegemonyHQ())) return false;
	if (!loadTexture(TileNames::molochHQ())) return false;
	if (!loadTexture(TileNames::doomsdayHQ())) return false;
	if (!loadTexture(TileNames::borgoHQ())) return false;

	//	Loading Outpost Unit tiles
	if (!loadTexture(TileNames::outpostCommando())) return false;
	if (!loadTexture(TileNames::outpostAnnihilator())) return false;
	if (!loadTexture(TileNames::outpostBrawler())) return false;

	//	Loading Hegemony Unit tiles
	if (!loadTexture(TileNames::hegemonyThug())) return false;
	if (!loadTexture(TileNames::hegemonyGanger())) return false;
	if (!loadTexture(TileNames::hegemonyGladiator())) return false;
	if (!loadTexture(TileNames::hegemonyNetFighter())) return false;
	if (!loadTexture(TileNames::hegemonyGuard())) return false;
	if (!loadTexture(TileNames::hegemonyUniversalSoldier())) return false;
	if (!loadTexture(TileNames::hegemonyNetMaster())) return false;

	//	Loading Moloch Unit tiles
	if (!loadTexture(TileNames::molochBlocker())) return false;
	if (!loadTexture(TileNames::molochHybrid())) return false;
	if (!loadTexture(TileNames::molochGaussCannon())) return false;
	if (!loadTexture(TileNames::molochJuggernaut())) return false;
	if (!loadTexture(TileNames::molochHunterKiller())) return false;
	if (!loadTexture(TileNames::molochProtector())) return false;
	if (!loadTexture(TileNames::molochArmouredHunter())) return false;
	if (!loadTexture(TileNames::molochArmouredGuard())) return false;
	if (!loadTexture(TileNames::molochGuard())) return false;
	if (!loadTexture(TileNames::molochHornet())) return false;
	if (!loadTexture(TileNames::molochNetFighter())) return false;
	
	//	Loading Doomsday Unit tiles
	if (!loadTexture(TileNames::doomsdayAlphaShooter())) return false;
	if (!loadTexture(TileNames::doomsdayGaussCannon())) return false;
	if (!loadTexture(TileNames::doomsdayDeltaShooter())) return false;
	if (!loadTexture(TileNames::doomsdayOmegaShooter())) return false;

	//	Loading Borgo Unit tiles
	if (!loadTexture(TileNames::borgoMutant())) return false;
	if (!loadTexture(TileNames::borgoClaws())) return false;
	if (!loadTexture(TileNames::borgoNetFighter())) return false;
	if (!loadTexture(TileNames::borgoSuperMutant())) return false;
	if (!loadTexture(TileNames::borgoBrawler())) return false;

	//	Loading font
	if (!_font.loadFromFile("comic.ttf"))
	{
		std::cout << "Unable to load font." << std::endl;
		return false;
	}

	return true;
}

bool Game::loadTexture(std::string textureName)
{
	sf::Texture *texture = new sf::Texture();
	if (texture->loadFromFile(kImageDirectory + textureName + kImageExtension))
	{
		_textures.addReference(textureName, texture);
		return true;
	}
	else
	{
		std::cout << "Unable to load texture " << textureName << std::endl;
		return false;
	}
}

void Game::update()
{
	//	Switch state
	//	Use appropriate function
	switch(_phase)
	{
	case Phase::Standby:
		updateStandbyPhase();
		break;
	case Phase::Draw:
		updateDrawPhase();
		break;
	case Phase::Discard:
		updateDiscardPhase();
		break;
	case Phase::Play:
		updatePlayPhase();
		break;
	case Phase::End:
		updateEndPhase();
		break;
	case Phase::ChooseLocation:
		updateChooseLocationPhase();
		break;
	case Phase::PlaceTile:
		updatePlaceTilePhase();
		break;
	case Phase::RotateTile:
		updateRotateTilePhase();
		break;
	case Phase::Battle:
		updateBattlePhase();
		break;
	case Phase::Start:
		updateStartPhase();
		break;
	case Phase::SelectFaction:
		updateSelectFactionPhase();
		break;
	case Phase::SelectStartingPosition:
		updateSelectStartingPositionPhase();
		break;
	}

	updateInput();
}

void Game::updateInput()
{
	_prevMouse = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void Game::updateStartPhase()
{
	//	Check if player number clicked
	int playerSelected = playerSelectClicked();
	if (playerSelected != -1)
	{
		//	If so then switch phase to Standby.
		_playerNumber = playerSelected + 2;
		switchPhase(Phase::SelectFaction);
		//initialiseGame();
	}
}

void Game::updateSelectFactionPhase()
{
	int factionSelected = selectFactionClicked();

	static bool selectedFaction[5] = {
		false, false, false, false, false };
	bool validSelection = false;

	if (factionSelected != -1)
	{
		Player *player;
		switch (factionSelected)
		{
		case 0:
			if (selectedFaction[0] == false)
			{
				selectedFaction[0] = true;
				player = new Player(DeckGenerator::outpostDeck());
				player->setFaction(Tile::Faction::Outpost);
				validSelection = true;
			}
			break;
		case 1:
			if (selectedFaction[1] == false)
			{
				selectedFaction[1] = true;
				player = new Player(DeckGenerator::hegemonyDeck());
				player->setFaction(Tile::Faction::Hegemony);
				validSelection = true;
			}
			break;
		case 2:
			if (selectedFaction[2] == false)
			{
				selectedFaction[2] = true;
				player = new Player(DeckGenerator::molochDeck());
				player->setFaction(Tile::Faction::Moloch);
				validSelection = true;
			}
			break;
		case 3:
			if (selectedFaction[3] == false)
			{
				selectedFaction[3] = true;
				player = new Player(DeckGenerator::doomsdayDeck());
				player->setFaction(Tile::Faction::Doomsday);
				validSelection = true;
			}
			break;
		case 4:
			if (selectedFaction[4] == false)
			{
				selectedFaction[4] = true;
				player = new Player(DeckGenerator::borgoDeck());
				player->setFaction(Tile::Faction::Borgo);
				validSelection = true;
			}
			break;
		}

		if (validSelection == true)
		{
			Deck *deck = player->getDeck();
			deck->shuffle();
			deck->move(850.0f, 0.0f + deck->getRadius());
			player->getHand()->setPosition(sf::Vector2f(850.0f, 200.0f + deck->getRadius()));
		
			_players.push_back(player);

			_playerCounter++;
		}
	}

	if (_playerCounter == _playerNumber)
	{
		_playerCounter = 0;
		initialiseGame();
		switchPhase(Phase::SelectStartingPosition);
	}
}

void Game::updateSelectStartingPositionPhase()
{
	//	Select starting position
	if (boardClicked())
	{
		sf::Vector2u lcbt = _lastClickedBoardTile;
		//	Check if tile
		if (_board.isEmpty(lcbt.x, lcbt.y))
		{
			//	Get player faction
			Tile::Faction faction = _players[_playerCounter]->getFaction();
			switch (faction)
			{
			case Tile::Faction::Outpost:
				placeTile(lcbt.x, lcbt.y, HexTile(TileGenerator::outpostHeadQuarters()));
				break;
			case Tile::Faction::Hegemony:
				placeTile(lcbt.x, lcbt.y, HexTile(TileGenerator::hegemonyHeadQuarters()));
				break;
			case Tile::Faction::Moloch:
				placeTile(lcbt.x, lcbt.y, HexTile(TileGenerator::molochHeadQuarters()));
				break;
			case Tile::Faction::Doomsday:
				placeTile(lcbt.x, lcbt.y, HexTile(TileGenerator::doomsdayHeadQuarters()));
				break;
			case Tile::Faction::Borgo:
				placeTile(lcbt.x, lcbt.y, HexTile(TileGenerator::borgoHeadQuarters()));
				break;
			}

			_playerCounter++;
		}
	}

	//	Check if finished
	if (_playerCounter == _playerNumber)
	{
		_playerCounter = 0;
		switchPhase(Phase::Standby);
	}
}

void Game::updateStandbyPhase()
{
	updateText();
	switchPhase(Phase::Draw);
}

void Game::updateDrawPhase()
{
	//	Click on deck until hand limit reached
	if (deckClicked())
	{
		if (_currentPlayer->getDeck()->isEmpty() == false)
		{
			std::cout << "Deck is not empty." << std::endl;

			Hand *hand = _currentPlayer->getHand();
			hand->addTile(_currentPlayer->getDeck()->draw());
			sf::Texture *texture = _textures.getResource(hand->getTile(hand->size() - 1)->getTile().getName());
			hand->getTile(hand->size() - 1)->setTexture(texture);
			hand = hand;
		}
		else
		{
			std::cout << "Deck is empty!" << std::endl;
		}
	}
	//	Click continue
	if (_currentPlayer->getHand()->size() >= Hand::handSize())
	{
		_drawContinueButton = true;
		if (continueClicked() == true)
		{
			std::cout << "Hand size limit reached, switching to Discard phase." << std::endl;
			_drawContinueButton = false;
			switchPhase(Phase::Discard);
		}
	}
}

void Game::updateDiscardPhase()
{
	//	Select tiles to discard
	if (handClicked() == true)
	{
		if (_currentPlayer->getHand()->size() > 1)
			_currentPlayer->getHand()->removeTile(_lastClickedHandTile);
	}
	//	Then click continue
	if (_currentPlayer->getHand()->size() < Hand::handSize())
	{
		//	If continue clicked go to Play phase
		_drawContinueButton = true;
		if (continueClicked() == true)
		{
			std::cout << "Exiting Discard Phase." << std::endl;
			_drawContinueButton = false;
			switchPhase(Phase::Play);
		}
	}
}

void Game::updatePlayPhase()
{
	if (_tilePlayed == true)
	{
		_drawContinueButton = true;
		if (continueClicked() == true)
		{
			_tilePlayed = false;
			_drawContinueButton = false;
			switchPhase(Phase::End);
		}
	}
	//	Select a tile to play
	if (handClicked() == true)
	{
		//	Resolve tile placement
		Tile::Type type = _currentPlayer->getHand()->getTile(_lastClickedHandTile)->getTile().getType();

		if (type == Tile::Type::Unit)
		{
			//	If "place" tile
			//	Push phase and go to "place tile" phase
			switchPhase(Phase::PlaceTile);
		}
		//	If "play" tile
		else if(type == Tile::Type::Play)
		{
			//	Resolve tile play as appropriate
			Tile::PlayType playType = _currentPlayer->getHand()->getTile(_lastClickedHandTile)->getTile().getPlayType();
			_currentPlayer->getHand()->removeTile(_lastClickedHandTile);
			_tilePlayed = true;

			switch (playType)
			{
			case Tile::PlayType::Battle:
				switchPhase(Phase::Battle);
				break;
			case Tile::PlayType::AirStrike:
				_resolvingPlayTile = playType;
				switchPhase(Phase::ChooseLocation);
				break;
			case Tile::PlayType::Snipe:
				_resolvingPlayTile = playType;
				switchPhase(Phase::ChooseLocation);
				break;
			case Tile::PlayType::Move:
				_resolvingPlayTile = playType;
				switchPhase(Phase::ChooseLocation);
				break;
			}
		}
	}
}

void Game::updateEndPhase()
{
	//	Check if only one player remains
	unsigned playersRemaining = 0;
	for (unsigned i = 0; i < _playerNumber; i++)
	{
		if (_players[i]->isDead() == false)
		{
			playersRemaining++;
		}
	}

	if (playersRemaining <= 1)
	{
		//	Find remaining player
		for (unsigned i = 0; i < _playerNumber; i++)
		{
			if (_players[i]->isDead() == false)
			{
				//	This player wins
				std::cout << "Player " << i << " is the winner!" << std::endl;
				break;
			}
		}
	}

	//	Switch player
	_playerCounter++;
	_playerCounter %= _playerNumber;
	_currentPlayer = _players[_playerCounter];

	while (_phaseStack.empty() == false)
		_phaseStack.pop();

	switchPhase(Phase::Standby);
}

void Game::updateChooseLocationPhase()
{
	if (boardClicked())
	{
		sf::Vector2u lcbt = _lastClickedBoardTile;
		std::cout << "Location " << lcbt.x << ", " << lcbt.y << " selected." << std::endl;
		switch (_resolvingPlayTile)
		{
		case Tile::PlayType::Null:
			revertPhase();
			break;
		case Tile::PlayType::Move:
			//	If clicked tile matches player faction switch to place tile phase
			if (_board.isEmpty(lcbt.x, lcbt.y) == true) break;
			if (_tiles[lcbt.x][lcbt.y].getTile().getFaction() != _currentPlayer->getFaction()) break;

			//	Store tile position
			_moveTileStartPosition = lcbt;

			//	Switch to place tile phase
			switchPhase(Phase::PlaceTile);
			break;
		case Tile::PlayType::Snipe:
			//	Check if location is occupied
			if (_board.isEmpty(lcbt.x, lcbt.y) == false)
			{
				//	Check if location is enemy
				if (_tiles[lcbt.x][lcbt.y].getTile().getFaction() != _currentPlayer->getFaction())
				{
					//	Check it's not an HQ
					if (_tiles[lcbt.x][lcbt.y].getTile().getType() == Tile::Type::Unit)
					{
						_tiles[lcbt.x][lcbt.y].getTile().applyWounds(1);
						if (_tiles[lcbt.x][lcbt.y].getTile().resolveWounds() == true)
						{
							removeTile(lcbt.x, lcbt.y);
						}
						revertPhase();
					}
				}
			}
			break;
		case Tile::PlayType::AirStrike:
			//	Click a tile
			if (boardClicked() == true)
			{
				sf::Vector2u lcbt = _lastClickedBoardTile;
				bool valid = true;

				//	Check surrounding tiles
				for (unsigned i = 0; i < Tile::numberOfEdges(); i++)
				{
					//	Ensure none are invalid (non-edge tile)
					sf::Vector2u adjacent = _board.getAdjacent(lcbt.x, lcbt.y, i);

					if (_board.isValid(adjacent.x, adjacent.y) == false)
					{
						valid = false;
						break;
					}
				}
				
				//	Deal a wound to every non-HQ tile
				if (valid == true)
				{
					for (unsigned i = 0; i < Tile::numberOfEdges(); i++)
					{
						sf::Vector2u adjacent = _board.getAdjacent(lcbt.x, lcbt.y, i);
						if (_tiles[adjacent.x][adjacent.y].getTile().getType() == Tile::Type::Unit)
						{
							_tiles[adjacent.x][adjacent.y].getTile().applyWounds(1);
							if (_tiles[adjacent.x][adjacent.y].getTile().resolveWounds())
							{
								removeTile(adjacent.x, adjacent.y);
							}
						}
					}
				}
			}
			break;
		case Tile::PlayType::Battle:
			switchPhase(Phase::Battle);
			break;
		}
	}
}

void Game::updatePlaceTilePhase()
{
	if (_tilePlaced == true)
	{
		_tilePlaced = false;
		_resolvingPlayTile = Tile::PlayType::Null;
		revertPhase();
		if (_board.isFull() == true)
		{
			switchPhase(Phase::Battle);
		}
		return;
	}

	if (boardClicked() == true)
	{
		sf::Vector2u lcbt = _lastClickedBoardTile;
		if (_board.isEmpty(_lastClickedBoardTile.x, _lastClickedBoardTile.y) == true)
		{
			if (_resolvingPlayTile == Tile::PlayType::Move)
			{
				//	Check if tile lcbt is adjacent
				if (_board.areAdjacent(lcbt.x, lcbt.y, _moveTileStartPosition.x, _moveTileStartPosition.y) != -1)
				{
					_tileToPlace =  _tiles[lcbt.x][lcbt.y];
					placeTile(lcbt.x, lcbt.y, _tiles[_moveTileStartPosition.x][_moveTileStartPosition.y]);
					removeTile(_moveTileStartPosition.x, _moveTileStartPosition.y);
				}
				else
				{
					return;
				}
			}
			else
			{
				//	Remove tile from hand
				_tileToPlace = *_currentPlayer->getHand()->getTile(_lastClickedHandTile);
				_currentPlayer->getHand()->removeTile(_lastClickedHandTile);

				//	Place tile on board
				//_board.placeTile(lcbt.x, lcbt.y);
				_tiles[lcbt.x][lcbt.y].setTile(_tileToPlace.getTile());
				_tiles[lcbt.x][lcbt.y].setTexture(_textures.getResource(_tileToPlace.getTile().getName()));
			}

			//	Enter rotation phase
			switchPhase(Phase::RotateTile);
		}
	}
}

void Game::updateRotateTilePhase()
{
	//	Store last clicked board tile
	sf::Vector2u lcbt = _lastClickedBoardTile;

	_drawRotateTargets = true;

	//	Position rotation targets
	for (unsigned i = 0; i < _rotateTargets.size(); i++)
	{
		sf::Vector2f tilePos = _tiles[lcbt.x][lcbt.y].getPosition();
		float tileRadius = _tiles[lcbt.x][lcbt.y].getRadius();
		float pi = atan(1.0f) * 4.0f;
		_rotateTargets[i].setPosition(tilePos + sf::Vector2f(sin(i * pi / 3.0f + pi / 6.0f) * tileRadius,
															-cos(i * pi / 3.0f + pi / 6.0f) * tileRadius));
	}

	int rotateTarget = rotateTargetClicked();
	if (rotateTarget != -1)
	{
		_tileToPlace.setRotation(rotateTarget);
		placeTile(_lastClickedBoardTile.x, _lastClickedBoardTile.y, _tileToPlace);
		_tilePlaced = true;
		_drawRotateTargets = false;
		_tilePlayed = true;
		revertPhase();
	}

	_lastClickedBoardTile = lcbt;
}

void Game::updateBattlePhase()
{

	//	If Battle phase is first being initiated
	if (_currentInitiative == -1)
	{
		//	Get highest initiative
		for (unsigned i = 0; i < _tiles.size(); i++)
		{
			for (unsigned j = 0; j < _tiles[i].size(); j++)
			{
				if (_board.isValid(i, j) == false) continue;
				std::cout << _tiles[i][j].getTile().getInitiative() << std::endl;
				if ((int)_tiles[i][j].getTile().getInitiative() > _currentInitiative)
				{
					_currentInitiative = _tiles[i][j].getTile().getInitiative();
				}
			}
		}
		std::cout << "Highest initiative is: " << _currentInitiative << std::endl;
	}

	_drawContinueButton = true;
	if (_continueBattlePhase == true)
	{
		_continueBattlePhase = false;

		std::cout << "Current initiative is: " << _currentInitiative << std::endl;
		//	For every tile of current initiative
		for (unsigned i = 0; i < _tiles.size(); i++)
		{
			for (unsigned j = 0; j < _tiles[i].size(); j++)
			{
				if (_board.isValid(i, j) == true)
				{
					if (_board.isEmpty(i, j) == false)
					{
						if (_tiles[i][j].getTile().getInitiative() == _currentInitiative)
						{
							std::cout << "Tile " << i << ", " << j << " can attack." << std::endl;

							//	Apply wounds

							//	For each edge, handle ranged, melee laser, etc
							Edge edge;
							for (unsigned k = 0; k < Tile::numberOfEdges(); k++)
							{
								edge = _tiles[i][j].getEdge(i, false);
								sf::Vector2u adjacent = _board.getAdjacent(i, j, k);
								//	If adjacent is invalid then continue
								if (_board.isValid(adjacent.x, adjacent.y) == false) continue;

								Tile::Faction tileFaction = _tiles[i][j].getTile().getFaction();
							
								//	If edge has melee
								if (edge.hasMelee() > 0)
								{
									if (_board.isEmpty(adjacent.x, adjacent.y) == false)
									{
										//	Check if neighbour is of opposing faction
										if (tileFaction != _tiles[adjacent.x][adjacent.y].getTile().getFaction())
										{
											//	If unit damage unit
											//	If HQ damage corresponding player
											switch (_tiles[adjacent.x][adjacent.y].getTile().getType())
											{
											case Tile::Type::Unit:
												_tiles[adjacent.x][adjacent.y].getTile().applyWounds(edge.hasMelee());
												break;
											case Tile::Type::HeadQuarters:
												damagePlayer(_tiles[adjacent.x][adjacent.y].getTile().getFaction(), edge.hasMelee());
												break;
											}
										}
									}
								}

								//	If edge has ranged
								if (edge.hasShot() > 0)
								{
									sf::Vector2u aligned = adjacent;
									while (_board.isValid(aligned.x, aligned.y) == true)
									{
										if (_board.isEmpty(aligned.x, aligned.y) == true) continue;

										if (tileFaction != _tiles[aligned.x][aligned.y].getTile().getFaction())
										{
											if (_tiles[aligned.x][aligned.y].getEdge((i + 3) % 6, false).hasArmour()) break;

											switch (_tiles[aligned.x][aligned.y].getTile().getType())
											{
											case Tile::Type::Unit:
												_tiles[aligned.x][aligned.y].getTile().applyWounds(edge.hasShot());
												break;
											case Tile::Type::HeadQuarters:
												damagePlayer(_tiles[aligned.x][aligned.y].getTile().getFaction(), edge.hasShot());
												break;
											}
										}

										aligned = _board.getAdjacent(aligned.x, aligned.y, i);
									}
								}

								//	If edge has laser
								if (edge.hasLaser() == true)
								{
									//	While adjacent is valid
									sf::Vector2u aligned = adjacent;
									while (_board.isValid(aligned.x, aligned.y) == true)
									{
										if (_board.isEmpty(aligned.x, aligned.y) == true) continue;
										
										//	Damage tile if not ally or HQ
										if (tileFaction != _tiles[aligned.x][aligned.y].getTile().getFaction())
										{
											switch (_tiles[aligned.x][aligned.y].getTile().getType())
											{
											case Tile::Type::Unit:
												_tiles[aligned.x][aligned.y].getTile().applyWounds(edge.hasShot());
												break;
											}
										}
										
										//	Update aligned
										aligned = _board.getAdjacent(aligned.x, aligned.y, i);
									}
								}
							}
						}
					}
				}
			}
		}

		//	Resolve wounds
		for (unsigned i = 0; i < _tiles.size(); i++)
		{
			for (unsigned j = 0; j < _tiles[i].size(); j++)
			{
				if (_board.isValid(i, j) == false) continue;
				if (_board.isEmpty(i, j) == true) continue;
				
				if (_tiles[i][j].getTile().resolveWounds() == true)
				{
					removeTile(i, j);
				}
			}
		}

	}

	//	Click continue
	if (continueClicked() == true)
	{
		_currentInitiative -= 1;
		_continueBattlePhase = true;

		if (_currentInitiative == -1)
		{
			_drawContinueButton = false;
			revertPhase();
		}
	}
}

void Game::damagePlayer(Tile::Faction faction, unsigned damage)
{
	//	Check players for corresponding faction
	for (unsigned i = 0; i < _playerNumber; i++)
	{
		if (_players[i]->getFaction() == faction)
		{
			_players[i]->removeHealth(damage);
		}
	}
}

int Game::playerSelectClicked()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !_prevMouse)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
		for (unsigned i = 0; i < _playerSelectButtons.size(); i++)
		{
			if (_playerSelectButtons[i].clicked(mousePos.x, mousePos.y))
			{
				return i;
			}
		}
	}

	return -1;
}

int Game::selectFactionClicked()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !_prevMouse)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
		for (unsigned i = 0; i < kFactionNumber; i++)
		{
			if (_factionButtons[i].clicked(mousePos.x, mousePos.y))
			{
				return i;
			}
		}
	}

	return -1;
}

bool Game::boardClicked()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !_prevMouse)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
		
		//	Check if it clicked on a board tile
		for(unsigned i = 0; i < _tiles.size(); i++)
		{
			for(unsigned j = 0; j < _tiles[i].size(); j++)
			{
				if (_board.isValid(i, j) == false) continue;
				if (_tiles[i][j].clicked(mousePos.x, mousePos.y))
				{
					std::cout << "Board clicked!" << std::endl;
					_lastClickedBoardTile = sf::Vector2u(i, j);
					return true;
				}
			}
		}
	}

	return false;
}

bool Game::deckClicked()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !_prevMouse)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
		if (_currentPlayer->getDeck()->clicked(mousePos.x, mousePos.y))
		{
			std::cout << "Deck clicked!" << std::endl;
			return true;
		}
	}

	return false;
}

bool Game::handClicked()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !_prevMouse)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
		for (unsigned i = 0; i < _currentPlayer->getHand()->size(); i++)
		{
			if (_currentPlayer->getHand()->getTile(i)->clicked(mousePos.x, mousePos.y))
			{
				std::cout << "Hand " << i << " clicked!" << std::endl;
				_lastClickedHandTile = i;
				return true;
			}
		}
	}

	return false;
}

int Game::rotateTargetClicked()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !_prevMouse)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
		for (unsigned i = 0; i < _rotateTargets.size(); i++)
		{
			if (_rotateTargets[i].clicked(mousePos.x, mousePos.y))
			{
				return i;
			}
		}
	}

	return -1;
}

bool Game::continueClicked()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !_prevMouse)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
		if (_continueButton.clicked(mousePos.x, mousePos.y))
		{
			std::cout << "Continue clicked!" << std::endl;
			return true;
		}
	}

	return false;
}

void Game::placeTile(unsigned x, unsigned y, HexTile tile)
{
	if (_board.isValid(x, y) == false) return;
	if (_board.isEmpty(x, y) == false) return;

	_board.placeTile(x, y);
	_tiles[x][y].setRotation(tile.getRotation());
	_tiles[x][y].setTexture(_textures.getResource(tile.getTile().getName()));
}

void Game::removeTile(unsigned x, unsigned y)
{
	if (_board.isValid(x, y) == false) return;
	if (_board.isEmpty(x, y) == true) return;

	_board.removeTile(x, y);
	_tiles[x][y].setRotation(0);
	_tiles[x][y].setTexture(_textures.getResource("Hex Default"));
}

void Game::switchPhase(Phase phase)
{
	//	Depending on phase, push to stack or empty stack
	switch (phase)
	{
	case Phase::PlaceTile:
		_phaseStack.push(_phase);
		break;
	case Phase::RotateTile:
		_phaseStack.push(_phase);
		break;
	case Phase::Battle:
		_phaseStack.push(_phase);
		break;
	case Phase::ChooseLocation:
		_phaseStack.push(_phase);
	}

	_phase = phase;

	updateTutorialText();

	std::cout << "Now in phase: " << _phase << std::endl;
}

void Game::revertPhase()
{
	if (_phaseStack.empty() == false)
	{
		_phase = _phaseStack.top();
		_phaseStack.pop();
	}

	updateTutorialText();
	
	std::cout << "Now in phase: " << _phase << std::endl;

	if (_phase == Phase::ChooseLocation)
	{
		revertPhase();
	}
}

void Game::updateText()
{
	updatePlayerText();
	updateHealthText();
	updateTutorialText();
}

void Game::updateTutorialText()
{
	switch (_phase)
	{
	case Phase::Start:
		_tutorialText.setString(kStartPhaseTutorialText);
		break;
	case Phase::Standby:

		break;
	case Phase::Draw:
		_tutorialText.setString(kDrawPhaseTutorialText);
		break;
	case Phase::Discard:
		_tutorialText.setString(kDiscardPhaseTutorialText);
		break;
	case Phase::Play:
		_tutorialText.setString(kPlayPhaseTutorialText);
		break;
	case Phase::PlaceTile:
		_tutorialText.setString(kPlaceTilePhaseTutorialText);
		break;
	case Phase::RotateTile:
		_tutorialText.setString(kRotateTilePhaseTutorialText);
		break;
	case Phase::ChooseLocation:
		_tutorialText.setString(kChooseLocationPhaseTutorialText);
		break;
	}
}

void Game::updatePlayerText()
{
	std::ostringstream text;
	text << "Player: " << _playerCounter + 1;
	_playerNumberDisplay.setString(text.str());
}

void Game::updateHealthText()
{
	std::ostringstream text;
	text << "Health: " << std::endl;
	for (unsigned i = 0; i < _players.size(); i++)
	{
		text << i + 1 << ": " << _players[i]->getHealth() << std::endl;
	}

	_playerHealthDisplay.setString(text.str());
}

void Game::draw()
{
	_window.clear();

	switch(_phase)
	{
	case Phase::Start:
		drawStartScreen();
		break;
	case Phase::SelectFaction:
		drawSelectFactionScreen();
		break;
	default:
		drawGameScreen();
	}

	_window.draw(_tutorialText);

	_window.display();
}

void Game::drawStartScreen()
{
	for (unsigned i = 0; i < _playerSelectButtons.size(); i++)
	{
		_window.draw(_playerSelectButtons[i]);
	}
}

void Game::drawSelectFactionScreen()
{
	for (unsigned i = 0; i < kFactionNumber; i++)
	{
		_window.draw(_factionButtons[i]);
	}
}

void Game::drawGameScreen()
{
	drawBoard();
	drawDeck();
	drawHand();

	if (_drawContinueButton == true)
		_window.draw(_continueButton);
	
	if (_drawRotateTargets == true)
	{
		for (unsigned i = 0; i < _rotateTargets.size(); i++)
		{
			_window.draw(_rotateTargets[i]);
		}
	}

	_window.draw(_playerNumberDisplay);
	_window.draw(_playerHealthDisplay);
}

void Game::drawBoard()
{
	for (unsigned i = 0; i < _board.getWidth(); i++)
	{
		for (unsigned j = 0; j < _board.getHeight(); j++)
		{
			//	If so, draw the tile
			if (_board.isValid(i, j))
			{
				_window.draw(_tiles[i][j]);
			}
		}
	}
}

void Game::drawDeck()
{
	//	Draw appropriate tile at position
	_window.draw(*_currentPlayer->getDeck());
}

void Game::drawHand()
{
	//	For each tile in hand
	for (unsigned i = 0; i < _currentPlayer->getHand()->size(); i++)
	{
		//	Draw it
		_window.draw(*(_currentPlayer->getHand()->getTile(i)));
	}
}