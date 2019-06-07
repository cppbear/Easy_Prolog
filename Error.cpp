#include"Error.h"

void Error::add(int line, std::string s)
{
	Mistake temp;
	temp.line = line;
	temp.error = s;
	mistakes.push_back(temp);
}

void Error::OutputMistake()
{
	int n = mistakes.size();
	for (int i = 0; i < n; i++)
	{
		std::cout << "Error: line " << mistakes[i].line << ": " << mistakes[i].error << std::endl;
	}
}

bool Error::LineIsIn(int L)
{
	for (int i = 0; i < mistakes.size(); i++)
	{
		if (mistakes[i].line == L)
			return true;
	}
	return false;
}
