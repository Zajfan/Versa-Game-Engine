#pragma once
#ifndef VGE_CORE_SCRIPTING_GRAPH_H
#define VGE_CORE_SCRIPTING_GRAPH_H

#include <vector>
#include <set>
#include <stack>
#include <algorithm>

#include "Node.h"
#include "Connection.h"

namespace VGE {
	namespace Core {
		namespace Scripting {
			class Graph {
			public:
				Graph();
				~Graph();
				void AddNode(Node* node);
				void RemoveNode(Node* node);
				Node* FindNodeById(int id);
				void CreateConnection(Node* source, Pin* sourcePin, Node* target, Pin* targetPin);
				void RemoveConnection(Connection* connection);
				std::vector<Node*> GetNodes();
				std::vector<Connection*> GetConnections();
				std::vector<Node*> FindNodesByTag(const std::string& tag);
				std::vector<Node*> TopologicalSort();
			private:
				std::vector<Node*> Nodes;
				std::vector<Connection*> Connections;
				void TopologicalSortUtil(Node* node, std::set<Node*>& visited, std::stack<Node*>& stack);
			};
		} // namespace Scripting
	} // namespace Core
} // namespace VGE

#endif // VGE_CORE_SCRIPTING_GRAPH_H