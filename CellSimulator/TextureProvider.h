#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
class TextureProvider final
{
public:
	~TextureProvider();

	static TextureProvider& getInstance();

	std::shared_ptr<sf::Texture> getTexture(const std::string& name);

private:
	TextureProvider();
	TextureProvider(const TextureProvider&) = delete;
	TextureProvider& operator=(const TextureProvider&) = delete;

	void loadTexture(const std::string&);

	std::map<std::string, std::shared_ptr<sf::Texture>> textures;
};

