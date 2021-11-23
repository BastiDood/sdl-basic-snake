#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>
#include <cstdint>
#include <memory>

namespace SDL {
    class Renderer {
            using UniqPtr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
            friend class Window;

        public:
            void fill_rect(const SDL_Rect & rect) const;
            void set_render_draw_color(uint8_t red, uint8_t green, uint8_t blue,
                                       uint8_t alpha) const;
            void clear() const;

        private:
            Renderer(SDL_Renderer * self);
            const UniqPtr m_Self;
    };
} // namespace SDL
