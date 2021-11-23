#include "Game/Direction.hpp"
#include "SDL/Context.hpp"
#include "SDL/Window.hpp"

#include <SDL_events.h>
#include <SDL_rect.h>
#include <SDL_timer.h>

#include <cstdint>
#include <optional>

int main() {
    constexpr int WINDOW_WIDTH = 480;
    constexpr int WINDOW_HEIGHT = 640;

    // Resource Acquisition is Initialization!
    // RAII Guard for the SDL context
    SDL::Context _guard;

    const auto window = SDL::Window::init("Hello World", WINDOW_WIDTH, WINDOW_HEIGHT);
    const auto renderer = window.create_renderer();

    constexpr uint64_t RENDER_INTERVAL = 1000;
    uint64_t next_render = SDL_GetTicks();
    while (true) {
        // Process all events in the queue first
        SDL_Event event;
        while (SDL_WaitEventTimeout(&event, RENDER_INTERVAL) != 0) {
            // Stop the program if requested
            if (event.type == SDL_QUIT)
                return 0;

            // Skip all non-keyboard events
            if (event.type != SDL_KEYDOWN)
                continue;

            // Debounce doubled inputs
            const auto data = event.key;
            if (data.repeat != 0)
                continue;

            // Skip if direction detection failed
            const auto maybe_direction = derive_direction(data.keysym.sym);
            if (!maybe_direction)
                continue;

            const auto direction = *maybe_direction;
            // scene.update(event);
        }

        // Only re-draw graphics once `RENDER_INTERVAL` has passed
        const uint64_t now = SDL_GetTicks();
        if (now >= next_render) {
            next_render = now + RENDER_INTERVAL;
            // scene.draw(renderer);
        }
    }

    return 0;
}
