#include "DeckGenerator.hpp"

#include "TileGenerator.hpp"

Deck *DeckGenerator::outpostDeck()
{
	Deck *deck = new Deck();

	unsigned i = 0;
	for (i = 0; i < 7; i++) deck->addTile(TileGenerator::outpostCommando());
	for (i = 0; i < 2; i++) deck->addTile(TileGenerator::outpostAnnihilator());
	for (i = 0; i < 3; i++) deck->addTile(TileGenerator::outpostBrawler());

	for (i = 0; i < 8; i++) deck->addTile(TileGenerator::battle());
	for (i = 0; i < 9; i++) deck->addTile(TileGenerator::move());
	for (i = 0; i < 3; i++) deck->addTile(TileGenerator::sniper());

	return deck;
}

Deck *DeckGenerator::hegemonyDeck()
{
	Deck *deck = new Deck();

	unsigned i = 0;
	for (i = 0; i < 3; i++) deck->addTile(TileGenerator::hegemonyThug());
	for (i = 0; i < 6; i++) deck->addTile(TileGenerator::hegemonyGanger());
	for (i = 0; i < 3; i++) deck->addTile(TileGenerator::hegemonyGladiator());
	for (i = 0; i < 4; i++) deck->addTile(TileGenerator::hegemonyNetFighter());
	for (i = 0; i < 3; i++) deck->addTile(TileGenerator::hegemonyGuard());
	for (i = 0; i < 4; i++) deck->addTile(TileGenerator::hegemonyUniversalSoldier());
	for (i = 0; i < 2; i++) deck->addTile(TileGenerator::hegemonyNetMaster());

	for (i = 0; i < 5; i++) deck->addTile(TileGenerator::battle());
	for (i = 0; i < 3; i++) deck->addTile(TileGenerator::move());
	deck->addTile(TileGenerator::sniper());

	return deck;
}

Deck *DeckGenerator::molochDeck()
{
	Deck *deck = new Deck();

	unsigned i = 0;
	for (i = 0; i < 4; i++) deck->addTile(TileGenerator::molochBlocker());
	for (i = 0; i < 4; i++) deck->addTile(TileGenerator::molochHybrid());
	for (i = 0; i < 2; i++) deck->addTile(TileGenerator::molochGaussCannon());
	for (i = 0; i < 2; i++) deck->addTile(TileGenerator::molochJuggernaut());
	for (i = 0; i < 3; i++) deck->addTile(TileGenerator::molochHunterKiller());
	for (i = 0; i < 2; i++) deck->addTile(TileGenerator::molochProtector());
	for (i = 0; i < 3; i++) deck->addTile(TileGenerator::molochArmouredHunter());
	for (i = 0; i < 2; i++) deck->addTile(TileGenerator::molochArmouredGuard());
	for (i = 0; i < 2; i++) deck->addTile(TileGenerator::molochGuard());
	for (i = 0; i < 2; i++) deck->addTile(TileGenerator::molochHornet());
	for (i = 0; i < 2; i++) deck->addTile(TileGenerator::molochNetFighter());

	deck->addTile(TileGenerator::airStrike());
	for (i = 0; i< 4; i++) deck->addTile(TileGenerator::battle());
	deck->addTile(TileGenerator::move());

	return deck;
}

Deck *DeckGenerator::doomsdayDeck()
{
	Deck *deck = new Deck();

	unsigned i = 0;
	for (i = 0; i < 7; i++) deck->addTile(TileGenerator::doomsdayAlphaShooter());
	for (i = 0; i < 6; i++) deck->addTile(TileGenerator::doomsdayGaussCannon());
	for (i = 0; i < 5; i++) deck->addTile(TileGenerator::doomsdayDeltaShooter());
	for (i = 0; i < 8; i++) deck->addTile(TileGenerator::doomsdayOmegaShooter());

	for (i = 0; i < 8; i++) deck->addTile(TileGenerator::battle());

	return deck;
}

Deck *DeckGenerator::borgoDeck()
{
	Deck *deck = new Deck();

	unsigned i = 0;
	for (i = 0; i < 8; i++) deck->addTile(TileGenerator::borgoMutant());
	for (i = 0; i < 6; i++) deck->addTile(TileGenerator::borgoClaws());
	for (i = 0; i < 4; i++) deck->addTile(TileGenerator::borgoNetFighter());
	for (i = 0; i < 3; i++) deck->addTile(TileGenerator::borgoSuperMutant());
	for (i = 0; i < 3; i++) deck->addTile(TileGenerator::borgoBrawler());

	for (i = 0; i < 6; i++) deck->addTile(TileGenerator::battle());
	for (i = 0; i < 4; i++) deck->addTile(TileGenerator::move());

	return deck;
}