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

	if (openMenuTex2)
		OpenTexturesMenu2();

	if (!active)
		texture = NULL;

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

		ImGui::Checkbox("Active", &active);
		
		if (ImGui::Button("Select Texture")) 
			openMenuTex2 = true;


		ImGui::Text("File:"); ImGui::SameLine();
		ImGui::TextColored(YELLOW_COLOR, go->GetComponentTexture()->tData.path.c_str());

		ImGui::Text("Texture Size:"); ImGui::SameLine(); ImGui::TextColored(YELLOW_COLOR, "%i",&go->GetComponentTexture()->tData.width); // Not working well
		ImGui::SameLine(); ImGui::Text("x"); ImGui::SameLine(); ImGui::TextColored(YELLOW_COLOR, "%i", &go->GetComponentTexture()->tData.height); // Not working well
		
		ImGui::Image((void*)go->GetComponentTexture()->texture, ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
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

void ComponentTexture::OpenTexturesMenu2()
{
	if (ImGui::Begin("Select Texture Menu", &openMenuTex2, ImGuiWindowFlags_AlwaysAutoResize))
	{
		if (ImGui::ImageButton((void*)App->scene_intro->GOselected->GetComponentTexture()->texture, ImVec2(200, 200)))
		{
			App->scene_intro->GOselected->GetComponentTexture()->EnableCheckersTexture = false;
			App->scene_intro->GOselected->GetComponentTexture()->EnableHouseTexture = true;
			//texture = App->tex_imp->texture;
			openMenuTex = false;
		}

		ImGui::SameLine();

		if (ImGui::ImageButton((void*)App->tex_imp->checker_texture, ImVec2(200, 200)))
		{
			App->scene_intro->GOselected->GetComponentTexture()->EnableHouseTexture = false;
			App->scene_intro->GOselected->GetComponentTexture()->EnableCheckersTexture = true;
			//texture = App->tex_imp->checker_texture;
			openMenuTex = false;
		}

		ImGui::End();
	}
}

void ComponentTexture::IsTextureComponentActive(GameObject* go)
{
	go = App->scene_intro->GOselected;

	if (go->GetComponentTexture()->active)
	{
		LOG_IMGUI_CONSOLE("Texture Component is active");
	}
	else
	{
		LOG_IMGUI_CONSOLE("ERROR: Texture Component is NOT active");
	}
}


