#include <iostream>
#include <string>
#include <sstream>
#include "scanner.h"
#include "parser.h"

using namespace std;

void create(string str_string)
{
	Scanner scanner(str_string);
	Parser parser(scanner);
	try{
		parser.buildExpression();
		string result = parser.getExpressionTree()->result();
		cout << result << "\n";
	//parser.getExpressionTree()->evaluate();
	}catch(std::string &msg){
		std::cout <<  msg << "\n";
	}
}
int main(){
	string input;
	string str_string="";
	cout <<"?- ";
	while(true){
		getline (cin,input);
		while (input.empty())
		{
			cout << "?- ";
			getline (cin,input);
		}
		if (input == "halt.")
			break;
		str_string=str_string+input;
		if (input.find(".")!=string::npos)
		{
			create(str_string);
			//cout << str_string << "\n";
			str_string="";
			cout <<"?- ";
		}		
		else if (input.find(",")!=string::npos || input.find(";")!=string::npos){
			cout << '|' << "\t";
			//continue;
		}
		
	}
	
	return 0;
}