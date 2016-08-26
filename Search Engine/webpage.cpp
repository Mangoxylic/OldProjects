#include "webpage.h"
#include <fstream>
#include <iostream>

using namespace std;

  WebPage::WebPage() {
  }

  WebPage::WebPage(std::string filename) {
  	file = filename;
  }

  WebPage::~WebPage() {}

  /**
   * Sets the filename/URL of this webpage
   */
  void WebPage::filename(std::string fname) {
  	file = fname;
  }

  /**
   * Returns the filename/URL of this webpage
   */
  std::string WebPage::filename() const {
  	return file;
  }

  /**
   * Updates the set containing all unique words in the text
   *  with the contents of the input parameter words
   */
  void WebPage::all_words(const MySet<std::string>& words) {
  	mysetstrings = mysetstrings.set_union(words);
  }

  /**
   * Returns all the unique, tokenized words in this webpage 
   */
  MySet<string> WebPage::all_words() const {
  	return mysetstrings;
  }

  /**
   * Adds a webpage that links to this page
   */
  void WebPage::add_incoming_link(WebPage* wp) {
  	incoming.insert(wp);
  }

  /**
   * Returns all webpages that link to this page
   */
  MySet<WebPage*> WebPage::incoming_links() const {
  	MySet<WebPage*> webpages;
    std::set<WebPage*>::iterator it;
  	for (it = incoming.begin(); it != incoming.end(); ++it) {
  		webpages.insert(*it);
  	}
  	return webpages;
  }

  /**
   * Adds a webpage that this page links to
   */
  void WebPage::add_outgoing_link(WebPage* wp) {
  	outgoing.insert(wp);
  }

  /**
   * Returns all webpages this page links to
   */
  MySet<WebPage*> WebPage::outgoing_links() const {
  	MySet<WebPage*> webpages;
    std::set<WebPage*>::iterator it;
  	for (it = outgoing.begin(); it != outgoing.end(); ++it) {
  		webpages.insert(*it);
  	}
  	return webpages;
  }

  /**
   * Displays the webpage text to the screen 
   */
  std::ostream & operator<< (std::ostream & os, const WebPage & page) {

  	//cout << "CHECK" << endl;
  	std::string filename = page.filename();
  	ifstream openfile(filename.c_str());
  	std::string line = "";

  	while (getline(openfile, line)) {
  		bool link = false;
  		for (unsigned int i = 0; i < line.length(); i++) {
  			if (line[i] == '(' && line[i - 1] == ']') {
  				link = true;
  			} else if (link == true && line[i] == ')') {
  				link = false;
  			} else if (link == false) {
  				os << line[i];
  			}
  		}
  		os << std::endl;
  	}
  	return os;
  }