#include "Mesh.h"

namespace Dementia{

	Mesh::Mesh(void) :
		Entity(Entity::TYPE::Mesh),
		m_geometry(nullptr),
		m_texture(nullptr),
		m_shader(nullptr)
	{
	}

	Mesh::Mesh(Geometry* geometry) :		
		Entity(Entity::TYPE::Mesh),
		m_geometry(geometry),
		m_texture(nullptr),
		m_shader(nullptr)
	{
		
	}

	Mesh::Mesh(Dementia::Geometry* geometry, Dementia::Texture* texture, Dementia::Shader* shader) :
		Entity(Entity::TYPE::Mesh),
		m_geometry(geometry),
		m_texture(texture),
		m_shader(shader)
	{
	}

	Mesh::~Mesh(void)
	{
	}

}