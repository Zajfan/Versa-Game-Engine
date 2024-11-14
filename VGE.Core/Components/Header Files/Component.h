#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <memory>
#include <glm/glm.hpp>

namespace vge
{
	class Node;
	class Component
	{
	public:
		Component();
		Component(const std::string& name);
		virtual ~Component();
		virtual void Update(float deltaTime);
		virtual void Render();
		virtual void Render(const glm::mat4& parentTransform);
		std::string GetName();
		void SetName(const std::string& name);
		std::shared_ptr<Node> GetNode();
		void SetNode(std::shared_ptr<Node> node);
	protected:
		std::string m_Name;
		std::shared_ptr<Node> m_Node;
	};
}

#endif // COMPONENT_H
