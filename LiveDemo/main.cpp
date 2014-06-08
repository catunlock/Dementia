/*
Live Demo Objetivos:
	- Crear una ventana.
	- Mostrar una geometria
	- Texturizar esa geometria
	- añadir nodos a los lados
	- hacer que roten
	- ultilizar varias texturas.
*/


#include <Dementia.h>

#include "Window.h"
#include "GeometryFactory.h"

class Game{
	
public:
	Game();
	~Game();

	void update();

public:
	Dementia::Window* window;

	Dementia::GameTimer* gameTimer;
	Dementia::SceneManager* sceneMgr;
	Dementia::Mouse* mouse;
	Dementia::Keyboard* keyboard;
	Dementia::Camera* camera;
	
	Dementia::Texture* wood;
	Dementia::Texture* arena;
	Dementia::Texture* tierra;

	Dementia::GeometryFactory* geometryFactory;

	Dementia::Geometry box;

	Dementia::Mesh* meshBoxWood;
	Dementia::Mesh* meshBoxArena;
	Dementia::Mesh* meshBoxTierra;

	Dementia::Node* rootSceneNode;
	Dementia::Node* center;
	Dementia::Node* nodoRotacion;


	Dementia::Node* nodoCaja1;
	Dementia::Node* nodoCaja2;
	Dementia::Node* nodoCaja3;
	Dementia::Node* nodoCaja4;

	std::vector<Dementia::Node*> cajas;
	// UPDATE VARIABLES
	
	XMFLOAT2 pos;

	XMFLOAT2 prevMousePos;

	float dt;

	int estado;
	bool rotar;

};

Game::Game() :
	dt(0.0f),
	estado(1),
	rotar(true)
{
	window = new Dementia::Window(1, 800, 600, L"Live Demo", false, true);
	window->init();
	
	gameTimer = window->getGameTimer();
	sceneMgr = window->getSceneManager(); 
	mouse = window->getInputManager()->getMouse();
	keyboard = window->getInputManager()->getKeyboard();
	camera = window->getCamera();
	
	wood = sceneMgr->createTexture(L"textures/woodDirectX.dds");
	arena = sceneMgr->createTexture(L"textures/arena.dds");
	tierra = sceneMgr->createTexture(L"textures/tierra.dds");

	rootSceneNode = sceneMgr->getRootSceneNode();

	center = sceneMgr->createNode(
		XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)
	);

	nodoRotacion = sceneMgr->createNode(
		XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)
	);

	geometryFactory = new Dementia::GeometryFactory(window);
	geometryFactory->CreateBox(2.0f, 2.0f, 2.0f, box);

	meshBoxWood = sceneMgr->createMesh(&box);
	meshBoxWood->setTexture(wood);

	meshBoxArena = sceneMgr->createMesh(&box);
	meshBoxArena->setTexture(arena);

	meshBoxTierra = sceneMgr->createMesh(&box);
	meshBoxTierra->setTexture(tierra);

	rootSceneNode->addChild(center);
	rootSceneNode->addChild(nodoRotacion);

	center->setEntity(meshBoxWood);
}

Game::~Game()
{
	delete geometryFactory;
	delete window;
}

