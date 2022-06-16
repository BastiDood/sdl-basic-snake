#include "Game/Scene.hpp"
#include "SDL/Context.hpp"
#include "TTF/Context.hpp"

#include <cstdint>
#include <SDL_events.h>
#include <SDL_timer.h>
#include <stdexcept>

int SDL_main(const int argc, char ** const argv) {
    if (argc <= 1) throw std::length_error{"missing font location"};

    // Resource Acquisition is Initialization!
    // RAII Guard for the full SDL context
    SDL::Context _system_guard;
    TTF::Context _ttf_guard;

    // Initialize game
    Game::Scene scene{argv[1]};

    // Initialize event loop
    constexpr uint64_t TICK_TIME = 500;
    auto next_render = static_cast<int64_t>(SDL_GetTicks() + TICK_TIME);
    while (true) {
        // Only re-draw graphics once `RENDER_INTERVAL` has passed
        scene.draw();

        // Process all events in the queue first
        SDL_Event event;
        int64_t timeout = TICK_TIME;
        while (SDL_WaitEventTimeout(&event, static_cast<int>(timeout)) != 0) {
            if (event.type == SDL_QUIT) return 0;
            if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
                scene.on_input(event.key.keysym.sym);
            timeout = std::max(0LL, next_render - SDL_GetTicks());
        }

        scene.tick();
        next_render = static_cast<int64_t>(SDL_GetTicks() + TICK_TIME);
    }

    return 0;
}
