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
        static constexpr auto WIDTH = static_cast<std::ptrdiff_t>(BOUNDS.first);
        static constexpr auto HEIGHT = static_cast<std::ptrdiff_t>(BOUNDS.second);
        static constexpr auto SIZE = WIDTH * HEIGHT;

        // Create a grid for all occupied cells
        std::array<bool, SIZE> grid;
        for (const auto & [x, y] : nodes) {
            const auto row = static_cast<std::size_t>(x);
            const auto col = static_cast<std::size_t>(y);
            grid[col * WIDTH + row] = true;
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
                if (++parent->y >= static_cast<int>(BOUNDS.first)) return false;
                break;
            case Direction::LEFT:
                if (--parent->x < 0) return false;
                break;
            case Direction::RIGHT:
                if (++parent->x >= static_cast<int>(BOUNDS.second)) return false;
                break;
        }

        // Check if head will collide with any of the nodes
        const auto & head = nodes.front();
        const auto has_collision =
            std::any_of(nodes.cbegin() + 1, nodes.cend(), [head](const SDL_Point & node) {
                return head.x == node.x && head.y == node.y;
            });
        if (has_collision) return false;

        // Check if head collides with an apple
        const auto hits_apple =
            head.x == static_cast<int>(apple.first) && head.y == static_cast<int>(apple.second);
        if (!hits_apple) return true;

        // Otherwise spawn a new apple
        const auto maybe_coords = gen_apple();
        if (!maybe_coords) return false;

        // TODO: update the scoreboard and lengthen the snake
        apple = *maybe_coords;
        return true;
    }

    void Snake::draw(const SDL::Renderer & renderer, const int width, const int height) const {
        const auto tile_x = width / static_cast<int>(BOUNDS.first);
        const auto tile_y = height / static_cast<int>(BOUNDS.second);

        // Render snake body
        renderer.set_render_draw_color(0, 255, 0, 255);
        for (const auto & [x, y] : nodes)
            renderer.fill_rect({x * tile_x, y * tile_y, tile_x, tile_y});

        // Render apple
        renderer.set_render_draw_color(255, 0, 0, 255);
        const auto apple_x = static_cast<int>(apple.first);
        const auto apple_y = static_cast<int>(apple.second);
        renderer.fill_rect({apple_x * tile_x, apple_y * tile_y, tile_x, tile_y});
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
