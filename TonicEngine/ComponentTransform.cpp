#include "ComponentTransform.h"

ComponentTransform::ComponentTransform(GameObject* gameObject, bool active) : Component(COMPONENT_TYPE::TRANSFORM, gameObject)
{
}

ComponentTransform::~ComponentTransform()
{
}

void ComponentTransform::Draw()
{
}
