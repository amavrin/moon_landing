#include "game.hpp"

void TextureHolder::load(Texture id, const std::string &filename)
{
    std::unique_ptr<sf::Texture> t(new sf::Texture());

    if (!t->loadFromFile(filename))
    {
        throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
    }
    mTextures.insert(std::make_pair(id, std::move(t)));
}

sf::Texture &TextureHolder::get(Texture id)
{
    auto found = mTextures.find(id);
    if (found == mTextures.end())
    {
        throw std::runtime_error("TextureHolder::get - Texture not found");
    }
    return *found->second;
};

const sf::Texture &TextureHolder::get(Texture id) const
{
    auto found = mTextures.find(id);
    if (found == mTextures.end())
    {
        throw std::runtime_error("TextureHolder::get - Texture not found");
    }
    return *found->second;
};

void SpriteHolder::add(Sprite id, const sf::Texture &texture)
{
    std::unique_ptr<sf::Sprite> s(new sf::Sprite());
    s->setTexture(texture);
    mSprites.insert(std::make_pair(id, std::move(s)));
}

sf::Sprite &SpriteHolder::get(Sprite id)
{
    auto found = mSprites.find(id);
    if (found == mSprites.end())
    {
        throw std::runtime_error("SpriteHolder::get - Sprite not found");
    }
    return *found->second;
};

const sf::Sprite &SpriteHolder::get(Sprite id) const
{
    auto found = mSprites.find(id);
    if (found == mSprites.end())
    {
        throw std::runtime_error("SpriteHolder::get - Sprite not found");
    }
    return *found->second;
};