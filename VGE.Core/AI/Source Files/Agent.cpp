// VGE.Core/AI/Source Files/Agent.cpp
#include "Agent.h"
#include "Pathfinding.h"

namespace VGE {
    namespace AI {
        namespace Core {

            Agent::Agent() {
                // Initialize member variables
                m_position = glm::vec3(0.0f);
                m_velocity = glm::vec3(0.0f);
                m_direction = glm::vec3(0.0f);
                m_steeringForce = glm::vec3(0.0f);
                m_maxSpeed = 5.0f; // Example value
                m_maxForce = 1.0f; // Example value
                pathfinding_ = new Pathfinding(); // Create an instance of your pathfinding system
                hasGoal_ = false;
                goalPosition_ = glm::vec3(0.0f); // Initialize goalPosition_
            }

            Agent::~Agent() {
                delete pathfinding_;
            }

            void Agent::Update(float deltaTime) {
                // 1. Update agent's state based on current goal
                if (hasGoal_) {
                    // a. Get path to goal from pathfinding_
                    std::vector<glm::vec3> path = pathfinding_->FindPath(m_position, goalPosition_);

                    // b. If a path is found, follow it
                    if (!path.empty()) {
                        glm::vec3 target = path[0]; // Get the next waypoint
                        glm::vec3 direction = glm::normalize(target - m_position);
                        m_velocity = direction * m_maxSpeed;

                        // c. Move the agent
                        m_position += m_velocity * deltaTime;

                        // d. Check if reached the current waypoint
                        if (glm::distance(m_position, target) < 0.1f) { // Example threshold
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

        } // namespace Core
    } // namespace AI
} // namespace VGE
