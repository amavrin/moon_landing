#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "config.hpp"
#include "resourcemanagers.hpp"

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

    ResourceHolder<sf::Texture, Entity> mTextureHolder;
    SpriteHolder mSpriteHolder;

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