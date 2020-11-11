#ifndef __JSONIMPORTER_H__
#define __JSONIMPORTER_H__

#include "Libraries/JSON/json.hpp"
using json = nlohmann::json;

class JsonImporter
{
public: 
	JsonImporter();
	~JsonImporter();

	void SaveJSON();
	void LoadJSON();
};


#endif

