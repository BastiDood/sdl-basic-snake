#include "../SDL/Renderer.hpp"
#include "Direction.hpp"

namespace Game {
    class IScene {
        public:
            virtual void update(Direction dir) = 0;
            virtual void tick() = 0;
            virtual void draw(SDL::Renderer const & renderer) = 0;
    };
} // namespace Game
