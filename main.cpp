#include "main.hpp"
#include "argparse/argparse.hpp"

int main(int argc, char *argv[])
{
    argparse::ArgumentParser program("game");
    program.add_argument("-f", "--fuel")
        .help("initial fuel volume")
        .default_value(Config::INITIAL_FUEL)
        .scan<'f', float>();
    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error &err)
    {
        std::cerr << err.what() << std::endl;
        return 1;
    }
    float fuelVolume = program.get<float>("--fuel");

    try
    {
        Game game(fuelVolume);
        game.run();
    }
    catch (const std::exception &err)
    {
        std::cerr << err.what() << std::endl;
        return 1;
    }
}