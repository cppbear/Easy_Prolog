#include"State.h"

void State::change(int line, int s, char ch, Error &mis, std::vector<Token> &t)
{
	if (!(ch == ' ' || int(ch) < 0 || ch >= 40 && ch <= 42 || ch >= 44 && ch <= 58 || ch >= 65 && ch <= 90 || ch == 95 || ch >= 97 && ch <= 122))
	{
		if (!mis.LineIsIn(line))
		{
			std::string str = "Lexical error. Illegal character";
			mis.add(line, str);
			state = -1;
			return;
		}
	}
	//填充谓词
	else if (s == 0)
	{
		if (ch == ' ' && content.length() == 0)
			return;
		else if (ch == ' ')
		{
			std::string str = "Lexical error. Illegal space";
			mis.add(line, str);
			state = -1;
			return;
		}
		else if ((ch >= 65 && ch <= 90) && content.length() == 0)
		{
			std::string str = "Lexical error. Incorrect capitalization";
			mis.add(line, str);
			state = -1;
			return;
		}
		else if ((ch >= 48 && ch <= 57) && content.length() == 0)
		{
			std::string str = "Lexical error. First character is a number";
			mis.add(line, str);
			state = -1;
			return;
		}
		else if (ch >= 48 && ch <= 57 || ch >= 65 && ch <= 90 || ch == 95 || ch >= 97 && ch <= 122)
		{
			content += ch;
			return;
		}
		else if (ch == 40)
		{
			Token p;
			p.token = content;
			p.type = "atom";
			t.push_back(p);
			state = 1;
			p.token = "(";
			p.type = "symbol";
			t.push_back(p);
			content = {};
			return;
		}
		else
		{
			std::string str = "Lexical error. Illegal character";
			mis.add(line, str);
			state = -1;
			return;
		}
	}
	//是否有参数
	else if (s == 1)
	{
		if (ch == ' ' && content.length() == 0)
			return;
		else if (ch == ' ')
		{
			Token p;
			p.token = content;
			if (content[0] >= 65 && content[0] <= 90)
				p.type = "variable";
			else
				p.type = "constant";
			t.push_back(p);
			content = {};
			return;
		}
		else if ((ch >= 48 && ch <= 57) && content.length() == 0)
		{
			std::string str = "Lexical error. First character is a number";
			mis.add(line, str);
			state = -1;
			return;
		}
		else if (ch == ')')
		{
			Token p;
			if (content.size() > 0)
			{
				p.token = content;
				if (content[0] >= 65 && content[0] <= 90)
					p.type = "variable";
				else
					p.type = "constant";
				t.push_back(p);
			}
			//content = {};
			//
			//Token p;
			p.token = ")";
			p.type = "symbol";
			if (t[t.size() - 1].token == "(")
			{
				t.push_back(p);
				state = 2;
			}
			else
			{
				t.push_back(p);
				state = 3;
			}
			content = {};
			return;
		}
		else if (ch == 44)
		{
			Token p;
			if (content.size() > 0)
			{
				p.token = content;
				if (content[0] >= 65 && content[0] <= 90)
					p.type = "variable";
				else
					p.type = "constant";
				t.push_back(p);
			}
			//Token p;
			p.token = ",";
			p.type = "symbol";
			t.push_back(p);
			content = {};
			return;
		}
		else if (ch >= 48 && ch <= 57 || ch >= 65 && ch <= 90 || ch == 95 || ch >= 97 && ch <= 122)
		{
			content += ch;
			return;
		}
		else
		{
			std::string str = "Lexical error. Illegal character";
			mis.add(line, str);
			state = -1;
			return;
		}
	}
	//无参数之后，是否为规则
	else if (s == 2)
	{
		if (ch == ' ' && content.length() == 0)
			return;
		else if (ch == ' ')
		{
			std::string str = "Lexical error. Illegal space";
			mis.add(line, str);
			state = -1;
			return;
		}
		else if (ch == ':')
		{
			content += ch;
			return;
		}
		else if (ch == '-')
		{
			if (content.length() == 1 && content[0] == ':')
			{
				Token p;
				p.token = ":-";
				p.type = "symbol";
				t.push_back(p);
				state = 4;
				content = {};
				return;
			}
			else
			{
				std::string str = "Syntax error. Illegal space";
				mis.add(line, str);
				state = -1;
				return;
			}
		}
		else if (ch == '.')
		{
			if (content.length() > 0)
			{
				std::string str = "Lexical error. Illegal character";
				mis.add(line, str);
				state = -1;
				return;
			}
			else
			{
				Token p;
				p.token = ".";
				p.type = "symbol";
				t.push_back(p);
				state = 5;
				content = {};
				return;
			}
		}
		else
		{
			std::string str = "Lexical error. Illegal character";
			mis.add(line, str);
			state = -1;
			return;
		}
	}
	//有参数之后，是否为规则
	else if (s == 3)
	{
		if (ch == ' ' && content.length() == 0)
			return;
		else if (ch == ' ')
		{
			std::string str = "Lexical error. Illegal space";
			mis.add(line, str);
			state = -1;
			return;
		}
		else if (ch == ':')
		{
			content += ch;
			return;
		}
		else if (ch == '-')
		{
			if (content.length() == 1 && content[0] == ':')
			{
				Token p;
				p.token = ":-";
				p.type = "symbol";
				t.push_back(p);
				state = 4;
				content = {};
				return;
			}
			else
			{
				std::string str = "Syntax error. Illegal space";
				mis.add(line, str);
				state = -1;
				return;
			}
		}
		else if (ch == '.')
		{
			if (content.length() > 0)
			{
				std::string str = "Lexical error. Illegal character";
				mis.add(line, str);
				state = -1;
				return;
			}
			else
			{
				Token p;
				p.token = ".";
				p.type = "symbol";
				t.push_back(p);
				state = 5;
				content = {};
				return;
			}
		}
		else
		{
			std::string str = "Lexical error. Illegal character";
			mis.add(line, str);
			state = -1;
			return;
		}
	}
	//有规则之后 填充谓词
	else if (s == 4)
	{
		if (ch == ' ' && content.length() == 0)
			return;
		else if (ch == ' ')
		{
			std::string str = "Lexical error. Illegal space";
			mis.add(line, str);
			state = -1;
			return;
		}
		else if (ch == '.')
		{
			if (content.length() > 0)
			{
				std::string str = "Lexical error. Illegal character";
				mis.add(line, str);
				state = -1;
				return;
			}
			else
			{
				Token p;
				p.token = ".";
				p.type = "symbol";
				t.push_back(p);
				state = 8;
				content = {};
				return;
			}
		}
		else if ((ch >= 65 && ch <= 90) && content.length() == 0)
		{
			std::string str = "Lexical error. Incorrect capitalization";
			mis.add(line, str);
			state = -1;
			return;
		}
		else if ((ch >= 48 && ch <= 57) && content.length() == 0)
		{
			std::string str = "Lexical error. First character is a number";
			mis.add(line, str);
			state = -1;
			return;
		}
		else if (ch >= 48 && ch <= 57 || ch >= 65 && ch <= 90 || ch == 95 || ch >= 97 && ch <= 122)
		{
			content += ch;
			return;
		}
		else if (ch == 40)
		{
			Token p;
			p.token = content;
			p.type = "atom";
			t.push_back(p);
			state = 6;
			p.token = "(";
			p.type = "symbol";
			t.push_back(p);
			content = {};
			return;
		}
		else
		{
			std::string str = "Lexical error. Illegal character";
			mis.add(line, str);
			state = -1;
			return;
		}
	}
	//无规则之后检测结束
	else if (s == 5)
	{
		if (ch == ' ' && content.length() == 0)
			return;
		else
		{
			std::string str = "Lexical error. Illegal character";
			mis.add(line, str);
			state = -1;
			return;
		}
	}
	//填充参数
	else if (s == 6)
	{
		if (ch == ' ' && content.length() == 0)
			return;
		else if (ch == ' ')
		{
			Token p;
			p.token = content;
			if (content[0] >= 65 && content[0] <= 90)
				p.type = "variable";
			else
				p.type = "constant";
			t.push_back(p);
			content = {};
			return;
		}
		else if ((ch >= 48 && ch <= 57) && content.length() == 0)
		{
			std::string str = "Lexical error. First character is a number";
			mis.add(line, str);
			state = -1;
			return;
		}
		else if (ch == ')')
		{
			Token p;
			if (content.size() > 0)
			{
				p.token = content;
				if (content[0] >= 65 && content[0] <= 90)
					p.type = "variable";
				else
					p.type = "constant";
				t.push_back(p);
			}
			//Token p;
			p.token = ")";
			p.type = "symbol";
			t.push_back(p);
			state = 7;
			content = {};
			return;
		}
		else if (ch == 44)
		{
			Token p;
			if (content.size() > 0)
			{
				p.token = content;
				if (content[0] >= 65 && content[0] <= 90)
					p.type = "variable";
				else
					p.type = "constant";
				t.push_back(p);
			}
			//Token p;
			p.token = ",";
			p.type = "symbol";
			t.push_back(p);
			content = {};
			return;
		}
		else if (ch >= 48 && ch <= 57 || ch >= 65 && ch <= 90 || ch == 95 || ch >= 97 && ch <= 122)
		{
			content += ch;
			return;
		}
		else
		{
			std::string str = "Lexical error. Illegal character";
			mis.add(line, str);
			state = -1;
			return;
		}
	}
	//检测逗号、句号
	else if (s == 7)
	{
		if (ch == ' ' && content.length() == 0)
			return;
		if (ch == ',')
		{
			Token p;
			p.token = ",";
			p.type = "symbol";
			t.push_back(p);
			content = {};
			state = 4;
			return;
		}
		else if (ch == '.')
		{
			Token p;
			p.token = ".";
			p.type = "symbol";
			t.push_back(p);
			content = {};
			state = 8;
			return;
		}
		else
		{
			std::string str = "Syntax error. Illegal character";
			mis.add(line, str);
			state = -1;
			return;
		}
	}
	//是否结束
	else if (s == 8)
	{
		if (ch == ' ' && content.length() == 0)
			return;
		else
		{
			std::string str = "Lexical error. Illegal character";
			mis.add(line, str);
			state = -1;
			return;
		}
	}
}
