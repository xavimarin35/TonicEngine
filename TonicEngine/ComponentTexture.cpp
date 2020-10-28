#include "ComponentTexture.h"
#include "ModuleGUI.h"
#include "ModuleSceneIntro.h"

ComponentTexture::ComponentTexture(GameObject* gameObject, bool active) : Component(COMPONENT_TYPE::TEXTURE, gameObject)
{
	type = COMPONENT_TYPE::TEXTURE;
}

ComponentTexture::~ComponentTexture()
{
}

void ComponentTexture::Draw()
{
	ImGui::Spacing();

	GameObject* go = App->scene_intro->GOselected;

	if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Spacing();



	}
}
