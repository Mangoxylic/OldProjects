#include <iostream>
#include "parsemd.h"
#include <fstream>
#include <map>
#include "myset.h"
#include <vector>
#include <set>
#include <stack>

using namespace std;

void add_parse_from_index_file(std::string index_file, vector<string>& links, ParseMD* parser);
void add_parse_page(std::string filename, vector<string>& links, 
					vector<string>& unvisited, vector<string>& visited, vector<string>& finished, ParseMD* parser);


bool alreadyExists(vector<string>& links, string link);
void removeElem(vector<string>& links, string link);
bool valid(string s);

int main(int argc, char* argv[]) {

/*
*** Getting the file to use as input ***
*/

  map<string, string> parameters;
  ifstream paramFile(argv[1]);

  string paramName = "";
  string param = "";
  string line;

  while (getline(paramFile, line)) {
    bool foundEquals = false;
    bool hashtag = false;

    for (unsigned int i = 0; i < line.length(); i++) {
      if (line[i] == '#') hashtag = true;
      else if (line[i] == '=') foundEquals = true;

      if (!hashtag && !foundEquals && line[i] != ' ') {
        paramName += line[i];
      } else if (!hashtag && foundEquals && line[i] != ' ' && line[i] != '=') {
        param += line[i];
      }

      if (i == line.length() - 1) {
        parameters.insert(make_pair(paramName, param));
      }

    } // End of for
    paramName = "";
    param = "";
  } // End of while

  /*
  map<string, string>::iterator it;
  for (it = parameters.begin(); it != parameters.end(); ++it) {
    cout << (*it).second << endl;
  }
  */

  string index_name = "";
  if (parameters.find("INDEX_FILE") != parameters.end())
  	index_name = (parameters.find("INDEX_FILE"))->second;

  //cout << index_name << endl;

  ParseMD* parser = new ParseMD;
  vector<string> result;
  add_parse_from_index_file(index_name, result, parser);

  string output_file = "";
  if (parameters.find("OUTPUT_FILE") != parameters.end())
  	output_file = (parameters.find("OUTPUT_FILE"))->second;

  ofstream output(output_file.c_str());

  for (unsigned int i = 0; i < result.size(); i++) {
  	output << result[i] << endl;
  }
}






void add_parse_from_index_file(std::string index_file, vector<string>& links, ParseMD* parser) {
	ifstream index(index_file.c_str());
	string directory;

	vector<string> unvisited;
	vector<string> visited;
	vector<string> finished;

	while (getline(index, directory)) {
		unvisited.push_back(directory);
	}


	index.close();
	index.open(index_file.c_str());

	while (getline(index, directory)) {
		if (alreadyExists(unvisited, directory))
			add_parse_page(directory, links, unvisited, visited, finished, parser);
	}


	return;
}

void add_parse_page(std::string filename, vector<string>& links, vector<string>& unvisited, 
					vector<string>& visited, vector<string>& finished, ParseMD* parser) {

	if (unvisited.size() == 0 && visited.size() == 0) return;

	removeElem(unvisited, filename);
	visited.push_back(filename);

	if (!alreadyExists(links, filename) && valid(filename))
		links.push_back(filename);

	vector<string> tempLinks;

	parser->linksParse(filename, tempLinks);

	/*
	cout << "File: " << filename << endl;
	cout << "# Links: " << tempLinks.size() << endl << endl;
	*/

	for (unsigned int i = 0; i < tempLinks.size(); i++) {
		if (alreadyExists(unvisited, tempLinks[i]))
			/*
			cout << "Current File:" << filename << endl;
			cout << "Going into: " << tempLinks[i] << endl << endl;
			*/

			add_parse_page(tempLinks[i], links, unvisited, visited, finished, parser);
	}

	finished.push_back(filename);

	removeElem(unvisited, filename);
	removeElem(visited, filename);

	
	if (!alreadyExists(links, filename) && valid(filename))
		links.push_back(filename);
	

}



bool alreadyExists(vector<string>& links, string link) {
	for (unsigned int i = 0; i < links.size(); i++) {
		if (links[i] == link) return true;
	}
	return false;
}

void removeElem(vector<string>& links, string link) {
	for (unsigned int i = 0; i < links.size(); i++) {
		if (links[i] == link) {
			links.erase(links.begin() + i);
			break;
		}
	}
}

bool valid(string s) {
	ifstream input(s.c_str());
	string test;
	input >> test;

	if (input.fail()) return false;
	else return true;
}