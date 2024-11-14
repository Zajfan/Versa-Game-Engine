#ifndef AGENT_H
#define AGENT_H

#include <glm/glm.hpp> // Include GLM for vector math
#include <vector>

namespace VersaEngine {
    namespace AI {

        class Pathfinding; // Forward declaration of the Pathfinding class

        class Agent {
        public:
            Agent();
            ~Agent();

            void Update(float deltaTime);
            void SetGoal(const glm::vec3& goalPosition);

            // Getter methods for position and velocity (you might need these for other parts of the engine)
            glm::vec3 GetPosition() const { return position_; }
            glm::vec3 GetVelocity() const { return velocity_; }

        protected:
            // Member variables
            glm::vec3 position_;
            glm::vec3 velocity_;
            glm::vec3 goalPosition_;
            bool hasGoal_ = false;
            float maxSpeed_;
            Pathfinding* pathfinding_;
            // ... (Add other member variables as needed)
        };

    } // namespace AI
} // namespace VersaEngine

#endif // AGENT_H