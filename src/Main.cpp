#include "Game/Direction.hpp"
#include "SDL/Context.hpp"
#include "SDL/Window.hpp"

#include <SDL_events.h>
#include <SDL_rect.h>
#include <SDL_timer.h>

#include <cstdint>
#include <optional>

constexpr std::optional<Game::Direction> derive_direction(const SDL_Keycode code) {
    switch (code) {
        case SDLK_w:
        case SDLK_UP: return Game::Direction::Up;
        case SDLK_s:
        case SDLK_DOWN: return Game::Direction::Down;
        case SDLK_a:
        case SDLK_LEFT: return Game::Direction::Left;
        case SDLK_d:
        case SDLK_RIGHT: return Game::Direction::Right;
        default: return {};
    }
}

int main() {
    constexpr int WINDOW_WIDTH = 480;
    constexpr int WINDOW_HEIGHT = 640;

    // Resource Acquisition is Initialization!
    // RAII Guard for the SDL context
    SDL::Context _guard;

    const auto window = SDL::Window::init("Hello World", WINDOW_WIDTH, WINDOW_HEIGHT);
    const auto renderer = window.create_renderer();

    constexpr uint64_t RENDER_INTERVAL = 1000;
    auto next_render = static_cast<int64_t>(SDL_GetTicks() + RENDER_INTERVAL);
    while (true) {
        // Process all events in the queue first
        SDL_Event event;
        int64_t timeout = RENDER_INTERVAL;
        while (SDL_WaitEventTimeout(&event, static_cast<int>(timeout)) != 0) {
            // Stop the program if requested
            if (event.type == SDL_QUIT)
                return 0;

            // Skip all non-keyboard events
            if (event.type != SDL_KEYDOWN) {
                timeout = next_render - SDL_GetTicks();
                continue;
            }

            // Debounce doubled inputs
            const auto data = event.key;
            if (data.repeat != 0) {
                timeout = next_render - SDL_GetTicks();
                continue;
            }

            // Skip if direction detection failed
            const auto maybe_direction = derive_direction(data.keysym.sym);
            if (!maybe_direction) {
                timeout = next_render - SDL_GetTicks();
                continue;
            }

            const auto direction = *maybe_direction;
            // scene.update(direction);
            timeout = next_render - SDL_GetTicks();
        }

        // Only re-draw graphics once `RENDER_INTERVAL` has passed
        // scene.tick();
        // scene.draw(renderer);
        next_render = static_cast<int64_t>(SDL_GetTicks() + RENDER_INTERVAL);
    }

    return 0;
}
