#pragma once
#include <memory>
#include <SDL_surface.h>

namespace TTF {
    class Font;
}

namespace SDL {
    class Surface {
        using Pointer = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;
        friend class Renderer;
        friend class TTF::Font;

      private:
        Surface(SDL_Surface * self);
        const Pointer self;
    };
} // namespace SDL
