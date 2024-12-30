#ifndef CONFIG_H
#define CONFIG_H

#include <string>

namespace Config
{
    constexpr int WINDOW_WIDTH = 640;
    constexpr int WINDOW_HEIGHT = 480;
    constexpr int LUNAR_HEIGHT = 100;
    constexpr int LUNAR_WIDTH = WINDOW_WIDTH;
    constexpr int LUNAR_MODULE_WIDTH = 30;
    constexpr int LUNAR_MODULE_HEIGHT = 50;
    constexpr int AUX_FLAME_WIDTH = 30;

    constexpr const char *LUNAR_TEXTURE_PATH = "media/img/lunar_surface.png";
    constexpr const char *SPACE_TEXTURE_PATH = "media/img/space.png";
    constexpr const char *PLAYER_TEXTURE_PATH = "media/img/lunar_module.png";
    constexpr const char *FONT_PATH = "media/font/courier_new.ttf";
    constexpr const char *MAIN_FLAME_TEXTURE_PATH = "media/img/rocket_flame.png";
    constexpr const char *LEFT_FLAME_TEXTURE_PATH = "media/img/rocket_flame_left.png";
    constexpr const char *RIGHT_FLAME_TEXTURE_PATH = "media/img/rocket_flame_right.png";
    constexpr const char *ROCKET_SOUND_PATH = "media/sound/rocket.wav";
    constexpr const char *BACKGROUND_MUSIC_PATH = "media/sound/background_music.mp3";
    constexpr const char *EXPLOSION_SOUND_PATH = "media/sound/explosion.wav";

    constexpr float INITIAL_PLAYER_X = 300;
    constexpr float INITIAL_PLAYER_Y = 100;
    constexpr float LUNAR_VELOCITY = 40.f;
    constexpr float PLAYER_MAIN_VELOCITY = 100.f;
    constexpr float PLAYER_AUX_VELOCITY = 50.f;
    constexpr float INITIAL_FUEL = 30.f;
    constexpr float MAIN_FUEL_CONSUMPTION = 10.f;
    constexpr float AUX_FUEL_CONSUMPTION = 5.f;
    constexpr float MAXIMUM_LANDING_V_SPEED = 50.f;
    constexpr float MAXIMUM_LANDING_H_SPEED = 20.f;
}
#endif // CONFIG_H