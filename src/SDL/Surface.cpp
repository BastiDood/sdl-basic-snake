#include "Surface.hpp"

#include <SDL_surface.h>

namespace SDL {
    Surface::Surface(SDL_Surface * const self)
        : self{Surface::Pointer{self, &SDL_FreeSurface}} { }
} // namespace SDL
