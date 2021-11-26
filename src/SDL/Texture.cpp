#include "Texture.hpp"
#include <cassert>

namespace SDL {
    Texture::Texture(SDL_Texture * const self)
        : self{Texture::Pointer{self, &SDL_DestroyTexture}} {}

    SDL_Point Texture::get_dimensions() const {
        SDL_Point dimensions;
        const int result =
            SDL_QueryTexture(self.get(), nullptr, nullptr, &dimensions.x, &dimensions.y);
        assert(result == 0);
        return dimensions;
    }
} // namespace SDL
