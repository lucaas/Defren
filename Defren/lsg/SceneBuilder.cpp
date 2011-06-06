#include "SceneBuilder.h"
#include "PlyNode.h"
#include "PointLight.h"

#include <iostream>

SceneBuilder::SceneBuilder(void)
{
}

SceneBuilder::SceneBuilder(char* file)
{
	scene = new Scene();
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(file);
	
	if (result) {
		pugi::xml_node nodes = doc.child("scene");
		pugi::xml_node lights = nodes.child("lights");
				
		for (pugi::xml_node light = lights.child("light"); light; light = light.next_sibling("light")) {
			std::cout << "Processing light: " << light << std::endl;
			pugi::xml_node::iterator it = light.begin();
			pugi::xml_node::iterator end = light.end();
			while (it != end) {
				pugi::xml_node position = light.child("position");
				float x = position.attribute("x").as_float();
				float y = position.attribute("y").as_float();
				float z = position.attribute("z").as_float();
				PointLight plight(x,y,z);

				pugi::xml_node color = light.child("color");				
				float r = color.attribute("r").as_float();
				float g = color.attribute("g").as_float();
				float b = color.attribute("b").as_float();
				plight.setColor(r,g,b);

				float intensity = light.child("intensity").attribute("value").as_float();	
				plight.setIntensity(intensity);

				scene->lights.push_back(plight);

				it++;
				
			}
		}
		for (pugi::xml_node node = nodes.child("node"); node; node = node.next_sibling("node")) {
			std::cout << "Processing node: " << node << std::endl;
			pugi::xml_node::iterator it = node.begin();
			pugi::xml_node::iterator end = node.end();
			while (it != end) {
				std::cout << (*it).name() << std::endl;
				//if (strcmp((*it).name(), "plynode")) {
					char* plyfile = (char *)(*it).attribute("file").value();
					std::cout << (*it).attribute("file").value() << std::endl;
					scene->root->addChild(new PlyNode(plyfile));
				//}

				it++;
				
			}
		}
	}
	else
	{
		std::cerr << "XML [" << file << "] parsed with errors. ]\n";
		std::cerr << "Error description: " << result.description() << "\n";
		std::cerr << "Error offset: " << result.offset << " (error at [..." << (file + result.offset) << "]\n\n";
	}
}

Scene* SceneBuilder::getScene() {
	return scene;
}

SceneBuilder::~SceneBuilder(void)
{
}
