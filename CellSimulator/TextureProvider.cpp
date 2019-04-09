#include "TextureProvider.h"

TextureProvider::TextureProvider()
{
	loadTexture("whiteNoise");
	loadTexture("background");
	loadTexture("greenLettuce");
}

void TextureProvider::loadTexture(const std::string &name)
{
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("./textures/" + name + ".png");
	texture->setRepeated(true);
	textures[name] = texture;
}

TextureProvider::~TextureProvider()
{
}

TextureProvider & TextureProvider::getInstance()
{
	static TextureProvider instance;
	return instance;
}

std::shared_ptr<sf::Texture> TextureProvider::getTexture(const std::string & name)
{
	return textures[name];
}
