#include "Graph.h"
#include "GraphNode.h"
#include "GraphConnection.h"

namespace VGE {
	namespace Core {
		namespace Scripting {

			Graph::Graph() {
				// Constructor implementation
				Nodes = std::vector<Node*>();
				Connections = std::vector<Connection*>();
			}

			Graph::~Graph() {
				// Destructor implementation
			}

			void Graph::AddNode(Node* node) {
				// AddNode implementation
			}

			void Graph::RemoveNode(Node* node) {
				// RemoveNode implementation
			}

			Node* Graph::FindNodeById(int id) {
				// FindNodeById implementation
				return nullptr;
			}

			void Graph::CreateConnection(Node* source, Pin* sourcePin, Node* target, Pin* targetPin) {
				// CreateConnection implementation
			}

			void Graph::RemoveConnection(Connection* connection) {
				// RemoveConnection implementation
			}

			std::vector<Node*> Graph::GetNodes() {
				// GetNodes implementation
				return Nodes;
			}

			std::vector<Connection*> Graph::GetConnections() {
				// GetConnections implementation
				return Connections;
			}

			std::vector<Node*> Graph::FindNodesByTag(const std::string& tag) {
				// FindNodesByTag implementation
				return {};
			}

			std::vector<Node*> Graph::TopologicalSort() {
				std::stack<Node*> stack;
				std::set<Node*> visited;
				std::vector<Node*> sortedNodes;

				for (Node* node : Nodes) {
					if (visited.find(node) == visited.end()) {
						TopologicalSortUtil(node, visited, stack);
					}
				}

				while (!stack.empty()) {
					sortedNodes.push_back(stack.top());
					stack.pop();
				}

				return sortedNodes;
			}

			void Graph::TopologicalSortUtil(Node* node, std::set<Node*>& visited, std::stack<Node*>& stack) {
				visited.insert(node);

				for (Connection* connection : Connections) {
					if (connection->Source == node) {
						Node* targetNode = connection->Target;
						if (visited.find(targetNode) == visited.end()) {
							TopologicalSortUtil(targetNode, visited, stack);
						}
					}
				}

				stack.push(node);
			}

			void Graph::Reset() {
				// Reset implementation
			}

		} // namespace Scripting
	} // namespace Core
} // namespace VGE
