#pragma once
#include <SDL_surface.h>

namespace SDL {
    class Surface {
        friend class Renderer;

      public:
        Surface(SDL_Surface * self);
        ~Surface();

      private:
        SDL_Surface * const self;
    };
} // namespace SDL
