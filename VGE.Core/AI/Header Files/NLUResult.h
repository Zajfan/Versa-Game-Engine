#pragma once
#ifndef VGE_CORE_AI_NLU_RESULT_H
#define VGE_CORE_AI_NLU_RESULT_H

#include <string>
#include <vector>

namespace VGE {
	namespace AI {
		namespace Core {
			// Represents the result of natural language understanding (NLU)
			struct NLUResult {
				std::string intent; // The intent of the user's input
				std::vector<std::string> entities; // The entities extracted from the user's input
			};
		} // namespace Core
	} // namespace AI
} // namespace VGE

#endif // VGE_CORE_AI_NLU_RESULT_H

