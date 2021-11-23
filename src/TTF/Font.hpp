#include "../SDL/Surface.hpp"
#include <SDL_ttf.h>
#include <memory>
#include <string>

namespace TTF {
    class Font {
        using UniqPtr = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>;

      public:
        static Font load(std::string_view path, int ptsize);
        SDL::Surface render_text_solid(std::string_view text, SDL_Color fg) const;

      private:
        Font(TTF_Font * self);
        const UniqPtr m_Self;
    };
} // namespace TTF
