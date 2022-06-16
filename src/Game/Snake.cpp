#include "Snake.hpp"

#include <algorithm>

namespace Game {
    bool Snake::tick() {
        auto parent = nodes.end() - 1;
        do {
            // Pull new position from the parent
            const auto child = parent--;
            *child = *parent;
        } while (parent != nodes.begin());

        // Check if the snake will collide with any of the walls
        direction = is_input_opposite_dir() ? direction : input;
        switch (direction) {
            case Direction::UP:
                if (--parent->y < 0) return false;
                break;
            case Direction::DOWN:
                if (++parent->y >= BOUNDS.y) return false;
                break;
            case Direction::LEFT:
                if (--parent->x < 0) return false;
                break;
            case Direction::RIGHT:
                if (++parent->x >= BOUNDS.x) return false;
                break;
        }

        // Check if head will collide with any of the nodes
        const auto & head = nodes.front();
        return std::none_of(nodes.cbegin() + 1, nodes.cend(), [head](const SDL_Point & node) {
            return head.x == node.x && head.y == node.y;
        });
    }

    void Snake::draw(const SDL::Renderer & renderer, const int width, const int height) const {
        renderer.set_render_draw_color(0, 255, 0, 255);
        const SDL_Point tile_size{width / BOUNDS.x, height / BOUNDS.y};
        for (const auto [x, y] : nodes)
            renderer.fill_rect({x * tile_size.x, y * tile_size.y, tile_size.x, tile_size.y});
    }

    bool Snake::is_input_opposite_dir() const {
        switch (direction) {
            case Direction::UP: return input == Direction::DOWN;
            case Direction::DOWN: return input == Direction::UP;
            case Direction::LEFT: return input == Direction::RIGHT;
            case Direction::RIGHT: return input == Direction::LEFT;
        }
    }

    void Snake::reset() {
        direction = Direction::RIGHT;
        nodes.clear();
        nodes.push_back({2, 0});
        nodes.push_back({1, 0});
        nodes.push_back({});
    }

    void Snake::set_current_direction(const Direction dir) {
        input = dir;
    }
} // namespace Game
