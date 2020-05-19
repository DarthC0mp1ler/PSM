#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <stack>

using namespace std;

#define _SEPARATOR "," 
#define __N 10 //no of iterations

#define _ANGLE (25 * 3.14159265 / 180) //N deg in rads
struct Rule
{
	string pattern;
	string toReplace;
};

void progress(string & command,const vector<Rule> rules) 
{
	for (size_t i = 0; i < __N; i++)
	{
		for (auto rule : rules)
		{
			command = regex_replace(command,regex(rule.pattern),rule.toReplace);
		}
	}
}

void print(const double x,const double y,ofstream &file) 
{
	file << x << _SEPARATOR << y << endl;
}
void print(ofstream &file)
{
	file << _SEPARATOR << endl;
}

void perform(string command) 
{
	ofstream file;
	file.open("output.txt");
	double x = 0, y = 0, angle = (25 * 3.14159265 / 180);
	stack<double> xs, ys,as;

	for (size_t i = 0; i < command.size(); i++)
	{
		switch (command.at(i))
		{
		case 'F':
			x += cos(angle);
			y += sin(angle);
			print(x, y, file);
			break;
		case '-':
			angle -= _ANGLE;
			break;
		case'+':
			angle += _ANGLE;
			break;
		case '[':
			xs.push(x);
			ys.push(y);
			as.push(angle);
			break;
		case']':
			if (!xs.empty()) {
				x = xs.top();
				xs.pop();
			}
			else cout << "empty" << endl;
			if (!ys.empty()) {
				y = ys.top();
				ys.pop();
			}
			if (!as.empty()) {
				angle = as.top();
				as.pop();
			}
			print(file);
			print(x, y, file);
			break;
		};
	}
	file.close();
}

int main()
{
	cout << _ANGLE << endl;

	string command = "X";

	vector < Rule > rules;

	rules.push_back({ "F","FF" });
	rules.push_back({"X","F+[[X]-X]-F[-FX]+X"});
	
	progress(command, rules);

	cout << command << endl;
	cout << command.size() << endl;

	perform(command);
}