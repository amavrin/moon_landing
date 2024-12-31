#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "config.hpp"

enum class Textures
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
    sf::Texture &get(Textures id);
    const sf::Texture &get(Textures id) const;
    void load(Textures id, const std::string &filename);

private:
    std::map<Textures, std::unique_ptr<sf::Texture>> mTextures;
};

class Game
{
public:
    Game(float fluelVolume = Config::INITIAL_FUEL);
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update_display(std::string message);
    void finish_fail();

    sf::RenderWindow mWindow;

    TextureHolder mTextureHolder;
    sf::Sprite mSpaceSprite;
    sf::Sprite mLunarSprite;
    sf::Sprite mPlayerSprite;
    sf::Sprite mMainFlameSprite;
    sf::Sprite mLeftFlameSprite;
    sf::Sprite mRightFlameSprite;
    sf::Sound mRocketSound;
    sf::SoundBuffer mRocketSoundBuffer;
    sf::Sound mExplosionSound;
    sf::SoundBuffer mExplosionSoundBuffer;
    sf::Music mBackgroundMusic;

    sf::Font mFont;
    sf::Text mText;

    bool mIsMainFire = false;
    bool mIsLeftFire = false;
    bool mIsRightFire = false;
    bool mIsMainFlameLit = false;
    bool mIsLeftFlameLit = false;
    bool mIsRightFlameLit = false;
    bool mGameOver = false;
    float mPlayerVSpeed = 0.f;
    float mPlayerHSpeed = 0.f;
    float mFuel;
};

#endif // GAME_HPP