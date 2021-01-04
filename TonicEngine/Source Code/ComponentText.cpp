#include "ComponentText.h"
#include "TextUI.h"
#include "ModuleSceneIntro.h"

ComponentText::ComponentText(GameObject* parent) : Component(COMPONENT_TYPE::TEXT_UI, parent)
{
	type = COMPONENT_TYPE::TEXT_UI;
	object = parent;

	text = new TextUI(this);
}

ComponentText::~ComponentText()
{
}

bool ComponentText::Start()
{
	return true;
}

bool ComponentText::Update()
{
	return true;
}

bool ComponentText::CleanUp()
{
	return true;
}

void ComponentText::Draw()
{
	text->Draw();
}

void ComponentText::DrawInspector()
{
	ComponentText* go = (ComponentText*)object->GetComponent(COMPONENT_TYPE::TEXT_UI);

	ImGui::Spacing();

	if (ImGui::CollapsingHeader("UI - Text", ImGuiTreeNodeFlags_DefaultOpen) && go != nullptr)
	{
		ImGui::Spacing();

		if (go != nullptr)
		{
			if (ImGui::InputText("Text", go->text->inspector_text, 100))
				go->text->SetText(go->text->inspector_text);
		}

	}
}
