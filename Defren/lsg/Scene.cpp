#include "Scene.h"
#include "Node.h"
#include "PlyNode.h"
#include "AnimationNode.h"
#include "../../libs/include/glm/gtx/random.hpp"

Scene::Scene(void)
{
	root = new Node();
	/*
	PlyNode *ground = new PlyNode("Scene/ground.ply");
	ground->setColor(0.75f,0.75f,0.5f);
	root->addChild((Node *)ground);
	*/
	
	AnimationNode *anim = new AnimationNode();
	anim->addChild(new PlyNode("Scene/monkey.ply"));
	root->addChild(anim);

	/*
	PlyNode *monkey = new PlyNode("Scene/monkey.ply");
	monkey->setColor(0.75f,0.75f,0.75f);
	
	AnimationNode *anim2 = new AnimationNode();
	anim2->addChild((Node*)monkey);
	
	root->addChild(monkey);
	*/

	for (int i=0; i < 50; ++i) {
		glm::vec3 position = glm::vecRand3(5.0f,10.0f);
		glm::vec3 color = glm::vecRand3(0.5f,1.0f);

		PointLight light1 = PointLight(position);
		light1.setColor(color);
		lights.push_back(light1);
	}

	/*
	PointLight light2 = PointLight(-10.0f,0.0f,0.0f);
	light2.setColor(0.0f,1.0f,0.0f);
	lights.push_back(light2);
	
	PointLight light3 = PointLight(0.0f,1.0f,0.0f);
	light3.setColor(0.0f,0.0f,1.0f);
	lights.push_back(light3);
	*/
}

void Scene::render(void) {
	root->render();
}

Scene::~Scene(void)
{
}
