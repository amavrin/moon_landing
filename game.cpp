#include "game.hpp"

Game::Game()
    : mWindow(sf::VideoMode(640u, 480u, 32u), "SFML Application"),
      mSpaceTexture(),
      mLunarTexture(),
      mSpaceSprite(),
      mLunarSprite(),
      mPlayerTexture(),
      mPlayerSprite(),
      mMainFlameTexture(),
      mMainFlameSprite(),
      mFont(), mText(),
      mRocketSound(), mRocketSoundBuffer(),
      mLeftFlameTexture(),
      mRightFlameTexture(),
      mLeftFlameSprite(),
      mRightFlameSprite(),
      mBackgroundMusic(),
      mExplosionSound(),
      mExplosionSoundBuffer()
{
    if (!mPlayerTexture.loadFromFile(Config::PLAYER_TEXTURE_PATH))
    {
        throw std::runtime_error("Failed to load lunar module texture");
    }
    mPlayerSprite.setTexture(mPlayerTexture);
    mPlayerSprite.setPosition({Config::INITIAL_PLAYER_X, Config::INITIAL_PLAYER_Y});

    if (!mSpaceTexture.loadFromFile(Config::SPACE_TEXTURE_PATH))
    {
        throw std::runtime_error("Failed to load space texture");
    }
    mSpaceSprite.setTexture(mSpaceTexture);
    mSpaceSprite.setPosition({0.f, 0.f});

    if (!mLunarTexture.loadFromFile(Config::LUNAR_TEXTURE_PATH))
    {
        throw std::runtime_error("Failed to load lunar texture");
    }
    mLunarSprite.setTexture(mLunarTexture);
    mLunarSprite.setPosition({0.f, Config::WINDOW_HEIGHT - Config::LUNAR_HEIGHT});

    if (!mMainFlameTexture.loadFromFile(Config::MAIN_FLAME_TEXTURE_PATH))
    {
        throw std::runtime_error("Failed to load flame texture");
    }
    mMainFlameSprite.setTexture(mMainFlameTexture);

    if (!mLeftFlameTexture.loadFromFile(Config::LEFT_FLAME_TEXTURE_PATH))
    {
        throw std::runtime_error("Failed to load left flame texture");
    }
    mLeftFlameSprite.setTexture(mLeftFlameTexture);

    if (!mRightFlameTexture.loadFromFile(Config::RIGHT_FLAME_TEXTURE_PATH))
    {
        throw std::runtime_error("Failed to load right flame texture");
    }
    mRightFlameSprite.setTexture(mRightFlameTexture);

    if (!mFont.loadFromFile(Config::FONT_PATH))
    {
        throw std::runtime_error("Failed to load font");
    }
    mText.setFont(mFont);
    mText.setCharacterSize(24);
    mText.setPosition({10.f, 10.f});
    mText.setFillColor(sf::Color::Green);

    if (!mRocketSoundBuffer.loadFromFile(Config::ROCKET_SOUND_PATH))
    {
        throw std::runtime_error("Failed to load rocket sound");
    }
    mRocketSound.setBuffer(mRocketSoundBuffer);
    mRocketSound.setLoop(true);
    mRocketSound.setVolume(0.f);
    mRocketSound.play();

    if (!mBackgroundMusic.openFromFile(Config::BACKGROUND_MUSIC_PATH))
    {
        throw std::runtime_error("Failed to load background music");
    }
    mBackgroundMusic.setVolume(50.f);
    mBackgroundMusic.play();

    if (!mExplosionSoundBuffer.loadFromFile(Config::EXPLOSION_SOUND_PATH))
    {
        throw std::runtime_error("Failed to load explosion sound");
    }
    mExplosionSound.setBuffer(mExplosionSoundBuffer);
    mExplosionSound.setLoop(false);
}

void Game::run()
{
    sf::Clock clock;
    while (mWindow.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        default:
            break;
        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::Space)
        mIsMainFire = isPressed;
    else if (key == sf::Keyboard::A)
        mIsRightFire = isPressed;
    else if (key == sf::Keyboard::D)
        mIsLeftFire = isPressed;
}

