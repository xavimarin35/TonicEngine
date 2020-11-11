#ifndef __ModuleH__
#define __ModuleH__

#include "Globals.h"
#include "JsonImporter.h"
#include "Application.h"

#include <string>

class Application;
class JsonImporter;

class Module
{
private :
	bool enabled;

public:
	Application* App;

	Module(Application* parent, bool start_enabled = true) : App(parent)
	{}

	virtual ~Module()
	{}

	virtual bool Init() 
	{
		return true; 
	}

	virtual bool Start()
	{
		return true;
	}

	virtual bool Draw()
	{
		return true;
	}

	virtual update_status PreUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}

	// Call them in every module we want to save JSON data
	virtual void Load(const nlohmann::json& config) 
	{}

	virtual void Save(nlohmann::json& config)
	{}
};

#endif __ModuleH__