#pragma once
#include <vector>


class Node
{
public:
	Node(void);
	~Node(void);
	void addChild(Node *node);
	virtual void render(void);
protected:
	std::vector<Node *> *children;
};

