#pragma once

#include "Node.h"

class Scene
{
public:
	Scene(void);
	~Scene(void);
	void render(void);

private:
	Node *root;
};

