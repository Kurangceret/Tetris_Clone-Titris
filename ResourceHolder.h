#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <map>
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <cstdlib>
#include <cassert>
#include "Texture.h"



//this class will attempt to hold all type of resources into one (exception for sf::Music)
template<typename Resource, typename Identifier>
class ResourceHolder{
public:
	
	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;
	//this load will load the whole images
	void load(Identifier id, const std::string& fileName);

	//this load can either load the whole images or only a fragment of it(used mostly by sf::Shader)
	template<typename Parameter>
	void load(Identifier id, const std::string& fileName,
		const Parameter& secondParam);
private:
	std::map<Identifier, std::unique_ptr<Resource> > mResourceMap;
};

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id,
	const std::string& fileName)
{
	std::unique_ptr<Resource> resource(new Resource);
	if (!resource->loadFromFile(fileName))
		throw std::runtime_error("ResourceHolder:: load - Failed to Load " + fileName);

	//std::move takes the ownership from the variable texture to the argument of make_pair
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}


template<typename Resource, typename Identifier, typename Parameter>
void load(Identifier id, const std::string& fileName,
	const Parameter& secondParam)
{
	std::unique_ptr<Resource> resource(new Resource);
	if (!resource->loadFromFile(fileName, secondParam))
		throw std::runtime_error("ResourceHolder:: load - Failed to Load " + fileName);

	//std::move takes the ownership from the variable texture to the argument of make_pair
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template<typename Resource, typename Identifier>
 Resource& ResourceHolder<Resource, Identifier>::get(
	Identifier id) 
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());
	//deference it to get the texture
	return *found->second;
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(
	Identifier id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());
	//deference it to get the texture
	return *found->second;
}
#endif