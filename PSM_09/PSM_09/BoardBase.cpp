#include "boardbase.h"
#include <iostream>

void Board::SetRules(wchar_t* str)
{
	bool alive = true;
	for (size_t i = 0; i < 19; i++)
	{
		if (str[i] == '\0') break;
		if (str[i] == '/')alive = false;
		else
			if (alive)
				rulesAlive.push_back(str[i] - 48);
			else
				rulesDead.push_back(str[i] - 48);
	}
}

Board::Board(wchar_t* str)
{
	SetRules(str);
	int x = 50, y = 50;
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t j = 0; j < dim; j++)
		{
			board[i][j].x = x;
			board[i][j].y = y;
			y += 15;
		}
		x += 15;
		y = 50;
	}

}

void Board::UpdateRules(wchar_t* str)
{
	rulesAlive.clear();
	rulesDead.clear();
	SetRules(str);
}

void Board::PaintCells(DrawMat mat)
{
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t j = 0; j < dim; j++)
		{
			D2D1_RECT_F rectangle = D2D1::RectF(
				board[i][j].x,
				board[i][j].y,
				board[i][j].x + 15,
				board[i][j].y + 15
			);
			if (i == 0 || i == dim - 1 || j == 0 || j == dim - 1)
			{
				if (board[i][j].isAlive)
					mat.pRenderTarget->FillRectangle(rectangle, mat.pBrushCell);
				mat.pRenderTarget->DrawRectangle(rectangle, mat.pBrushEmptyCell);
			}
			else {
				if (board[i][j].isAlive)
					mat.pRenderTarget->FillRectangle(rectangle, mat.pBrushCell);
				else
					mat.pRenderTarget->DrawRectangle(rectangle, mat.pBrushBorder);
			}
		}
	}
}

void Board::ChangeCell(float x, float y)
{
	x = x - 50;
	y = y - 50;
	board[(int)(x / 15)][(int)(y / 15)].negate();

	SyclicBounds();
}

int Board::countNeighbours(int i, int j)
{
	int count = 0;

	if (board[i - 1][j].isAlive) count++;
	if (board[i - 1][j - 1].isAlive) count++;
	if (board[i - 1][j + 1].isAlive) count++;
	if (board[i][j - 1].isAlive) count++;
	if (board[i][j + 1].isAlive) count++;
	if (board[i + 1][j].isAlive) count++;
	if (board[i + 1][j - 1].isAlive) count++;
	if (board[i + 1][j + 1].isAlive) count++;
	return count;

}

void Board::SyclicBounds()
{
	for (size_t i = 1; i < dim - 1; i++)
	{
		board[dim - 1][i].setData(board[1][i]);
		board[i][dim - 1].setData(board[i][1]);

		board[0][i].setData(board[dim - 2][i]);
		board[i][0].setData(board[i][dim - 2]);
	}

	board[dim - 1][dim - 1].setData(board[1][1]);
	board[0][dim - 1].setData(board[dim - 2][1]);
	board[dim - 1][0].setData(board[1][dim - 1]);
	board[0][0].setData(board[dim - 2][dim - 2]);
}


void Board::Step()
{
	Cell newBoard[dim][dim];
	int x = 50, y = 50;
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t j = 0; j < dim; j++)
		{
			newBoard[i][j].x = x;
			newBoard[i][j].y = y;
			y += 15;
			newBoard[i][j].setData(board[i][j]);
		}
		x += 15;
		y = 50;
	}

	SyclicBounds();
	for (size_t i = 1; i < dim - 1; i++)
	{
		for (size_t j = 1; j < dim - 1; j++)
		{

			int n = countNeighbours(i, j);
			if (board[i][j].isAlive) {
				for (auto r : rulesAlive)
				{
					if (n == r)
					{
						goto endloop;
					}
				}
				newBoard[i][j].negate();
			}
			else {
				for (auto r : rulesDead)
				{
					if (n == r)
					{
						newBoard[i][j].negate();
						goto endloop;
					}
				}

			}
		endloop: std::cout;
		}
	}
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t j = 0; j < dim; j++)
		{
			board[i][j].setData(newBoard[i][j]);
		}
	}
}