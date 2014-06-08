//-------------------------------------------------------------------------------
// Aquet tutorial explica com afegir diversos nodes
// ------------------------------------------------------------------------------

#include "Dementia.h"	//Incluim el encabezat base del framework. Necessari per poder ultilitzar el framework.
#include "Window.h"		//Incluim el encabezat per poder ultilitzar una finestra.
#include "GeometryFactory.h"

#include <iostream>		//Incluim el encabezat de entrada sortida estandard, per poder imprimir per consola.

int main(){

	Dementia::Window window(1, 800, 600, L"UserDemo1", false, true);

	window.init();

	Dementia::Mouse* mouse = window.getInputManager()->getMouse();
	Dementia::Keyboard* keyboard = window.getInputManager()->getKeyboard();
	Dementia::GameTimer* gameTimer = window.getGameTimer();
	Dementia::Camera* camera = window.getCamera();
	Dementia::GeometryFactory geometryFactory(&window);

	Dementia::Geometry box;

	
	geometryFactory.CreateBox(1.0f, 1.0f, 1.0f, box);

	// Li demanem a la finestra que ens doni el seu managador de escena.
	Dementia::SceneManager* sceneMgr = window.getSceneManager();

	// Cambien el color de fons.
	window.setBackgroundColor(XMVectorSet(0.0f, 0.00784f, 0.2f, 1.0f));

	// Creem una textura a partir de un fitxer de textura existent.
	Dementia::Texture* wood = sceneMgr->createTexture(L"textures/woodDirectX.dds");

	// Li demanem al managador de escena que ens crei un mesh amb la geometria
	// creada anteriorment asignada. Aixo es aixi perque com a minim un mesh
	// ha de tenir una geometria, pero podria tenir tambe textura i shader.
	Dementia::Mesh* meshBox = sceneMgr->createMesh(&box);

	// Li apliquem la textura al mesh
	meshBox->setTexture(wood);

	// Obtenem el node arrel que es a partir de on s'ha de desenvolupar la escena.
	Dementia::Node* rootSceneNode = sceneMgr->getRootSceneNode();


	int f;
	int c;

	for(f = -10; f<100; f++){
		for(c = -10; c<100; c++)
		{
			Dementia::Node* nodo = sceneMgr->createNode(
				XMVectorSet(f, c, 0.0f, 0.0f),
				XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),
				XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)
			);

			nodo->setEntity(meshBox);
			rootSceneNode->addChild(nodo);
		}
	}


	// Creem una variable de posicio per enmagatzemar la posicio actual del ratoli
	XMFLOAT2 pos;

	// Creem una variable que guarda la posicio del ratoli en la imatge anterior.
	XMFLOAT2 prevMousePos;

	// Creem una variable per engamatzemar el delta de temps entre la imatge 
	// anterior i la actual.
	float dt = 0.0f;
	
	// Inicialitzem la posicio anterior del ratoli al centre de la finestra.
	prevMousePos.x = window.getWidth()/2;
	prevMousePos.y = window.getHeight()/2;

	// La variable on guardarem la rotacio dels objectes que farem a la escena
	float rotation = 0.0f;

	while( window.run(NULL) ){

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

	return 0;	//Fi del programa
}
