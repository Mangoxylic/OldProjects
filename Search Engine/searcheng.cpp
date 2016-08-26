#include <iostream>
#include "searcheng.h"
#include <fstream>
#include <map>

using namespace std;

string makelower(string s);
string andor(string s);

SearchEng::SearchEng() {
  wpIndex = 0;
}

SearchEng::~SearchEng() {}

void SearchEng::add_parse_from_index_file(std::string index_file, PageParser* parser) {
	ifstream index(index_file.c_str());
	string directory;

  while (getline(index, directory)) {
    WebPage* webpage = new WebPage(directory);
    webpages.push_back(webpage);
  }

  index.close();
  index.open(index_file.c_str());

	while (getline(index, directory)) {
		//cout << filename << endl;
		add_parse_page(directory, parser);
    wpIndex++;
	}
  wpIndex = 0;
}

void SearchEng::add_parse_page(std::string filename, PageParser* parser) {

	MySet<string> links; // All of the outgoing links on the page
	MySet<string> words; // All of the words on the page
	parser->parse(filename, words, links);


	// Update list of WebPages per word

	webpages[wpIndex]->all_words(words); // Add the parsed words into webpage
	MySet<string> webWords = webpages[wpIndex]->all_words(); // MySet that holds all of the parsed words
	MySet<string>::iterator tor; // Iterates throuhg a MySet
	map<string, MySet<WebPage*> >::iterator it;

  // Do outgoing links for current webpage (webpages[wpIndex])
  for (tor = links.begin(); tor != links.end(); ++tor) {
    for (unsigned int i = 0; i < webpages.size(); i++) {
      if (*tor == webpages[i]->filename()) {
        webpages[wpIndex]->add_outgoing_link(webpages[i]);
        webpages[i]->add_incoming_link(webpages[wpIndex]);
      }
    }
  }


	for (tor = webWords.begin(); tor != webWords.end(); ++tor) {
		// if the word exists, add this webpage
		if (mymap.find(makelower(*tor)) != mymap.end()) {
			//cout << "CHECK 2" << endl;
			(mymap.find(makelower(*tor)))->second.insert(webpages[wpIndex]);
		} else {
		// add the word and the corresponding webpage
			//cout << "CHECK 3" << endl;
			MySet<WebPage*> mypages;
			mypages.insert(webpages[wpIndex]);
			mymap[makelower(*tor)] = mypages;
		}
	}

}


bool SearchEng::query(MySet<WebPage*> & pages, string type, string myline) {

  if (makelower(type) == "or") {
      // Stores all of the words from the query
      vector<string> words;
      string builder = "";
      // Adding all of the words
      for (unsigned int i = 0; i < myline.length(); i++) {
        if ((myline[i] == ' ' || i == myline.length()-1) && builder != "") {
          if (i == myline.length()-1 && myline[i] != ' ') builder += myline[i];
          words.push_back(makelower(builder));
          builder = "";
        } else {
          if (myline[i] != ' ') builder += myline[i];
          if (builder.length() > 0 && i == myline.length()-1) words.push_back(makelower(builder));
        }
        //cout << builder << endl;
        //cout << builder.length() << endl;
      }
      //cout << words.size() << endl;
      // Going through the map to look for webpages

      for (unsigned int i = 0; i < words.size(); i++) {
        pages = pages.set_union(this->search(words[i]));
        //cout << words[i];
      }
      //cout << endl;

      return true;

    } else if (makelower(type) == "and") {
      vector<string> words;
      string builder = "";

      for (unsigned int i = 0; i < myline.length(); i++) {
        if ((myline[i] == ' ' || i == myline.length()-1) && builder != "") {
          if (i == myline.length()-1 && myline[i] != ' ') builder += myline[i];
          words.push_back(makelower(builder));
          builder = "";
        } else {
          if (myline[i] != ' ') builder += myline[i];
          if (builder.length() > 0 && i == myline.length()-1) words.push_back(makelower(builder));
        }
        //cout << builder << endl;
        //cout << builder.length() << endl;
      }

      for (unsigned int i = 0; i < words.size(); i++) {
        pages = pages.set_intersection(this->search(words[i]));
        //cout << words[i] << " ";
      }
      //cout << endl;

      return true;

    } else {
      vector<string> words;
      string builder = "";

      for (unsigned int i = 0; i < myline.length(); i++) {
        if ((myline[i] == ' ' || i == myline.length()-1) && builder != "") {
          if (i == myline.length()-1 && myline[i] != ' ') builder += myline[i];
          words.push_back(makelower(builder));
          builder = "";
        } else {
          if (myline[i] != ' ') builder += myline[i];
          if (builder.length() > 0 && i == myline.length()-1) words.push_back(makelower(builder));
        }
        //cout << builder << endl;
        //cout << builder.length() << endl;
      }
      //cout << words.size() << endl;

      if (words.size() == 1) {
        pages = this->search(words[0]);
        return true;
      } else {
        return false;
      }

    }
}



MySet<WebPage*> SearchEng::search(string s) {
	typename map<string, MySet<WebPage*> >::iterator it = mymap.find(s);
	if (it != mymap.end()) {
		return (it->second);
	}
	MySet<WebPage*> webpage;
	return webpage;

}

void SearchEng::printWords() {
	map<string, MySet<WebPage*> >::iterator it;
	for (it = mymap.begin(); it != mymap.end(); ++it) {
		cout << it->first << " ";
	}
	cout << endl;
}

WebPage* SearchEng::getPage(string name) {
  MySet<WebPage*>::iterator it;
  for (it = mySetPage.begin(); it != mySetPage.end(); ++it) {
    if ((*it)->filename() == name) return *it;
  }

  WebPage* tempPage = new WebPage(name);
  mySetPage.insert(tempPage);
  return tempPage;
}

string makelower(string s) {
  string result = "";
  for (unsigned int i = 0; i < s.length(); i++) {
    result += tolower(s[i]);
  }
  return result;
}

string andor(string s) {
  string builder = "";
  for (unsigned int i = 0; i < 3; i++) {;
    builder += s[i];
    if (i == 1 && makelower(builder) == "or") return builder;
  }
  if (makelower(builder) == "and") return builder;
  else return "";
}