#include "TileGenerator.hpp"

Tile TileGenerator::blankTile()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::None, "Default");

	return tile;
}

Tile TileGenerator::outpostHeadQuarters()
{
	Tile tile(Tile::Type::HeadQuarters, Tile::PlayType::Null, Tile::Faction::Outpost, "outpost_HQ");
	tile.setInitiative(0);

	tile.setEdge(Edge(false, 0, 1, 0, false), 0);
	tile.setEdge(Edge(false, 0, 1, 0, false), 1);
	tile.setEdge(Edge(false, 0, 1, 0, false), 2);
	tile.setEdge(Edge(false, 0, 1, 0, false), 3);
	tile.setEdge(Edge(false, 0, 1, 0, false), 4);
	tile.setEdge(Edge(false, 0, 1, 0, false), 5);

	return tile;
}

Tile TileGenerator::hegemonyHeadQuarters()
{
	Tile tile(Tile::Type::HeadQuarters, Tile::PlayType::Null, Tile::Faction::Hegemony, "hegemony_HQ");
	tile.setInitiative(0);

	tile.setEdge(Edge(false, 0, 1, 0, false), 0);
	tile.setEdge(Edge(false, 0, 1, 0, false), 1);
	tile.setEdge(Edge(false, 0, 1, 0, false), 2);
	tile.setEdge(Edge(false, 0, 1, 0, false), 3);
	tile.setEdge(Edge(false, 0, 1, 0, false), 4);
	tile.setEdge(Edge(false, 0, 1, 0, false), 5);

	return tile;
}

Tile TileGenerator::molochHeadQuarters()
{
	Tile tile(Tile::Type::HeadQuarters, Tile::PlayType::Null, Tile::Faction::Moloch, "moloch_HQ");
	tile.setInitiative(0);

	tile.setEdge(Edge(false, 0, 1, 0, false), 0);
	tile.setEdge(Edge(false, 0, 1, 0, false), 1);
	tile.setEdge(Edge(false, 0, 1, 0, false), 2);
	tile.setEdge(Edge(false, 0, 1, 0, false), 3);
	tile.setEdge(Edge(false, 0, 1, 0, false), 4);
	tile.setEdge(Edge(false, 0, 1, 0, false), 5);

	return tile;
}

Tile TileGenerator::doomsdayHeadQuarters()
{
	Tile tile(Tile::Type::HeadQuarters, Tile::PlayType::Null, Tile::Faction::Doomsday, "doomsday_HQ");
	tile.setInitiative(0);

	tile.setEdge(Edge(false, 0, 1, 0, false), 0);
	tile.setEdge(Edge(false, 0, 1, 0, false), 1);
	tile.setEdge(Edge(false, 0, 1, 0, false), 2);
	tile.setEdge(Edge(false, 0, 1, 0, false), 3);
	tile.setEdge(Edge(false, 0, 1, 0, false), 4);
	tile.setEdge(Edge(false, 0, 1, 0, false), 5);

	return tile;
}

Tile TileGenerator::borgoHeadQuarters()
{
	Tile tile(Tile::Type::HeadQuarters, Tile::PlayType::Null, Tile::Faction::Borgo, "borgo_HQ");
	tile.setInitiative(0);

	tile.setEdge(Edge(false, 0, 1, 0, false), 0);
	tile.setEdge(Edge(false, 0, 1, 0, false), 1);
	tile.setEdge(Edge(false, 0, 1, 0, false), 2);
	tile.setEdge(Edge(false, 0, 1, 0, false), 3);
	tile.setEdge(Edge(false, 0, 1, 0, false), 4);
	tile.setEdge(Edge(false, 0, 1, 0, false), 5);

	return tile;
}

Tile TileGenerator::battle()
{
	Tile tile(Tile::Type::Play, Tile::PlayType::Battle, Tile::Faction::None, "battle");

	return tile;
}

Tile TileGenerator::move()
{
	Tile tile(Tile::Type::Play, Tile::PlayType::Move, Tile::Faction::None, "move");

	return tile;
}

Tile TileGenerator::sniper()
{
	Tile tile(Tile::Type::Play, Tile::PlayType::Snipe, Tile::Faction::None, "sniper");

	return tile;
}

Tile TileGenerator::airStrike()
{
	Tile tile(Tile::Type::Play, Tile::PlayType::AirStrike, Tile::Faction::None, "air_strike");

	return tile;
}

Tile TileGenerator::outpostCommando()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Outpost, "outpost_commando");
	tile.setInitiative(3);
	
	tile.setEdge(Edge(false, 1, 0, false, false), 2);

	return tile;
}

