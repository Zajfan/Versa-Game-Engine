#pragma once
#ifndef NODECHILDREN_H
#define NODECHILDREN_H

#include <vector>

class Node;

class NodeChildren {
public:
	NodeChildren();
	~NodeChildren();

	void AddChild(Node* child);
	void RemoveChild(Node* child);
	Node* GetChild(int index) const;
	const std::vector<Node*>& GetChildren() const;
	int GetNumChildren() const;

private:
	std::vector<Node*> children;
};

#endif // NODECHILDREN_H