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

void TextureHolder::load(Entity id, const std::string &filename)
{
    std::unique_ptr<sf::Texture> t(new sf::Texture());

    if (!t->loadFromFile(filename))
    {
        throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
    }
    auto inserted = mTextures.insert(std::make_pair(id, std::move(t)));
    if (!inserted.second)
    {
        throw std::logic_error("TextureHolder::load - Texture already exists for id " + to_string(id) + "");
    }
}

sf::Texture &TextureHolder::get(Entity id)
{
    auto found = mTextures.find(id);
    if (found == mTextures.end())
    {
        throw std::runtime_error("TextureHolder::get - Texture not found");
    }
    return *found->second;
};

sf::Texture &TextureHolder::operator[](Entity id)
{
    return get(id);
};

const sf::Texture &TextureHolder::get(Entity id) const
{
    auto found = mTextures.find(id);
    if (found == mTextures.end())
    {
        throw std::runtime_error("TextureHolder::get - Texture not found");
    }
    return *found->second;
};

const sf::Texture &TextureHolder::operator[](Entity id) const
{
    return get(id);
};

void SpriteHolder::add(Entity id, const sf::Texture &texture)
{
    std::unique_ptr<sf::Sprite> s(new sf::Sprite());
    s->setTexture(texture);
    mSprites.insert(std::make_pair(id, std::move(s)));
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