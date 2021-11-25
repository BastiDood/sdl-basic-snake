#include "Surface.hpp"
#include <SDL_surface.h>

namespace SDL {
    Surface::Surface(SDL_Surface * const self) : self{self} {}
    Surface::~Surface() { SDL_FreeSurface(self); }
} // namespace SDL
