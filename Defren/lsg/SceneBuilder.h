#pragma once
#include "../../libs/include/pugixml/pugixml.hpp"
#include "Scene.h"

class SceneBuilder
{
private:
	Scene* scene;
public:
	SceneBuilder(void);
	SceneBuilder(char *file);
	~SceneBuilder(void);
	Scene* getScene();
};

