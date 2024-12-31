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

//

void SpriteHolder::add(Entity id, const sf::Texture &texture)
{
    auto sprite = std::make_unique<sf::Sprite>();
    sprite->setTexture(texture);
    auto inserted = mSprites.emplace(id, std::move(sprite));
    if (!inserted.second)
    {
        throw std::runtime_error("SpriteHolder::add - Failed to insert sprite");
    }
}

sf::Sprite &SpriteHolder::get(Entity id)
{
    auto found = mSprites.find(id);
    if (found == mSprites.end())
    {
        throw std::runtime_error("SpriteHolder::get - Sprite not found");
    }
    return *found->second;
};

sf::Sprite &SpriteHolder::operator[](Entity id)
{
    return get(id);
};

const sf::Sprite &SpriteHolder::get(Entity id) const
{
    auto found = mSprites.find(id);
    if (found == mSprites.end())
    {
        throw std::runtime_error("SpriteHolder::get - Sprite not found");
    }
    return *found->second;
};

const sf::Sprite &SpriteHolder::operator[](Entity id) const
{
    return get(id);
};