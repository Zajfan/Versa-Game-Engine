// Date: 03/04/2020
// Description: Implementation of the GraphExecutor class.

#include "GraphExecutor.h"

void GraphExecutor::Execute(Graph& graph) {
	std::vector<Node*> sortedNodes;
	TopologicalSort(graph, sortedNodes);
	for (Node* node : sortedNodes) {
		ExecuteNode(node);
	}
	
}

void GraphExecutor::TopologicalSort(Graph& graph, std::vector<Node*>& sortedNodes) {
	std::set<Node*> visited;
	std::stack<Node*> stack;
	for (Node* node : graph.GetNodes()) {
		if (visited.find(node) == visited.end()) {
			TopologicalSortUtil(node, visited, stack);
		}
	}
	while (!stack.empty()) {
		sortedNodes.push_back(stack.top());
		stack.pop();
	}
}

void GraphExecutor::TopologicalSortUtil(Node* node, std::set<Node*>& visited, std::stack<Node*>& stack) {
	visited.insert(node);
	for (Connection* connection : node->GetOutputConnections()) {
		Node* targetNode = connection->GetTargetNode();
		if (visited.find(targetNode) == visited.end()) {
			TopologicalSortUtil(targetNode, visited, stack);
		}
	}
	stack.push(node);
}

void GraphExecutor::ExecuteNode(Node* node) {
	node->Execute();
}

void GraphExecutor::ExecuteConnection(Connection* connection) {
	connection->Execute();
}

void GraphExecutor::ExecutePin(Pin* pin) {
	pin->Execute();
}

void GraphExecutor::ExecuteFunction(Function* function) {
	function->Execute();
}

void GraphExecutor::ExecuteEvent(Event* event) {
	event->Execute();
}

void GraphExecutor::ExecuteData(Data* data) {
	data->Execute();
}

void GraphExecutor::ExecuteState(State* state) {
	state->Execute();
}

void GraphExecutor::ExecuteHierarchy(Hierarchy* hierarchy) {
	hierarchy->Execute();
}

void GraphExecutor::ExecuteTags(Tags* tags) {
	tags->Execute();
}

void GraphExecutor::ExecuteCustomProperties(CustomProperties* customProperties) {
	customProperties->Execute();
}

void GraphExecutor::ExecutePosition(Position* position) {
	position->Execute();
}

void GraphExecutor::ExecuteSize(Size* size) {
	size->Execute();
}

void GraphExecutor::ExecuteColor(Color* color) {
	color->Execute();
}

void GraphExecutor::ExecuteVisualStyle(VisualStyle* visualStyle) {
	visualStyle->Execute();
}

void GraphExecutor::ExecuteName(Name* name) {
	name->Execute();
}

void GraphExecutor::ExecuteComment(Comment* comment) {
	comment->Execute();
}

// ... (Implementations for helper functions)