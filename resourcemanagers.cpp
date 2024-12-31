#include "main.hpp"

std::string to_string(Entity id)
{
    switch (id)
    {
    case Entity::Space:
        return "Space";
    case Entity::Lunar:
        return "Lunar";
    case Entity::Player:
        return "Player";
    case Entity::MainFlame:
        return "MainFlame";
    case Entity::LeftFlame:
        return "LeftFlame";
    case Entity::RightFlame:
        return "RightFlame";
    default:
        throw std::runtime_error("TextureHolder::toString - Unknown texture id");
    }
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename)
{
    std::unique_ptr<Resource> t(new Resource());

    if (!t->loadFromFile(filename))
    {
        throw std::runtime_error("ResourseHolder::load - Failed to load " + filename);
    }
    auto inserted = mResources.insert(std::make_pair(id, std::move(t)));
    assert(inserted.second);
}

template <typename Resource, typename Identifier>
Resource &ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    auto found = mResources.find(id);
    assert(found != mResources.end());
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
    assert(found != mResources.end());
    return *found->second;
};

template <typename Resource, typename Identifier>
const Resource &ResourceHolder<Resource, Identifier>::operator[](Identifier id) const
{
    return get(id);
};

//

void SpriteHolder::add(Entity id, const sf::Texture &texture)
{
    std::unique_ptr<sf::Sprite> s(new sf::Sprite());
    s->setTexture(texture);
    mSprites.insert(std::make_pair(id, std::move(s)));
}

sf::Sprite &SpriteHolder::get(Entity id)
{
    auto found = mSprites.find(id);
    assert(found != mSprites.end());
    return *found->second;
};

sf::Sprite &SpriteHolder::operator[](Entity id)
{
    return get(id);
};

const sf::Sprite &SpriteHolder::get(Entity id) const
{
    auto found = mSprites.find(id);
    assert(found != mSprites.end());
    return *found->second;
};

const sf::Sprite &SpriteHolder::operator[](Entity id) const
{
    return get(id);
};