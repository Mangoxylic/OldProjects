#include "parsemd.h"
#include <fstream>
#include <iostream>

using namespace std;

string filterString(string s);
bool isLetter(char c);
string trimBrackets(string s);
string trimParenths(string s);
// Checks if a link already exists in the vector
bool exists(vector<string>& links, string link);


void ParseMD::parse(string filename, MySet<string>& allWords, MySet<string>& allLinks) {
	// Convert filename to a C string when reading in
	ifstream file(filename.c_str());
	string line = "";

	while (getline(file, line)) {
		string builder = "";
		bool inParenth = false;
		bool inBracket = false;
		bool link = false;

		for (unsigned int i = 0; i < line.length(); i++) {
			// Add to builder string only if a given character is a letter
			if (isLetter(tolower(line[i]))) builder += line[i];
			else if (link == true) builder += line[i];
			// Case for opening bracket
			if (line[i] == '[') {
				inBracket = true;
			// Found opening parenthesis and not currently in one yet
			} else if (line[i] == '(' && !inParenth) {
				inParenth = true;
			// Parentheses case but not a link
			} else if (inParenth && link == false && !isLetter(tolower(line[i]))) {
				allWords.insert(builder);
				builder = "";
				inParenth = false;
			// Case for if we reach a closing bracket
			} else if (line[i] == ']' && inBracket == true) {
				// If we are looking at a link
				if (line[i + 1] == '(') link = true;
				// Parse whatever is in the brackets
				string newBuilder = "";
				for (unsigned int j = 0; j < builder.length(); j++) {
					// If a character is a letter, add to new string builder
					if (isLetter(tolower(builder[j]))) newBuilder += builder[j];
					// a character is not a letter and new string builder is not empty
					if ((!isLetter(tolower(builder[j])) || j == builder.length()-1) && newBuilder.length() > 0) {
						// Add word to allWords and reset newBuilder
						allWords.insert(newBuilder);
						newBuilder = "";
					} 
				}
				builder = "";
				inBracket = false;
			// If we are dealing with a link and reached end of it
			} else if (link == true && line[i] == ')') {
				link = false;
				inParenth = false;
				builder = trimParenths(builder);
				allLinks.insert(builder);
				builder = "";
			} else if ((!isLetter(tolower(line[i])) || i == line.length()-1) && builder.length() > 0 && !link) {
				allWords.insert(builder);
				builder = "";
			}
		}
	}
}

// Copy of the parse function except we are pushing into a vector.
// I also just comment out whenever we added "words" for simplicity. Probably bad runtime.
// Will probably think of a way to avoid this, but for now this will do.

void ParseMD::linksParse(string filename, vector<string>& links) {
// Convert filename to a C string when reading in
	//cout << "Doing linksParse" << endl;
	ifstream file(filename.c_str());
	string line = "";

	if (file.fail()) return;

	while (getline(file, line)) {
		string builder = "";
		bool inParenth = false;
		bool inBracket = false;
		bool link = false;

		for (unsigned int i = 0; i < line.length(); i++) {
			// Add to builder string only if a given character is a letter
			if (isLetter(tolower(line[i]))) builder += line[i];
			else if (link == true) builder += line[i];
			// Case for opening bracket
			if (line[i] == '[') {
				inBracket = true;
			// Found opening parenthesis and not currently in one yet
			} else if (line[i] == '(' && !inParenth) {
				inParenth = true;
			// Parentheses case but not a link
			} else if (inParenth && link == false && !isLetter(tolower(line[i]))) {
				//allWords.insert(builder);
				builder = "";
				inParenth = false;
			// Case for if we reach a closing bracket
			} else if (line[i] == ']' && inBracket == true) {
				// If we are looking at a link
				if (line[i + 1] == '(') link = true;
				// Parse whatever is in the brackets
				string newBuilder = "";
				for (unsigned int j = 0; j < builder.length(); j++) {
					// If a character is a letter, add to new string builder
					if (isLetter(tolower(builder[j]))) newBuilder += builder[j];
					// a character is not a letter and new string builder is not empty
					if ((!isLetter(tolower(builder[j])) || j == builder.length()-1) && newBuilder.length() > 0) {
						// Add word to allWords and reset newBuilder
						//allWords.insert(newBuilder);
						newBuilder = "";
					} 
				}
				builder = "";
				inBracket = false;
			// If we are dealing with a link and reached end of it
			} else if (link == true && line[i] == ')') {
				link = false;
				inParenth = false;
				builder = trimParenths(builder);
				if (!exists(links, builder)) links.push_back(builder);
				builder = "";
			} else if ((!isLetter(tolower(line[i])) || i == line.length()-1) && builder.length() > 0 && !link) {
				//allWords.insert(builder);
				builder = "";
			}
		}
	}

}


// Removes any symbols from a string
string filterString(string s) {
	std::string result = "";
	for (unsigned int i = 0; i < s.length(); i++) {
		if (isLetter(s[i])) result += s[i];
	}
	return result;
}

// Checks to see if a given character is a valid letter/number
bool isLetter(char c) {
	std::string letters = "abcdefghijklmnopqrstuvwxyz0123456789";
	for (unsigned int i = 0; i < letters.length(); i++) {
		if (c == letters[i]) return true;
	}
	return false;
}

// Function to get only characters in between []
string trimBrackets(string s) {
	string result = "";
	for (unsigned int i = 0; i < s.length(); i++) {
		if (s[i] != '[' && s[i] != ']') result += s[i];
	}
	return result;
}

// Function to get only characters in between ()
string trimParenths(string s) {
	string result = "";
	/*for (unsigned int i = 0; i < s.length(); i++) {
		if (s[i] != '(' && s[i] != ')') result += s[i];
	}*/
	for (unsigned int i = 1; i < s.length() - 1; i++) {
		result += s[i];
	}
	return result;
}

bool exists(vector<string>& links, string link) {
	for (unsigned int i = 0; i < links.size(); i++) {
		if (links[i] == link) return true;
	}
	return false;
}
