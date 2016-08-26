#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <QApplication>
#include <map>
#include <fstream>

#include "main_window.h"
#include "webpage.h"
#include "searcheng.h"
#include "parsemd.h"

using namespace std;

//void display_results(set<WebPage*>& results);
//void printSet(MySet<string> words);

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "usage: ./search index_file...Please provide an index file" << endl;
    return 1;
  }

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

  // Reading in needed data for page rank
  string index_name = "";
  if (parameters.find("INDEX_FILE") != parameters.end())
    index_name = (parameters.find("INDEX_FILE"))->second;

  int epsilon = 0;
  if (parameters.find("STEP_NUMBER") != parameters.end())
    epsilon = stoi((parameters.find("STEP_NUMBER"))->second);

  double probability = 0;
  if (parameters.find("RESTART_PROBABILITY") != parameters.end())
    probability = stod((parameters.find("RESTART_PROBABILITY"))->second);

  /*
  cout << "epsilon: " << epsilon << endl;
  cout << "probability: " << probability << endl;
  */

  //cout << index_name << endl;

  SearchEng searchengine;
  ParseMD parser;
  searchengine.add_parse_from_index_file(index_name, &parser);

  QApplication app(argc, argv);

  MainWindow mainWindow(searchengine, epsilon, probability);

  mainWindow.show();

  return app.exec();
}

/*
void display_results(set<WebPage*>& results)
{
  int hits = results.size();
  cout << hits << " hits." << endl;
  cout << "=====" << endl;
  int i=0;
  for(set<WebPage*>::iterator it = results.begin();
      it != results.end();
      ++it)
    {
      cout << (*it)->filename() << endl;
      cout << "+---+" << endl;
      cout << (**it) << "\n" << endl;
      i++;
    }
}

void printSet(MySetString words) {
  MySetString::iterator it;
  for (it = words.begin(); it != words.end(); ++it) {
    cout << *it;
  }
  cout << endl;
}
*/