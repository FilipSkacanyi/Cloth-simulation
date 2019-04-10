#include "Grid.h"

#include <cmath>
#include <cstdlib>
#include "GameObject.h"
//#include "OBJ_Loader.h"
#include "Renderer.h"


Grid::Grid(int width, int heigth, int depth, int cellSize)
{
	//create grid
	m_width = width;
	m_heigth = heigth;
	m_depth = depth;
	m_cellSize = cellSize;
	m_numCellsX = ceil((float)width / cellSize);
	m_numCellsY = ceil((float)heigth / cellSize);
	m_numCellsZ = ceil((float)depth / cellSize);

	//since the cells are being created on stack
	//there is no need to worry about memory deletion
	//create cells by resizing the vector
	m_cells.resize(m_numCellsX * m_numCellsY * m_numCellsZ);

	for (int i = 0; i < m_cells.size(); i++)
	{
		m_cells[i].objects_in_cell.reserve(25);
	}


}

Grid::Grid(int width, int heigth, int depth, int cellSize, Renderer * renderer)
{
	//create grid and cube for rendering
	m_width = width;
	m_heigth = heigth;
	m_depth = depth;
	m_cellSize = cellSize;
	m_numCellsX = ceil((float)width / cellSize);
	m_numCellsY = ceil((float)heigth / cellSize);
	m_numCellsZ = ceil((float)depth / cellSize);
	m_tex = new Texture();
	m_tex->Initialize(renderer->getDevice(), L"./Resources/red.png");
	m_cells.resize(m_numCellsX * m_numCellsY * m_numCellsZ);

	//create one vertex and index buffer and use it to create multiple cubes
	//since the cubes are all the same there could be just one model and other boxes just get a pointer to it

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
			//set up cubes for rendering
			for (int k = 0; k < m_numCellsZ; k++)
			{
				m_cells[i + m_numCellsX * (j + m_numCellsY * k)].model = renderer->createRawModel(vertices, 8, indices,36);
				m_cells[i + m_numCellsX * (j + m_numCellsY * k)].model->setPosition(i*cellSize + (float)m_cellSize / 2, j*cellSize + (float)m_cellSize / 2, k*cellSize + (float)m_cellSize / 2);
				m_cells[i + m_numCellsX * (j + m_numCellsY * k)].model->setScale((float)m_cellSize/2 , (float)m_cellSize /2, (float)m_cellSize/2 );
				m_cells[i + m_numCellsX * (j + m_numCellsY * k)].model->setTexture(m_tex);
			}
		}
	}

	
}


Grid::~Grid()
{
	if (m_tex)
	{
		delete m_tex;
		m_tex = nullptr;
	}
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

void Grid::clearAllCells()
{
	for (int i = 0; i < m_cells.size(); i++)
	{
		m_cells[i].objects_in_cell.clear();

	}

}

void Grid::handleCollisions()
{


	for (int x = 0; x < m_numCellsX; x++)
	{
		for (int y = 0; y < m_numCellsY; y++)
		{
			for (int z = 0; z < m_numCellsZ; z++)
			{
				//m_cells[x + m_numCellsX * (y + m_numCellsY * z)];
				int index = x + m_numCellsX * (y + m_numCellsY * z);

				for (int i = 0; i < m_cells[index].objects_in_cell.size(); i++)
				{
					//check all objects within the same cell
					for (int j = i + 1; j <m_cells[index].objects_in_cell.size(); j++)
					{
						if (m_cells[index].objects_in_cell[i]->getCollider()->Intersect(m_cells[index].objects_in_cell[j]->getCollider()))
						{
							m_cells[index].objects_in_cell[i]->collision(m_cells[index].objects_in_cell[j]);
							m_cells[index].objects_in_cell[j]->collision(m_cells[index].objects_in_cell[i]);

						}

						

					}

					//check nearby cells
					//for the purposes of this simulation, we only need 4 cases
					//other cases should be done with a for loop in 3x3x3 space around the original cell
					//one in front
					if (z + 1 < m_numCellsZ)
					{
						checkNeigbourCells(index, i, x + m_numCellsX * (y + m_numCellsY * (z + 1)));
						
					}
					//one behind
					if (z - 1 > 0)
					{
					
						checkNeigbourCells(index, i, x + m_numCellsX * (y + m_numCellsY * (z - 1)));
					}
					//right
					if (x + 1 < m_numCellsX)
					{

						checkNeigbourCells(index, i, (x+1) + m_numCellsX * (y + m_numCellsY * z));
					}
					//left
					if (x - 1 > 0)
					{

						checkNeigbourCells(index, i, (x-1) + m_numCellsX * (y + m_numCellsY * z));
					}

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

void Grid::checkNeigbourCells(int currentCell, int currentObject, int neigbour)
{
		for (int j = 0; j < m_cells[neigbour].objects_in_cell.size(); j++)
		{
			if (m_cells[currentCell].objects_in_cell[currentObject]->getCollider()->Intersect(m_cells[neigbour].objects_in_cell[j]->getCollider()))
			{
				m_cells[currentCell].objects_in_cell[currentObject]->collision(m_cells[neigbour].objects_in_cell[j]);
				m_cells[neigbour].objects_in_cell[j]->collision(m_cells[currentCell].objects_in_cell[currentObject]);

			}
		}
}
