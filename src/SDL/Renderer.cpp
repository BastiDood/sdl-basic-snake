#include "Renderer.hpp"
#include <SDL_render.h>
#include <stdexcept>

namespace SDL {
    Renderer::Renderer(SDL_Renderer * const self)
        : self{Renderer::Pointer{self, &SDL_DestroyRenderer}} {}

    SDL_Point Renderer::get_output_size() const {
        int width, height;
        const int result = SDL_GetRendererOutputSize(self.get(), &width, &height);
        if (result != 0)
            throw std::runtime_error{"cannot get renderer output size"};
        return {width, height};
    }

    Texture Renderer::create_texture_from_surface(Surface const & surface) const {
        auto * const texture = SDL_CreateTextureFromSurface(self.get(), surface.self.get());
        if (texture == nullptr)
            throw std::runtime_error{"cannot create texture from surface"};
        return {texture};
    }

    void Renderer::fill_rect(SDL_Rect const & rect) const {
        const int result = SDL_RenderFillRect(self.get(), &rect);
        if (result != 0)
            throw std::runtime_error{"cannot render filled rectangle"};
    }

    void Renderer::set_viewport(const std::optional<SDL_Rect> & bounds) const {
        auto const * const rect = bounds.has_value() ? &bounds.value() : nullptr;
        const int result = SDL_RenderSetViewport(self.get(), rect);
        if (result != 0)
            throw std::runtime_error{"cannot set renderer viewport"};
    }

    void Renderer::set_render_draw_color(uint8_t red, uint8_t green, uint8_t blue,
                                         uint8_t alpha) const {
        const int result = SDL_SetRenderDrawColor(self.get(), red, green, blue, alpha);
        if (result != 0)
            throw std::runtime_error{"cannot set render draw color"};
    }

    void Renderer::render_copy(SDL::Texture const & texture, std::optional<SDL_Rect> const & src,
                               std::optional<SDL_Rect> const & dest) const {
        auto const * const a = src.has_value() ? &src.value() : nullptr;
        auto const * const b = dest.has_value() ? &dest.value() : nullptr;
        const int result = SDL_RenderCopy(self.get(), texture.self.get(), a, b);
        if (result != 0)
            throw std::runtime_error{"cannot copy texture onto renderer buffer"};
    }

    void Renderer::clear() const {
        const int result = SDL_RenderClear(self.get());
        if (result != 0)
            throw std::runtime_error{"cannot copy texture onto renderer buffer"};
    }

    void Renderer::present() const { SDL_RenderPresent(self.get()); }
} // namespace SDL
