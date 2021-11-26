#pragma once

#include "../SDL/Renderer.hpp"
#include "../SDL/Window.hpp"
#include "../TTF/Font.hpp"

#include "Snake.hpp"

#include <SDL_events.h>
#include <SDL_rect.h>

#include <cstdint>
#include <string_view>

namespace Game {
    constexpr int WINDOW_WIDTH = 480;
    constexpr int WINDOW_HEIGHT = 640;
    constexpr int FONT_SIZE = 32;

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
        /** Font to be used for rendering scores. */
        const TTF::Font font;

        /** Handle to the current game window. */
        const SDL::Window window{"Hello World", WINDOW_WIDTH, WINDOW_HEIGHT};

        /** Underlying renderer from SDL. */
        const SDL::Renderer renderer = window.create_renderer();

        /** Cached texture for keeping the "Score" text. */
        const SDL::Texture score_texture = renderer.create_texture_from_surface(
            font.render_text_blended("Score:", {255, 255, 255, 255}));

        /** Cached texture for keeping the "Press Spacebar to Continue" text. */
        const SDL::Texture restart_texture =
            renderer.create_texture_from_surface(font.render_text_blended(
                "Game over! Press [Space] to restart...", {255, 255, 255, 255}));

        /** State manager for snake logic. */
        Snake snake;
        /** Apple location. */
        /** Initial state of the game is the play screen. */
        bool is_playing = true;
        /** Checks whether the game is pending a new game. */
        bool pending_reset = false;
        /** Game starts with no score. */
        uint16_t score = 0;
    };
} // namespace Game
