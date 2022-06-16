#include "Renderer.hpp"

#include <stdexcept>

namespace SDL {
    Renderer::Renderer(SDL_Renderer * const self)
        : self{Renderer::Pointer{self, &SDL_DestroyRenderer}} { }

    SDL_Point Renderer::get_output_size() const {
        int width, height;
        const int result = SDL_GetRendererOutputSize(self.get(), &width, &height);
        if (result != 0) throw std::runtime_error{SDL_GetError()};
        return {width, height};
    }

    Texture Renderer::create_texture_from_surface(const Surface & surface) const {
        auto * const texture = SDL_CreateTextureFromSurface(self.get(), surface.self.get());
        if (texture == nullptr) throw std::runtime_error{SDL_GetError()};
        return {texture};
    }

    void Renderer::fill_rect(const SDL_Rect & rect) const {
        const int result = SDL_RenderFillRect(self.get(), &rect);
        if (result != 0) throw std::runtime_error{SDL_GetError()};
    }

    void Renderer::set_viewport(const std::optional<SDL_Rect> & bounds) const {
        const auto * const rect = bounds.has_value() ? &bounds.value() : nullptr;
        const int result = SDL_RenderSetViewport(self.get(), rect);
        if (result != 0) throw std::runtime_error{SDL_GetError()};
    }

    void Renderer::set_render_draw_color(uint8_t red, uint8_t green, uint8_t blue,
                                         uint8_t alpha) const {
        const int result = SDL_SetRenderDrawColor(self.get(), red, green, blue, alpha);
        if (result != 0) throw std::runtime_error{SDL_GetError()};
    }

    void Renderer::render_copy(const SDL::Texture & texture, const std::optional<SDL_Rect> & src,
                               const std::optional<SDL_Rect> & dest) const {
        const auto * const left = src.has_value() ? &src.value() : nullptr;
        const auto * const right = dest.has_value() ? &dest.value() : nullptr;
        const int result = SDL_RenderCopy(self.get(), texture.self.get(), left, right);
        if (result != 0) throw std::runtime_error{SDL_GetError()};
    }

    void Renderer::clear() const {
        const int result = SDL_RenderClear(self.get());
        if (result != 0) throw std::runtime_error{SDL_GetError()};
    }

    void Renderer::present() const { SDL_RenderPresent(self.get()); }
} // namespace SDL
