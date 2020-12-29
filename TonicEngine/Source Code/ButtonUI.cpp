#include "ButtonUI.h"
#include "ModuleUserInterface.h"

ButtonUI::ButtonUI(ComponentButton* button)
{
	button = Cbutton;
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
	App->ui->SetUIRenderSettings();

	return true;
}
