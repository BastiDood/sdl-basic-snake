#include "Texture.hpp"
#include <cassert>

namespace SDL {
    Texture::Texture(SDL_Texture * const self)
        : self{Texture::Pointer{self, &SDL_DestroyTexture}} {}

    Texture::Attributes Texture::get_attributes() const {
        Texture::Attributes attrs;
        const int result = SDL_QueryTexture(self.get(), &attrs.format, &attrs.access,
                                            &attrs.dimensions.x, &attrs.dimensions.y);
        assert(result == 0);
        return attrs;
    }
} // namespace SDL