void Game::update()
{
	// Inicialitzem la posicio anterior del ratoli al centre de la finestra.
	prevMousePos.x = window->getWidth()/2;
	prevMousePos.y = window->getHeight()/2;

	float gameTime = 0.0f;

	while( window->run(NULL) ){

		 gameTime += gameTimer->getDeltaTime();

		if(gameTime > 1.0f && estado == 1)
		{
			nodoCaja1 = sceneMgr->createNode(
				XMVectorSet(3.0f, 0.0f, 0.0f, 0.0f),
				XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),
				XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)
			);

			nodoCaja1->setEntity(meshBoxWood);
			nodoRotacion->addChild(nodoCaja1);

			estado = 2;
		}
		else if(gameTime > 7.0f && estado == 2) //7.0f
		{
			nodoCaja2 = sceneMgr->createNode(
				XMVectorSet(-3.0f, 0.0f, 0.0f, 0.0f),
				XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),
				XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)
			);

			nodoCaja2->setEntity(meshBoxWood);
			nodoRotacion->addChild(nodoCaja2);
			
			estado = 3;
		}
		else if (gameTime > 13.0f && estado == 3) // 13.0f
		{
			nodoCaja3 = sceneMgr->createNode(
				XMVectorSet(0.0f, 0.0f, 3.0f, 0.0f),
				XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),
				XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)
			);

			nodoCaja3->setEntity(meshBoxWood);
			nodoRotacion->addChild(nodoCaja3);
			
			estado = 4;
		}
		else if (gameTime > 19.0f && estado == 4) // 19.0f
		{
			nodoCaja4 = sceneMgr->createNode(
				XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f),
				XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),
				XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)
			);

			nodoCaja4->setEntity(meshBoxWood);
			nodoRotacion->addChild(nodoCaja4);

			estado = 5;
		}
		else if (gameTime > 21.2f && estado == 5) //21.2f
		{
			rotar = false;
		
			estado = 6;
		}
		else if(gameTime > 21.5f && estado == 6) // 21.5f
		{
			nodoCaja1->setLocalPosition(XMVectorZero());
			nodoCaja2->setLocalPosition(XMVectorZero());
			nodoCaja3->setLocalPosition(XMVectorZero());
			nodoCaja4->setLocalPosition(XMVectorZero());

			estado = 7;
		}
		else if(gameTime > 21.7f && estado == 7) //21.7f
		{
			static XMVECTOR position1 = XMVectorZero();
			static int suma1 = 0;

			nodoRotacion->setLocalRotation(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f));

			float dt = gameTimer->getDeltaTime();
			position1 = XMVectorAdd(XMVectorSet(10.0f*dt, 0.0f, 10.0f*dt, 0.0f), position1);
			nodoCaja1->setLocalPosition(position1);

			if(suma1 > 1000){
				estado = 8;
			}
			suma1++;
		}
		else if(gameTime > 23.7f && estado == 8) //23.7f
		{
			static XMVECTOR position1 = XMVectorZero();
			static int suma1 = 0;

			float dt = gameTimer->getDeltaTime();
			position1 = XMVectorAdd(XMVectorSet(-10.0f*dt, 0.0f, 10.0f*dt, 0.0f), position1);
			nodoCaja2->setLocalPosition(position1);

			if(suma1 > 1000){
				estado = 9;
			}
			suma1++;
		}
		else if(gameTime > 25.7f && estado == 9) //25.7f
		{
			static XMVECTOR position1 = XMVectorZero();
			static int suma1 = 0;

			float dt = gameTimer->getDeltaTime();
			position1 = XMVectorAdd(XMVectorSet(-10.0f*dt, 0.0f, -10.0f*dt, 0.0f), position1);
			nodoCaja3->setLocalPosition(position1);

			if(suma1 > 1000){
				estado = 10;
			}
			suma1++;
		}
		else if(gameTime > 27.7f && estado == 10) //27.7f
		{
			static XMVECTOR position1 = XMVectorZero();
			static int suma1 = 0;

			float dt = gameTimer->getDeltaTime();
			position1 = XMVectorAdd(XMVectorSet(10.0f*dt, 0.0f, -10.0f*dt, 0.0f), position1);
			nodoCaja4->setLocalPosition(position1);

			if(suma1 > 1000){
				estado = 11;
			}
			suma1++;
		}
		else if(gameTime > 27.7f && estado == 11) //27.7f
		{
			cajas.reserve(200);

			for(int i = -5; i<6; i+=2)
			{
				for(int j = -5; j<6; j+=2)
				{
					Dementia::Node* caja = sceneMgr->createNode(
						XMVectorSet(i, 20.0f, j, 0.0f),
						XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),
						XMVectorZero()
					);
					center->addChild(caja);

					cajas.push_back(caja);
				}
			}

			estado = 12;
		}
		else if(gameTime > 27.7f && estado == 12) // 27.7f
		{
			static int i = 0;
			float dt = gameTimer->getDeltaTime();

			cajas[i]->setEntity(meshBoxTierra);

			if( XMVectorGetY(cajas[i]->getLocalPosition()) > 0)
			{
				XMVECTOR position = XMVectorSubtract(cajas[i]->getLocalPosition(), XMVectorSet(0.0f, 100.f*dt, 0.0f, 0.0f)); //40.0f
				cajas[i]->setLocalPosition(position);
			}else
			{
				i++;
				if(i >= 36){
					estado = 13;
				}
			}
		}
		else if(gameTime > 27.7f && estado == 13) //27.7f
		{
			static int i = 0;
			static int c = 0;
			float dt = gameTimer->getDeltaTime();
			
			if((i*6)+c < 36)
			{
				Dementia::Node* caja = cajas[(i*6)+c];
				if(XMVectorGetY(caja->getLocalPosition()) < 2)
				{
					caja->setLocalPosition(XMVectorAdd(caja->getLocalPosition(), XMVectorSet(0.0f, 100.0f*dt, 0.0f, 0.0f)));
					if(i-1 >= 0)
					{
						Dementia::Node* cajaAnterior = cajas[((i-1)*6)+c];
						cajaAnterior->setLocalPosition(XMVectorSubtract(cajaAnterior->getLocalPosition(), XMVectorSet(0.0f, 100.0f*dt, 0.0f, 0.0f)));
					}
				}else{
					c++;
				}

				if(c == 6){
					c = 0;
					i++;
				}
			}
			else
			{
				Dementia::Node* cajaAnterior = cajas[((i-1)*6)+c];
				if( XMVectorGetY(cajaAnterior->getLocalPosition()) > 0)
				{
					cajaAnterior->setLocalPosition(XMVectorSubtract(cajaAnterior->getLocalPosition(), XMVectorSet(0.0f, 100.0f*dt, 0.0f, 0.0f)));
				}else
				{
					c++;
				}
				
				if(c == 6)
				{
					estado = 14;
				}
			}

		}
		
		if( gameTime > 1.0f && rotar)
		{
			nodoRotacion->setLocalRotation(XMVectorSet(0.0f, gameTime, 0.0f, 0.0f));
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
}

int main()
{
	Game game;

	game.update();

	return 0;
}
