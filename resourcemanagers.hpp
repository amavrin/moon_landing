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

std::string toString(Entity texture);

class TextureHolder
{
public:
    sf::Texture &get(Entity id);
    const sf::Texture &get(Entity id) const;
    sf::Texture &operator[](Entity id);
    const sf::Texture &operator[](Entity id) const;
    void load(Entity id, const std::string &filename);

private:
    std::map<Entity, std::unique_ptr<sf::Texture>> mTextures;
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
#endif // RESOURCEMANAGERS_H