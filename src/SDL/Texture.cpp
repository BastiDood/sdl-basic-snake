#include "Texture.hpp"
#include <SDL_render.h>

namespace SDL {
    Texture::Texture(SDL_Texture * const self)
        : self{Texture::Pointer{self, &SDL_DestroyTexture}} {}
} // namespace SDL
