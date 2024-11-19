#ifndef RenderComponent_H
#define RenderComponent_H

#include "Component.h"

namespace VGE
{
	class RenderComponent : public vge::Component
	{
	public:
		RenderComponent();
		~RenderComponent();
		void Update(float deltaTime) override;
		void Render() override;
		void Render(const glm::mat4& parentTransform) override;
	};
}

#endif // RenderComponent_H