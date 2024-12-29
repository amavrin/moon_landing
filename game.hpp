#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <unistd.h>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "config.hpp"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update_display(std::string message);
    void finish_fail();

    sf::RenderWindow mWindow;

    sf::Texture mSpaceTexture;
    sf::Texture mLunarTexture;
    sf::Texture mPlayerTexture;
    sf::Texture mMainFlameTexture;
    sf::Texture mLeftFlameTexture;
    sf::Texture mRightFlameTexture;
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
    float mFuel = Config::INITIAL_FUEL;
};

#endif // GAME_HPP