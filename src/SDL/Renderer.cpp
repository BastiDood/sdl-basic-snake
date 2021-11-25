#include "Renderer.hpp"
#include <SDL_render.h>
#include <cassert>

namespace SDL {
    Renderer::Renderer(SDL_Renderer * const self) : self{self} {}

    Renderer::Renderer(Renderer && other) noexcept : self{other.self} { other.self = nullptr; }

    Renderer::~Renderer() { SDL_DestroyRenderer(self); }

    Texture Renderer::create_texture_from_surface(Surface const & surface) const {
        auto * const texture = SDL_CreateTextureFromSurface(self, surface.self);
        assert(texture);
        return {texture};
    }

    void Renderer::fill_rect(SDL_Rect const & rect) const {
        const int result = SDL_RenderFillRect(self, &rect);
        assert(result == 0);
    }

    void Renderer::set_render_draw_color(uint8_t red, uint8_t green, uint8_t blue,
                                         uint8_t alpha) const {
        const int result = SDL_SetRenderDrawColor(self, red, green, blue, alpha);
        assert(result == 0);
    }

    void Renderer::render_copy(SDL::Texture const & texture) const {
        const int result = SDL_RenderCopy(self, texture.self, nullptr, nullptr);
        assert(result == 0);
    }

    void Renderer::clear() const {
        const int result = SDL_RenderClear(self);
        assert(result == 0);
    }

    void Renderer::present() const { SDL_RenderPresent(self); }
} // namespace SDL
