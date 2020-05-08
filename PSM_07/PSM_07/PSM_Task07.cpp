#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

#define Rsz 41
#define sz (Rsz*Rsz-2)

double north = 200, south = 150, west = 100, east = 50;

	struct Matrix {
		vector<vector<double>> m;

		void rowAdd(int row,double d)
		{
			if (row < m.size()) 
			{
				for (size_t i = 0; i < m.at(row).size(); i++)
				{
					m.at(row).at(i) = m.at(row).at(i) + d;
				}
			}
		}
		void rowAdd(int row,vector<double> d)
		{
			if (row < m.size() && m.at(row).size() == d.size())
			{
				for (size_t i = 0; i < m.at(row).size(); i++)
				{
					m.at(row).at(i) = m.at(row).at(i) + d.at(i);
				}
			}
		}

		void rowMultiply(int row, double d)
		{
			if (row < m.size())
			{
				for (size_t i = 0; i < m.at(row).size(); i++)
				{
					m.at(row).at(i) = m.at(row).at(i) * d;
				}
			}
		}
		void rowMultiply(int row, vector<double> d)
		{
			if (row < m.size() && m.at(row).size() == d.size())
			{
				for (size_t i = 0; i < m.at(row).size(); i++)
				{
					m.at(row).at(i) = m.at(row).at(i) * d.at(i);
				}
			}
		}

		bool swapWithFirstNonZero(int row, int col,bool down)
		{
			if (row < m.size() && m.at(row).size() > col)
			{

				if (m.at(row).at(col) != 0) return false;
				size_t i = col;
				if (down) 
				{
					while (i < m.size())
					{
						if (m.at(i).at(col) != 0.) 
						{
							iter_swap(m.begin() + row, m.begin() + i);
							return true;
						}
						i++;
					}
				}
				else
				{
					while (i >= 0)
					{
						if (m.at(i).at(col) != 0.)
						{
							iter_swap(m.begin() + row, m.begin() + i);
							return true;
						}
						i--;
					}
				}				
			}
			return false;
		}

		vector<double> getVector(int row)
		{
			if (row < m.size()) 
			{
				return m.at(row);
			}
			return vector<double>{};
		}

		vector<double> getOutputColumn()
		{
			vector<double> v;
			for (size_t i = 0; i < m.size(); i++)
			{
				v.push_back(m.at(i).at(m.at(i).size()-1));
			}
			return v;
		}

		vector<double> getNegativeVector(int row)
		{
			if (row < m.size())
			{
				vector < double > v;
				for (size_t i = 0; i < m.at(row).size(); i++)
				{
					v.push_back(m.at(row).at(i)*(-1));
				}
				return v;
			}
			return vector<double>{};
		}
		

		Matrix operator*(double d) {
			vector<vector<double>> res;
			for (auto r :m)
			{
				vector<double> v;
				for (auto c : r)
				{
					v.push_back(c*d);
				}
				res.push_back( v );
			}
			return Matrix{res};
		}
		Matrix operator/(double d) {
		
			return *this * (1/d);
		}
		 
		Matrix operator=(Matrix m) 
		{
			vector<vector<double>> v;
			for (auto r : m.m)
			{
				vector<double> d;
				for (auto c : r)
				{
					d.push_back(c);
				}
				v.push_back(d);
			}
			this->m = v;
			return *this;
		}
		
	};

	ostream& operator<<(ostream& os, const Matrix& M)
	{
		os << "\n";
		for (auto r : M.m)
		{
			os << "|[ ";
			for (auto c : r)
			{
				os << c << " ";
			}
			os << "]|\n";
		}
		return os;
	}

	


ostream& operator<<(ostream& os, const vector < double >& v)
{
	os << "\n";
	os << "|[ ";
	for (auto c : v)
	{
		os << c << " ";
	}
	os << "]|\n";
	return os;
}

Matrix gauss(Matrix M)
{
	//todo not empty
	//todo rows same length
	for (size_t j = 0, k = 0; k < M.m.size(); j++,k++)
	{
		size_t tmp = j;
		loop:if (M.m.at(k).at(j) == 0) {
			if (!M.swapWithFirstNonZero(k, j, true))
			{
				j++;
				if (j > M.m.size()) {
					tmp++;
					j = tmp;
				}
				goto loop;
			}
		}

		if (M.m.at(k).at(j) != 1) M.rowMultiply(k, (1 / M.m.at(k).at(j)));
		for (size_t i = 0; i < M.m.size(); i++)
		{
			if (i != j) {
				vector<double> tmp = M.m.at(k);
				M.rowMultiply(k, M.m.at(i).at(j));
				M.rowAdd(i, M.getNegativeVector(k));
				M.m.at(k) = tmp;
			}
		}
		cout << k <<" - "<<((double)k*100./(double)M.m.size())<<"%" << endl;
	}
	for (size_t i = 0; i < M.m.size(); i++)
	{
		M.rowAdd(i, 0);
	}
	return M;
}




void getRow(size_t r, size_t c, vector<double>& vec)
{
	for (size_t k = 0; k < sz; k++)
	{
		if (k == (r*(Rsz-2)+c))
		{
			vec.push_back(-4);
		}
		else if ((c - 1) != -1 && (k == (r * (Rsz - 2) + (c - 1))))
		{
			vec.push_back(1);
		}
		else if ((c + 1) != Rsz-2 && (k == (r * (Rsz - 2) + (c + 1))))
		{
			vec.push_back(1);
		}
		else if ((r - 1) != -1 && (k == ((r-1) * (Rsz - 2) + c)))
		{
			vec.push_back(1);
		}
		else if ((r + 1) != Rsz-1 && (k == ((r+1) * (Rsz - 2) + c )))
		{
			vec.push_back(1);
		}
		else vec.push_back(0);
	}
}



vector<vector<double>> getMatrix()
{
	vector<vector<double>> res;
	for (size_t row = 1; row < Rsz; row++)
	{
		for (size_t col = 1; col < Rsz-1; col++)
		{
			double d = 0;
			if (col - 1 == 0) d -= west;
			if (col + 1 == Rsz-1) d -= east;
			if (row - 1 == 0) d -= south;
			if (row + 1 == Rsz) d -= north;
			vector<double> vec;
			getRow(row-1, col-1, vec);
			vec.push_back(d);
			res.push_back(vec);
		}
	}
	return res;
}

void write(vector<double> v)
{
	ofstream file;
	file.open("output.txt");

	for (size_t i = 0,k=0; i < Rsz; i++)
	{
		for (size_t j = 0; j < Rsz; j++)
		{
			if ((i == 0 && j == 0) || (i == Rsz - 1 && j == 0) || (i == 0 && j == Rsz - 1) || (i == Rsz - 1 && j == Rsz - 1)) file << ",";
			else if (i == 0) file << south << ",";
			else if (i == Rsz - 1) file << north << ",";
			else if (j == 0) file << west << ",";
			else if (j == Rsz - 1) file << east << ",";
			else 
			{
				file << v.at(k++) << ",";
			}
		}
		file << "\n";
	}
	file.close();
}



int main() 
{
	Matrix m1 = {getMatrix()};
	cout << "Matrix created" << endl;

	vector < double > out;
	m1 = gauss(m1);
	cout << "Gaussian Elimination" << endl;
	cout << "output" << endl;
	out = m1.getOutputColumn();

	write(out);
}

