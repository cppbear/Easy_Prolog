#include"Data.h"
#include"State.h"

int Data::isCapital(std::string s)
{
	if (s[0] >= 65 && s[0] <= 90)
		return true;
	else if (s[0] >= 97 && s[0] <= 122)
		return false;
	else
		return 2;							//首字符不是字母
}

//0 正确 1 错误 2 文件不存在
int Data::consult(std::string filename, Error &mis)
{
	std::vector<std::string> file_content;
	std::ifstream fin;
	fin.open(filename);
	if (!fin.is_open())
		return 2;
	else
	{
		while (fin.good())
		{
			std::string s;
			getline(fin, s);
			file_content.push_back(s);
		}
		//illegal_space(file_content);
		split(file_content, mis);
		SyntaxCheck(mis);
		if (mis.SizeOf_mistakes() == 0)
		{
			//OutputTokens();
			return 0;
		}
		else
		{
			mis.OutputMistake();
			//OutputTokens();
			return 1;
		}
	}
}

/*
bool Data::illegal_space(std::vector<std::string> content)
{
	for (int i = 0; i < content.size(); i++)
	{
		int p = content[i].find(" (");
		int q = content[i].find(":");
		if (p != -1)
		{
			Mistake fault;
			fault.line = i + 1;
			fault.error = "Space before left bracket";
			mistakes.push_back(fault);
		}
		if (q != -1)
		{
			if (q == content.size() || content[i][q + 1] != '-')
			{
				Mistake fault;
				fault.line = i + 1;
				fault.error = "Wrong use of /':'/";
				mistakes.push_back(fault);
			}
		}
	}
	if (mistakes.size() == 0)
		return true;
	else
		return false;
}
*/

void Data::split(std::vector<std::string> content, Error& mis)
{
	for (int i = 0; i < content.size(); i++)
	{
		std::vector<Token> t;
		std::string str = content[i];
		int n = str.length();
		//去注释
		RemoveComment(i + 1, str, mis);
		n = str.length();
		if (n == 0)
		{
			Token p;
			p.token = str;
			p.type = "NULL";
			t.push_back(p);
			tokens.push_back(t);
			continue;
		}
		int j = 0;
		State state;
		while (j < n)
		{
			switch (state.OutState())
			{
			case 0:state.change(i + 1, 0, str[j], mis, t); break;
			case 1:state.change(i + 1, 1, str[j], mis, t); break;
			case 2:state.change(i + 1, 2, str[j], mis, t); break;
			case 3:state.change(i + 1, 3, str[j], mis, t); break;
			case 4:state.change(i + 1, 4, str[j], mis, t); break;
			case 5:state.change(i + 1, 5, str[j], mis, t); break;
			case 6:state.change(i + 1, 6, str[j], mis, t); break;
			case 7:state.change(i + 1, 7, str[j], mis, t); break;
			case 8:state.change(i + 1, 8, str[j], mis, t); break;
			case -1:break;
			}
			j++;
		}
		tokens.push_back(t);
	}
}

void Data::OutputTokens()
{
	int n = tokens.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < tokens[i].size(); j++)
			std::cout << tokens[i][j].token << "\t" << tokens[i][j].type << std::endl;
	}
}

void Data::SyntaxCheck(Error& mis)
{
	int t = mis.SizeOf_mistakes();
	int n = tokens.size();
	for (int i = 0; i < n; i++)
	{
		if (tokens[i].size() > 0 && tokens[i][0].type == "NULL")
			continue;
		int num_of_dot = 0;
		int left_bracket = 0;
		int right_bracket = 0;
		bool isRule = false;
		for (int j = 0; j < tokens[i].size(); j++)
		{
			if (tokens[i][j].token == ":-")
				isRule = true;
			else if (tokens[i][j].token == ".")
				num_of_dot++;
			else if (tokens[i][j].token == "(")
				left_bracket++;
			else if (tokens[i][j].token == ")")
				right_bracket++;
			else if (tokens[i][j].type == "variable" || tokens[i][j].type == "constant")
			{
				if (j < tokens[i].size() - 1)
				{
					if (tokens[i][j + 1].type == "variable" || tokens[i][j + 1].type == "constant")
					{
						if (!mis.LineIsIn(i + 1))
						{
							std::string str = "Syntax error. No comma between arguments";
							mis.add(i + 1, str);
							break;
						}
					}
				}
			}
			else if (tokens[i][j].token == ",")
			{
				if (tokens[i][j - 1].type != "variable" && tokens[i][j - 1].type != "constant" && tokens[i][j - 1].token != ")")
				{
					if (!mis.LineIsIn(i + 1))
					{
						std::string str = "Syntax error. Lack of arguments";
						mis.add(i + 1, str);
						break;
					}
				}
				if (j < tokens[i].size() - 1)
				{
					if (tokens[i][j + 1].type != "variable" && tokens[i][j + 1].type != "constant" && tokens[i][j + 1].type != "atom")
					{
						if (!mis.LineIsIn(i + 1))
						{
							std::string str = "Syntax error. Lack of arguments";
							mis.add(i + 1, str);
							break;
						}
					}
				}
			}
		}
		if (!isRule)
		{
			for (int j = 0; j < tokens[i].size(); j++)
			{
				if (tokens[i][j].type == "variable")
				{
					if (!mis.LineIsIn(i + 1))
					{
						std::string str = "Syntax error. Variable in fact";
						mis.add(i + 1, str);
						break;
					}
				}
			}
		}
		if (num_of_dot == 0)
		{
			if (!mis.LineIsIn(i + 1))
			{
				std::string str = "Syntax error. No dot";
				mis.add(i + 1, str);
			}
		}
		if (right_bracket != left_bracket)
		{
			if (!mis.LineIsIn(i + 1))
			{
				std::string str = "Syntax error. Bracket mismatch";
				mis.add(i + 1, str);
			}
		}
	}
}

