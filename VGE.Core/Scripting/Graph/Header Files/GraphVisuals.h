#pragma once
#ifndef GRAPHVISUALS_H
#define GRAPHVISUALS_H


#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "GraphPin.h"

namespace VGE {
	namespace Core {
		namespace Scripting {
			class GraphVisual {
			public:
				GraphVisual();
				GraphVisual(const std::string& name, const glm::vec2& position, const glm::vec2& size);
				~GraphVisual();
				void SetName(const std::string& name);
				std::string GetName();
				void SetPosition(const glm::vec2& position);
				glm::vec2 GetPosition();
				void SetSize(const glm::vec2& size);
				glm::vec2 GetSize();
				void AddPin(GraphPin* pin);
				void RemovePin(GraphPin* pin);
				std::vector<GraphPin*> GetPins();
				GraphPin* GetPin(const std::string& name);
			private:
				std::string Name;
				glm::vec2 Position;
				glm::vec2 Size;
				std::vector<GraphPin*> Pins;
			};

		}
	}
}

#endif // GRAPHVISUALS_H