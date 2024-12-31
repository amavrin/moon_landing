#ifndef RESOURCEMANAGERS_H
#define RESOURCEMANAGERS_H

#include <SFML/Graphics.hpp>
#include <map>

enum class Texture
{
    Space,
    Lunar,
    Player,
    MainFlame,
    LeftFlame,
    RightFlame
};

enum class Sprite
{
    Space,
    Lunar,
    Player,
    MainFlame,
    LeftFlame,
    RightFlame
};

class TextureHolder
{
public:
    sf::Texture &get(Texture id);
    const sf::Texture &get(Texture id) const;
    void load(Texture id, const std::string &filename);

private:
    std::map<Texture, std::unique_ptr<sf::Texture>> mTextures;
};

class SpriteHolder
{
public:
    sf::Sprite &get(Sprite id);
    const sf::Sprite &get(Sprite id) const;
    void add(Sprite id, const sf::Texture &texture);

private:
    std::map<Sprite, std::unique_ptr<sf::Sprite>> mSprites;
};
#endif // RESOURCEMANAGERS_H