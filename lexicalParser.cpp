#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

void getNextWord(string &input, ofstream &file, ifstream &inFile);
void analyzeWord(string word);
void commentReader(ifstream &inFile, string &input);

int main () {
    ifstream inFile;
    ofstream outFile;
    string input;
    
    inFile.open ("in.txt");
    outFile.open("tokens.txt");
    
    if (inFile.is_open()) {
        while (getline(inFile, input)) {
            while (input != "") {
                cout << "getNextWord\n";
                getNextWord(input, outFile, inFile);
            }
            
            cout << input << '\n';
        }
        inFile.close();
        outFile.close();
    }
    
    return 0;
}

void getNextWord(string &input, ofstream &outFile, ifstream &inFile) {
    string word;
    bool splitInput;
    
    for(int i = 0; i < input.length(); i++) {
        splitInput = true;
        
        //cout << "index at " << i << " input.length() " << input.length() << "\n";
        //cout << "input: " << input << " word: " << word << "\n";
        
        switch (input.at(i)) {
            case ' ':
                word = input.substr(0, i);
                analyzeWord(word);
                break;
            // Symbols
            case ':':
                word = input.substr(0, i);
                analyzeWord(word);
                cout << ": is a valid symbol.\n";
                break;
            case ',':
                word = input.substr(0, i);
                analyzeWord(word);
                cout << ", is a valid symbol.\n";
                break;
            case ';':
                word = input.substr(0, i);
                analyzeWord(word);
                cout << "; is a valid symbol.\n";
                break;
            case '(':
                word = input.substr(0, i);
                analyzeWord(word);
                cout << "( is a valid symbol.\n";
                break;
            case ')':
                word = input.substr(0, i);
                analyzeWord(word);
                cout << ") is a valid symbol.\n";
                break;
            case '{':
                word = input.substr(0, i);
                analyzeWord(word);
                cout << "{ is a valid symbol.\n";
                break;
            case '}':
                word = input.substr(0, i);
                analyzeWord(word);
                cout << "} is a valid symbol.\n";
                break;
            // Operators
            case '/':
                word = input.substr(0, i);
                analyzeWord(word);
                
                if ((i + 1) < input.length() && input.at(i + 1) == '/') {
                    cout << word << input << " is a comment.\n";
                    return;
                }else
                if ((i + 1) < input.length() && input.at(i + 1) == '*') {
                    cout << "/* is the beginning of a comment.\n";
                    commentReader(inFile, input);
                }
                else
                    cout << "/ is a division operator.\n";
                break;
            case '+':
                word = input.substr(0, i);
                analyzeWord(word);
                cout << "+ is an addition operator.\n";
                break;
            case '-':
                word = input.substr(0, i);
                analyzeWord(word);
                /*
                if(isdigit(input.at(i + 1))) {
                       
                }
                else {
                    cout << "- is a subtraction operator.\n";
                }
                */
                cout << "- is a subtraction operator.\n";
                break;
            case '*':
                word = input.substr(0, i);
                analyzeWord(word);
                cout << "* is a multiplication operator.\n";
                break;
            case '=':
                word = input.substr(0, i);
                analyzeWord(word);
                cout << "= is an equals operator.\n";
                break;
            case '>':
                word = input.substr(0, i);
                analyzeWord(word);
                cout << "> is a greater than operator\n";
                break;
            case '[':
                word = input.substr(0, i);
                analyzeWord(word);
                cout << "[ is an opening array operator\n";
                break;
            case ']':
                word = input.substr(0, i);
                analyzeWord(word);
                cout << "] is a closing array operator\n";
                break;
            // End of File
            case '$':
                word = input.substr(0, i);
                analyzeWord(word);
                cout << "$ is the end of file\n";
                break;
            // Non-special Character
            default:
                splitInput = false;
                break;
        }
        //cout << "index at " << i << "\n";
        
        if ((i + 1) < input.length() && splitInput) {
            //cout << "index at " << i << " input.length() " << input.length() << "\n";
            //cout << "input: " << input << " word: " << word << "\n";
            input = input.substr(i + 1);
            i = -1;
        } else if (splitInput) {
            input = "";
            //return;   
        } else if ((i + 1) >= input.length()) {
            word = input;
            input = "";
            //cout << "index at " << i << " input.length() " << input.length() << "\n";
            //cout << "input: " << input << " word: " << word << "\n";
            analyzeWord(word);
        }
            
        //cout << "index at " << i << "\n";
        
    }
    return;
}

void analyzeWord(string word) {
    if (word.length() == 0)
        return;
    
    bool isNumber = true;
    bool isAlphaNum = true;
    
    for (int i = 0; i < word.length(); i++) {
        if (!isNumber || !isdigit(word.at(i))) {
            isNumber = false;
        }
        if (!isalnum(word.at(i))) {
            isAlphaNum = false;
            break;
        }
    }
    
    //TODO: Axe regex, check by char
    
    /*
    string int_num = "^[0-9][0-9]*$";
    regex number(int_num, regex_constants::ECMAScript);
    regex alphanumeric("[a-zA-Z]{1}[a-zA-Z0-9]{0,}", regex_constants::basic);
    smatch m;
    
    regexIsNumber = regex_match(word, m, number);
    
    //cout << m[0] << m[0].matched << endl;
    
    regexIsAlphaNum = regex_match(word, m, alphanumeric);
    
    cout << "is \"" << word << "\" a number? " << regexIsNumber << endl;
    */
    
    if (word.length() > 0) {
        if(word.compare("int") == 0){
            cout << "int is a valid keyword.\n";
        } else
        if(word.compare("if") == 0){
            cout << "if is a valid keyword.\n";
        } else
        if(word.compare("then") == 0){
            cout << "then is a valid keyword.\n";
        } else
        if(word.compare("else") == 0){
            cout << "else is a valid keyword.\n";
        } else
        if(word.compare("endif") == 0){
            cout << "endif is a valid keyword.\n";
        } else if (isdigit(word.at(0)) && isNumber) {
            cout << word << " is a constant\n";
        } else if (!isdigit(word.at(0)) && isAlphaNum) {
            
            cout << word << " is an identifier\n";
        } else {
            cout << word << " is an invalid identifier\n";
        }
    }
    //cout << "Test";
    return;
}
void commentReader(ifstream &inFile, string &input) {
	int locator = -2;
	string comment;
	bool found = false;
	string inputAdj = input;
	while (inputAdj.length() != 0 && locator != -1) {
		locator = inputAdj.find('*');
		if (inputAdj.at(locator+1) == '/' && locator != -1 && found == false) {
			comment = inputAdj.substr(0, locator);
			cout << "Comment: " << comment << "\n";
			found = true;
			break;
		}
		inputAdj = inputAdj.substr(locator+1);
	}
	comment.append(input);
	locator = -2;
	while (getline(inFile, input) && found == false) {
		inputAdj = input;
		if (inputAdj.length() != 0) {
			locator = inputAdj.find('*');
			if (inputAdj.at(locator + 1) == '/' && locator != -1 && found == false) {
				comment.append(inputAdj.substr(0, locator + 2));
				cout << "Comment: " << comment << "\n";
				found = true;
				break;
			}
			inputAdj = inputAdj.substr(locator + 1);
			comment.append(inputAdj.substr(0, locator + 2));
		}
	}
}