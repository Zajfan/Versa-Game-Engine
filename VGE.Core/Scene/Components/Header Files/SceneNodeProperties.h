#pragma once
#ifndef NODEPROPERTIES_H
#define NODEPROPERTIES_H

enum class NodePropertyType {
	None = 0,

	// Basic Properties
	Name,
	Type,
	Position,
	Size,

	// Appearance
	Color,
	BorderColor,
	BorderWidth,
	BorderRadius,

	// Shadow (consider grouping these)
	ShadowColor,
	ShadowOffset,
	ShadowBlur,
	// ... other shadow properties

	// State
	Visible,
	Enabled,
	Focused,
	Hovered,

	// Interaction
	Pressed,
	Dragged,

	// ... other essential node properties ...
};

#endif // NODEPROPERTIES_H
