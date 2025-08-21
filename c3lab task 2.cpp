#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <unordered_set>
using namespace std;


unordered_set<char> delimiters = {
    ' ', ';', ',', '(', ')', '{', '}', '[', ']', ':'
};

void classifyToken(const string& token) {
    if (token.empty()) return;


    bool isNumber = true;
    bool hasDot = false;

    for (char c : token) {
        if (isdigit(c)) continue;
        else if (c == '.' && !hasDot) {
            hasDot = true;
        } else {
            isNumber = false;
            break;
        }
    }

    if (isNumber) {
        if (hasDot) {
            cout << "[Real Number]   : " << token << endl;
        } else {
            cout << "[Integer]       : " << token << endl;
        }
    }
}

void tokenizeLine(const string& line) {
    string token;
    for (size_t i = 0; i < line.length(); i++) {
        char ch = line[i];


        if (delimiters.find(ch) != delimiters.end()) {
            if (!token.empty()) {
                classifyToken(token);
                token.clear();
            }
            if (!isspace(ch)) {
                cout << "[Delimiter]    : " << ch << endl;
            }
        }
        else {
            token += ch;
        }
    }

    if (!token.empty()) {
        classifyToken(token);
    }
}

int main() {
    ifstream file("compilerlab3.txt");
    if (!file) {
        cout << "Error opening file." << endl;
        return 1;
    }

    cout << "Detecting Delimiters, Integers and Real Numbers...\n\n";

    string line;
    while (getline(file, line)) {
        tokenizeLine(line);
    }

    file.close();
    return 0;
}
