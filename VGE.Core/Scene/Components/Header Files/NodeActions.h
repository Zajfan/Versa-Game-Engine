#pragma once
#ifndef NODEACTIONS_H
#define NODEACTIONS_H

enum class NodeAction {
	None = 0,

	// Execution and State
	Execute,
	Reset,
	Validate,

	// Data & Connections
	Connect,
	Disconnect,
	SetData,
	GetData,

	// UI & Interaction
	Select,
	Deselect,
	Focus,
	Blur,
	Drag,

	// Context Menu
	OpenContextMenu,

	// ... other potential node actions ...
};

#endif // !NODEACTIONS_H