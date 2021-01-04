#include "ComponentContainer.h"
#include "ComponentTransform.h"
#include "Application.h"
#include "ComponentMesh.h"
#include "ResourceMesh.h"
#include "GameObject.h"
#include "ModuleGUI.h"
#include "ModuleRenderer3D.h"

ComponentContainer::ComponentContainer(GameObject* parent) : Component(COMPONENT_TYPE::CONTAINER_UI, parent)
{
	type = COMPONENT_TYPE::CONTAINER_UI;

	object = parent;

	transf = new ComponentTransform(parent);

	transf->position = float3::zero;
	transf->rotation_quaternion = Quat::identity;
	transf->scale = float3::one;

	anchor.min_x = anchor.min_y = anchor.max_x = anchor.max_y = 0.5;

	relative_pos = { 0,0 };
}

ComponentContainer::~ComponentContainer()
{
	delete transf;
}

bool ComponentContainer::Start()
{
	CreateQuad();

	scale = { 1,1,1 };

	return true;
}

bool ComponentContainer::Update()
{
	UpdateRectAnchors();

	return true;
}

bool ComponentContainer::CleanUp()
{
	return true;
}

void ComponentContainer::Draw()
{
	DrawFrame();

	ComponentContainer* parent_container = nullptr;

	if (object->GOparent)
	{
		parent_container = object->GOparent->container;

		float3 parent_pos = parent_container->GetTransform()->GetPosition();

		float3 start_pos;
		start_pos.x = parent_pos.x - parent_container->width / 2;
		start_pos.y = parent_pos.y - parent_container->height / 2;

		float3 anchor_minX, anchor_minY;

		anchor_minX = start_pos;
		anchor_minX.x += parent_container->width * anchor.min_x;

		DrawAnchorPoint(anchor_minX, { 10,10 });

		anchor_minY = start_pos;
		anchor_minY.y += parent_container->height * anchor.min_y;

		DrawAnchorPoint(anchor_minY, { -10,-10 });
	}

	//DebugDrawSize();
}

void ComponentContainer::DrawInspector()
{
}

void ComponentContainer::DrawAnchorPoint(float3 pos, float2 length)
{
	glLineWidth(5.0f);

	glBegin(GL_LINES);

	glColor4f(1.0f, .0f, .0f, 1.0f);

	glVertex3f(pos.x, pos.y, pos.z);
	glVertex3f(pos.x - length.x, pos.y, pos.z);

	glVertex3f(pos.x, pos.y, pos.z);
	glVertex3f(pos.x, pos.y + length.y, pos.z);

	glEnd();
}

void ComponentContainer::Rect2ScreenSize()
{
	float2 screen_size = float2(App->gui->Pgame->size.x, App->gui->Pgame->size.y);
	Resize(screen_size);
}

void ComponentContainer::CreateQuad()
{
	mesh = new ResourceMesh(App->GenerateUUID());
	width = height = 1;
	mesh->LoadInMemory();
}

void ComponentContainer::DrawFrame()
{	
}

void ComponentContainer::Resize(float2 new_size)
{
	float2 half = new_size / 2;

	mesh->data.vertex[0] = { -half.x, half.y, 0 };
	mesh->data.vertex[1] = { half.x, half.y, 0 };
	mesh->data.vertex[2] = { -half.x, -half.y, 0 };
	mesh->data.vertex[3] = { half.x, -half.y, 0 };

	width = new_size.x;
	height = new_size.y;

	float3 pos = { half.x, half.y, 0 };

	GetTransform()->SetPosition(pos);

	for (auto it = object->componentsList.begin(); it != object->componentsList.end(); it++)
		(*it)->FitToRect();
}

float2 ComponentContainer::GetRelativePos() const
{
	return relative_pos;
}

void ComponentContainer::SetRelativePos(float2 new_pos)
{
	relative_pos = new_pos;
}

void ComponentContainer::UpdateRectAnchors()
{
	float3 real_pos = transf->GetPosition();
	float3 parent_pos = { 0,0,0 };

	ComponentContainer* parent_container = nullptr;
	ComponentTransform* parent_transform = nullptr;

	if (object->GOparent)
		parent_container = object->GOparent->container;

	if (parent_container)
	{
		parent_transform = parent_container->transf;

		parent_pos = parent_transform->GetPosition();

		float2 start_pos = { parent_pos.x - parent_container->width, parent_pos.y - parent_container->height };

		real_pos.y = (start_pos.y + (anchor.min_y * parent_container->height) + relative_pos.y);
		real_pos.x = (start_pos.x + (anchor.min_x * parent_container->width) + relative_pos.x);

		transf->SetPosition(real_pos);
	}
}

ComponentTransform* ComponentContainer::GetTransform()
{
	return transf;
}

void ComponentContainer::SetAnchorPoint(float minX, float minY, float maxX, float maxY)
{
	ComponentContainer* parent_container = nullptr;

	if (object->GOparent)
	{
		parent_container = object->GOparent->container;
	}

	float x_offset = (minX - anchor.min_x) * parent_container->width;
	float y_offset = (minY - anchor.min_y) * parent_container->height;

	relative_pos.x -= x_offset;
	relative_pos.y -= y_offset;

	anchor.min_x = minX;
	anchor.min_y = minY;
	anchor.max_x = maxX;
	anchor.max_y = maxY;
}

AnchorPoints ComponentContainer::GetAnchorPoint() const
{
	return anchor;
}