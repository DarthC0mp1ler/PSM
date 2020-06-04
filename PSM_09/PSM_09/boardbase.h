#include <d2d1.h>
#include <vector>
#include <algorithm>

#ifndef __BOARDBASE_H_
#define __BOARDBASE_H_

#define dim  30

struct DrawMat
{
	ID2D1RenderTarget* pRenderTarget;
	ID2D1SolidColorBrush* pBrushCell;
	ID2D1SolidColorBrush* pBrushEmptyCell;
	ID2D1SolidColorBrush* pBrushBorder;
};

struct Cell
{
	bool isAlive;
	int x, y;

	void negate()
	{
		isAlive = !isAlive;
	}

	Cell getCopy()
	{
		return Cell{ isAlive, x, y};
	}

	void setData(Cell c)
	{
		isAlive = c.isAlive;
		//x = c.x;
		//y = c.y;
	}
};

class Board
{
	
	std::vector<int> rulesAlive, rulesDead;

	Cell board[dim][dim];

	void SetRules(wchar_t*);
	int countNeighbours(int i, int j);
	void SyclicBounds();
public:
	void UpdateRules(wchar_t*);
	void PaintCells(DrawMat mat);

	Board(wchar_t*);
	//~Board();
	void ChangeCell(float x, float y);
	
	void Step();
	


};
#endif //!__BOARDBASE_H_

