#include "Font.hpp"
#include <SDL_ttf.h>
#include <cassert>

namespace TTF {
    Font::Font(const std::string_view path, const int ptsize)
        : self{Font::Pointer{TTF_OpenFont(path.data(), ptsize), &TTF_CloseFont}} {
        assert(self);
    }

    SDL::Surface Font::render_text_blended(const std::string_view text, const SDL_Color fg) const {
        auto * const surface = TTF_RenderText_Blended(self.get(), text.data(), fg);
        assert(surface);
        return {surface};
    }
} // namespace TTF
