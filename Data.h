#pragma once
#include<string>
#include<vector>
#include<fstream>
#include"Error.h"

struct Token
{
	std::string token;
	std::string type;
};

struct Fact
{
	std::string predicate;
	int num;
	std::vector<std::string> content;
};

struct Rule
{
	std::string predicate;
	int num;
	std::vector<std::string> content;
};

class Data
{
private:
	std::vector<std::vector<Token>> tokens;
	std::vector<Fact> facts;
	std::vector<Rule> rules;
	int isCapital(std::string s);
public:
	Data() {};
	~Data() {};
	int consult(std::string filename, Error &mis);
	//bool illegal_space(std::vector<std::string> content);
	void split(std::vector<std::string> content, Error& mis);
	void OutputTokens();
	void SyntaxCheck(Error& mis);
	void RemoveComment(int line, std::string &s, Error& mis);
	void Answer(Data origin);
	void OutToken();
};
