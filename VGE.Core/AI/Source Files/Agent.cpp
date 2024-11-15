#include "VersaEngine/AI/Agent.h"
#include "VersaEngine/AI/Pathfinding.h"

namespace VersaEngine {
    namespace AI {

        Agent::Agent() {
            // Initialize member variables
            position_ = glm::vec3(0.0f);
            velocity_ = glm::vec3(0.0f);
            maxSpeed_ = 5.0f; // Example value
            pathfinding_ = new Pathfinding(); // Create an instance of your pathfinding system
        }

        Agent::~Agent() {
            delete pathfinding_;
        }

        void Agent::Update(float deltaTime) {
            // 1. Update agent's state based on current goal
            if (hasGoal_) {
                // a. Get path to goal from pathfinding_
                std::vector<glm::vec3> path = pathfinding_->FindPath(position_, goalPosition_);

                // b. If a path is found, follow it
                if (!path.empty()) {
                    glm::vec3 target = path[0]; // Get the next waypoint
                    glm::vec3 direction = glm::normalize(target - position_);
                    velocity_ = direction * maxSpeed_;

                    // c. Move the agent
                    position_ += velocity_ * deltaTime;

                    // d. Check if reached the current waypoint
                    if (glm::distance(position_, target) < 0.1f) { // Example threshold
                        path.erase(path.begin()); // Remove the reached waypoint
                    }
                }
                else {
                    // No path found, handle accordingly (e.g., stop, replan)
                    hasGoal_ = false;
                }
            }

            // 2. (Optional) Apply other AI behaviors here
            //    - Collision avoidance
            //    - Animation updates
            //    - ...
        }

        void Agent::SetGoal(const glm::vec3& goalPosition) {
            goalPosition_ = goalPosition;
            hasGoal_ = true;
        }

    } // namespace AI
} // namespace VersaEngine