// Last write: 03/07/2021 12:00:00 +00:00
// Date: 03/07/2021
// Description: Implementation of the GraphExecutor class.
#pragma once
#ifndef GRAPHEXECUTOR_H
#define GRAPHEXECUTOR_H

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <set>
#include <stack>

#include "Node.h"
#include "Connection.h"
#include "Pin.h"
#include "Function.h"
#include "Event.h"
#include "Data.h"
#include "State.h"
#include "Hierarchy.h"
#include "Tags.h"
#include "CustomProperties.h"
#include "Position.h"
#include "Size.h"
#include "Color.h"
#include "VisualStyle.h"
#include "Name.h"
#include "Comment.h"
#include "Graph.h"

class GraphExecutor
{
public:
    static void Execute(Graph& graph);

private:
	static void TopologicalSort(Graph& graph, std::vector<Node*>& sortedNodes);
	static void ExecuteNode(Node* node);
	static void ExecuteConnection(Connection* connection);
	static void ExecutePin(Pin* pin);
	static void ExecuteFunction(Function* function);
	static void ExecuteEvent(Event* event);
	static void ExecuteData(Data* data);
	static void ExecuteState(State* state);
	static void ExecuteHierarchy(Hierarchy* hierarchy);
	static void ExecuteTags(Tags* tags);
	static void ExecuteCustomProperties(CustomProperties* customProperties);
	static void ExecutePosition(Position* position);
	static void ExecuteSize(Size* size);
	static void ExecuteColor(Color* color);
	static void ExecuteVisualStyle(VisualStyle* visualStyle);
	static void ExecuteName(Name* name);
	static void ExecuteComment(Comment* comment);

};

#endif // GRAPHEXECUTOR_H
