#include "ImageUI.h"
#include "ContainerUI.h"
#include "glew/include/GL/glew.h"

ImageUI::ImageUI(ComponentImage* image)
{
	Cimage = image;
}

ImageUI::~ImageUI()
{
}

bool ImageUI::Start()
{
	return true;
}

bool ImageUI::Update()
{
	return true;
}

bool ImageUI::CleanUp()
{
	return true;
}

bool ImageUI::Draw()
{
	DrawImageTexture();

	return true;
}

void ImageUI::DrawImageTexture()
{
	ComponentContainer* rtransform = (ComponentContainer*)Cimage->object->GetComponent(COMPONENT_TYPE::CONTAINER_UI);
	ComponentTransform* trans = rtransform->GetTransform();

	App->ui->SetUIRenderSettings();

	float4x4 view_mat = float4x4::identity;

	if (trans)
	{
		GLfloat matrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		view_mat.Set((float*)matrix);

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf((GLfloat*)((trans->globalMatrix).Transposed() * view_mat).v);
	}

	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, container_image->GetMesh()->data.id_vertex);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	if (image_texture != nullptr)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, container_image->GetMesh()->data.id_tex_coords);

		glBindTexture(GL_TEXTURE_2D, 0); // bind container_image texture

		glTexCoordPointer(3, GL_FLOAT, 0, NULL);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, container_image->GetMesh()->data.id_index);
	glDrawElements(GL_TRIANGLES, container_image->GetMesh()->data.num_index, GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (container_image != nullptr)
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glDisableClientState(GL_VERTEX_ARRAY);

	if (trans)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf((GLfloat*)view_mat.v);
	}
}

ContainerUI* ImageUI::GetContainer()
{
	return container_image;
}

void ImageUI::ResizeImage(float2 size)
{
	
}

void ImageUI::CreateContainerImage()
{
	container_image = new ContainerUI();
}

void ImageUI::SetImageID(int new_img_id)
{
	img_id = new_img_id;
}

int ImageUI::GetImageID()
{
	return img_id;
}

void ImageUI::SetTextureToImageUI(ResourceTexture* new_img_tex)
{
	image_texture = new_img_tex;
}

ResourceTexture* ImageUI::GetMaterial()
{
	return image_texture;
}
