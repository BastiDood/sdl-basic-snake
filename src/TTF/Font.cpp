#include "Font.hpp"
#include <SDL_ttf.h>
#include <cassert>

namespace TTF {
    Font::Font(std::string_view path, int ptsize) : self{TTF_OpenFont(path.data(), ptsize)} {
        assert(self);
    }

    Font::Font(Font && other) noexcept : self{other.self} { other.self = nullptr; }

    Font::~Font() { TTF_CloseFont(self); }

    SDL::Surface Font::render_text_blended(const std::string_view text, const SDL_Color fg) const {
        auto * const surface = TTF_RenderText_Blended(self, text.data(), fg);
        assert(surface);
        return {surface};
    }
} // namespace TTF