Tile TileGenerator::outpostAnnihilator()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Outpost, "outpost_annihilator");
	tile.setInitiative(2);

	tile.setEdge(Edge(false, 2, 0, false, false), 4);

	return tile;
}

Tile TileGenerator::outpostBrawler()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Outpost, "outpost_brawler");
	tile.setInitiative(3);

	tile.setEdge(Edge(false, 0, 2, false, false), 0);

	return tile;
}

Tile TileGenerator::hegemonyThug()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Hegemony, "hegemony_thug");
	tile.setInitiative(2);

	tile.setEdge(Edge(false, 0, 2, false, false), 0);
	tile.setEdge(Edge(false, 0, 1, false, false), 1);
	tile.setEdge(Edge(false, 0, 1, false, false), 5);

	return tile;
}

Tile TileGenerator::hegemonyGanger()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Hegemony, "hegemony_ganger");
	tile.setInitiative(3);

	tile.setEdge(Edge(false, 0, 1, false, false), 5);

	return tile;
}

Tile TileGenerator::hegemonyGladiator()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Hegemony, "hegemony_gladiator");
	tile.setInitiative(1);
	tile.setShields(1);

	tile.setEdge(Edge(true, 0, 2, false, false), 0);
	tile.setEdge(Edge(true, 0, 2, false, false), 1);
	tile.setEdge(Edge(true, 0, 2, false, false), 5);

	return tile;
}

Tile TileGenerator::hegemonyNetFighter()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Hegemony, "hegemony_net_fighter");
	tile.setInitiative(0);

	tile.setEdge(Edge(true, 0, 0, false, false), 1);

	return tile;
}

Tile TileGenerator::hegemonyGuard()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Hegemony, "hegemony_guard");
	tile.setInitiative(2);
	tile.setShields(1);

	tile.setEdge(Edge(false, 0, 1, false, false), 0);
	tile.setEdge(Edge(false, 0, 1, false, false), 4);
	tile.setEdge(Edge(false, 0, 1, false, false), 5);

	return tile;
}

Tile TileGenerator::hegemonyUniversalSoldier()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Hegemony, "hegemony_universal_soldier");
	tile.setInitiative(3);

	tile.setEdge(Edge(false, 1, 1, false, false), 5);

	return tile;
}

Tile TileGenerator::hegemonyNetMaster()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Hegemony, "hegemony_net_master");
	tile.setInitiative(2);

	tile.setEdge(Edge(true, 0, 0, false, false), 2);
	tile.setEdge(Edge(false, 0, 1, false, false), 3);
	tile.setEdge(Edge(true, 0, 0, false, false), 4);

	return tile;
}

Tile TileGenerator::molochBlocker()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Moloch, "moloch_blocker");
	tile.setInitiative(0);
	tile.setShields(2);

	tile.setEdge(Edge(false, 0, 0, true, false), 0);

	return tile;
}

Tile TileGenerator::molochHybrid()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Moloch, "moloch_hybrid");
	tile.setInitiative(3);

	tile.setEdge(Edge(false, 1, 0, false, false), 0);

	return tile;
}

Tile TileGenerator::molochGaussCannon()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Moloch, "moloch_gauss_cannon");
	tile.setInitiative(1);
	tile.setShields(1);

	tile.setEdge(Edge(false, 0, 0, false, true), 0);

	return tile;
}

Tile TileGenerator::molochJuggernaut()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Moloch, "moloch_juggernaut");
	tile.setInitiative(1);
	tile.setShields(1);

	tile.setEdge(Edge(false, 0, 2, true, false), 0);
	tile.setEdge(Edge(false, 1, 0, false, false), 1);
	tile.setEdge(Edge(false, 0, 0, true, false), 2);
	tile.setEdge(Edge(false, 0, 0, true, false), 4);

	return tile;
}

Tile TileGenerator::molochHunterKiller()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Moloch, "moloch_hunter_killer");
	tile.setInitiative(3);

	tile.setEdge(Edge(false, 0, 1, false, false), 0);
	tile.setEdge(Edge(false, 0, 1, false, false), 1);
	tile.setEdge(Edge(false, 0, 1, false, false), 3);
	tile.setEdge(Edge(false, 0, 1, false, false), 5);

	return tile;
}

Tile TileGenerator::molochProtector()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Moloch, "moloch_protector");
	tile.setInitiative(1);
	tile.setShields(1);

	tile.setEdge(Edge(false, 1, 0, false, false), 0);
	tile.setEdge(Edge(false, 1, 0, false, false), 1);
	tile.setEdge(Edge(false, 1, 0, false, false), 5);

	return tile;
}

