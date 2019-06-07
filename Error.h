#pragma once
#include<string>
#include<vector>
#include<iostream>

struct Mistake
{
	int line;
	std::string error;
};

class Error
{
private:
	std::vector<Mistake> mistakes;
public:
	Error() {};
	~Error() {};
	void add(int line, std::string s);
	int SizeOf_mistakes() { return mistakes.size(); }
	void OutputMistake();
	bool LineIsIn(int L);
};