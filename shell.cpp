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
	parser.buildExpression();
	parser.getExpressionTree()->evaluate();
}
int main(){
	string input;
	string str_string="";
	cout <<"?- ";
	while(true){
		cout <<"?- ";
		cin >> input;
		if (input == "halt.")
			break;
		str_string=str_string+input;
		if (input.find(".")!=string::npos)
		{
			//create(str_string);
			cout << str_string << "\n";
			str_string="";
			cout <<"?- ";
		}		
		else{
			cout << '|' << "\t";
			//continue;
		}
		
	}
	
	return 0;
}