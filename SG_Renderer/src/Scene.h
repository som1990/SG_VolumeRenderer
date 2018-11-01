#ifndef Scene_h__
#define Scene_h__
#include "Camera.h"
#include "VolumeObject.h"
#include "PointLight.h"
#include <map>
#include <string>
#include <memory>
#include <vector>

class Scene
{
public:
	Scene(){}
	void createCam(const lux::Vector &position, const lux::Vector& direction, const lux::Vector& upDir, const float &fov, const float &aRatio);
	const std::shared_ptr<obj::Camera>& getCam() const { return cam; }
	void addObject(const std::string &name, std::shared_ptr<obj::VolumeObject> object);
	void addLight(const std::string &name, std::shared_ptr<obj::Light> light);

	void removeLight(const std::string &name);
	void removeObject(const std::string &name);
	
	const std::shared_ptr<obj::VolumeObject> getObject(const std::string &name) const;
	const std::shared_ptr<obj::Light> getLight(const std::string &name) const;

	const std::map<std::string, std::shared_ptr<obj::Light>>& getLights() const { return lightList; }
	const std::map<std::string, std::shared_ptr<obj::VolumeObject>>& getObjList() const { return objList; }


private:
	std::shared_ptr<obj::Camera> cam;
	std::map<std::string, std::shared_ptr<obj::VolumeObject>> objList;
	std::map<std::string, std::shared_ptr<obj::Light>> lightList;
	
	
};


#endif // Scene_h__
