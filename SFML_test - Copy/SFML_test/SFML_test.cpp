//#include "stdafx.h"
#include <SFML/Graphics.hpp>

#include "TestApp.hpp"
#include "APDTest.hpp"
#include "NoiseTest.hpp"
#include "PeopleSpawning.hpp"
#include "ParticleTest.hpp"
#include "SPHTest.h"
#include "BoomShine.hpp"
#include "Noise3DTest.hpp"
#include "DragonSpiralTest.hpp"
#include "MonteCarloPi.hpp"
#include "ModuloProduct.hpp"
#include "PathFollowing.hpp"
#include "VoronoiDiagramTest.hpp"
#include "MandelbrotTest.hpp"
#include "PixelBufferTest.hpp"
#include "StrategyTestGame.hpp"
#include "PlayingCardTest.hpp"
#include "DominosAITest.hpp"
#include "WavePuzzle.hpp"

int main()
{
	WavePuzzle app(1280, 720, "Wave Puzzle");
	app.initialise();
	app.run();

    return 0;
}