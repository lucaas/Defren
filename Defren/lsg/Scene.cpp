#include "Scene.h"
#include "Node.h"
#include "PlyNode.h"
#include "AnimationNode.h"

Scene::Scene(void)
{
	root = new Node();
	PlyNode *ground = new PlyNode("Scene/ground.ply");
	ground->setColor(0.75f,0.75f,0.5f);
	root->addChild((Node *)ground);

	AnimationNode *anim = new AnimationNode();
	anim->addChild((Node *)new PlyNode("Scene/torus.ply"));
	root->addChild(anim);

	PlyNode *monkey = new PlyNode("Scene/monkey.ply");
	monkey->setColor(0.25f,0.75f,0.75f);
	AnimationNode *anim2 = new AnimationNode();
	anim2->addChild((Node*)monkey);
	root->addChild(anim2);
}

void Scene::render(void) {
	root->render();
}

Scene::~Scene(void)
{
}
