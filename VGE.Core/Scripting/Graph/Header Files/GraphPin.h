// GraphPin.h
#ifndef GRAPHPIN_H
#define GRAPHPIN_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace VGE {
	namespace Core {
		namespace Scripting {
			class GraphPin {
			public:
				GraphPin();
				GraphPin(const std::string& name, const std::string& type, const glm::vec2& position);
				~GraphPin();
				void SetName(const std::string& name);
				std::string GetName();
				void SetType(const std::string& type);
				std::string GetType();
				void SetPosition(const glm::vec2& position);
				glm::vec2 GetPosition();
			private:
				std::string Name;
				std::string Type;
				glm::vec2 Position;
			};
		}
	}
}

#endif // GRAPHPIN_H
