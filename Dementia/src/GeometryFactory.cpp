#include "Dementia.h"

#include "GeometryFactory.h"
#include "Window.h"
#include "Geometry.h"
#include "MathHelper.h"

namespace Dementia{


	GeometryFactory::GeometryFactory(Dementia::Window* window) :
		m_window(window)
	{

	}

	GeometryFactory::~GeometryFactory()
	{

	}

	void GeometryFactory::CreateBox(float width, float height, float depth, Dementia::Geometry& geometry)
	{
		//
		// Create the vertices.
		//

		Geometry::Vertex v[24];

		float w2 = 0.5f*width;
		float h2 = 0.5f*height;
		float d2 = 0.5f*depth;
    
		// Fill in the front face vertex data.
		v[0] = Geometry::Vertex(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		v[1] = Geometry::Vertex(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		v[2] = Geometry::Vertex(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		v[3] = Geometry::Vertex(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

		// Fill in the back face vertex data.
		v[4] = Geometry::Vertex(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		v[5] = Geometry::Vertex(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		v[6] = Geometry::Vertex(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		v[7] = Geometry::Vertex(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

		// Fill in the top face vertex data.
		v[8]  = Geometry::Vertex(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		v[9]  = Geometry::Vertex(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		v[10] = Geometry::Vertex(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		v[11] = Geometry::Vertex(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

		// Fill in the bottom face vertex data.
		v[12] = Geometry::Vertex(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		v[13] = Geometry::Vertex(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		v[14] = Geometry::Vertex(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		v[15] = Geometry::Vertex(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

		// Fill in the left face vertex data.
		v[16] = Geometry::Vertex(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
		v[17] = Geometry::Vertex(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
		v[18] = Geometry::Vertex(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
		v[19] = Geometry::Vertex(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

		// Fill in the right face vertex data.
		v[20] = Geometry::Vertex(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		v[21] = Geometry::Vertex(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
		v[22] = Geometry::Vertex(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
		v[23] = Geometry::Vertex(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

		geometry.Vertices.assign(&v[0], &v[24]);
 
		//
		// Create the indices.
		//

		UINT i[36];

		// Fill in the front face index data
		i[0] = 0; i[1] = 1; i[2] = 2;
		i[3] = 0; i[4] = 2; i[5] = 3;

		// Fill in the back face index data
		i[6] = 4; i[7]  = 5; i[8]  = 6;
		i[9] = 4; i[10] = 6; i[11] = 7;

		// Fill in the top face index data
		i[12] = 8; i[13] =  9; i[14] = 10;
		i[15] = 8; i[16] = 10; i[17] = 11;

		// Fill in the bottom face index data
		i[18] = 12; i[19] = 13; i[20] = 14;
		i[21] = 12; i[22] = 14; i[23] = 15;

		// Fill in the left face index data
		i[24] = 16; i[25] = 17; i[26] = 18;
		i[27] = 16; i[28] = 18; i[29] = 19;

		// Fill in the right face index data
		i[30] = 20; i[31] = 21; i[32] = 22;
		i[33] = 20; i[34] = 22; i[35] = 23;

		geometry.Indices.assign(&i[0], &i[36]);

		BuildGeometry(&geometry);
	}

	void GeometryFactory::CreateSphere(float radius, UINT sliceCount, UINT stackCount, Dementia::Geometry& geometry)
	{
		geometry.Vertices.clear();
		geometry.Indices.clear();

		//
		// Compute the vertices stating at the top pole and moving down the stacks.
		//

		// Poles: note that there will be texture coordinate distortion as there is
		// not a unique point on the texture map to assign to the pole when mapping
		// a rectangular texture onto a sphere.
		Geometry::Vertex topVertex(0.0f, +radius, 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		Geometry::Vertex bottomVertex(0.0f, -radius, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

		geometry.Vertices.push_back( topVertex );

		float phiStep   = XM_PI/stackCount;
		float thetaStep = 2.0f*XM_PI/sliceCount;

		// Compute vertices for each stack ring (do not count the poles as rings).
		for(UINT i = 1; i <= stackCount-1; ++i)
		{
			float phi = i*phiStep;

			// Vertices of ring.
			for(UINT j = 0; j <= sliceCount; ++j)
			{
				float theta = j*thetaStep;

				Geometry::Vertex v;

				// spherical to cartesian
				v.Position.x = radius*sinf(phi)*cosf(theta);
				v.Position.y = radius*cosf(phi);
				v.Position.z = radius*sinf(phi)*sinf(theta);

				// Partial derivative of P with respect to theta
				v.TangentU.x = -radius*sinf(phi)*sinf(theta);
				v.TangentU.y = 0.0f;
				v.TangentU.z = +radius*sinf(phi)*cosf(theta);

				XMVECTOR T = XMLoadFloat3(&v.TangentU);
				XMStoreFloat3(&v.TangentU, XMVector3Normalize(T));

				XMVECTOR p = XMLoadFloat3(&v.Position);
				XMStoreFloat3(&v.Normal, XMVector3Normalize(p));

				v.TexC.x = theta / XM_2PI;
				v.TexC.y = phi / XM_PI;

				geometry.Vertices.push_back( v );
			}
		}

		geometry.Vertices.push_back( bottomVertex );

		//
		// Compute indices for top stack.  The top stack was written first to the vertex buffer
		// and connects the top pole to the first ring.
		//

		for(UINT i = 1; i <= sliceCount; ++i)
		{
			geometry.Indices.push_back(0);
			geometry.Indices.push_back(i+1);
			geometry.Indices.push_back(i);
		}
	
		//
		// Compute indices for inner stacks (not connected to poles).
		//

		// Offset the indices to the index of the first vertex in the first ring.
		// This is just skipping the top pole vertex.
		UINT baseIndex = 1;
		UINT ringVertexCount = sliceCount+1;
		for(UINT i = 0; i < stackCount-2; ++i)
		{
			for(UINT j = 0; j < sliceCount; ++j)
			{
				geometry.Indices.push_back(baseIndex + i*ringVertexCount + j);
				geometry.Indices.push_back(baseIndex + i*ringVertexCount + j+1);
				geometry.Indices.push_back(baseIndex + (i+1)*ringVertexCount + j);

				geometry.Indices.push_back(baseIndex + (i+1)*ringVertexCount + j);
				geometry.Indices.push_back(baseIndex + i*ringVertexCount + j+1);
				geometry.Indices.push_back(baseIndex + (i+1)*ringVertexCount + j+1);
			}
		}

		//
		// Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
		// and connects the bottom pole to the bottom ring.
		//

		// South pole vertex was added last.
		UINT southPoleIndex = (UINT)geometry.Vertices.size()-1;

		// Offset the indices to the index of the first vertex in the last ring.
		baseIndex = southPoleIndex - ringVertexCount;
	
		for(UINT i = 0; i < sliceCount; ++i)
		{
			geometry.Indices.push_back(southPoleIndex);
			geometry.Indices.push_back(baseIndex+i);
			geometry.Indices.push_back(baseIndex+i+1);
		}

		BuildGeometry(&geometry);
	}
 
	void GeometryFactory::Subdivide(Dementia::Geometry& geometry)
	{
		// Save a copy of the input geometry.
		Geometry inputCopy = geometry;


		geometry.Vertices.resize(0);
		geometry.Indices.resize(0);

		//       v1
		//       *
		//      / \
		//     /   \
		//  m0*-----*m1
		//   / \   / \
		//  /   \ /   \
		// *-----*-----*
		// v0    m2     v2

		UINT numTris = inputCopy.Indices.size()/3;
		for(UINT i = 0; i < numTris; ++i)
		{
			Geometry::Vertex v0 = inputCopy.Vertices[ inputCopy.Indices[i*3+0] ];
			Geometry::Vertex v1 = inputCopy.Vertices[ inputCopy.Indices[i*3+1] ];
			Geometry::Vertex v2 = inputCopy.Vertices[ inputCopy.Indices[i*3+2] ];

			//
			// Generate the midpoints.
			//

			Geometry::Vertex m0, m1, m2;

			// For subdivision, we just care about the position component.  We derive the other
			// vertex components in CreateGeosphere.

			m0.Position = XMFLOAT3(
				0.5f*(v0.Position.x + v1.Position.x),
				0.5f*(v0.Position.y + v1.Position.y),
				0.5f*(v0.Position.z + v1.Position.z));

			m1.Position = XMFLOAT3(
				0.5f*(v1.Position.x + v2.Position.x),
				0.5f*(v1.Position.y + v2.Position.y),
				0.5f*(v1.Position.z + v2.Position.z));

			m2.Position = XMFLOAT3(
				0.5f*(v0.Position.x + v2.Position.x),
				0.5f*(v0.Position.y + v2.Position.y),
				0.5f*(v0.Position.z + v2.Position.z));

			//
			// Add new geometry.
			//

			geometry.Vertices.push_back(v0); // 0
			geometry.Vertices.push_back(v1); // 1
			geometry.Vertices.push_back(v2); // 2
			geometry.Vertices.push_back(m0); // 3
			geometry.Vertices.push_back(m1); // 4
			geometry.Vertices.push_back(m2); // 5
 
			geometry.Indices.push_back(i*6+0);
			geometry.Indices.push_back(i*6+3);
			geometry.Indices.push_back(i*6+5);

			geometry.Indices.push_back(i*6+3);
			geometry.Indices.push_back(i*6+4);
			geometry.Indices.push_back(i*6+5);

			geometry.Indices.push_back(i*6+5);
			geometry.Indices.push_back(i*6+4);
			geometry.Indices.push_back(i*6+2);

			geometry.Indices.push_back(i*6+3);
			geometry.Indices.push_back(i*6+1);
			geometry.Indices.push_back(i*6+4);
		}

		BuildGeometry(&geometry);
	}

	void GeometryFactory::CreateGeosphere(float radius, UINT numSubdivisions, Dementia::Geometry& geometry)
	{
		// Put a cap on the number of subdivisions.
		numSubdivisions = MathHelper::Min(numSubdivisions, 5u);

		// Approximate a sphere by tessellating an icosahedron.

		const float X = 0.525731f; 
		const float Z = 0.850651f;

		XMFLOAT3 pos[12] = 
		{
			XMFLOAT3(-X, 0.0f, Z),  XMFLOAT3(X, 0.0f, Z),  
			XMFLOAT3(-X, 0.0f, -Z), XMFLOAT3(X, 0.0f, -Z),    
			XMFLOAT3(0.0f, Z, X),   XMFLOAT3(0.0f, Z, -X), 
			XMFLOAT3(0.0f, -Z, X),  XMFLOAT3(0.0f, -Z, -X),    
			XMFLOAT3(Z, X, 0.0f),   XMFLOAT3(-Z, X, 0.0f), 
			XMFLOAT3(Z, -X, 0.0f),  XMFLOAT3(-Z, -X, 0.0f)
		};

		DWORD k[60] = 
		{
			1,4,0,  4,9,0,  4,5,9,  8,5,4,  1,8,4,    
			1,10,8, 10,3,8, 8,3,5,  3,2,5,  3,7,2,    
			3,10,7, 10,6,7, 6,11,7, 6,0,11, 6,1,0, 
			10,1,6, 11,0,9, 2,11,9, 5,2,9,  11,2,7 
		};

		geometry.Vertices.resize(12);
		geometry.Indices.resize(60);

		for(UINT i = 0; i < 12; ++i)
			geometry.Vertices[i].Position = pos[i];

		for(UINT i = 0; i < 60; ++i)
			geometry.Indices[i] = k[i];

		for(UINT i = 0; i < numSubdivisions; ++i)
			Subdivide(geometry);

		// Project vertices onto sphere and scale.
		for(UINT i = 0; i < geometry.Vertices.size(); ++i)
		{
			// Project onto unit sphere.
			XMVECTOR n = XMVector3Normalize(XMLoadFloat3(&geometry.Vertices[i].Position));

			// Project onto sphere.
			XMVECTOR p = radius*n;

			XMStoreFloat3(&geometry.Vertices[i].Position, p);
			XMStoreFloat3(&geometry.Vertices[i].Normal, n);

			// Derive texture coordinates from spherical coordinates.
			float theta = MathHelper::AngleFromXY(
				geometry.Vertices[i].Position.x, 
				geometry.Vertices[i].Position.z);

			float phi = acosf(geometry.Vertices[i].Position.y / radius);

			geometry.Vertices[i].TexC.x = theta/XM_2PI;
			geometry.Vertices[i].TexC.y = phi/XM_PI;

			// Partial derivative of P with respect to theta
			geometry.Vertices[i].TangentU.x = -radius*sinf(phi)*sinf(theta);
			geometry.Vertices[i].TangentU.y = 0.0f;
			geometry.Vertices[i].TangentU.z = +radius*sinf(phi)*cosf(theta);

			XMVECTOR T = XMLoadFloat3(&geometry.Vertices[i].TangentU);
			XMStoreFloat3(&geometry.Vertices[i].TangentU, XMVector3Normalize(T));
		}

		BuildGeometry(&geometry);
	}

	void GeometryFactory::CreateCylinder(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, Dementia::Geometry& geometry)
	{
		geometry.Vertices.clear();
		geometry.Indices.clear();

		//
		// Build Stacks.
		// 

		float stackHeight = height / stackCount;

		// Amount to increment radius as we move up each stack level from bottom to top.
		float radiusStep = (topRadius - bottomRadius) / stackCount;

		UINT ringCount = stackCount+1;

		// Compute vertices for each stack ring starting at the bottom and moving up.
		for(UINT i = 0; i < ringCount; ++i)
		{
			float y = -0.5f*height + i*stackHeight;
			float r = bottomRadius + i*radiusStep;

			// vertices of ring
			float dTheta = 2.0f*XM_PI/sliceCount;
			for(UINT j = 0; j <= sliceCount; ++j)
			{
				Geometry::Vertex vertex;

				float c = cosf(j*dTheta);
				float s = sinf(j*dTheta);

				vertex.Position = XMFLOAT3(r*c, y, r*s);

				vertex.TexC.x = (float)j/sliceCount;
				vertex.TexC.y = 1.0f - (float)i/stackCount;

				// Cylinder can be parameterized as follows, where we introduce v
				// parameter that goes in the same direction as the v tex-coord
				// so that the bitangent goes in the same direction as the v tex-coord.
				//   Let r0 be the bottom radius and let r1 be the top radius.
				//   y(v) = h - hv for v in [0,1].
				//   r(v) = r1 + (r0-r1)v
				//
				//   x(t, v) = r(v)*cos(t)
				//   y(t, v) = h - hv
				//   z(t, v) = r(v)*sin(t)
				// 
				//  dx/dt = -r(v)*sin(t)
				//  dy/dt = 0
				//  dz/dt = +r(v)*cos(t)
				//
				//  dx/dv = (r0-r1)*cos(t)
				//  dy/dv = -h
				//  dz/dv = (r0-r1)*sin(t)

				// This is unit length.
				vertex.TangentU = XMFLOAT3(-s, 0.0f, c);

				float dr = bottomRadius-topRadius;
				XMFLOAT3 bitangent(dr*c, -height, dr*s);

				XMVECTOR T = XMLoadFloat3(&vertex.TangentU);
				XMVECTOR B = XMLoadFloat3(&bitangent);
				XMVECTOR N = XMVector3Normalize(XMVector3Cross(T, B));
				XMStoreFloat3(&vertex.Normal, N);

				geometry.Vertices.push_back(vertex);
			}
		}

		// Add one because we duplicate the first and last vertex per ring
		// since the texture coordinates are different.
		UINT ringVertexCount = sliceCount+1;

		// Compute indices for each stack.
		for(UINT i = 0; i < stackCount; ++i)
		{
			for(UINT j = 0; j < sliceCount; ++j)
			{
				geometry.Indices.push_back(i*ringVertexCount + j);
				geometry.Indices.push_back((i+1)*ringVertexCount + j);
				geometry.Indices.push_back((i+1)*ringVertexCount + j+1);

				geometry.Indices.push_back(i*ringVertexCount + j);
				geometry.Indices.push_back((i+1)*ringVertexCount + j+1);
				geometry.Indices.push_back(i*ringVertexCount + j+1);
			}
		}

		BuildCylinderTopCap(bottomRadius, topRadius, height, sliceCount, stackCount, geometry);
		BuildCylinderBottomCap(bottomRadius, topRadius, height, sliceCount, stackCount, geometry);

		BuildGeometry(&geometry);
	}

	void GeometryFactory::BuildCylinderTopCap(float bottomRadius, float topRadius, float height, 
												UINT sliceCount, UINT stackCount, Dementia::Geometry& geometry)
	{
		UINT baseIndex = (UINT)geometry.Vertices.size();

		float y = 0.5f*height;
		float dTheta = 2.0f*XM_PI/sliceCount;

		// Duplicate cap ring vertices because the texture coordinates and normals differ.
		for(UINT i = 0; i <= sliceCount; ++i)
		{
			float x = topRadius*cosf(i*dTheta);
			float z = topRadius*sinf(i*dTheta);

			// Scale down by the height to try and make top cap texture coord area
			// proportional to base.
			float u = x/height + 0.5f;
			float v = z/height + 0.5f;

			geometry.Vertices.push_back( Geometry::Vertex(x, y, z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, u, v) );
		}

		// Cap center vertex.
		geometry.Vertices.push_back( Geometry::Vertex(0.0f, y, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f) );

		// Index of center vertex.
		UINT centerIndex = (UINT)geometry.Vertices.size()-1;

		for(UINT i = 0; i < sliceCount; ++i)
		{
			geometry.Indices.push_back(centerIndex);
			geometry.Indices.push_back(baseIndex + i+1);
			geometry.Indices.push_back(baseIndex + i);
		}

		BuildGeometry(&geometry);
	}

	void GeometryFactory::BuildCylinderBottomCap(float bottomRadius, float topRadius, float height, 
												   UINT sliceCount, UINT stackCount, Dementia::Geometry& geometry)
	{
		// 
		// Build bottom cap.
		//

		UINT baseIndex = (UINT)geometry.Vertices.size();
		float y = -0.5f*height;

		// vertices of ring
		float dTheta = 2.0f*XM_PI/sliceCount;
		for(UINT i = 0; i <= sliceCount; ++i)
		{
			float x = bottomRadius*cosf(i*dTheta);
			float z = bottomRadius*sinf(i*dTheta);

			// Scale down by the height to try and make top cap texture coord area
			// proportional to base.
			float u = x/height + 0.5f;
			float v = z/height + 0.5f;

			geometry.Vertices.push_back( Geometry::Vertex(x, y, z, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, u, v) );
		}

		// Cap center vertex.
		geometry.Vertices.push_back( Geometry::Vertex(0.0f, y, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f) );

		// Cache the index of center vertex.
		UINT centerIndex = (UINT)geometry.Vertices.size()-1;

		for(UINT i = 0; i < sliceCount; ++i)
		{
			geometry.Indices.push_back(centerIndex);
			geometry.Indices.push_back(baseIndex + i);
			geometry.Indices.push_back(baseIndex + i+1);
		}

		BuildGeometry(&geometry);
	}

	void GeometryFactory::CreateGrid(float width, float depth, UINT m, UINT n, Dementia::Geometry& geometry)
	{
		UINT vertexCount = m*n;
		UINT faceCount   = (m-1)*(n-1)*2;

		//
		// Create the vertices.
		//

		float halfWidth = 0.5f*width;
		float halfDepth = 0.5f*depth;

		float dx = width / (n-1);
		float dz = depth / (m-1);

		float du = 1.0f / (n-1);
		float dv = 1.0f / (m-1);

		geometry.Vertices.resize(vertexCount);
		for(UINT i = 0; i < m; ++i)
		{
			float z = halfDepth - i*dz;
			for(UINT j = 0; j < n; ++j)
			{
				float x = -halfWidth + j*dx;

				geometry.Vertices[i*n+j].Position = XMFLOAT3(x, 0.0f, z);
				geometry.Vertices[i*n+j].Normal   = XMFLOAT3(0.0f, 1.0f, 0.0f);
				geometry.Vertices[i*n+j].TangentU = XMFLOAT3(1.0f, 0.0f, 0.0f);

				// Stretch texture over grid.
				geometry.Vertices[i*n+j].TexC.x = j*du;
				geometry.Vertices[i*n+j].TexC.y = i*dv;
			}
		}
 
		//
		// Create the indices.
		//

		geometry.Indices.resize(faceCount*3); // 3 indices per face

		// Iterate over each quad and compute indices.
		UINT k = 0;
		for(UINT i = 0; i < m-1; ++i)
		{
			for(UINT j = 0; j < n-1; ++j)
			{
				geometry.Indices[k]   = i*n+j;
				geometry.Indices[k+1] = i*n+j+1;
				geometry.Indices[k+2] = (i+1)*n+j;

				geometry.Indices[k+3] = (i+1)*n+j;
				geometry.Indices[k+4] = i*n+j+1;
				geometry.Indices[k+5] = (i+1)*n+j+1;

				k += 6; // next quad
			}
		}

		BuildGeometry(&geometry);
	}

	void GeometryFactory::CreateFullscreenQuad(Dementia::Geometry& geometry)
	{
		geometry.Vertices.resize(4);
		geometry.Indices.resize(6);

		// Position coordinates specified in NDC space.
		geometry.Vertices[0] = Geometry::Vertex(
			-1.0f, -1.0f, 0.0f, 
			0.0f, 0.0f, -1.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f);

		geometry.Vertices[1] = Geometry::Vertex(
			-1.0f, +1.0f, 0.0f, 
			0.0f, 0.0f, -1.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 0.0f);

		geometry.Vertices[2] = Geometry::Vertex(
			+1.0f, +1.0f, 0.0f, 
			0.0f, 0.0f, -1.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f);

		geometry.Vertices[3] = Geometry::Vertex(
			+1.0f, -1.0f, 0.0f, 
			0.0f, 0.0f, -1.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 1.0f);

		geometry.Indices[0] = 0;
		geometry.Indices[1] = 1;
		geometry.Indices[2] = 2;

		geometry.Indices[3] = 0;
		geometry.Indices[4] = 2;
		geometry.Indices[5] = 3;

		BuildGeometry(&geometry);
	}

	void GeometryFactory::BuildGeometry(Geometry* geometry)
	{
		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(Geometry::Vertex) * geometry->Vertices.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &geometry->Vertices[0];
		m_window->getDevice()->CreateBuffer(&vbd, &vinitData, &geometry->vb);
	
	
		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(UINT) * geometry->Indices.size();
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;
		ibd.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA iinitData;
		iinitData.pSysMem = &geometry->Indices[0];
		HR(m_window->getDevice()->CreateBuffer(&ibd, &iinitData, &geometry->ib));

	}
}