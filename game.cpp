#include "game.hpp"

Game::Game()
    : mWindow(sf::VideoMode(640u, 480u, 32u), "SFML Application"), mSpaceTexture(), mLunarTexture(), mSpaceSprite(), mLunarSprite(), mPlayerTexture(), mPlayerSprite(), mFlameTexture(), mFlameSprite(), mFont(), mText(), mRocketSound(), mRocketSoundBuffer()
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

    if (!mFlameTexture.loadFromFile(Config::FLAME_TEXTURE_PATH))
    {
        throw std::runtime_error("Failed to load flame texture");
    }
    mFlameSprite.setTexture(mFlameTexture);

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
        mIsFire = isPressed;
    else if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}

void Game::update_display(std::string message)
{
    std::ostringstream text;
    text << "Speed: " << std::setprecision(2) << std::fixed << (-mPlayerSpeed) << std::endl;
    text << "Fuel: " << std::setprecision(2) << std::fixed << mFuel << std::endl;
    text << message;
    mText.setString(text.str());
}

void Game::update(sf::Time deltaTime)
{
    mIsFlameOn = false;
    float landingY = Config::WINDOW_HEIGHT - Config::LUNAR_HEIGHT - Config::LUNAR_MODULE_HEIGHT;
    if (mPlayerSprite.getPosition().y >= landingY)
    {
        mPlayerSprite.setPosition({mPlayerSprite.getPosition().x, landingY});
        if (mPlayerSpeed < -Config::MAXIMUM_LANDING_SPEED)
        {
            mText.setFillColor(sf::Color::Red);
            update_display("chrashed!");
        }
        else
        {
            update_display("landed!");
        }
        return;
    }

    mPlayerSpeed -= Config::LUNAR_VELOCITY * deltaTime.asSeconds();

    sf::Vector2f movement(0.f, 0.f);
    if (mIsFire)
    {
        if (mFuel > 0.f)
        {
            mPlayerSpeed += Config::PLAYER_VELOCITY * deltaTime.asSeconds();
            mFuel -= Config::FUEL_CONSUMPTION * deltaTime.asSeconds();
            mIsFlameOn = true;
        }
    }
    if (mIsMovingLeft)
        movement.x -= mPlayerSpeed;
    if (mIsMovingRight)
        movement.x += mPlayerSpeed;

    movement.y -= mPlayerSpeed;
    mPlayerSprite.move(movement * deltaTime.asSeconds());
    mFlameSprite.setPosition(mPlayerSprite.getPosition() + sf::Vector2f(0.f, Config::LUNAR_MODULE_HEIGHT));

    update_display("landing...");
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mSpaceSprite);
    mWindow.draw(mLunarSprite);
    mWindow.draw(mPlayerSprite);
    if (mIsFlameOn)
    {
        mWindow.draw(mFlameSprite);
        mRocketSound.setVolume(50.f);
    }
    else
    {
        mRocketSound.setVolume(0.f);
    }
    mWindow.draw(mText);
    mWindow.display();
}
