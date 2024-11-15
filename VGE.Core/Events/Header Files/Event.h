#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <memory>
#include <glm/glm.hpp>

namespace vge
{
	class Node;
	class Event
	{
	public:
		Event();
		Event(const std::string& name);
		virtual ~Event();
		virtual void Initialize();
		virtual void Terminate();
		virtual void Update(float deltaTime);
		virtual void Render();
		virtual void Render(const glm::mat4& parentTransform);
		virtual void HandleEvent(Event event);
		virtual void Execute();
		virtual void Reset();
		std::string GetName();
		void SetName(const std::string& name);
		std::shared_ptr<Node> GetNode();
		void SetNode(std::shared_ptr<Node> node);
	protected:
		std::string m_Name;
		std::shared_ptr<Node> m_Node;
	};
}

#endif // EVENT_H
