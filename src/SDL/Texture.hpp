#pragma once
#include <SDL_render.h>

namespace SDL {
    class Texture {
        friend class Renderer;

      public:
        Texture(SDL_Texture * self);
        ~Texture();

      private:
        SDL_Texture * const self;
    };
} // namespace SDL
