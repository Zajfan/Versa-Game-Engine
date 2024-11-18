#pragma once
#ifndef VGE_CORE_SCENE_GENERAL_CONNECTION_H
#define VGE_CORE_SCENE_GENERAL_CONNECTION_H

// Include standard library headers
#include <memory> // For std::shared_ptr

// Include project headers
#include "Node.h"
#include "Pin.h"

namespace VGE
{
	// Forward declaration of Node class
	class Node;
	// Forward declaration of Pin class
	class Pin;
	// Connection class
	class Connection
	{
	public:
		// Constructor
		Connection(std::shared_ptr<Node> source, std::shared_ptr<Node> target, std::shared_ptr<Pin> sourcePin, std::shared_ptr<Pin> targetPin);
		// Destructor
		~Connection();
		// Check if the connection is valid
		bool IsValid() const;
	private:
		// Check if the connection is circular
		bool IsCircularConnection() const;
		// Source node
		std::shared_ptr<Node> Source;
		// Target node
		std::shared_ptr<Node> Target;
		// Source pin
		std::shared_ptr<Pin> SourcePin;
		// Target pin
		std::shared_ptr<Pin> TargetPin;
	};
}

#endif // VGE_CORE_SCENE_GENERAL_CONNECTION_H