Tile TileGenerator::molochArmouredHunter()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Moloch, "moloch_armoured_hunter");
	tile.setInitiative(2);

	tile.setEdge(Edge(false, 0, 1, true, false), 0);
	tile.setEdge(Edge(false, 0, 1, false, false), 1);
	tile.setEdge(Edge(false, 0, 1, false, false), 2);
	tile.setEdge(Edge(false, 0, 1, false, false), 3);
	tile.setEdge(Edge(false, 0, 1, false, false), 4);
	tile.setEdge(Edge(false, 0, 1, true, false), 5);

	return tile;
}

Tile TileGenerator::molochArmouredGuard()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Moloch, "moloch_armoured_guard");
	tile.setInitiative(2);

	tile.setEdge(Edge(false, 0, 0, true, false), 0);
	tile.setEdge(Edge(false, 1, 0, false, false), 1);
	tile.setEdge(Edge(false, 1, 0, false, false), 5);

	return tile;
}

Tile TileGenerator::molochGuard()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Moloch, "moloch_guard");
	tile.setInitiative(2);

	tile.setEdge(Edge(false, 1, 0, false, false), 0);
	tile.setEdge(Edge(false, 1, 0, false, false), 5);

	return tile;
}

Tile TileGenerator::molochHornet()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Moloch, "moloch_hornet");
	tile.setInitiative(2);

	tile.setEdge(Edge(false, 0, 2, false, false), 0);

	return tile;
}

Tile TileGenerator::molochNetFighter()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Moloch, "moloch_net_fighter");
	tile.setInitiative(0);

	tile.setEdge(Edge(true, 0, 0, false, false), 0);
	tile.setEdge(Edge(true, 0, 0, false, false), 5);

	return tile;
}

Tile TileGenerator::doomsdayAlphaShooter()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Doomsday, "doomsday_alpha_shooter");
	tile.setInitiative(3);

	tile.setEdge(Edge(false, 1, 0, false, false), 1);
	tile.setEdge(Edge(false, 1, 0, false, false), 5);

	return tile;
}

Tile TileGenerator::doomsdayGaussCannon()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Doomsday, "doomsday_gauss_cannon");
	tile.setInitiative(1);
	tile.setShields(1);

	tile.setEdge(Edge(false, 0, 1, false, true), 0);

	return tile;
}

Tile TileGenerator::doomsdayDeltaShooter()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Doomsday, "doomsday_delta_shooter");
	tile.setInitiative(1);
	tile.setShields(1);

	tile.setEdge(Edge(false, 2, 0, false, false), 0);

	return tile;
}

Tile TileGenerator::doomsdayOmegaShooter()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Doomsday, "doomsday_omega_shooter");
	tile.setInitiative(2);

	tile.setEdge(Edge(false, 1, 0, false, false), 0);
	tile.setEdge(Edge(false, 1, 0, false, false), 1);
	tile.setEdge(Edge(false, 0, 0, true, false), 3);
	tile.setEdge(Edge(false, 1, 0, false, false), 5);

	return tile;
}

Tile TileGenerator::borgoMutant()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Borgo, "borgo_mutant");
	tile.setInitiative(2);

	tile.setEdge(Edge(false, 0, 1, false, false), 0);
	tile.setEdge(Edge(false, 0, 1, false, false), 1);
	tile.setEdge(Edge(false, 0, 1, false, false), 5);

	return tile;
}

Tile TileGenerator::borgoClaws()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Borgo, "borgo_claws");
	tile.setInitiative(3);

	tile.setEdge(Edge(false, 0, 1, false, false), 4);
	tile.setEdge(Edge(false, 0, 1, false, false), 5);

	return tile;
}

Tile TileGenerator::borgoNetFighter()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Borgo, "borgo_net_fighter");
	tile.setInitiative(1);

	tile.setEdge(Edge(true, 0, 3, false, false), 2);

	return tile;
}

Tile TileGenerator::borgoSuperMutant()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Borgo, "borgo_super_mutant");
	tile.setInitiative(2);
	tile.setShields(1);

	tile.setEdge(Edge(false, 0, 2, true, false), 0);
	tile.setEdge(Edge(false, 0, 1, true, false), 1);
	tile.setEdge(Edge(false, 0, 1, true, false), 5);

	return tile;
}

Tile TileGenerator::borgoBrawler()
{
	Tile tile(Tile::Type::Unit, Tile::PlayType::Null, Tile::Faction::Borgo, "borgo_brawler");
	tile.setInitiative(2);

	tile.setEdge(Edge(false, 0, 2, false, false), 0);

	return tile;
}