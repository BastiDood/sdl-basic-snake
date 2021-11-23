#pragma once
#include "../SDL/Renderer.hpp"
#include "../TTF/Font.hpp"
#include <SDL_events.h>
#include <cstdint>
#include <string_view>
#include <variant>

namespace Game {
    class Scene {
      public:
        Scene(std::string_view font_path);

        /** Reacts to user input. */
        void update(std::variant<SDL_Point, SDL_Keycode> dir);

        /** Commits the latest mutations from user input. */
        void tick();

        /** Renders the current state of the scene. */
        void draw(SDL::Renderer const & renderer) const;

      private:
        const TTF::Font m_Font;
        bool m_IsMenu = true;
        uint16_t m_Score = 0;

        void handle_mouse(SDL_Point point);
        void handle_key(SDL_Keycode code);
    };
} // namespace Game
