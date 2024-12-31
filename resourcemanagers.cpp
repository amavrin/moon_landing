#include "game.hpp"

void TextureHolder::load(Textures id, const std::string &filename)
{
    std::unique_ptr<sf::Texture> t(new sf::Texture());

    if (!t->loadFromFile(filename))
    {
        throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
    }
    mTextures.insert(std::make_pair(id, std::move(t)));
}

sf::Texture &TextureHolder::get(Textures id)
{
    auto found = mTextures.find(id);
    if (found == mTextures.end())
    {
        throw std::runtime_error("TextureHolder::get - Texture not found");
    }
    return *found->second;
};

const sf::Texture &TextureHolder::get(Textures id) const
{
    auto found = mTextures.find(id);
    if (found == mTextures.end())
    {
        throw std::runtime_error("TextureHolder::get - Texture not found");
    }
    return *found->second;
};