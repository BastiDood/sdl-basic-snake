#include "Context.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <cassert>

namespace SDL {
    Context::Context() {
        const int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
        assert(result == 0);
    }

    Context::~Context() { SDL_Quit(); }
} // namespace SDL
