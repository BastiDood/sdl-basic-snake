#pragma once
#include "Surface.hpp"
#include "Texture.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <cstdint>
#include <memory>

namespace SDL {
    class Renderer {
        using Pointer = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

      public:
        Renderer(SDL_Renderer * self);

        Texture create_texture_from_surface(Surface const & surface) const;

        void fill_rect(const SDL_Rect & rect) const;

        void set_render_draw_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) const;

        void render_copy(SDL::Texture const &) const;
        void clear() const;
        void present() const;

      private:
        Pointer self;
    };
} // namespace SDL
