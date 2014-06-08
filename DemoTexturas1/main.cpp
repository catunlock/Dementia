//-------------------------------------------------------------------------------
// Aquet tutorial explica com afegir diversos nodes
// ------------------------------------------------------------------------------

#include "Dementia.h"	//Incluim el encabezat base del framework. Necessari per poder ultilitzar el framework.
#include "Window.h"		//Incluim el encabezat per poder ultilitzar una finestra.
#include "GeometryFactory.h"

#include <iostream>		//Incluim el encabezat de entrada sortida estandard, per poder imprimir per consola.

int main(){

	Dementia::Window window(1, 800, 600, L"UserDemo1", false, true);

	//Fem la inicialitzacio de la finestra abans de res, per tenir tot preparat.
	window.init();

	Dementia::Mouse* mouse = window.getInputManager()->getMouse();
	Dementia::Keyboard* keyboard = window.getInputManager()->getKeyboard();

	// Obtenim el game timer per despres obtenir el delta entre els frames.
	Dementia::GameTimer* gameTimer = window.getGameTimer();

	// Obtenim la camara asociada a la finestra.
	Dementia::Camera* camera = window.getCamera();

	// Creem una fabrica de geometries, com a parametre le pasem la finestra 
	// per a que sapiga per quina finestra son.
	Dementia::GeometryFactory geometryFactory(&window);

	// Creem una geometria buida box, que es on desprem la omplirem.
	Dementia::Geometry box;

	// Creem una altra geometria,
	Dementia::Geometry cylinder;

	// Li demanem a la fabrica de geometries que ens crei una caixa de 1.0f de
	// ample, 1.0f de alçada i 1.0f de fons, i ens la guarda a la variable box,
	// que es la geometria que hem creat abans.
	geometryFactory.CreateBox(1.0f, 1.0f, 1.0f, box);

	// Li demanem a la fabrica de geometries que ens crei un cilindre de 3.0f
	// de radi de base, 1.0f de radi de tap, 5.0f de llargada, de 20 divisions,
	// tant horitzonatls com verticals, ens la guarda a la geometria cylinder 
	// que hem creat abans.
	geometryFactory.CreateCylinder(1.0f, 1.0f, 5.0f, 60, 60, cylinder);


	// Li demanem a la finestra que ens doni el seu managador de escena.
	Dementia::SceneManager* sceneMgr = window.getSceneManager();

	// Cambien el color de fons.
	window.setBackgroundColor(XMVectorSet(0.0f, 0.00784f, 0.2f, 1.0f));

	// Creem una textura a partir de un fitxer de textura existent.
	Dementia::Texture* wood = sceneMgr->createTexture(L"textures/woodDirectX.dds");
	Dementia::Texture* oxido = sceneMgr->createTexture(L"textures/oxido.dds");
	Dementia::Texture* aluminio = sceneMgr->createTexture(L"textures/aluminio.dds");


	// Li demanem al managador de escena que ens crei un mesh amb la geometria
	// creada anteriorment asignada. Aixo es aixi perque com a minim un mesh
	// ha de tenir una geometria, pero podria tenir tambe textura i shader.
	Dementia::Mesh* meshBox = sceneMgr->createMesh(&box);

	// Li demanem al managador de escena que ens crei un mesh amb la geometria
	// cylinder asignada.
	Dementia::Mesh* meshCylinder = sceneMgr->createMesh(&cylinder);
	meshCylinder->setTexture(aluminio);

	Dementia::Mesh* meshCylinderOxided = sceneMgr->createMesh(&cylinder);
	meshCylinderOxided->setTexture(oxido);

	// Li apliquem la textura al mesh
	meshBox->setTexture(wood);

	// Obtenem el node arrel que es a partir de on s'ha de desenvolupar la escena.
	Dementia::Node* rootSceneNode = sceneMgr->getRootSceneNode();

	// Creem un nou node per al cilindre.
	Dementia::Node* nodeCylinderLeft = sceneMgr->createNode(
		XMVectorSet(-3.0f, 0.0f, 0.0f, 0.0f),	// Indiquem la posicio on es troba el node (X,Y,Z,W)
		XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),	// Indiquem la escala del node, per no alterar la escala ha de ser 1 (X,Y,Z,W)
		XMVectorSet(45.0f, 0.0f, 0.0f, 0.0f)		// Indiquem la rotacio del node en agle de 360º (X,Y,Z,W)
	);


	Dementia::Node* nodeCylinderRight =sceneMgr->createNode(
		XMVectorSet(3.0f, 0.0f, 0.0f, 0.0f),
		XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),
		XMVectorSet(-45.0f, 0.0f, 0.0f, 0.0f)
	);

	// Li indiquem al node arrel que te la entitat meshBox asociada a ell,
	// d'aquesta manera fem que surti per pantalla.
	rootSceneNode->setEntity(meshBox);

	// Li indiquem al node cylinder que te la entitat meshCylinder asociada a
	// ell.
	nodeCylinderLeft->setEntity(meshCylinder);
	nodeCylinderRight->setEntity(meshCylinderOxided);

	rootSceneNode->addChild(nodeCylinderLeft);
	rootSceneNode->addChild(nodeCylinderRight);

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

		// Afegim una mica de rotacio.
		rotation = rotation+(1.0f*dt);

		// Cambien la rotacio amb els valors nous.
		//nodeCylinder->setLocalRotation(XMVectorSet(rotation, 2.0f, rotation, 0.0f));
		// Cambien la posicio amb els valors nous.
		//nodeCylinder->setLocalPosition(XMVectorSet(rotation, 1.0f, rotation, 0.0f));

		if(rotation > 8){ rotation = 0; }

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
