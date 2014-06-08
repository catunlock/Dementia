#include <Dementia.h>

#include "Window.h"
#include "GeometryFactory.h"

int main()
{
	Dementia::Window window(1, 800, 600, L"Live Demo", false, true);
	window.init();
	
	Dementia::GameTimer* gameTimer = window.getGameTimer();
	Dementia::SceneManager* sceneMgr = window.getSceneManager(); 
	
	Dementia::Texture* wood = sceneMgr->createTexture(L"textures/woodDirectX.dds");
	Dementia::Texture* arena = sceneMgr->createTexture(L"textures/arena.dds");
	Dementia::Texture* tierra = sceneMgr->createTexture(L"textures/tierra.dds");

	Dementia::GeometryFactory geometryFactory(&window);
	Dementia::Geometry box;

	geometryFactory.CreateBox(2.0f, 2.0f, 2.0f, box);

	Dementia::Mesh* meshBox = sceneMgr->createMesh(&box);
	meshBox->setTexture(wood);

	Dementia::Mesh* meshBoxArena = sceneMgr->createMesh(&box);
	meshBoxArena->setTexture(arena);

	Dementia::Mesh* meshBoxTierra = sceneMgr->createMesh(&box);
	meshBoxTierra->setTexture(tierra);

	Dementia::Node* nodeBox = sceneMgr->createNode(
		XMVectorSet(0.0f,0.0f,0.0f,0.0f),
		XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)
	);

	Dementia::Node* nodeEsquerra = sceneMgr->createNode(
		XMVectorSet(-3.0f,0.0f,0.0f,0.0f),
		XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)
	);

	Dementia::Node* nodeDreta = sceneMgr->createNode(
		XMVectorSet(3.0f,0.0f,0.0f,0.0f),
		XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)
	);

	nodeBox->setEntity(meshBox);
	nodeEsquerra->setEntity(meshBoxArena);
	nodeDreta->setEntity(meshBoxTierra);

	Dementia::Node* rootSceneNode = sceneMgr->getRootSceneNode();
	rootSceneNode->addChild(nodeBox);
	nodeBox->addChild(nodeEsquerra);
	nodeBox->addChild(nodeDreta);

	float rotation = 0.0f;

	while(window.run(NULL))
	{
		nodeBox->setLocalRotation(XMVectorSet(rotation, rotation, rotation, 0.0f));
		rotation += 1.0f * gameTimer->getDeltaTime();
	}

	return 0;
}