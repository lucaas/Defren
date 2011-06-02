#pragma once

#include "Node.h"
#include "PointLight.h"
#include "Camera.h"

class Scene
{
public:
	Scene(void);
	~Scene(void);
	void render(void);
	std::vector<PointLight> lights;

private:
	Node *root;
	Camera *camera;

};

