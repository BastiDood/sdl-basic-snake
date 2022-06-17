#include "Snake.hpp"

#include <algorithm>
#include <array>
#include <functional>
#include <random>
#include <pcg_random.hpp>

namespace Game {
    std::ptrdiff_t Snake::gen_index(const std::ptrdiff_t max) {
        static pcg32 rng{pcg_extras::seed_seq_from<std::random_device>{}};
        const std::uniform_int_distribution<std::ptrdiff_t> dist{0, max};
        return dist(rng);
    }

    std::optional<Snake::Coords> Snake::gen_apple() {
        static constexpr auto WIDTH = static_cast<std::ptrdiff_t>(BOUNDS.x);
        static constexpr auto HEIGHT = static_cast<std::ptrdiff_t>(BOUNDS.y);
        static constexpr auto SIZE = WIDTH * HEIGHT;

        // Create a grid for all occupied cells
        std::array<bool, SIZE> grid;
        for (const auto & [x, y] : nodes) {
            const auto col = static_cast<std::size_t>(x);
            const auto row = static_cast<std::size_t>(y);
            grid[row * WIDTH + col] = true;
        }

        const auto rand = gen_index(SIZE - 1);
        const auto mid = grid.cbegin() + rand;

        // Find first empty cell from `mid` to the end
        const auto right_candidate = std::find_if_not(mid, grid.cend(), std::identity{});
        if (right_candidate != grid.cend()) {
            const auto index = right_candidate - grid.cbegin();
            return std::make_pair(index % WIDTH, index / WIDTH);
        }

        // Otherwise find first empty cell from start to `mid`
        const auto left_candidate = std::find_if_not(grid.cbegin(), mid, std::identity{});
        if (left_candidate != mid) {
            const auto index = left_candidate - grid.cbegin();
            return std::make_pair(index % WIDTH, index / WIDTH);
        }

        // There are no more available cells
        return std::nullopt;
    }

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

    void Snake::set_current_direction(const Direction dir) { input = dir; }
} // namespace Game
