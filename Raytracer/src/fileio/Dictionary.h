#pragma once

#include "..\scene\Camera.h"

#include <string>
#include <vector>
#include <fstream>
#include <map>

class Dictionary;

class DictObject
{
public:
	DictObject(std::string name) : m_name(name) {}

	// Override this function if DictObject has function
	virtual void ParseObjectMethod(std::vector<std::string>::iterator lineIter, std::vector<std::string>& lines) { }

protected:
	std::string m_name;

	friend class Dictionary;
};

class CameraObject : public DictObject
{
public:
	CameraObject(std::string name, Camera* camera) 
		: DictObject(name), m_camera(camera) {}
private:
	Camera* m_camera;
};

class Dictionary
{
public:
	void Add(std::string name, std::shared_ptr<DictObject> object)
	{
		strObjPair.insert({ name, object });
	}

	DictObject* Get(std::string name)
	{
		return strObjPair[name].get();
	}

	bool Contains(std::string name)
	{
		return strObjPair.count(name);
	}

private:
	std::map<std::string, std::shared_ptr<DictObject>> strObjPair;
};
