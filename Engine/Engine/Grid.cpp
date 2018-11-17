#include "Grid.h"

#include <cmath>
#include <cstdlib>
#include "GameObject.h"

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
}


Grid::~Grid()
{
}

Cell & Grid::getCell(int x, int y, int z)
{
	if (x < 0) x = 0;
	
	else if(x >= m_numCellsX) x = m_numCellsX - 1;
	
	if (y < 0)y = 0;
	else if (y >= m_numCellsY) y = m_numCellsY - 1;
	
	if (z < 0)z = 0;
	else if (z >= m_numCellsZ) z = m_numCellsZ - 1;
	
	
	return m_cells[x + m_width * (y + m_heigth * z)];
}

Cell & Grid::getCell(Vector3 position)
{
	int cellX = (int)position.x / m_cellSize;
	int cellY = (int)position.y / m_cellSize;
	int cellZ = (int)position.z / m_cellSize;

	return getCell(cellX, cellY, cellZ);
	// TODO: insert return statement here
}

void Grid::addObjectToCell( GameObject * obj)
{
	Vector3 tmp;
	tmp = obj->getPosition();
	Cell& cell = getCell(tmp);

	cell.objects_in_cell.push_back(obj);
}
