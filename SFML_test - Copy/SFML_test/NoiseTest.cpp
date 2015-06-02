#include "NoiseTest.hpp"

NoiseTest::NoiseTest(unsigned width, unsigned height, std::string title)
	: Application(width, height, title)
{

}

void NoiseTest::initialise()
{
	_noise.generateInitialNoise();

	_octaves = 2;
	for (unsigned i = 0; i < _octaves; i++)
	{
		PerlinNoise noise(40.0f, 40.0f, rand());
		noise.initialise();
		_perlin.push_back(noise);
	}

	_sampleTextures = std::vector<sf::Texture>(_octaves);
	_sampleData = std::vector<std::vector<sf::Uint8> >(0);

	calculateNoise();
}

void NoiseTest::calculateNoise()
{
	unsigned drawDim = 350;

	//	Create textures for number of octaves
	for (unsigned i = 0; i < _sampleTextures.size(); i++)
	{
		_sampleTextures[i].create(drawDim, drawDim);
		_sampleData.push_back(std::vector<sf::Uint8>(drawDim * drawDim * 16, 0));
	}

	_noiseData = std::vector<sf::Uint8>(drawDim * drawDim * 16, 0);
	_noiseTexture.create(drawDim, drawDim);

	for (unsigned i = 0; i < drawDim; i++)
	{
		for (unsigned j = 0; j < drawDim; j++)
		{
			float noise = 0.0f;
			for (unsigned k = 0; k < _octaves; k++)
			{
				float preNoise = _perlin[k].getNoise(i * 0.1f * powf(2.0f, k), j * 0.1f * powf(2.0f, k)) / powf(2.0f, k);

				sf::Uint8 pixel[4] = { 0, 0, unsigned(255 * (preNoise + 1.0f) / 2.0f), 255 };
				_sampleData[k][i * 4 * drawDim + j * 4 + 2] = unsigned(255 * (preNoise + 1.0f) / 2.0f);
				_sampleData[k][i * 4 * drawDim + j * 4 + 3] = 255;
				//textures[k].update(pixel,1 , 1, i, j);

				//_window.draw(shape);

				noise += preNoise;
			}

			//noise /= _octaves;

			noise *= 2.0f;
			noise += 4.0f;
			noise /= 8.0f;

			sf::Uint8 pixel[4] = { 0, 0, unsigned(255 * noise), 255 };
			_noiseData[i * 4 * drawDim + j * 4 + 2] = unsigned(255 * noise);
			_noiseData[i * 4 * drawDim + j * 4 + 3] = 255;

			//noiseTexture.update(pixel,1 , 1, i, j);

			//_window.draw(shape);
		}
	}

	_noiseTexture.update(&_noiseData[0]);

	for (unsigned i = 0; i < _octaves; i++)
	{
		_sampleTextures[i].update(&_sampleData[i][0]);
	}
}

void NoiseTest::update()
{

}

void NoiseTest::draw()
{
	_window.clear(sf::Color::Black);

	float dimension = 350.0f;

	sf::RectangleShape textureShape(sf::Vector2f(dimension, dimension));
	textureShape.setPosition(0.0f, 0.0f);
	textureShape.setTexture(&_noiseTexture);

	_window.draw(textureShape);

	for (unsigned i = 0; i < _octaves; i++)
	{
		textureShape.setTexture(&_sampleTextures[i]);
		textureShape.setPosition(i * dimension, dimension);

		_window.draw(textureShape);
	}

	_window.display();
}