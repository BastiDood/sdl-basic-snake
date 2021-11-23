#include "Font.hpp"
#include <cassert>

namespace TTF {
    Font::Font(TTF_Font * const self) : m_Self{Font::UniqPtr{self, &TTF_CloseFont}} {}

    Font Font::load(const std::string_view path, const int ptsize) {
        auto * const self = TTF_OpenFont(path.data(), ptsize);
        assert(self);
        return {self};
    }

    SDL::Surface Font::render_text_solid(const std::string_view text, SDL_Color fg) const {
        auto * const surface = TTF_RenderText_Solid(m_Self.get(), text.data(), fg);
        assert(surface);
        return {surface};
    }
} // namespace TTF
