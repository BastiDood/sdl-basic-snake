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
        struct Attributes {
            uint32_t format;
            int access;
            SDL_Point dimensions;
        };

        Attributes get_attributes() const;

      private:
        Texture(SDL_Texture * self);
        const Pointer self;
    };
} // namespace SDL
