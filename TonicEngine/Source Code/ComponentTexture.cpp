#include "ComponentTexture.h"
#include "ModuleGUI.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleInput.h"
#include "ModuleCamera3D.h"

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

bool ComponentTexture::CleanUp()
{
	if (rTexture != nullptr)
	{
		rTexture->references -= 1;
		rTexture->loaded -= 1;

		if (rTexture->loaded == 0)
			rTexture->ReleaseMemory();
	}

	return true;
}

void ComponentTexture::DrawInspector()
{
	ImGui::Spacing();

	GameObject* go = App->scene_intro->GOselected;
	uint tex;

	if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_DefaultOpen) && go->GetComponentTexture() != nullptr)
	{
		ImGui::Spacing();

		if (active && rTexture != nullptr)
		{
			if (ImGui::Button("Select Texture"))
				openMenuTex = true;

			ImGui::SameLine();

			if (ImGui::Button("Disable Texture"))
				active = false;

			ImGui::Spacing();
			ImGui::Separator();

			if (App->scene_intro->GOselected != nullptr)
			{
				ImGui::Text("File:"); ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "%s", rTexture->file.c_str());
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::TextColored(GREY_COLOR, "%s", rTexture->file.c_str());
					ImGui::EndTooltip();
				}

				ImGui::Separator();

				ImGui::Text("Texture Size:"); ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "%i", rTexture->tex.width);

				ImGui::SameLine(); ImGui::Text("x"); ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "%i", rTexture->tex.height);
			}

			if (EnableAssignedTexture)
				tex = rTexture->tex.id;
			else if (EnableCheckersTexture)
				tex = App->tex_imp->checker_texture.id;

			ImGui::Image((ImTextureID*)tex, ImVec2(310, 310), ImVec2(0, 1), ImVec2(1, 0), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
		}

		else if(!active)
		{
			if (ImGui::Button("Enable Texture"))
				active = true;

			ImGui::SameLine();

			App->gui->HelpMarker("Click 'Enable' button to select a texture");
		}

		else if (rTexture == nullptr)
		{
			ImGui::Spacing();

			App->gui->HelpMarker("This texture has not loaded propertly, but you\ncan select one from the Textures folder!");
		}
	}
}


void ComponentTexture::OpenTexturesMenu()
{
	if (ImGui::Begin("Select Texture Menu", &openMenuTex, ImGuiWindowFlags_AlwaysAutoResize))
	{
		if (ImGui::IsWindowHovered())
			App->camera->isOnSelectTexture = true;		
		else
			App->camera->isOnSelectTexture = false;

		if (ImGui::ImageButton((void*)App->scene_intro->GOselected->GetComponentTexture()->rTexture->tex.id, ImVec2(140, 140), ImVec2(0, 1), ImVec2(1, 0)))
		{
			App->scene_intro->GOselected->GetComponentTexture()->EnableCheckersTexture = false;
			App->scene_intro->GOselected->GetComponentTexture()->EnableAssignedTexture = true;
			openMenuTex = false;
		}

		ImGui::SameLine();

		if (ImGui::ImageButton((void*)App->tex_imp->checker_texture.id, ImVec2(140, 140)))
		{
			App->scene_intro->GOselected->GetComponentTexture()->EnableAssignedTexture = false;
			App->scene_intro->GOselected->GetComponentTexture()->EnableCheckersTexture = true;
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
	LOG_C("Texture path is: %s", texture.path.c_str());
}

void ComponentTexture::Save(uint GO_id, nlohmann::json& scene)
{
	scene[object->data.name]["Components"]["Texture"]["UUID"] = UUID;
	scene[object->data.name]["Components"]["Texture"]["Active"] = active;
	scene[object->data.name]["Components"]["Texture"]["Checkers Texture"] = EnableCheckersTexture;

	if (rTexture != nullptr)
		scene[object->data.name]["Components"]["Texture"]["Name"] = rTexture->exported_file;
}