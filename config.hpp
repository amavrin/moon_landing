#ifndef CONFIG_H
#define CONFIG_H

#include <string>

namespace Config
{
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    const int LUNAR_HEIGHT = 100;
    const int LUNAR_WIDTH = WINDOW_WIDTH;
    const int LUNAR_MODULE_WIDTH = 30;
    const int LUNAR_MODULE_HEIGHT = 50;

    const std::string LUNAR_TEXTURE_PATH = "media/img/lunar_surface.png";
    const std::string SPACE_TEXTURE_PATH = "media/img/space.png";
    const std::string PLAYER_TEXTURE_PATH = "media/img/lunar_module.png";
    const std::string FONT_PATH = "media/font/courier_new.ttf";
    const std::string FLAME_TEXTURE_PATH = "media/img/rocket_flame.png";
    const std::string ROCKET_SOUND_PATH = "media/sound/rocket.wav";

    const float INITIAL_PLAYER_X = 300;
    const float INITIAL_PLAYER_Y = 100;
    const float LUNAR_VELOCITY = 50.f;
    const float PLAYER_VELOCITY = 100.f;
    const float INITIAL_FUEL = 30.f;
    const float FUEL_CONSUMPTION = 10.f;
    const float MAXIMUM_LANDING_SPEED = 50.f;
}
#endif // CONFIG_H