#include "Texture.hpp"

#include <stdexcept>

namespace SDL {
    Texture::Texture(SDL_Texture * const self)
        : self{Texture::Pointer{self, &SDL_DestroyTexture}} { }

    SDL_Point Texture::get_dimensions() const {
        SDL_Point dimensions;
        const int result =
            SDL_QueryTexture(self.get(), nullptr, nullptr, &dimensions.x, &dimensions.y);
        if (result != 0) throw std::runtime_error{"cannot get texture dimensions"};
        return dimensions;
    }
} // namespace SDL
