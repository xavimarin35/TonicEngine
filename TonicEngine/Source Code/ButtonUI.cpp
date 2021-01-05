#include "ButtonUI.h"
#include "ModuleUserInterface.h"
#include "ModuleGUI.h"

ButtonUI::ButtonUI(ComponentButton* button)
{
	Cbutton = button;
}

ButtonUI::~ButtonUI()
{
}

bool ButtonUI::Start()
{
	return true;
}

bool ButtonUI::Update()
{
	return true;
}

bool ButtonUI::CleanUp()
{
	return true;
}

bool ButtonUI::Draw()
{
	App->ui->UseUIRenderSettings();

	return true;
}