void Data::RemoveComment(int line, std::string &s, Error& mis)
{
	int p = s.find("/*");
	int q = s.find("*/");
	if (p != -1 && q != -1 && q > p)
	{
		s.erase(p, q + 2 - p);
	}
	else if (p == -1 && q == -1)
		return;
	else
	{
		std::string str = "Syntax error. Wrong comments";
		mis.add(line, str);
	}
}

void Data::Answer(Data origin)
{
	int NumOfConstant = 0;
	int NumOfVariable = 0;
	for (int i = 0; i < tokens[0].size(); i++)
	{
		if (tokens[0][i].type == "variable")
			NumOfVariable++;
		else if (tokens[0][i].type == "constant")
			NumOfConstant++;

	}
	if (NumOfVariable == 0)
	{
		bool flag = false;
		std::vector<std::string> use;
		for (int j = 0; j < tokens[0].size(); j++)
			if (tokens[0][j].type == "constant")
				use.push_back(tokens[0][j].token);
		for (int i = 0; i < origin.tokens.size(); i++)
		{
			if (origin.tokens[i].size() > 0 && origin.tokens[i][0].token == tokens[0][0].token)
			{
				std::vector<std::string> database;
				for (int j = 0; j < origin.tokens[i].size(); j++)
					if (origin.tokens[i][j].type == "constant")
						database.push_back(origin.tokens[i][j].token);
				if (database == use)
					flag = true;
			}
		}
		if (flag == true)
		{
			std::cout << "true." << std::endl;
			return;
		}
		else
		{
			std::cout << "false." << std::endl;
			return;
		}
	}
	else
	{
		
		std::vector<std::string> use;
		for (int j = 0; j < tokens[0].size(); j++)
			if (tokens[0][j].type == "constant" || tokens[0][j].type == "variable")
				use.push_back(tokens[0][j].token);
		for (int i = 0; i < origin.tokens.size(); i++)
		{
			if (origin.tokens[i].size() > 0 && origin.tokens[i][0].token == tokens[0][0].token)
			{
				bool flag = true;
				//std::vector<std::string> keys;
				std::vector<std::string> database;
				for (int j = 0; j < origin.tokens[i].size(); j++)
					if (origin.tokens[i][j].type == "constant")
						database.push_back(origin.tokens[i][j].token);
				if (database.size() == use.size())
				{
					for (int k = 0; k < use.size(); k++)
					{
						if (use[k][0] >= 'A' && use[k][0] <= 'Z')
						{
							continue;
						}
						else if (use[k] != database[k])
						{
							flag = false;
							break;
						}
					}
				}
				if (flag == true)
				{
					for (int k = 0; k < use.size(); k++)
					{
						if (use[k][0] >= 'A' && use[k][0] <= 'Z')
						{
							std::cout << use[k] << " = " << database[k] << "." << std::endl;
						}
					}
				}
				else
				{
					std::cout << "No answer." << std::endl;
				}
			}
		}
	}
}

void Data::OutToken()
{
	std::ofstream fout;
	fout.open("token.txt");
	int n = tokens.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < tokens[i].size(); j++)
		{
			if (tokens[i][j].token.length() > 4)
				fout << tokens[i][j].token << "\t" << tokens[i][j].type << std::endl;
			else
				fout << tokens[i][j].token << "\t\t" << tokens[i][j].type << std::endl;
		}
	}
}