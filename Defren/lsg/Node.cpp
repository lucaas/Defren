#include "Node.h"


Node::Node(void)
{
	children = new std::vector<Node *>();
}

void Node::addChild(Node *node) {
	children->push_back(node);
}

void Node::render() {
	std::vector<Node *>::iterator it = children->begin();
	while (it != children->end()) {
		(*it)->render();
		++it;
	}
}

Node::~Node(void)
{
	delete children;
}
