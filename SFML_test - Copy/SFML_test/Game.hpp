#ifndef GAME_HPP
#define GAME_HPP

#include "Application.hpp"
#include "ResourceManager.hpp"
#include "Board.hpp"
#include "Hand.hpp"
#include "Deck.hpp"
#include "Button.hpp"
#include "Player.hpp"

#include <stack>
#include <vector>
#include <SFML/Graphics.hpp>

class Game : public Application
{

public:
	Game(unsigned width, unsigned height, std::string title);
	~Game();

	void initialise();

private:
	enum Phase { Null, Standby, Draw, Discard, Play, End,
				 ChooseLocation, PlaceTile, RotateTile, Battle,
				 Start, SelectFaction, SelectStartingPosition };

	ResourceManager<sf::Texture> _textures;
	Phase _phase;
	std::stack<Phase> _phaseStack;

	Board _board;
	std::vector<std::vector<HexTile> > _tiles;

	unsigned _playerNumber;
	std::vector<Player *> _players;
	Player *_currentPlayer;
	unsigned _playerCounter;

	std::vector<Button> _factionButtons;

	bool _prevMouse;

	sf::Vector2u _lastClickedBoardTile;
	unsigned _lastClickedHandTile;

	Button _continueButton;
	bool _drawContinueButton;
	HexTile _tileToPlace;
	bool _tilePlaced;
	bool _tilePlayed;
	Tile::PlayType _resolvingPlayTile;
	sf::Vector2u _moveTileStartPosition;

	int _currentInitiative;
	bool _continueBattlePhase;

	bool _drawRotateTargets;
	std::vector<HexTile> _rotateTargets;

	std::vector<HexTile> _playerSelectButtons;

	sf::Font _font;
	sf::Text _tutorialText;
	sf::Text _playerHealthDisplay;
	sf::Text _playerNumberDisplay;

protected:

	void initialiseGame();

	bool loadAssets();
	bool loadTexture(std::string textureName);

	void update();

	void updateInput();

	void updateStartPhase();
	void updateSelectFactionPhase();
	void updateSelectStartingPositionPhase();

	void updateStandbyPhase();
	void updateDrawPhase();
	void updateDiscardPhase();
	void updatePlayPhase();
	void updateEndPhase();
	void updateChooseLocationPhase();
	void updatePlaceTilePhase();
	void updateRotateTilePhase();
	void updateBattlePhase();

	void damagePlayer(Tile::Faction faction, unsigned damage);

	void updateText();
	void updateTutorialText();
	void updatePlayerText();
	void updateHealthText();

	int playerSelectClicked();
	int selectFactionClicked();
	bool boardClicked();
	bool deckClicked();
	bool handClicked();
	int rotateTargetClicked();
	bool continueClicked();

	void placeTile(unsigned x, unsigned y, HexTile tile);
	void removeTile(unsigned x, unsigned y);

	void switchPhase(Phase phase);
	void revertPhase();

	void draw();

	void drawStartScreen();
	void drawSelectFactionScreen();
	void drawGameScreen();

	void drawBoard();
	void drawDeck();
	void drawHand();
};

#endif