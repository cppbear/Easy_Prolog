#pragma once
#include<string>
#include"Error.h"
#include"Data.h"

class State
{
private:
	int state = 0;
	std::string content;
public:
	State() {};
	~State() {};
	int OutState() { return state; }
	void change(int line, int s, char ch, Error &mis, std::vector<Token> &t);

};