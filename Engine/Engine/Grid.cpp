#include "Grid.h"

#include <cmath>
#include <cstdlib>
#include "GameObject.h"
//#include "OBJ_Loader.h"
#include "Renderer.h"


Grid::Grid(int width, int heigth, int depth, int cellSize)
{
	m_width = width;
	m_heigth = heigth;
	m_depth = depth;
	m_cellSize = cellSize;
	m_numCellsX = ceil((float)width / cellSize);
	m_numCellsY = ceil((float)heigth / cellSize);
	m_numCellsZ = ceil((float)depth / cellSize);

	m_cells.resize(m_numCellsX * m_numCellsY * m_numCellsZ);

	for (int i = 0; i < m_cells.size(); i++)
	{
		m_cells[i].objects_in_cell.reserve(25);
	}


}

Grid::Grid(int width, int heigth, int depth, int cellSize, Renderer * renderer)
{
	m_width = width;
	m_heigth = heigth;
	m_depth = depth;
	m_cellSize = cellSize;
	m_numCellsX = ceil((float)width / cellSize);
	m_numCellsY = ceil((float)heigth / cellSize);
	m_numCellsZ = ceil((float)depth / cellSize);

	m_cells.resize(m_numCellsX * m_numCellsY * m_numCellsZ);
	Vertex vertices[] =
	{
		{ DirectX::XMFLOAT3(-1.0f,  1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f,  1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f,  1.0f,  1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-1.0f,  1.0f,  1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, -1.0f,  1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-1.0f, -1.0f,  1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
	};

	// Create index buffer
	unsigned long indices[] =
	{
		3,1,0,
		2,1,3,

		0,5,4,
		1,5,0,

		3,4,7,
		0,4,3,

		1,6,5,
		2,6,1,

		2,7,6,
		3,7,2,

		6,4,5,
		7,4,6,
	};

	


	for (int i = 0; i < m_numCellsX; i++)
	{
		for (int j = 0; j < m_numCellsY; j++)
		{
			for (int k = 0; k < m_numCellsZ; k++)
			{
				m_cells[i + m_numCellsX * (j + m_numCellsY * k)].model = renderer->createRawModel(vertices, 8, indices,36);
				m_cells[i + m_numCellsX * (j + m_numCellsY * k)].model->setPosition(i*cellSize + (float)m_cellSize / 2, j*cellSize + (float)m_cellSize / 2, k*cellSize + (float)m_cellSize / 2);
				m_cells[i + m_numCellsX * (j + m_numCellsY * k)].model->setScale((float)m_cellSize/2 , (float)m_cellSize /2, (float)m_cellSize/2 );
			}
		}
	}

	
}


Grid::~Grid()
{
}

Cell * Grid::getCell(int x, int y, int z)
{
	if (x < 0) x = 0;
	
	else if(x >= m_numCellsX) x = m_numCellsX - 1;
	
	if (y < 0)y = 0;
	else if (y >= m_numCellsY) y = m_numCellsY - 1;
	
	if (z < 0)z = 0;
	else if (z >= m_numCellsZ) z = m_numCellsZ - 1;
	
	
	return &m_cells[x + m_numCellsX * (y + m_numCellsY * z)];
}

Cell * Grid::getCell(Vector3 position)
{
	int cellX = (int)position.x / m_cellSize;
	int cellY = (int)position.y / m_cellSize;
	int cellZ = (int)position.z / m_cellSize;

	return getCell(cellX, cellY, cellZ);
	
}

void Grid::addObject(GameObject * obj)
{
	Vector3 tmp;
	tmp = obj->getPosition();
	Cell* cell = getCell(tmp);

	cell->objects_in_cell.push_back(obj);

}

void Grid::addObjectToCell( GameObject * obj, Cell * cell)
{
	cell->objects_in_cell.push_back(obj);

	
}

void Grid::removeObjectFromCell(GameObject * obj)
{
	


}

void Grid::clearAllCells()
{
	for (int i = 0; i < m_cells.size(); i++)
	{
		m_cells[i].objects_in_cell.clear();

	}

}

void Grid::handleCollisions()
{

	for (int k = 0; k < m_cells.size(); k++)
	{
		
		for (int i = 0; i < m_cells[k].objects_in_cell.size(); i++)
		{
			for (int j = i + 1; j < m_cells[k].objects_in_cell.size(); j++)
			{
				if (m_cells[k].objects_in_cell[i]->getCollider()->Intersect(m_cells[k].objects_in_cell[j]->getCollider()))
				{
					m_cells[k].objects_in_cell[i]->collision(m_cells[k].objects_in_cell[j]);
   					m_cells[k].objects_in_cell[j]->collision(m_cells[k].objects_in_cell[i]);
					//m_objectsInScene[j]->AddForce(DirectX::XMFLOAT3(0, 5, 0));
				}
			}
		}
	}
}

void Grid::Render(Renderer * renderer)
{
	for (int i = 0; i < m_cells.size(); i++)
	{
		renderer->renderModel(m_cells[i].model);
	}
}
