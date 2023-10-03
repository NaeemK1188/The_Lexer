#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <regex>
#include <iomanip>
using namespace std;



int main()
{


	string sourceCode = "while (t < upper)s=22.00;";
	string sourceCode1 = "int s=20; cout<<s<<endl;";
	string keywords[] = { "cin", "cout", "while", "if", "else", "for", "int", "float", "endl" };
	string regexId = "\\b(?!(cin|cout|while|for|if|else|int|float|endl)\\b)[a-zA-Z_]\\w*\\b";
	string symbol = "[{}();,]| >> | <<";
	string ope = "[\\+\\-*/=<>!%] | == | >= | <= | != ";
	string regexDig = "\\d+\\.\\d+";
	regex regexDigit(regexDig);
	regex regexIdentifier(regexId);
	regex regexOper(ope);
	regex regexSy(symbol);
	smatch match;
	string::const_iterator  searchStart(sourceCode.cbegin());
	


	while (regex_search(searchStart, sourceCode.cend(), match, regexDigit)) // != eol()
	{
		//string matchDig = match[0];
		//double number = stod(matchDig);
		cout << "constant: " << match[0]; // matchDig
		searchStart = match.suffix().first; // i++
	}
	
	cout << endl;

	searchStart = sourceCode.cbegin(); // reset starting point to th beginning of the sourceCode string 


	while (regex_search(searchStart, sourceCode.cend(), match, regexIdentifier))
	{
		
		

		cout << "Identifier: " << match[0] << " ";
		searchStart = match.suffix().first;
		cout << endl;
		
	}

	searchStart = sourceCode.cbegin();

	while (regex_search(searchStart, sourceCode.cend(), match, regexOper))
	{

		cout << "Operator: " << match[0] << " ";

		searchStart = match.suffix().first;
		cout << endl;
	}


	for (string keyword : keywords)
	{
		if (sourceCode.find(keyword) != string::npos)
		{
			cout << "keyword: " << keyword << endl;
		}
	}

	searchStart = sourceCode.cbegin();

	while (regex_search(searchStart, sourceCode.cend(), match, regexSy))
	{

		cout << "Symbol: " << match[0] << " ";

		searchStart = match.suffix().first;
		cout << endl;
	}

    
	return 0;
}