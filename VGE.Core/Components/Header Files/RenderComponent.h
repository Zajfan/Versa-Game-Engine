#ifndef RenderComponent_H
#define RenderComponent_H

#include "Component.h"

namespace VGE
{
	class RenderComponent : public Component
	{
	public:
		RenderComponent();
		~RenderComponent();
		void Update(float deltaTime) override;
		void Render() override;
	};
}

#endif // RenderComponent_H