#pragma once
#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <string>
#include <vector>
#include <map>
#include <any>
#include <chrono>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/quaternion.hpp>

#include "NodeComponent.h"
#include "GraphEvent.h"
#include "ISelectable.h"
#include "GraphPin.h"
#include "GraphConnection.h"
#include "GraphNode.h"
#include "GraphVisuals.h"
#include "GraphExecution.h"
#include "GraphConnections.h"
#include "GraphData.h"

namespace VGE {
	namespace Core {
		namespace Scripting {
			class Node : public ISelectable {
			public:
				Node();
				Node(const std::string& name, const std::string& tag, const glm::vec2& position);
				~Node();
				void AddComponent(NodeComponent* component);
				void RemoveComponent(NodeComponent* component);
				std::vector<NodeComponent*> GetComponents();
				NodeComponent* GetComponent(const std::string& name);
				void SetName(const std::string& name);
				std::string GetName();
				void SetTag(const std::string& tag);
				std::string GetTag();
				void SetPosition(const glm::vec2& position);
				glm::vec2 GetPosition();
				void SetSize(const glm::vec2& size);
				glm::vec2 GetSize();
				void SetId(int id);
				int GetId();
				void SetGraph(Graph* graph);
				Graph* GetGraph();
				void SetVisuals(GraphVisuals* visuals);
				GraphVisuals* GetVisuals();
				void SetExecution(GraphExecution* execution);
				GraphExecution* GetExecution();
				void SetConnections(GraphConnections* connections);
				GraphConnections* GetConnections();
				void SetData(GraphData* data);
				GraphData* GetData();
				void SetSelected(bool selected);
				bool IsSelected();
				void SetHovered(bool hovered);
				bool IsHovered();
				void SetExpanded(bool expanded);
				bool IsExpanded();
				void SetVisible(bool visible);
				bool IsVisible();
				void SetEnabled(bool enabled);
				bool IsEnabled();
				void SetPinned(bool pinned);
				bool IsPinned();
				void SetColor(const glm::vec4& color);
				glm::vec4 GetColor();
				void SetBorderColor(const glm::vec4& color);
				glm::vec4 GetBorderColor();
				void SetBackgroundColor(const glm::vec4& color);
				glm::vec4 GetBackgroundColor();
				void SetTextColor(const glm::vec4& color);
				glm::vec4 GetTextColor();
				void SetIcon(const std::string& icon);
				std::string GetIcon();
				void SetIconColor(const glm::vec4& color);
				glm::vec4 GetIconColor();
				void SetIconSize(const glm::vec2& size);
				glm::vec2 GetIconSize();
				void SetTitle(const std::string& title);
				std::string GetTitle();
				void SetDescription(const std::string& description);
				std::string GetDescription();
				void SetTooltip(const std::string& tooltip);
				std::string GetTooltip();

#endif // GRAPHNODE_H