#ifndef __JSONIMPORTER_H__
#define __JSONIMPORTER_H__

#include "Libraries/JSON/json.hpp"
using json = nlohmann::json;

#include <assert.h>
#include <fstream>
#include <iomanip>

class JsonImporter // actually it's not necessary to create this class
{
public: 
	JsonImporter() {};

};

#endif