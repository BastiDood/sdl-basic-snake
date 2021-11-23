#include "Texture.hpp"

namespace SDL {
    Texture::Texture(SDL_Texture * const self)
        : m_Self(Texture::UniqPtr{self, &SDL_DestroyTexture}) {}
} // namespace SDL
