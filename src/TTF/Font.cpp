#include "Font.hpp"
#include <SDL_ttf.h>
#include <stdexcept>
#include <string>

namespace TTF {
    Font::Font(const std::string_view path, const int ptsize)
        : self{Font::Pointer{TTF_OpenFont(path.data(), ptsize), &TTF_CloseFont}} {
        using namespace std::string_literals;
        if (self == nullptr)
            throw std::runtime_error{"failed to initialize font: "s + path.data()};
    }

    SDL::Surface Font::render_text_blended(const std::string_view text, const SDL_Color fg) const {
        auto * const surface = TTF_RenderText_Blended(self.get(), text.data(), fg);
        if (surface == nullptr)
            throw std::runtime_error{"cannot render blended text onto surface"};
        return {surface};
    }
} // namespace TTF
