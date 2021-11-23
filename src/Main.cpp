#include "Game/Scene.hpp"
#include "SDL/Context.hpp"
#include "SDL/Window.hpp"
#include "TTF/Context.hpp"

#include <SDL_events.h>
#include <SDL_rect.h>
#include <SDL_timer.h>

#include <cstdint>
#include <optional>

int main() {
    constexpr int WINDOW_WIDTH = 480;
    constexpr int WINDOW_HEIGHT = 640;

    // Resource Acquisition is Initialization!
    // RAII Guard for the full SDL context
    SDL::Context _system_guard;
    TTF::Context _ttf_guard;

    const auto window = SDL::Window::init("Hello World", WINDOW_WIDTH, WINDOW_HEIGHT);
    const auto renderer = window.create_renderer();

    Game::Scene scene;
    constexpr uint64_t RENDER_INTERVAL = 1000;
    auto next_render = static_cast<int64_t>(SDL_GetTicks() + RENDER_INTERVAL);
    while (true) {
        // Process all events in the queue first
        SDL_Event event;
        int64_t timeout = RENDER_INTERVAL;
        while (SDL_WaitEventTimeout(&event, static_cast<int>(timeout)) != 0) {
            if (event.type == SDL_QUIT)
                return 0;
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                scene.update(SDL_Point{event.button.x, event.button.y});
            else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
                scene.update(event.key.keysym.sym);
            timeout = next_render - SDL_GetTicks();
        }

        // Only re-draw graphics once `RENDER_INTERVAL` has passed
        // scene.tick();
        // scene.draw(renderer);
        next_render = static_cast<int64_t>(SDL_GetTicks() + RENDER_INTERVAL);
    }

    return 0;
}
