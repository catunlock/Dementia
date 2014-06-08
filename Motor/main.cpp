#include "Dementia.h"
#include "Window.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "InputManager.h"
#include "GeometryFactory.h"
#include "Geometry.h"


#include <iostream>
#include <sstream>

using namespace std;

int main(){
	
	std::wostringstream salida;
	int exitCode;

	Dementia::Window ventana(1,800, 600, L"Dementia", false, true);
	ventana.init();
	
	Dementia::InputManager* im = ventana.getInputManager();
	Dementia::Mouse* mouse = im->getMouse();
	Dementia::Keyboard* keyboard = im->getKeyboard();
	Dementia::Camera* camera = ventana.getCamera();
	Dementia::GameTimer* timer = ventana.getGameTimer();
	Dementia::SceneManager* sceneManager = ventana.getSceneManager();
	Dementia::GeometryFactory geoFactory(&ventana);

	Dementia::Geometry cube;
	Dementia::Geometry suelo;
	Dementia::Geometry sphere;
	Dementia::Geometry geoSphere;
	Dementia::Geometry cylinder;

	Dementia::Mesh* meshCube;
	Dementia::Mesh* meshSuelo;
	Dementia::Mesh* meshSphere;
	Dementia::Mesh* meshGeoSphere;
	Dementia::Mesh* meshCilinder;

	Dementia::Texture* textura1;

	geoFactory.CreateBox(1.0f,1.0f,1.0f,cube);
	geoFactory.CreateGrid(50.0f, 50.0f, 50, 50, suelo);
	geoFactory.CreateSphere( 1.0f, 20, 20, sphere);
	geoFactory.CreateGeosphere(1.0f, 20, geoSphere);
	geoFactory.CreateCylinder(1.0f, 1.0f, 5.0f, 20, 20, cylinder);

	textura1 = sceneManager->createTexture(L"textures/wood.dds");

	meshCube = sceneManager->createMesh(&cube);
	meshSuelo = sceneManager->createMesh(&suelo);
	meshSphere = sceneManager->createMesh(&sphere);
	meshGeoSphere = sceneManager->createMesh(&geoSphere);
	meshCilinder = sceneManager->createMesh(&cylinder);
	
	meshCube->setTexture(textura1);

	Dementia::Node* root = sceneManager->getRootSceneNode();
	Dementia::Node* nodo1 = sceneManager->createNode(XMVectorSet(0.0f, 5.0f, 0.0f, 0.0f), XMVectorSet(1.0f,1.0f,1.0f,1.0f), XMVectorSet(0.0f, 45.4f, 0.0f, 0.0f));
	Dementia::Node* nodoSuelo = sceneManager->createNode(XMVectorSet(-5.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f));
	Dementia::Node* nodo2 = sceneManager->createNode(XMVectorSet(1.0f, 1.0f, 5.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f));	
	Dementia::Node* nodo3 = sceneManager->createNode(XMVectorSet(-5.0f, 5.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(90.0f, 0.0f, 0.0f, 0.0f));	
	Dementia::Node* nodo4 = sceneManager->createNode(XMVectorSet(5.0f, 5.0f, 1.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f));
	
	root->setEntity(meshCube);
	nodoSuelo->setEntity(meshSuelo);
	nodo1->setEntity(meshSphere);
	nodo2->setEntity(meshGeoSphere);
	nodo3->setEntity(meshCilinder);
	nodo4->setEntity(meshCube);

	root->addChild(nodo1);
	root->addChild(nodoSuelo);
	nodoSuelo->addChild(nodo2);
	nodo2->addChild(nodo3);
	nodo3->addChild(nodo4);

	XMFLOAT2 prevMousePos;
	prevMousePos.x = ventana.getWidth()/2;
	prevMousePos.y = ventana.getHeight()/2;

	XMFLOAT2 pos;
	float dt;
	
	while(ventana.run(&exitCode))
	{
		dt = timer->getDeltaTime();

		if(mouse->isMoved()){

		}

		if(mouse->isButtonPressed(mouse->Right)){

		}

		if(mouse->isButtonPressed(mouse->Middle)){
			
		}

		if(mouse->isButtonPressed(mouse->Left)){
			if(mouse->isMoved()){
				pos = mouse->getPosition();
			
				float dx = XMConvertToRadians(0.25f * static_cast<float>(pos.x - prevMousePos.x) );
				float dy = XMConvertToRadians(0.25f * static_cast<float>(pos.y - prevMousePos.y) );

				camera->RotateY(dx);
				camera->Pitch(dy);

				prevMousePos = pos;
				//std::cout << "[Mouse] X: "<< pos.x << " Y: " << pos.y << std::endl;
			}
		}

		if(keyboard->isKeyPressed('W') ){
			camera->Walk(10.0f*dt);
		}
		if(keyboard->isKeyPressed('A') ){
			camera->Strafe(-10.0f*dt);
		}
		if(keyboard->isKeyPressed('S') ){
			camera->Walk(-10.0f*dt);
		}
		if(keyboard->isKeyPressed('D') ){
			camera->Strafe(10.0f*dt);
		}
		camera->UpdateViewMatrix();
	}

	salida << "El programa ha devuelto: " << exitCode;

	MessageBox(NULL, salida.str().c_str(), L"Codigo devuelto", MB_OK);
	
	return 0;
}