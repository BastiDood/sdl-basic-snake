#include <SDL_rect.h>
#include <deque>

namespace Game {
    class Snake {
      public:
        enum class Direction { UP, DOWN, LEFT, RIGHT };

        Snake(SDL_Point bounds);

        /**
         * Controls the upcoming direction in the next tick.
         * Ignore invalid inputs, such as when trying to send
         * the snake into a 180-degree turn.
         */
        void set_current_direction(Direction dir);
        /** Returns `true` if tick was successful. Otherwise, the game is over. */
        bool tick();

      private:
        /** Determines whether a given direction cancels out the current direction. */
        bool is_opposite_direction(Direction dir) const;

        struct Node {
            SDL_Point position{0, 0};
            Direction direction = Direction::RIGHT;
        };

        /** Grid-space coordinate bounds of the simulation. */
        const SDL_Point bounds;
        /** The upcoming velocity of the snake head. By default, it goes right. */
        Direction direction = Direction::RIGHT;
        /** Velocity and grid position of each snake node. */
        std::deque<Node> nodes{1};
    };
} // namespace Game
