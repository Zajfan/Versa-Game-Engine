#pragma once
#ifndef VGE_CORE_AI_PATHFINDING_H
#define VGE_CORE_AI_PATHFINDING_H

#include <vector>
#include <glm/glm.hpp>

namespace VGE {
	namespace AI {
		namespace Core {
			class Pathfinding {
			public:
				Pathfinding();
				~Pathfinding();
				std::vector<glm::vec3> FindPath(const glm::vec3& start, const glm::vec3& goal);
			};
		} // namespace Core
	} // namespace AI
} // namespace VGE

#endif // VGE_CORE_AI_PATHFINDING_H
