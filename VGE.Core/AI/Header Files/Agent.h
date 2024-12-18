#ifndef AGENT_H
#define AGENT_H

#include <glm/glm.hpp>
#include "Pathfinding.h"

namespace VGE
{
	namespace AI
	{
		namespace Core
		{
			class Agent
			{
			public:
				Agent();
				~Agent();
				void SetPosition(glm::vec3 position);
				void SetVelocity(glm::vec3 velocity);
				void SetMaxSpeed(float maxSpeed);
				void SetMaxForce(float maxForce);
				glm::vec3 GetPosition();
				glm::vec3 GetVelocity();
				glm::vec3 GetDirection();
				glm::vec3 GetSteeringForce();
				glm::vec3 Seek(glm::vec3 target);
				glm::vec3 Flee(glm::vec3 target);
				glm::vec3 Arrive(glm::vec3 target, float slowingRadius);
				glm::vec3 Pursuit(Agent* target);
				glm::vec3 Evade(Agent* target);
				void Update(float deltaTime);
				float GetMaxSpeed();
				float GetMaxForce();
				void SetGoal(const glm::vec3& goalPosition);
			private:
				glm::vec3 m_position;
				glm::vec3 m_velocity;
				glm::vec3 m_direction;
				glm::vec3 m_steeringForce;
				float m_maxSpeed;
				float m_maxForce;
				Pathfinding* pathfinding_; // Add this line to declare pathfinding_ member variable
				bool hasGoal_;
				glm::vec3 goalPosition_;
			};
		}
	}
}

#endif // AGENT_H
