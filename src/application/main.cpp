#include <iostream>

#include <GDK/Application.hpp>
#include <GDK/WindowBuilder.hpp>

#include <Snake2D/Game.hpp>
#include <Snake2D/Renderer.hpp>

auto main(int argc, char* argv[]) -> int
{
    try {
        gamedevkit::Application application{argc, argv};
        application.window(gamedevkit::WindowBuilder{"Snake 2D", {800, 600}}.opengl_profile_core().context_version(4, 0).build())
            .game(std::make_shared<Game>())
            .renderer(std::make_unique<Renderer>())
            .setup();

        return application.run();
    }
    catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        return EXIT_FAILURE;
    }
}
