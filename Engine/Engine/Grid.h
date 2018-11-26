#pragma once
#include <vector>
#include "CollisionUtilities.h"

class GameObject;
class Renderer;
class Model;
struct Cell
{
	std::vector<GameObject*> objects_in_cell;

	Model* model = nullptr;
};

class Grid
{
public:
	Grid(int width, int heigth, int depth, int cellSize);
	Grid(int width, int heigth, int depth, int cellSize, Renderer* renderer);
	~Grid();

	//get cell base don the indexes in the array
	Cell* getCell(int x, int y, int z);

	//get cell based on world position
	Cell* getCell(Vector3 position);

	void addObject(GameObject* obj);
	void addObjectToCell( GameObject * obj, Cell * cell);
	void removeObjectFromCell(GameObject * obj);
	void clearAllCells();
	void handleCollisions();

	void Render(Renderer* renderer);

private:
	std::vector<Cell> m_cells;

	int m_width,
		m_heigth,
		m_depth,
		m_cellSize,
		m_numCellsX,
		m_numCellsY,
		m_numCellsZ;
};

