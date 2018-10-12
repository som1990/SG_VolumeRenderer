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

void Scene::addLight(const std::string &name, std::shared_ptr<obj::Light> light)
{
	lightList.insert(pair < string, shared_ptr<obj::Light>>(name, light));
}


void Scene::removeLight(const std::string &name)
{
	map<string, shared_ptr<obj::Light>>::iterator it;
	it = lightList.find(name);
	if (it != lightList.end())
	{
		lightList.erase(it);
		return;
	}
	cout << "Light '" << name << "' does not exist." << endl;
}

/*
void Scene::addObject(const string &name, unique_ptr<obj::VolumeObject> object)
{
	objList.insert(pair<string, unique_ptr<obj::VolumeObject>(new obj::VolumeObject)>(name, object));
}*/

/*
const std::unique_ptr<obj::VolumeObject> Scene::getObject(const std::string& name) 
{
	map<string, unique_ptr<obj::VolumeObject>>::iterator it;
	it = objList.find(name);
	
	return it->second;
	
}*/

const std::shared_ptr<obj::VolumeObject> Scene::getObject(const std::string& name) const
{
	//map<string, shared_ptr<obj::VolumeObject>>::iterator it;
	auto it = objList.find(name);

	return it->second;

}

const std::shared_ptr<obj::Light> Scene::getLight(const std::string &name) const
{
	auto it = lightList.find(name);

	return it->second;
}



