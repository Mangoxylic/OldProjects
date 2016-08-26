#ifndef SEARCHENG_H
#define SEARCHENG_H

#include <map>
#include <vector>
#include <string>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"

class SearchEng {
 public:
  SearchEng();
  ~SearchEng();
  void add_parse_from_index_file(std::string index_file, 
				 PageParser* parser);
  void add_parse_page(std::string filename, 
		      PageParser* parser);
  /**** Add other desired member functions here *****/
  bool query(MySet<WebPage*> & pages, std::string s, std::string s2);
  MySet<WebPage*> search(std::string s);
  void printWords();
  WebPage* getPage(std::string name);


 private:
 	// Contains every word and every webpage that it is in (pointer)
 	std::map<std::string, MySet<WebPage*> > mymap;
  MySet<WebPage*> mySetPage;
  std::vector<WebPage*> webpages;
  int wpIndex;



};

#endif
