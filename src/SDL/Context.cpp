#include "Context.hpp"

#include <SDL.h>
#include <stdexcept>

namespace SDL {
    Context::Context() {
        const int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
        if (result != 0) throw std::runtime_error{SDL_GetError()};
    }

    Context::~Context() { SDL_Quit(); }
} // namespace SDL
