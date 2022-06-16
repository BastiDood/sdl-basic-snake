#include "../SDL/Renderer.hpp"

#include <deque>
#include <SDL_rect.h>

namespace Game {
    class Snake {
        static constexpr SDL_Point BOUNDS{10, 10};

      public:
        enum class Direction { UP, DOWN, LEFT, RIGHT };

        /**
         * Controls the upcoming direction in the next tick.
         * Ignore invalid inputs, such as when trying to send
         * the snake into a 180-degree turn.
         */
        constexpr void set_current_direction(const Direction dir) {
            if (!is_opposite_direction(dir)) direction = dir;
        }

        /** Returns `true` if tick was successful. Otherwise, the game is over. */
        bool tick();
        /** Render the snake on the screen. */
        void draw(const SDL::Renderer & renderer, int width, int height) const;

        /** Resets the snake's state. */
        constexpr void reset() {
            direction = Direction::RIGHT;
            nodes.clear();
            nodes.push_back({2, 0});
            nodes.push_back({1, 0});
            nodes.push_back({});
        }

      private:
        /** Determines whether a given direction cancels out the current direction. */
        constexpr bool is_opposite_direction(const Direction dir) const {
            switch (direction) {
                case Direction::UP: return dir == Direction::DOWN;
                case Direction::DOWN: return dir == Direction::UP;
                case Direction::LEFT: return dir == Direction::RIGHT;
                case Direction::RIGHT: return dir == Direction::LEFT;
            }
        }

        /** The upcoming velocity of the snake head. By default, it goes right. */
        Direction direction = Direction::RIGHT;
        /** Velocity and grid position of each snake node. */
        std::deque<SDL_Point> nodes{{2, 0}, {1, 0}, {}};
    };
} // namespace Game
