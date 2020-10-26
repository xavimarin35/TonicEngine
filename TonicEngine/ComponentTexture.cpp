#include "ComponentTexture.h"
#include "ModuleGUI.h"

ComponentTexture::ComponentTexture(GameObject* gameObject, bool active) : Component(COMPONENT_TYPE::TEXTURE, gameObject)
{
}

ComponentTexture::~ComponentTexture()
{
}

void ComponentTexture::Draw()
{
}
