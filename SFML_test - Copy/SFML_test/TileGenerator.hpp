#pragma once

#include "Tile.hpp"

class TileGenerator
{
public:
	static Tile blankTile();

	static Tile outpostHeadQuarters();
	static Tile hegemonyHeadQuarters();
	static Tile molochHeadQuarters();
	static Tile doomsdayHeadQuarters();
	static Tile borgoHeadQuarters();

	static Tile battle();
	static Tile move();
	static Tile sniper();
	static Tile airStrike();

	static Tile outpostCommando();
	static Tile outpostAnnihilator();
	static Tile outpostBrawler();

	static Tile hegemonyThug();
	static Tile hegemonyGanger();
	static Tile hegemonyGladiator();
	static Tile hegemonyNetFighter();
	static Tile hegemonyGuard();
	static Tile hegemonyUniversalSoldier();
	static Tile hegemonyNetMaster();

	static Tile molochBlocker();
	static Tile molochHybrid();
	static Tile molochGaussCannon();
	static Tile molochJuggernaut();
	static Tile molochHunterKiller();
	static Tile molochProtector();
	static Tile molochArmouredHunter();
	static Tile molochArmouredGuard();
	static Tile molochGuard();
	static Tile molochHornet();
	static Tile molochNetFighter();

	static Tile doomsdayAlphaShooter();
	static Tile doomsdayGaussCannon();
	static Tile doomsdayDeltaShooter();
	static Tile doomsdayOmegaShooter();

	static Tile borgoMutant();
	static Tile borgoClaws();
	static Tile borgoNetFighter();
	static Tile borgoSuperMutant();
	static Tile borgoBrawler();
};