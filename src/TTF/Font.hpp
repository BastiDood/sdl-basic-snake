#pragma once
#include "../SDL/Surface.hpp"
#include <SDL_ttf.h>
#include <cstdint>
#include <string_view>

namespace TTF {
    class Font {
      public:
        Font(std::string_view path, int ptsize);
        Font(Font && other) noexcept;
        ~Font();

        SDL::Surface render_text_blended(std::string_view text, SDL_Color fg) const;

      private:
        TTF_Font * self;
    };
} // namespace TTF
