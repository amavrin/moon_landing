#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

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

    sf::RenderWindow mWindow;

    sf::Texture mSpaceTexture;
    sf::Texture mLunarTexture;
    sf::Texture mPlayerTexture;
    sf::Texture mFlameTexture;
    sf::Sprite mSpaceSprite;
    sf::Sprite mLunarSprite;
    sf::Sprite mPlayerSprite;
    sf::Sprite mFlameSprite;
    sf::Sound mRocketSound;
    sf::SoundBuffer mRocketSoundBuffer;

    sf::Font mFont;
    sf::Text mText;

    bool mIsFire = false;
    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;
    bool mIsFlameOn = false;
    float mPlayerSpeed = 0.f;
    float mFuel = Config::INITIAL_FUEL;
};

#endif // GAME_HPP