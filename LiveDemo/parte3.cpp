/*
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

	Dementia::GeometryFactory geometryFactory(&window);
	Dementia::Geometry box;

	geometryFactory.CreateBox(2.0f, 2.0f, 2.0f, box);

	Dementia::Mesh* meshBox = sceneMgr->createMesh(&box);
	meshBox->setTexture(wood);

	Dementia::Node* nodeBox = sceneMgr->createNode(
		XMVectorSet(0.0f,0.0f,0.0f,0.0f),
		XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)
	);

	nodeBox->setEntity(meshBox);

	sceneMgr->getRootSceneNode()->addChild(nodeBox);


	while(window.run(NULL))
	{

	}

	return 0;
}
*/