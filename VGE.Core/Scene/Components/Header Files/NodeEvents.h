#pragma once
#ifndef NODEEVENTS_H
#define NODEEVENTS_H

#include <functional>
#include <glm/glm.hpp>

class NodeEvents {
public:
	NodeEvents();
	~NodeEvents();

	// Execution and State
	std::function<void()> OnExecuteBegin;
	std::function<void()> OnExecuteEnd;
	std::function<void()> OnStateChanged;
	std::function<void(const std::string&)> OnError;

	// Data & Connections
	std::function<void()> OnConnect;
	std::function<void()> OnDisconnect;
	std::function<void()> OnDataChanged;

	// UI & Interaction
	std::function<void()> OnSelected;
	std::function<void()> OnDeselected;
	std::function<void()> OnFocus;
	std::function<void()> OnBlur;
	std::function<void(const glm::vec2&)> OnDragStart;
	std::function<void(const glm::vec2&)> OnDragEnd;
	std::function<void(const glm::vec2&)> OnDragMove;

	// Context Menu
	std::function<void()> OnContextMenuOpened;

	// ... other potential node events ...
};

#endif // NODEEVENTS_H