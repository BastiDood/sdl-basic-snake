#pragma once
#include <SDL_render.h>
#include <memory>

namespace SDL {
    class Texture {
        using UniqPtr = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;
        friend class Renderer;

      public:
        Texture(SDL_Texture * self);

      private:
        const UniqPtr m_Self;
    };
} // namespace SDL
