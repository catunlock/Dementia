#include "SceneManager.h"

namespace Dementia{
SceneManager::SceneManager(Dementia::Window* window) :
	m_id(0), m_window(window),
	m_rootSceneNode(createNode(XMVectorZero(),XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),XMVectorZero()))
{
	defaultTexture = createTexture(L"textures/default.dds");
}

SceneManager::~SceneManager(void)
{
	for (Dementia::Node* node : nodes)
	{
		delete node;
	}

	for (Dementia::Mesh* mesh : meshes)
	{
		delete mesh;
	}

	for (Dementia::DirectionalLight* directionalLight : directionalLights)
	{
		delete directionalLight;
	}

	for (Dementia::SpotLight* spotLight : spotLights)
	{
		delete spotLight;
	}

	for (Dementia::PointLight* pointLight : pointLights)
	{
		delete pointLight;
	}
}

Dementia::Node* SceneManager::createNode (XMVECTOR position, XMVECTOR scale, XMVECTOR rotation)
{
	Dementia::Node* nodo = new Dementia::Node(getLastId(), position, scale, rotation);
	nodes.push_back(nodo);

	return nodo;
}

Dementia::Mesh* SceneManager::createMesh (Dementia::Geometry* geometry)
{
	Dementia::Mesh* mesh = new Dementia::Mesh(geometry);
	mesh->setTexture(defaultTexture);
	meshes.push_back(mesh);

	return mesh;
}

Dementia::Texture* SceneManager::createTexture(std::wstring path)
{
	Dementia::Texture* texture = new Dementia::Texture();
	HR(D3DX11CreateShaderResourceViewFromFile( m_window->getDevice(), path.c_str(), NULL, NULL, &texture->g_pTextureRV, NULL ));
	
	textures.push_back(texture);
	return texture;
}

DirectionalLight* SceneManager::createDirectionalLight (XMFLOAT4 ambient, XMFLOAT4 diffuse, XMFLOAT4 specular,	XMFLOAT3 direction)
{
	Dementia::DirectionalLight* directionalLight = new Dementia::DirectionalLight(ambient,diffuse,specular,direction,0.0f);
	directionalLights.push_back(directionalLight);

	return directionalLight;
}

SpotLight* SceneManager::createSpotLight (XMFLOAT4 ambient, XMFLOAT4 diffuse, XMFLOAT4 specular, XMFLOAT3 position, float range, XMFLOAT3 direction, float spot, XMFLOAT3 att)
{
	Dementia::SpotLight* spotLight = new Dementia::SpotLight(ambient,diffuse,specular,position,range,direction,spot,att,0.0f);
	spotLights.push_back(spotLight);

	return spotLight;
}

PointLight* SceneManager::createPointLight (XMFLOAT4 ambient, XMFLOAT4 diffuse, XMFLOAT4 specular, XMFLOAT3 position, float range,	XMFLOAT3 att)
{
	Dementia::PointLight* pointLight = new Dementia::PointLight(ambient,diffuse,specular,position,range,att,0.0f);
	pointLights.push_back(pointLight);

	return pointLight;
}

Material* SceneManager::createMaterial (XMFLOAT4 ambient, XMFLOAT4 diffuse, XMFLOAT4 specular, XMFLOAT4 reflect)
{
	Dementia::Material* material = new Dementia::Material(ambient,diffuse,specular,reflect);

	return material;
}

bool SceneManager::removeNode(UINT id)
{
	for(auto it = nodes.begin(); it != nodes.end(); it++)
	{
		if( (*it)->getId() == id )
		{
			(*it)->getParent()->removeChild(id);
			nodes.erase(it);
			return true;
		}
	}

	return false;
}

}
