#pragma once
#include "Surface.hpp"
#include "Texture.hpp"

#include <cstdint>
#include <memory>
#include <optional>

namespace SDL {
    class Renderer {
        using Pointer = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

      public:
        Renderer(SDL_Renderer * self);

        SDL_Point get_output_size() const;

        Texture create_texture_from_surface(const Surface & surface) const;

        void fill_rect(const SDL_Rect & rect) const;

        void set_render_draw_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) const;

        void set_viewport(const std::optional<SDL_Rect> & bounds) const;

        void render_copy(const SDL::Texture &, const std::optional<SDL_Rect> & src,
                         const std::optional<SDL_Rect> & dest) const;
        void clear() const;
        void present() const;

      private:
        Pointer self;
    };
} // namespace SDL
