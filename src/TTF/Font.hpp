#pragma once
#include "../SDL/Surface.hpp"

#include <memory>
#include <SDL_ttf.h>
#include <string_view>

namespace TTF {
    class Font {
        using Pointer = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>;

      public:
        Font(std::string_view path, int ptsize);

        SDL::Surface render_text_blended(std::string_view text, SDL_Color fg) const;

      private:
        Pointer self;
    };
} // namespace TTF
