#include "ComponentCanvas.h"
#include "CanvasUI.h"
#include "ModuleSceneIntro.h"
#include "ModuleGUI.h"
#include "ModuleUserInterface.h"

ComponentCanvas::ComponentCanvas(GameObject* parent) : Component(COMPONENT_TYPE::CANVAS_UI, parent)
{
	type = COMPONENT_TYPE::CANVAS_UI;
	object = parent;

}

ComponentCanvas::~ComponentCanvas()
{
	delete canvas;
}

bool ComponentCanvas::Start()
{
	canvas = new CanvasUI();
	App->ui->AddCanvasGO(object);
	
	return false;
}

bool ComponentCanvas::Update()
{
	canvas->Update();

	return true;
}

bool ComponentCanvas::CleanUp()
{
	return true;
}

void ComponentCanvas::Draw()
{
	for (auto it = canvas->canvas_elements.begin(); it != canvas->canvas_elements.end(); it++)
	{
		(*it)->Draw();
	}
}

void ComponentCanvas::CreateElementInCanvas(GameObject* element)
{
	if (element != nullptr)
		canvas->canvas_elements.push_back(element);
	else
	{
		LOG_C("ERROR: Couldn't create the UI element in the canvas");
	}
}