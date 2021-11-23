#include "Context.hpp"
#include <SDL.h>

namespace SDL {
    Context::Context() { SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER); }
    Context::~Context() { SDL_Quit(); }
} // namespace SDL
