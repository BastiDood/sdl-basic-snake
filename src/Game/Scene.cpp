#include "Scene.hpp"

#include <algorithm>
#include <SDL_keycode.h>

namespace Game {
    Scene::Scene(const std::string_view font_path)
        : font{font_path, FONT_SIZE} { }

    void Scene::on_input(const SDL_Keycode input) {
        // Respond to input
        if (is_playing) switch (input) {
                case SDLK_UP:
                case SDLK_w: return snake.set_current_direction(Snake::Direction::UP);
                case SDLK_DOWN:
                case SDLK_s: return snake.set_current_direction(Snake::Direction::DOWN);
                case SDLK_LEFT:
                case SDLK_a: return snake.set_current_direction(Snake::Direction::LEFT);
                case SDLK_RIGHT:
                case SDLK_d: return snake.set_current_direction(Snake::Direction::RIGHT);
            }

        // Ignore non-space SDL_Key
        if (input != SDLK_SPACE) return;

        // Reset the game otherwise
        if (pending_reset) {
            is_playing = true;
            pending_reset = false;
            score = 0;
            snake.reset();
        }
    }

    void Scene::tick() {
        if (is_playing) {
            is_playing = snake.tick();
            pending_reset = !is_playing;
        }
    }

    void Scene::draw() const {
        renderer.set_render_draw_color(0, 0, 0, 255);
        renderer.clear();

        if (is_playing) {
            // Draw snake game
            const auto [width, height] = renderer.get_output_size();
            const auto side = std::min(width, height);
            renderer.set_viewport({{0, 0, side, side}});
            snake.draw(renderer, width, height);

            // Draw the current score
            renderer.set_viewport({{0, side, width, height - side}});
            renderer.render_copy(score_texture, {}, {});
            renderer.set_viewport({});
        } else {
            const SDL_Point dimensions = restart_texture.get_dimensions();
            renderer.render_copy(restart_texture, {}, {{0, 0, dimensions.x, dimensions.y}});
        }

        renderer.present();
    }
} // namespace Game