void Game::update_display(std::string message)
{
    std::ostringstream text;
    text << "Vertical speed: " << std::setprecision(2) << std::fixed << (-mPlayerVSpeed) << std::endl;
    text << "Horizontal speed: " << std::setprecision(2) << std::fixed << std::abs(mPlayerHSpeed) << std::endl;
    text << "Fuel: " << std::setprecision(2) << std::fixed << mFuel << std::endl;
    text << message;
    mText.setString(text.str());
}

void Game::update(sf::Time deltaTime)
{
    if (mGameOver)
        return;
    mIsMainFlameLit = false;
    mIsLeftFlameLit = false;
    mIsRightFlameLit = false;
    float landingY = Config::WINDOW_HEIGHT - Config::LUNAR_HEIGHT - Config::LUNAR_MODULE_HEIGHT;
    if (mPlayerSprite.getPosition().y >= landingY)
    {
        mPlayerSprite.setPosition({mPlayerSprite.getPosition().x, landingY});
        if (mPlayerVSpeed < -Config::MAXIMUM_LANDING_V_SPEED)
        {
            mText.setFillColor(sf::Color::Red);
            update_display("Chrashed!\nVertical speed greater than " + std::to_string(int(Config::MAXIMUM_LANDING_V_SPEED)) + " m/s");
            finish_fail();
        }
        else if (std::abs(mPlayerHSpeed) > Config::MAXIMUM_LANDING_H_SPEED)
        {
            mText.setFillColor(sf::Color::Red);
            update_display("Chrashed!\nHorizontal speed greater than " + std::to_string(int(Config::MAXIMUM_LANDING_H_SPEED)) + " m/s");
            finish_fail();
        }
        else
        {
            update_display("landed!");
        }
        return;
    }

    mPlayerVSpeed -= Config::LUNAR_VELOCITY * deltaTime.asSeconds();

    sf::Vector2f movement(0.f, 0.f);
    if (mIsMainFire && mFuel > 0.f)
    {
        mPlayerVSpeed += Config::PLAYER_MAIN_VELOCITY * deltaTime.asSeconds();
        mFuel -= Config::MAIN_FUEL_CONSUMPTION * deltaTime.asSeconds();
        mIsMainFlameLit = true;
    }
    if (mIsLeftFire && mFuel > 0.f)
    {
        mPlayerHSpeed -= Config::PLAYER_AUX_VELOCITY * deltaTime.asSeconds();
        mFuel -= Config::AUX_FUEL_CONSUMPTION * deltaTime.asSeconds();
        mIsLeftFlameLit = true;
    }
    if (mIsRightFire && mFuel > 0.f)
    {
        mPlayerHSpeed += Config::PLAYER_AUX_VELOCITY * deltaTime.asSeconds();
        mFuel -= Config::AUX_FUEL_CONSUMPTION * deltaTime.asSeconds();
        mIsRightFlameLit = true;
    }

    movement.y -= mPlayerVSpeed;
    movement.x += mPlayerHSpeed;
    mPlayerSprite.move(movement * deltaTime.asSeconds());
    mMainFlameSprite.setPosition(mPlayerSprite.getPosition() + sf::Vector2f(0.f, Config::LUNAR_MODULE_HEIGHT));
    mLeftFlameSprite.setPosition(mPlayerSprite.getPosition() + sf::Vector2f(-Config::AUX_FLAME_WIDTH, Config::LUNAR_MODULE_HEIGHT / 2));
    mRightFlameSprite.setPosition(mPlayerSprite.getPosition() + sf::Vector2f(Config::LUNAR_MODULE_WIDTH, Config::LUNAR_MODULE_HEIGHT / 2));

    update_display("landing...");
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mSpaceSprite);
    mWindow.draw(mLunarSprite);
    mWindow.draw(mPlayerSprite);
    if (mIsMainFlameLit)
        mWindow.draw(mMainFlameSprite);
    if (mIsLeftFlameLit)
        mWindow.draw(mRightFlameSprite);
    if (mIsRightFlameLit)
        mWindow.draw(mLeftFlameSprite);

    mWindow.draw(mText);
    mWindow.display();
    if (mIsMainFlameLit || mIsLeftFlameLit || mIsRightFlameLit)
        mRocketSound.setVolume(100.f);
    else
        mRocketSound.setVolume(0.f);
}

void Game::finish_fail()
{
    mBackgroundMusic.stop();
    mRocketSound.stop();
    usleep(300);
    mExplosionSound.play();
    mGameOver = true;
}