#include "Scene.h"
#include <iostream>

using namespace std;

void Scene::createCam(const lux::Vector &position, const lux::Vector& direction, const lux::Vector& upDir, const float &fov, const float &aRatio)
{
	cam = make_shared<obj::Camera>(position, direction, upDir, fov, aRatio);
}

void Scene::addObject(const string &name, shared_ptr<obj::VolumeObject> object)
{
	objList.insert(pair<string, shared_ptr<obj::VolumeObject>>(name, object));
}

std::shared_ptr<obj::VolumeObject> Scene::getObject(const std::string& name)
{
	map<string, shared_ptr<obj::VolumeObject>>::iterator it;
	it = objList.find(name);
	if (it != objList.end())
	{
		return it->second;
	}
	return nullptr;
}

void Scene::removeObject(const std::string &name)
{
	map<string, shared_ptr<obj::VolumeObject>>::iterator it;
	it = objList.find(name);
	if (it != objList.end())
	{
		objList.erase(it);
		return;
	}
	cout << "Object '" << name << "' does not exist." << endl;
}

