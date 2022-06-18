#pragma once

#include "../SDL/Renderer.hpp"
#include "../SDL/Window.hpp"
#include "../TTF/Font.hpp"
#include "Snake.hpp"

#include <cstdint>
#include <SDL_events.h>
#include <SDL_rect.h>
#include <string_view>

namespace Game {
    static constexpr int WINDOW_WIDTH = 480;
    static constexpr int WINDOW_HEIGHT = 640;
    static constexpr int FONT_SIZE = 40;

    class Scene {
      public:
        Scene(std::string_view font_path);

        /** Reacts to user input. */
        void on_input(SDL_Keycode input);

        /** Commits the latest mutations from user input. */
        void tick();

        /** Renders the current state of the scene. */
        void draw() const;

      private:
        /** State manager for snake logic. */
        Snake snake;
        /** Initial state of the game is the play screen. */
        bool is_playing = true;
        /** Checks whether the game is pending a new game. */
        bool pending_reset = false;

        /** Font to be used for rendering scores. */
        const TTF::Font font;

        /** Handle to the current game window. */
        const SDL::Window window{"Snake", WINDOW_WIDTH, WINDOW_HEIGHT};

        /** Underlying renderer from SDL. */
        const SDL::Renderer renderer = window.create_renderer();

        /** Cached texture for keeping the "Score" text. */
        SDL::Texture score_texture = renderer.create_texture_from_surface(
            font.render_text_blended("Score: 0", {255, 255, 255, 255}));

        /** Cached texture for keeping the "Press Spacebar to Continue" text. */
        const SDL::Texture restart_texture =
            renderer.create_texture_from_surface(font.render_text_blended(
                "Game over! Press [Space] to restart...", {255, 255, 255, 255}));
    };
} // namespace Game
