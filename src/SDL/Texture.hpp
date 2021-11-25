#pragma once
#include <SDL_render.h>
#include <memory>

namespace SDL {
    class Texture {
        using Pointer = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;
        friend class Renderer;

      private:
        Texture(SDL_Texture * self);
        const Pointer self;
    };
} // namespace SDL
