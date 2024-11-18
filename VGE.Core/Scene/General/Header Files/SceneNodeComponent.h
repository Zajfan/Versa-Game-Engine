#ifndef VGE_SCENE_NODE_COMPONENT_H
#define VGE_SCENE_NODE_COMPONENT_H

#include "SceneNode.h"

namespace vge
{
	class SceneNodeComponent : public NodeComponent
	{
	public:
		SceneNodeComponent(Node* owner);
		virtual ~SceneNodeComponent();
		virtual void Initialize() override;
		virtual void Terminate() override;
		virtual void Update(float deltaTime) override;
		virtual void HandleEvent(const Event& event) override;
		virtual std::string GetType() const override;
		virtual void Execute() override;
		virtual void Reset() override;
	};
} // namespace vge
