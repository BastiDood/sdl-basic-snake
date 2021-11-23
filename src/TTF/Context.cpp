#include "Context.hpp"
#include <SDL_ttf.h>
#include <cassert>

namespace TTF {
    Context::Context() {
        const int result = TTF_Init();
        assert(result == 0);
    }

    Context::~Context() { TTF_Quit(); }
} // namespace TTF
