#ifndef TEXTURE_H
#define TEXTURE_H
#include <SFML/Graphics.hpp>
//forward declaration
template<typename Resource, typename Identifier>
class ResourceHolder;

namespace Textures{
	enum ID{
		Blue_Square,
		Red_Square,
		Yellow_Square,
		Green_Square,
		Purple_Square,
		Selector,
		TypeCount
	};
}

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;

#endif