#include "ComponentCanvas.h"
#include "CanvasUI.h"
#include "ModuleSceneIntro.h"
#include "ModuleGUI.h"
#include "ModuleUserInterface.h"

ComponentCanvas::ComponentCanvas(GameObject* parent) : Component(COMPONENT_TYPE::CANVAS_UI, parent)
{
	type = COMPONENT_TYPE::CANVAS_UI;
	object = parent;
	render_elements = true;

	canvas = new CanvasUI(this);
	App->ui->AddCanvasGO(object);

}

ComponentCanvas::~ComponentCanvas()
{
}

bool ComponentCanvas::Start()
{
	canvas->Start();
	
	return true;
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
	if (!render_elements)
		return;

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (std::vector<GameObject*>::iterator it = canvas->canvas_elements.begin(); it != canvas->canvas_elements.end(); it++)
	{
		(*it)->Draw();
	}
}

void ComponentCanvas::DrawInspector()
{
	GameObject* go = App->scene_intro->GOselected;

	ImGui::Spacing();

	if (ImGui::CollapsingHeader("UI - Canvas", ImGuiTreeNodeFlags_DefaultOpen) && go->GetComponentCanvasUI() != nullptr)
	{
		ImGui::Spacing();

		ImGui::Text("This is the Canvas component");
	}
	
}

void ComponentCanvas::CreateElementInCanvas(GameObject* element)
{
	if (element != nullptr)
		canvas->canvas_elements.push_back(element);
	else
	{
		LOG_C("ERROR: Couldn't create the UI element to the canvas");
	}
}

