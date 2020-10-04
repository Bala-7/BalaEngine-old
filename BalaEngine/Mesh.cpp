#include "Mesh.h"
#define _USE_MATH_DEFINES
#include "math.h"


void Mesh::setTriData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
	std::vector<Vertex> _vertices = {
		{	
			{ 0.0f, -1.0f, 0.0f }, // Position
			{ 0.0f, 0.0f, 1.0 }, // Normal
			{ 1.0f, 0.0f, 0.0 }, // Color
			{ 0.0, 1.0 } // Texture Coordinate
		}, // 0
		{ 
			{ 1.0f, 1.0f, 0.0f }, 
			{ 0.0f, 0.0f, 1.0 },
			{ 0.0f, 1.0f, 0.0 },
			{ 0.0, 0.0 } 
		}, // 1
		{ 
			{ -1.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0 },
			{ 0.0f, 0.0f, 1.0 },
			{ 1.0, 0.0 } }, // 2
	}; 

	std::vector<uint32_t> _indices = { 0, 1, 2, };

	vertices.clear(); indices.clear();
	vertices = _vertices;
	indices = _indices;
}


void Mesh::setQuadData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
	std::vector<Vertex> _vertices = {
		{
			{ -1.0f, -1.0f, 0.0f }, // Position
			{ 0.0f, 0.0f, 1.0 }, // Normal
			{ 1.0f, 0.0f, 0.0 }, // Color
			{ 0.0, 1.0 } // Texture Coordinate
		}, // 0
		{
			{ 1.0f, -1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0 },
			{ 0.0f, 1.0f, 0.0 },
			{ 0.0, 0.0 }
		}, // 1
		{
			{ 1.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0 },
			{ 0.0f, 0.0f, 1.0 },
			{ 1.0, 0.0 } 
		}, // 2
		{
			{ -1.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0 },
			{ 1.0f, 0.0f, 1.0 },
			{ 1.0, 0.0 }
		} // 3
	};

	std::vector<uint32_t> _indices = {	0, 1, 2, 
										0, 2, 3 };

	vertices.clear(); indices.clear();
	vertices = _vertices;
	indices = _indices;
}

void Mesh::setCubeData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
	std::vector<Vertex> _vertices = {
		{
			{ -1.0f, -1.0f, 0.0f }, // Position
			{ 0.0f, 0.0f, 1.0 }, // Normal
			{ 1.0f, 0.0f, 0.0 }, // Color
			{ 0.0, 1.0 } // Texture Coordinate
		}, // 0
		{
			{ 1.0f, -1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0 },
			{ 0.0f, 1.0f, 0.0 },
			{ 0.0, 0.0 }
		}, // 1
		{
			{ 1.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0 },
			{ 0.0f, 0.0f, 1.0 },
			{ 1.0, 0.0 } 
		}, // 2
		{
			{ -1.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0 },
			{ 1.0f, 0.0f, 1.0 },
			{ 1.0, 0.0 }
		}, // 3
		{
			{ -1.0f, -1.0f, -2.0f }, // Position
			{ 0.0f, 0.0f, 1.0 }, // Normal
			{ 0.0f, 1.0f, 0.0 }, // Color
			{ 0.0, 1.0 } // Texture Coordinate
		}, // 4
		{
			{ 1.0f, -1.0f, -2.0f },
			{ 0.0f, 0.0f, 1.0 },
			{ 0.5f, 1.5f, 1.0 },
			{ 0.0, 0.0 }
		}, // 5
		{
			{ 1.0f, 1.0f, -2.0f },
			{ 0.0f, 0.0f, 1.0 },
			{ 1.0f, 0.0f, 1.0 },
			{ 1.0, 0.0 }
		}, // 6
		{
			{ -1.0f, 1.0f, -2.0f },
			{ 0.0f, 0.0f, 1.0 },
			{ 1.0f, 1.0f, 1.0 },
			{ 1.0, 0.0 }
		} // 7
	};

	std::vector<uint32_t> _indices = {	0, 1, 2,	// Front
										0, 2, 3,
										2, 3, 7,	// Top
										2, 6, 7,
										1, 2, 5,	// Right
										2, 5, 6,
										0, 3, 4,	//Left
										3, 4, 7,
										0, 1, 4,	// Bottom
										1, 4, 5, 
										4, 5, 6,	// Back
										4, 6, 7 };

	vertices.clear(); indices.clear();
	vertices = _vertices;
	indices = _indices;
}

void Mesh::setSphereData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
	
	int i, j;
	//std::vector<GLfloat> _vertices;
	//std::vector<GLuint> _indices;
	std::vector<Vertex> _vertices;
	std::vector<uint32_t> _indices;
	
	int lats = 5;
	int longs = 5;

	int indicator = 0;
	/*for (i = 0; i <= lats; i++) {
		
		double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = M_PI * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		for (j = 0; j <= longs; j++) {
			double lng = 2 * M_PI * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			Vertex v0{ 
				{x * zr0, y * zr0, z0},	// Pos
				{0.0, 0.0, 1.0 },	// Normal
				{0.0, 1.0, 1.0 },	// Color
				{1.0, 1.0},	// Texture coords
					};
			_vertices.push_back(v0);
			_indices.push_back(indicator);
			indicator++;
			
			Vertex v1{
				{x * zr1, y * zr1, z1},	// Pos
				{0.0, 0.0, 1.0 },	// Normal
				{0.0, 1.0, 1.0 },	// Color
				{1.0, 1.0},	// Texture coords
			};
			_vertices.push_back(v1);
			_indices.push_back(indicator);
			indicator++;
		}
		indices.push_back(GL_PRIMITIVE_RESTART_FIXED_INDEX);
	}*/

	float radius = 1.0f;
	float x, y, z, xy;                              // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
	float s, t;                                     // vertex texCoord
	int sectorCount = 36;
	int stackCount = 18;
	float sectorStep = 2.0f * M_PI / sectorCount;
	float stackStep = M_PI / static_cast<float>(stackCount);
	float sectorAngle, stackAngle;
	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
			
			// normalized vertex normal (nx, ny, nz)
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			
			// vertex tex coord (s, t) range between [0, 1]
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			
			Vertex v{
				{x, y, z},	// Pos
				{nx, ny, nz },	// Normal
				{x, ny, nz },	// Color
				{s, t},	// Texture coords
			};
			_vertices.push_back(v);
		}
	}

	int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // beginning of current stack
		k2 = k1 + sectorCount + 1;      // beginning of next stack

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				_indices.push_back(k1);
				_indices.push_back(k2);
				_indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				_indices.push_back(k1 + 1);
				_indices.push_back(k2);
				_indices.push_back(k2 + 1);
			}
		}
	}

	vertices.clear(); indices.clear();
	vertices = _vertices;
	indices = _indices;
	
}