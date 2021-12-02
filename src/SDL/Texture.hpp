#pragma once
#include <cstdint>
#include <memory>
#include <SDL_rect.h>
#include <SDL_render.h>

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
