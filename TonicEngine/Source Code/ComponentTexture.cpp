#include "ComponentTexture.h"
#include "ModuleGUI.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"

ComponentTexture::ComponentTexture(GameObject* gameObject, bool active) : Component(COMPONENT_TYPE::TEXTURE, gameObject)
{
	type = COMPONENT_TYPE::TEXTURE;
}

ComponentTexture::~ComponentTexture()
{
}

bool ComponentTexture::Update()
{
	if (openMenuTex)
		OpenTexturesMenu();
	return true;
}

void ComponentTexture::Draw()
{
	ImGui::Spacing();

	GameObject* go = App->scene_intro->GOselected;

	if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Spacing();

		//if (ImGui::Checkbox("Active", &noTexture))
		//	App->renderer3D->Texture2DView(noTexture);

		//if (go->GetComponentTexture()->active)
		//{
		//	// code
		//}

		ImGui::Checkbox("Active", &go->GetComponentTexture()->active);
		
		if (ImGui::Button("Select Texture")) 
			openMenuTex = true;


		ImGui::Text("File:"); ImGui::SameLine();
		ImGui::TextColored(YELLOW_COLOR, go->GetComponentTexture()->tData.path.c_str());

		ImGui::Text("Texture Size:"); ImGui::SameLine(); ImGui::TextColored(YELLOW_COLOR, "%i",&go->GetComponentTexture()->tData.width); // Not working well
		ImGui::SameLine(); ImGui::Text("x"); ImGui::SameLine(); ImGui::TextColored(YELLOW_COLOR, "%i", &go->GetComponentTexture()->tData.height); // Not working well
		
		ImGui::Image((void*)go->GetComponentTexture()->tData.id, ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
	}
}

void ComponentTexture::OpenTexturesMenu()
{
	if (ImGui::Begin("Select Texture Menu", &openMenuTex, ImGuiWindowFlags_AlwaysAutoResize))
	{
		if (ImGui::ImageButton((void*)App->scene_intro->GOselected->GetComponentTexture()->tData.id, ImVec2(200, 200)))
		{
			App->scene_intro->GOselected->GetComponentTexture()->EnableCheckersTexture = false;
			App->scene_intro->GOselected->GetComponentTexture()->EnableHouseTexture = true;
			openMenuTex = false;
		}
		
		ImGui::SameLine();

		if (ImGui::ImageButton((void*)App->tex_imp->CheckersTexture.id, ImVec2(200, 200)))
		{
			App->scene_intro->GOselected->GetComponentTexture()->EnableHouseTexture = false;
			App->scene_intro->GOselected->GetComponentTexture()->EnableCheckersTexture = true;
			openMenuTex = false;
		}
			

		ImGui::End();
	}
}


