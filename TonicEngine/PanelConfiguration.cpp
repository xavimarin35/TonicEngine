#include "Application.h"
#include "PanelConfiguration.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"

PanelConfiguration::PanelConfiguration() : PanelManager()
{
	
}

PanelConfiguration::~PanelConfiguration()
{
}

bool PanelConfiguration::Start()
{
	return true;
}

bool PanelConfiguration::Draw()
{
	if (App->gui->Pconfig)
	{

	}

	return true;
}
