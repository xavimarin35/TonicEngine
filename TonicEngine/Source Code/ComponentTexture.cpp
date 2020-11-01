#include "ComponentTexture.h"
#include "ModuleGUI.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleInput.h"

ComponentTexture::ComponentTexture(GameObject* gameObject) : Component(COMPONENT_TYPE::TEXTURE, gameObject)
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
	uint tex = 0;

	if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Spacing();

		if (active)
		{
			if (ImGui::Button("Select Texture"))
				openMenuTex = true;
				
			ImGui::SameLine();

			if (ImGui::Button("Disable Texture"))
				active = false;


			if (App->scene_intro->GOselected != nullptr)
			{
				uint width, height;

				width = App->scene_intro->GOselected->textureWidth;
				height = App->scene_intro->GOselected->textureHeight;

				// It has to be improved, but works
				ImGui::Text("Texture Size:"); ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "%i", width);

				ImGui::SameLine(); ImGui::Text("x"); ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "%i", height);
			}

			if (EnableHouseTexture)
				tex = texture;
			else if (EnableCheckersTexture)
				tex = App->tex_imp->checker_texture;

			ImGui::Image((void*)tex, ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
		}
		else
		{
			if (ImGui::Button("Enable Texture"))
				active = true;

			ImGui::SameLine();

			App->gui->HelpMarker("Click 'Enable' button to select a texture");
		}
	}
}


void ComponentTexture::OpenTexturesMenu()
{
	if (ImGui::Begin("Select Texture Menu", &openMenuTex, ImGuiWindowFlags_AlwaysAutoResize))
	{
		

		if (ImGui::ImageButton((void*)App->scene_intro->GOselected->GetComponentTexture()->texture, ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0)))
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
		LOG_C("Texture Component is active");
	}
	else
	{
		LOG_C("ERROR: Texture Component is NOT active");
	}
}

void ComponentTexture::GetTexturePath()
{
	LOG_C("Texture path is: %s", texture_path.c_str());
}


