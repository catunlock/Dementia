#include <Dementia.h>

#include "Window.h"
#include "GeometryFactory.h"

int main()
{

	Dementia::Window* window = new Dementia::Window(1, 800, 600, L"Live Demo", true, true);
	window->init();
	
	std::vector<Dementia::Node*> spheres;

	Dementia::GameTimer* gameTimer = window->getGameTimer();
	Dementia::SceneManager* sceneMgr = window->getSceneManager(); 
	Dementia::Mouse* mouse = window->getInputManager()->getMouse();
	Dementia::Keyboard* keyboard = window->getInputManager()->getKeyboard();
	Dementia::Camera* camera = window->getCamera();
	
	Dementia::Texture* wood = sceneMgr->createTexture(L"textures/woodDirectX.dds");
	Dementia::Texture* arena = sceneMgr->createTexture(L"textures/arena.dds");
	Dementia::Texture* tierra = sceneMgr->createTexture(L"textures/tierra.dds");

	Dementia::GeometryFactory geometryFactory = Dementia::GeometryFactory(window);
	Dementia::Geometry sphere;

	geometryFactory.CreateSphere(1.0f, 60, 60, sphere);

	Dementia::Mesh*	meshSphere = sceneMgr->createMesh(&sphere);

	Dementia::Node* rootSceneNode = sceneMgr->getRootSceneNode();
	Dementia::Node* center = sceneMgr->createNode(
		XMVectorZero(),
		XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),
		XMVectorZero()
	);

	rootSceneNode->addChild(center);

	Dementia::Node* nodeGranSphere = sceneMgr->createNode(
		XMVectorSet(0.0f, -10.0f, 0.0f, 0.0f),
		XMVectorSet(5.0f, 5.0f, 5.0f, 5.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)
	);

	nodeGranSphere->setEntity(meshSphere);
	center->addChild(nodeGranSphere);

	for(int i = -3; i<3; i+=2)
	{
		for(int j = -3; j<3; j+=2)
		{
			Dementia::Node* nodo = sceneMgr->createNode(
				XMVectorSet(i, 0.0f, j, 0.0f),
				XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),
				XMVectorZero()
			);

			nodo->setEntity(meshSphere);
			center->addChild(nodo);
			spheres.push_back(nodo);
		}
	}

	XMFLOAT2 pos(0.0f, 0.0f);

	XMFLOAT2 prevMousePos;

	prevMousePos.x = window->getWidth()/2;
	prevMousePos.y = window->getHeight()/2;

	float dt;
	float gameTime;

	int i = 0;
	XMFLOAT4 posSphere;
	XMFLOAT4 scaleSphere;

	while(window->run(NULL) )
	{
		gameTime = gameTimer->getGameTime();
		dt = gameTimer->getDeltaTime();

		if(gameTime > 10.0f){

			XMStoreFloat4(&posSphere, spheres[i]->getLocalPosition());
			
			if(posSphere.x < 0) posSphere.x += 1.0f;
			if(posSphere.x > 0) posSphere.x -= 1.0f;

			if(posSphere.y < -50.0f) posSphere.y += 1.0f;
			if(posSphere.y > -50.0f) posSphere.y -= 1.0f;

			if(posSphere.z < 0) posSphere.z += 1.0f;
			if(posSphere.z > 0) posSphere.z -= 1.0f;

			spheres[i]->setLocalPosition(XMLoadFloat4(&posSphere));

			
			if(posSphere.x == 0.0f && posSphere.y == -50.0f && posSphere.z == 0.0f)
			{
				if(i < spheres.size()-1){

					nodeGranSphere->setLocalScale(XMVectorAdd(nodeGranSphere->getLocalScale(), XMVectorSet(1.1f, 1.1f, 1.1f, 1.1f)));
					nodeGranSphere->setLocalPosition(XMVectorSubtract(nodeGranSphere->getLocalPosition(), XMVectorSet(0.0f, -1.1f, 0.0f, 0.0f)));

					i++;
				}
			}
			
			/*
			if( (posSphere.x >= -0.2f && posSphere.x <= 0.2f) &&
				(posSphere.y >= -49.8f && posSphere.y <= 50.2f) &&
				(posSphere.z >= -0.2f && posSphere.z <= 0.2f))
			{
				i++;
			}
			*/
			
		}
		// Mourem la camara cuan l'usuari premi el boto esquerra del ratoli.
		if(mouse->isButtonPressed(mouse->Left)){

			// Si el ratoli ha cambiat de posicio des de la ultima vegada que es va 
			// cridar al metode getPosition.
			if(mouse->isMoved()){

				// Ens guardem la nova posicio per treballar amb ella.
				pos = mouse->getPosition();
				
				// Convertim la diferencia entre la posicio anterior i la actual en un 
				// angle que despres convertim a radians per dirli a la camara quant a
				// de rotar.
				
				// Angle del pla X
				float dx = XMConvertToRadians(0.25f * static_cast<float>(pos.x - prevMousePos.x) );
				
				// Angle del pla Y
				float dy = XMConvertToRadians(0.25f * static_cast<float>(pos.y - prevMousePos.y) );

				// Rotem el eix Y el anlge del pla X.
				camera->RotateY(dx);

				// Rotem el eix X el anlge del pla Y.
				camera->Pitch(dy);

				// Igualem la posicio anterior a la posicio actual del ratoli.
				prevMousePos = pos;
			}
		}

		// Obtenim el delta de temps entre el frame anterior i el actual.
		dt = gameTimer->getDeltaTime();

		// Comprobem si la tecla W esta polsada
		if(keyboard->isKeyPressed('W') ){
			// Li diem a la camara que simuli que el usuari a caminat cap 
			// endevant 10 unitats, pero les multipliquem per el delta perque
			// aixi aconseguim que avançi el mateix independent-ment del
			// processador si s'executa mes vegades per segon o menys.
			camera->Walk(10.0f*dt);
		}

		// Comprobem si la tecla A esta polsada
		if(keyboard->isKeyPressed('A') ){
			// Li diem a la camara que simuli que es d'esplaça de costat 10
			// unitats multiplicades per el delta.
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

	return 0;
}