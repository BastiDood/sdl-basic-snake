#include "Font.hpp"

#include <stdexcept>

namespace TTF {
    Font::Font(const std::string_view path, const int ptsize)
        : self{Font::Pointer{TTF_OpenFont(path.data(), ptsize), &TTF_CloseFont}} {
        if (self == nullptr) throw std::runtime_error{SDL_GetError()};
    }

    SDL::Surface Font::render_text_blended(const std::string_view text,
                                           const SDL_Color color) const {
        auto * const surface = TTF_RenderText_Blended(self.get(), text.data(), color);
        if (surface == nullptr) throw std::runtime_error{SDL_GetError()};
        return {surface};
    }
} // namespace TTF
