#pragma once

#include "Dementia.h"
#include "Geometry.h"
#include "Window.h"


namespace Dementia{

class UTILS_API GeometryFactory
{
public:

	GeometryFactory(Dementia::Window* window);
	virtual ~GeometryFactory();

	///<summary>
	/// Crea una caixa centrada al origen de les dimensions donades.
	///</summary>
	void CreateBox(float width, float height, float depth, Dementia::Geometry& geometry);

	///<summary>
	/// Crea una esfera centrada al origen del seu radi. Els slices i stacks controlan el grau de tessellation.
	///</summary>
	void CreateSphere(float radius, UINT sliceCount, UINT stackCount, Dementia::Geometry& geometry);

	///<summary>
	/// Crea una geoesfera centrada al origen del seu radi. El depth controla el grau de tessellation.
	///</summary>
	void CreateGeosphere(float radius, UINT numSubdivisions, Dementia::Geometry& geometry);

	///<summary>
	/// Crea un cilindre paral-lel al eix de les Y, centrat al seu origen.
	/// La part inferior i la part superior poden variar el radi, per fer figures diferents a cilindres de veritat,
	/// com per exemple un Con.
	/// Els slices i stacks controlan el grau de tessellation.
	///</summary>
	void CreateCylinder(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, Dementia::Geometry& geometry);

	///<summary>
	/// Crea una graella del ample i profunditats especificats en el planol XZ centrat al origen de les dimensions donades.
	///</summary>
	void CreateGrid(float width, float depth, UINT m, UINT n, Dementia::Geometry& geometry);

	///<summary>
	/// Crea un Quad que ocupa exactament tota la pantalla, ideal per a efectes de post renderitzat.
	///</summary>
	void CreateFullscreenQuad(Geometry& geometry);

private:
	void Subdivide(Geometry& geometry);
	void BuildCylinderTopCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, Dementia::Geometry& geometry);
	void BuildCylinderBottomCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, Dementia::Geometry& geometry);

	void BuildGeometry(Geometry* geometry);

private:

	/// <summary>	La referencia a la clase window que ha creat el GeometryFactory. </summary>
	Dementia::Window* m_window;

};

}