#include "ComponentButton.h"
#include "ButtonUI.h"
#include "ModuleSceneIntro.h"
#include "ModuleGUI.h"

ComponentButton::ComponentButton(GameObject* parent) : Component(COMPONENT_TYPE::BUTTON_UI, parent)
{
	type = COMPONENT_TYPE::BUTTON_UI;
	object = parent;

	button = new ButtonUI(this);

	hover_color = { 0.9f, 0.9f, 0.9f };
	pressed_color = { 0.7f, 0.7f, 0.7f };
}

ComponentButton::~ComponentButton()
{
}

bool ComponentButton::Start()
{
	return true;
}

bool ComponentButton::Update()
{
	button->Update();

	return true;
}

bool ComponentButton::CleanUp()
{
	return true;
}

void ComponentButton::Draw()
{
}

void ComponentButton::DrawInspector()
{
	GameObject* go = App->scene_intro->GOselected;

	ImGui::Spacing();

	if (ImGui::CollapsingHeader("Button", ImGuiTreeNodeFlags_DefaultOpen) && go->GetComponentButtonUI() != nullptr)
	{
		ImGui::Spacing();

		ImGui::Text("This is the Button component");
	}
}
