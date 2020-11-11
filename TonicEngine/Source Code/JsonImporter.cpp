#include "JsonImporter.h"
#include "Application.h"

#include <assert.h>
#include <fstream>
#include <iomanip>

JsonImporter::JsonImporter()
{
}

JsonImporter::~JsonImporter()
{
}

void JsonImporter::SaveJSON()
{
	json configData;

	configData["Application"]["Name"] = App->appName;

	std::list<Module*>::iterator it = App->list_modules.begin();

	// Save JSON data to all modules
	while (it != App->list_modules.end())
	{
		(*it)->Save(configData);
		it++;
	}

	std::ofstream stream;
	stream.open(App->jsonPath);
	stream << std::setw(4) << configData << std::endl;
	stream.close();
}

void JsonImporter::LoadJSON()
{
	json configData;

	assert(App->jsonPath != nullptr);

	std::ifstream stream;
	stream.open(App->jsonPath);

	std::list<Module*>::iterator it = App->list_modules.begin();

	configData = json::parse(stream);

	stream.close();

	std::string name = configData["Application"]["Name"];
	App->appName = name;

	// Load JSON data to all modules
	while (it != App->list_modules.end())
	{
		(*it)->Load(configData);
		it++;
	}
}
