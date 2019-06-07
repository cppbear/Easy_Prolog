#include "Interface.h"

void Interface::begin()
{
	bool end = false;
	while (!end)
	{
		Error errors;
		Data data;
		std::cout << "?- ";
		std::string a;
		std::getline(std::cin, a);
		if (a[a.length() - 1] == '.')
		{
			if (a.substr(0, 8) == "consult(")
			{
				int p = a.find(')');
				std::string file = a.substr(8, p - 8) + ".pl";
				int flag = data.consult(file, errors);
				if (flag == 2)
					std::cout << "No such file." << std::endl;
				else if (flag == 0)
				{
					std::cout << "true." << std::endl;
					data.OutToken();
				}
				else
					std::cout << "false." << std::endl;
			}
			else if (a == "halt.")
				end = true;
			else
			{
				std::vector<std::string> s;
				s.push_back(a);
				Data user;
				Error u;
				user.split(s, u);
				if (u.SizeOf_mistakes() > 0)
					std::cout << "Wrong command." << std::endl;
				else
					user.Answer(data);
				//user.OutputTokens();
			}
		}
		else
			std::cout << "Wrong command." << std::endl;
	}
}
