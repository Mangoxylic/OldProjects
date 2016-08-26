#ifndef PAGERANK_H
#define PAGERANK_H

#include <iostream>
#include <vector>
#include "webpage.h"
#include "myset.h"
#include "msort.h"
#include <map>


class Node {
public:
	Node(WebPage* page);
	//double getEpsilon();
	std::string getName();
	MySet<WebPage*> getOutgoing();
	MySet<WebPage*> getIncoming();

private:
	//double epsilon;
	std::string wpName;
	MySet<WebPage*> outgoing;
	MySet<WebPage*> incoming;


};

class sortHelper {
public:
	sortHelper(Node* funcNode, double number);
	std::string getName();
	double getNumber();


private:
	std::string sortName;
	double sortNumber;


};

std::vector<WebPage*> pagerank(MySet<WebPage*>& pages, int n, double probability);

#endif