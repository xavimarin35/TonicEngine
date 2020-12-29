#include "ComponentCanvas.h"
#include "CanvasUI.h"
#include "ModuleSceneIntro.h"
#include "ModuleGUI.h"

ComponentCanvas::ComponentCanvas(GameObject* parent) : Component(COMPONENT_TYPE::CANVAS_UI, parent)
{
	type = COMPONENT_TYPE::CANVAS_UI;
	object = parent;

	canvas = new CanvasUI(this);

	render_elements = true;
}

ComponentCanvas::~ComponentCanvas()
{
}

bool ComponentCanvas::Start()
{
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

	for (std::list<GameObject*>::iterator it = canvas->canvas_elements.begin(); it != canvas->canvas_elements.end(); it++)
	{
		(*it)->Draw();
	}
}

void ComponentCanvas::DrawInspector()
{
	GameObject* go = App->scene_intro->GOselected;

	ImGui::Spacing();

	if (ImGui::CollapsingHeader("Canvas", ImGuiTreeNodeFlags_DefaultOpen) && go->GetComponentCanvasUI() != nullptr)
	{
		ImGui::Spacing();

		ImGui::Text("This is the Canvas component");
	}
	
}

