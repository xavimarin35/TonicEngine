#include "ComponentImage.h"
#include "ImageUI.h"
#include "ModuleSceneIntro.h"
#include "ModuleGUI.h"

ComponentImage::ComponentImage(GameObject* parent) : Component(COMPONENT_TYPE::IMAGE_UI, parent)
{
	type = COMPONENT_TYPE::IMAGE_UI;
	object = parent;

	image = new ImageUI(this);
}

ComponentImage::~ComponentImage()
{
}

bool ComponentImage::Start()
{
	return true;
}

bool ComponentImage::Update()
{
	if (image != nullptr)
		image->Update();

	return true;
}

bool ComponentImage::CleanUp()
{
	if (image != nullptr)
		image->CleanUp();

	return true;
}

void ComponentImage::Draw()
{
	if (image != nullptr)
		image->Draw();
}

void ComponentImage::DrawInspector()
{
	GameObject* go = App->scene_intro->GOselected;

	ImGui::Spacing();

	if (ImGui::CollapsingHeader("UI - Image", ImGuiTreeNodeFlags_DefaultOpen) && go->GetComponentImageUI() != nullptr)
	{
		ImGui::Spacing();

		ImGui::Text("This is the Image component");

	}
}
