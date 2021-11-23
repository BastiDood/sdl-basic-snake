#include "Renderer.hpp"
#include <cassert>

namespace SDL {
    Renderer::Renderer(SDL_Renderer * const self)
        : m_Self{Renderer::UniqPtr{self, &SDL_DestroyRenderer}} {}

    Texture Renderer::create_texture_from_surface(Surface const & surface) const {
        auto * const texture = SDL_CreateTextureFromSurface(m_Self.get(), surface.m_Self.get());
        assert(texture);
        return {texture};
    }

    void Renderer::fill_rect(SDL_Rect const & rect) const {
        const int result = SDL_RenderFillRect(m_Self.get(), &rect);
        assert(result == 0);
    }

    void Renderer::set_render_draw_color(uint8_t red, uint8_t green, uint8_t blue,
                                         uint8_t alpha) const {
        const int result = SDL_SetRenderDrawColor(m_Self.get(), red, green, blue, alpha);
        assert(result == 0);
    }

    void Renderer::clear() const {
        const int result = SDL_RenderClear(m_Self.get());
        assert(result == 0);
    }

    void Renderer::present() const { SDL_RenderPresent(m_Self.get()); }
} // namespace SDL
