#include "../SDL/Renderer.hpp"
#include <SDL_events.h>
#include <cstdint>
#include <variant>

namespace Game {
    class Scene {
      public:
        void update(std::variant<SDL_Point, SDL_Keycode> dir);
        void tick();
        void draw(SDL::Renderer const & renderer) const;

      private:
        uint16_t m_Score = 0;
        bool m_IsMenu = true;

        void handle_mouse(SDL_Point point);
        void handle_key(SDL_Keycode code);
    };
} // namespace Game
