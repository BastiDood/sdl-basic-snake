#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>
#include <cstdint>
#include <memory>

namespace SDL {
    class Texture {
        using Pointer = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;
        friend class Renderer;

      public:
        SDL_Point get_dimensions() const;

      private:
        Texture(SDL_Texture * self);
        const Pointer self;
    };
} // namespace SDL
