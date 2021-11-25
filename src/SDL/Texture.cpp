#include "Texture.hpp"
#include <SDL_render.h>

namespace SDL {
    Texture::Texture(SDL_Texture * const self) : self{self} {}
    Texture::~Texture() { SDL_DestroyTexture(self); }
} // namespace SDL
