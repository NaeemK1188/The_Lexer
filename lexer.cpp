#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <regex>
#include <iomanip>
#include <fstream>
using namespace std;

string readtext(const string& filename) {
    ifstream file(filename);
    string textFile;

    if (file.is_open()) {
        // Read the entire file into the string
        file.seekg(0, ios::end);
        textFile.reserve(file.tellg());
        file.seekg(0, ios::beg);

        textFile.assign(
            (istreambuf_iterator<char>(file)),
            istreambuf_iterator<char>()
        );

        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }

    return textFile;
}


int main()
{
	ofstream outputFile("output.txt");

  streambuf *original = std::cout.rdbuf();
  cout.rdbuf(outputFile.rdbuf());


	cout<< "Token      |Lexeme " << endl;
	cout<< "-----------|------" << endl;


	string filename = "input_scode.txt";
  string fileContents = readtext(filename);
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
	string::const_iterator  searchStart(fileContents.cbegin());



	while (regex_search(searchStart, fileContents.cend(), match, regexDigit)) // != eol()
	{
		//string matchDig = match[0];
		//double number = stod(matchDig);
		cout << "constant   |" << match[0]; // matchDig
		searchStart = match.suffix().first; // i++
	}

	cout << endl;

	searchStart = fileContents.cbegin(); // reset starting point to th beginning of the fileContents string


	while (regex_search(searchStart, fileContents.cend(), match, regexIdentifier))
	{



		cout << "Identifier |" << match[0] << " ";
		searchStart = match.suffix().first;
		cout << endl;

	}

	searchStart = fileContents.cbegin();

	while (regex_search(searchStart, fileContents.cend(), match, regexOper))
	{

		cout << "Operator   |" << match[0] << " ";

		searchStart = match.suffix().first;
		cout << endl;
	}


	for (string keyword : keywords)
	{
		if (fileContents.find(keyword) != string::npos)
		{
			cout << "keyword    |" << keyword << endl;
		}
	}

	searchStart = fileContents.cbegin();

	while (regex_search(searchStart, fileContents.cend(), match, regexSy))
	{

		cout << "Symbol     |" << match[0] << " ";

		searchStart = match.suffix().first;
		cout << endl;
	}

	std::cout.rdbuf(original);
	outputFile.close();
	return 0;
}
