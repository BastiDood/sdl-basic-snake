#pragma once
#include "../SDL/Renderer.hpp"
#include "../SDL/Window.hpp"
#include "../TTF/Font.hpp"
#include <SDL_events.h>
#include <SDL_rect.h>
#include <cstdint>
#include <string_view>

constexpr size_t DIGIT_COUNT = 10;
constexpr int WINDOW_WIDTH = 480;
constexpr int WINDOW_HEIGHT = 640;

namespace Game {
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
        const TTF::Font m_Font;

        /** Handle to the current game window. */
        const SDL::Window m_Window{"Hello World", WINDOW_WIDTH, WINDOW_HEIGHT};

        /** Underlying renderer from SDL. */
        const SDL::Renderer m_Renderer{m_Window.create_renderer()};
        /** Viewport dimensions. We don't expect this to change since resizing is turned off. */
        const SDL_Point m_ViewportDimensions{m_Renderer.get_viewport_dimensions()};

        /** Cached texture for keeping the "Score" text. */
        const SDL::Texture m_ScoreTexture{m_Renderer.create_texture_from_surface(
            m_Font.render_text_blended("Score:", {255, 255, 255, 255}))};
        /** Texture dimensions for the score texture. */
        const SDL_Point m_ScoreTextureDimensions{m_ScoreTexture.get_attributes().dimensions};

        /** Cached texture for keeping the "Press Spacebar to Continue" text. */
        const SDL::Texture m_RestartTexture{
            m_Renderer.create_texture_from_surface(m_Font.render_text_blended(
                "Game over! Press [Space] to restart...", {255, 255, 255, 255}))};
        /** Texture dimensions for the score texture. */
        const SDL_Point m_RestartTextureDimensions{m_ScoreTexture.get_attributes().dimensions};

        /** Initial state of the game is the play screen. */
        bool m_IsPlaying = true;
        /** Game starts with no score. */
        uint16_t m_Score = 0;
    };
} // namespace Game
