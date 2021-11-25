#include "Renderer.hpp"
#include <SDL_render.h>
#include <cassert>

namespace SDL {
    Renderer::Renderer(SDL_Renderer * const self)
        : self{Renderer::Pointer{self, &SDL_DestroyRenderer}} {}

    Texture Renderer::create_texture_from_surface(Surface const & surface) const {
        auto * const texture = SDL_CreateTextureFromSurface(self.get(), surface.self.get());
        assert(texture);
        return {texture};
    }

    void Renderer::fill_rect(SDL_Rect const & rect) const {
        const int result = SDL_RenderFillRect(self.get(), &rect);
        assert(result == 0);
    }

    void Renderer::set_render_draw_color(uint8_t red, uint8_t green, uint8_t blue,
                                         uint8_t alpha) const {
        const int result = SDL_SetRenderDrawColor(self.get(), red, green, blue, alpha);
        assert(result == 0);
    }

    void Renderer::render_copy(SDL::Texture const & texture) const {
        const int result = SDL_RenderCopy(self.get(), texture.self.get(), nullptr, nullptr);
        assert(result == 0);
    }

    void Renderer::clear() const {
        const int result = SDL_RenderClear(self.get());
        assert(result == 0);
    }

    void Renderer::present() const { SDL_RenderPresent(self.get()); }
} // namespace SDL
