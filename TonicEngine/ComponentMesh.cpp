#include "ComponentMesh.h"

ComponentMesh::ComponentMesh(GameObject* gameObject, bool active) : Component(COMPONENT_TYPE::MESH, gameObject)
{
}

ComponentMesh::~ComponentMesh()
{
}

void ComponentMesh::Draw()
{
}

void ComponentMesh::DrawFaceNormals()
{
}

void ComponentMesh::DrawVertexNormals()
{
}
