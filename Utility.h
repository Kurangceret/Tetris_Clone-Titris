#ifndef UTILITY_H
#define UTILITY_H
#include <SFML/Graphics.hpp>
#include <random>

namespace{

	inline std::default_random_engine createRandomEngine()
	{
		auto seed = static_cast<unsigned long>(std::time(nullptr));
		return std::default_random_engine(seed);
	}

	auto RandomEngine = createRandomEngine();
}

inline int randomInt(int exclusiveMax)
{
	std::uniform_int_distribution<> distr(0, exclusiveMax - 1);
	return distr(RandomEngine);
}


template<class Object>
inline void centerOrigin(Object& obj)
{
	sf::Vector2f newVelo(obj.getLocalBounds().width / 2, obj.getLocalBounds().height / 2);
	obj.setOrigin(newVelo.x, newVelo.y);
}

#endif