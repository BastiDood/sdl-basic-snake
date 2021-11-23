#include "Surface.hpp"

namespace SDL {
    Surface::Surface(SDL_Surface * const self) : m_Self{Surface::UniqPtr{self, &SDL_FreeSurface}} {}
} // namespace SDL
