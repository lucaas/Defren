#include "Scene.h"
#include "Node.h"
#include "PlyNode.h"
#include "PlaneNode.h"
#include "AnimationNode.h"
#include "RotationNode.h"
#include "ScaleNode.h"
#include "TranslationNode.h"
#include "../../libs/include/glm/gtx/random.hpp"
#define M_PI 3.141592653589793238462643
Scene::Scene(void)
{
	root = new Node();
	PlyNode *ground = new PlyNode("Scene/ground-2.ply");
	ground->setColor(0.5f,0.5f,0.5f);

	RotationNode *rotation = new RotationNode();
	rotation->setRotation(90,0,0);
	ScaleNode *scale = new ScaleNode();
	scale->setScale(50.0f, 50.0f, 50.0f);
	rotation->addChild(ground);
	scale->addChild(rotation);
	root->addChild(scale);
	
	TranslationNode *trans = new TranslationNode();
	trans->setTranslation(0.0f,-0.1f,0.0f);
	trans->addChild(new PlaneNode());
	root->addChild(trans);

	AnimationNode *anim2 = new AnimationNode();
	PlyNode* monkey = new PlyNode("Scene/monkey.ply");
	monkey->setColor(0.5f, 1.0f, 0.5f);
	anim2->addChild(monkey);
	root->addChild(anim2);


	TranslationNode *trans2 = new TranslationNode();
	trans2->setTranslation(5.0f,1.0f,-5.0f);
	PlyNode *sphere = new PlyNode("Scene/sphere-medium.ply");
	sphere->setColor(1.0f, 0.25f, 0.25f);
	trans2->addChild(sphere);
	root->addChild(trans2);

	PointLight light = PointLight(glm::vec3(10.0f ,5.0f, 10.0f));
	light.setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	light.setIntensity(1.0f);
	lights.push_back(light);
	
	PointLight light2 = PointLight(glm::vec3(-10.0f ,5.0f, 10.0f));
	light2.setColor(glm::vec3(0.0f, 1.0f, 0.0f));
	light2.setIntensity(1.0f);
	lights.push_back(light2);
	

	PointLight light3 = PointLight(glm::vec3(0 ,5.0f, -10.0f));
	light3.setColor(glm::vec3(0.0f, 1.0f, 1.0f));
	light3.setIntensity(1.0f);
	lights.push_back(light3);

	for (int i=0; i < 17; ++i) {
		glm::vec3 position = glm::vecRand3(8.0f,10.0f);
		glm::vec3 color = glm::vecRand3(1.0f,1.0f);
		//glm::vec3 color = glm::vec3(1.0f, 0.9f, 0.9f);
		position.y += 10.0f;
		PointLight light1 = PointLight(position);
		light1.setColor(color);
		light1.setIntensity(0.25f);
		lights.push_back(light1);
	}
}

void Scene::defaultScene() {
	PlyNode *ground = new PlyNode("Scene/ground-2.ply");
	ground->setColor(0.5f,0.5f,0.5f);

	RotationNode *rotation = new RotationNode();
	rotation->setRotation(90,0,0);
	ScaleNode *scale = new ScaleNode();
	scale->setScale(50.0f, 50.0f, 50.0f);
	rotation->addChild(ground);
	scale->addChild(rotation);
	root->addChild(scale);
	
	//root->addChild(new PlaneNode());
	for (int i=0; i < 10; i++) {
		TranslationNode *trans = new TranslationNode();
		glm::vec3 position = glm::vecRand3(20.0f,20.0f);
		position.y = 2.0f;
		trans->setTranslation(position);
		//AnimationNode *anim = new AnimationNode();
		trans->addChild(new PlyNode("Scene/sphere-medium.ply"));
		//trans->addChild(anim);
		root->addChild(trans);
	}
	/*

	for (int i=0; i < 10; i++) {
		TranslationNode *trans = new TranslationNode();
		RotationNode *rot = new RotationNode();
		glm::vec3 position = glm::vecRand3(2.0f,20.0f);
		position.y = 2.0f;
		trans->setTranslation(position);
		rot->setRotation(glm::vecRand3(0.0f,180.0f));
		trans->addChild(new PlyNode("Scene/torus.ply"));
		rot->addChild(trans);
		root->addChild(rot);
	}
	*/


	/*
	PlyNode *monkey = new PlyNode("Scene/monkey.ply");
	monkey->setColor(0.75f,0.75f,0.75f);
	
	AnimationNode *anim2 = new AnimationNode();
	anim2->addChild((Node*)monkey);
	
	root->addChild(monkey);
	*/
	

	
	/*
	PointLight light = PointLight(glm::vec3(0.0f ,2.0f, 10.0f));
	light.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	light.setIntensity(1.0f);
	lights.push_back(light);
	*/
	PointLight light = PointLight(glm::vec3(10.0f ,5.0f, 10.0f));
	light.setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	light.setIntensity(1.0f);
	lights.push_back(light);
	
	PointLight light2 = PointLight(glm::vec3(-10.0f ,5.0f, 10.0f));
	light2.setColor(glm::vec3(0.0f, 1.0f, 0.0f));
	light2.setIntensity(1.0f);
	lights.push_back(light2);
	

	PointLight light3 = PointLight(glm::vec3(0 ,5.0f, -10.0f));
	light3.setColor(glm::vec3(0.0f, 1.0f, 1.0f));
	light3.setIntensity(1.0f);
	lights.push_back(light3);

	/*
	for (int i=0; i < 50; ++i) {
		glm::vec3 position = glm::vecRand3(8.0f,10.0f);
		glm::vec3 color = position / 10.0f;
		//glm::vec3 color = glm::vec3(1.0f, 0.9f, 0.9f);
		position.y += 10.0f;
		PointLight light1 = PointLight(position);
		light1.setColor(color);
		light1.setIntensity(0.5f);
		lights.push_back(light1);
	}
	*/
}

void Scene::render(void) {

	static float anim = 0;
	anim += 0.01f;
	//lights.at(0).setPosition(glm::vec3(10*sin(anim),5.0f, 10*cos(anim)));
	//lights.at(1).setPosition(glm::vec3(10*sin(anim + M_PI),5.0f, 10*cos(anim + M_PI)));
	root->render();

}

Scene::~Scene(void)
{
}
