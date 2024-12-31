#ifndef RESOURCEMANAGERS_H
#define RESOURCEMANAGERS_H

#include <SFML/Graphics.hpp>
#include <map>

enum class Entity
{
    Space,
    Lunar,
    Player,
    MainFlame,
    LeftFlame,
    RightFlame
};

std::string to_string(Entity texture);

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    Resource &get(Identifier id);
    const Resource &get(Identifier id) const;
    Resource &operator[](Identifier id);
    const Resource &operator[](Identifier id) const;
    void load(Identifier id, const std::string &filename);

private:
    std::map<Identifier, std::unique_ptr<Resource>> mResources;
};

class SpriteHolder
{
public:
    sf::Sprite &get(Entity id);
    sf::Sprite &operator[](Entity id);
    const sf::Sprite &operator[](Entity id) const;
    const sf::Sprite &get(Entity id) const;
    void add(Entity id, const sf::Texture &texture);

private:
    std::map<Entity, std::unique_ptr<sf::Sprite>> mSprites;
};

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename)
{
    auto resource = std::make_unique<Resource>();
    if (!resource->loadFromFile(filename))
    {
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    }
    auto inserted = mResources.emplace(id, std::move(resource));
    if (!inserted.second)
    {
        throw std::runtime_error("ResourceHolder::load - Failed to insert " + filename);
    }
}

template <typename Resource, typename Identifier>
Resource &ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    auto found = mResources.find(id);
    if (found == mResources.end())
    {
        throw std::runtime_error("ResourceHolder::get - Resource not found");
    }
    return *found->second;
};

template <typename Resource, typename Identifier>
Resource &ResourceHolder<Resource, Identifier>::operator[](Identifier id)
{
    return get(id);
};

template <typename Resource, typename Identifier>
const Resource &ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    auto found = mResources.find(id);
    if (found == mResources.end())
    {
        throw std::runtime_error("ResourceHolder::get - Resource not found");
    }
    return *found->second;
};

template <typename Resource, typename Identifier>
const Resource &ResourceHolder<Resource, Identifier>::operator[](Identifier id) const
{
    return get(id);
};

#endif // RESOURCEMANAGERS_H