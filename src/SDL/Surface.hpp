#include <SDL_surface.h>
#include <memory>

namespace SDL {
    class Surface {
            using UniqPtr = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;

        public:
            Surface(SDL_Surface * self);

        private:
            const UniqPtr m_Self;
    };
} // namespace SDL
