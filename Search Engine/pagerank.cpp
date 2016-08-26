#include <iostream>
#include <vector>
#include "webpage.h"
#include "myset.h"
#include "msort.h"
#include <map>
#include "pagerank.h"

using namespace std;

sortHelper::sortHelper(Node* funcNode, double number) {
	sortName = funcNode->getName();
	sortNumber = number;
}

string sortHelper::getName() {
	return sortName;
}

double sortHelper::getNumber() {
	return sortNumber;
}


Node::Node(WebPage* page) {
	outgoing = page->outgoing_links();
	incoming = page->incoming_links();
	outgoing.insert(page);
	incoming.insert(page);
	wpName = page->filename();
}

string Node::getName() {
	return wpName;
}

MySet<WebPage*> Node::getOutgoing() {
	return outgoing;
}

MySet<WebPage*> Node::getIncoming() {
	return incoming;
}





struct sortCompare {
	bool operator()(sortHelper* helper1, sortHelper* helper2) {
		return helper1->getNumber() >= helper2->getNumber();
	}
};

vector<WebPage*> pagerank(MySet<WebPage*>& pages, int n, double probability) {
	MySet<Node*> nodes;
	//map<WebPage*, double> oldScores;
	//map<WebPage*, double> newScores;
	map<Node*, double> oldNodes;
	map<Node*, double> newNodes;
	vector<WebPage*> result;


	// iterators
	typename MySet<WebPage*>::iterator it;
	map<WebPage*, double>::iterator mapit;
	MySet<Node*>::iterator nodeit;

	for (it = pages.begin(); it != pages.end(); ++it) {
		Node* node = new Node(*it); // Adds all incoming/outgoing in constructor
		nodes.insert(node);
		//cout << node->getName() << endl;
	}

	

	map<Node*, double>::iterator mapnode;

	// Node version
	for (nodeit = nodes.begin(); nodeit != nodes.end(); ++nodeit) {
		oldNodes.insert(make_pair(*nodeit, 1 / (double)nodes.size()));
		newNodes.insert(make_pair(*nodeit, 1 / (double)nodes.size()));
		//cout << "Node size: " << nodes.size() << endl;
	}

	/*
	for (mapnode = newNodes.begin(); mapnode != newNodes.end(); ++mapnode) {
		cout << (mapnode->first)->getName() << " " << mapnode->second << endl;
	}
	*/

	// Implement PageRank algorithm (NODE VERSION!)


	for (int i = 0; i < n; i++) {
		for (nodeit = nodes.begin(); nodeit != nodes.end(); ++nodeit) {
			double sum = 0;
			MySet<WebPage*> incoming = (*nodeit)->getIncoming();

			typename MySet<WebPage*>::iterator it2;
			for (it2 = incoming.begin(); it2 != incoming.end(); ++it2) {
				string name = (*it2)->filename();
				double currScore;
				double numOut;

				for (mapnode = oldNodes.begin(); mapnode != oldNodes.end(); ++mapnode) {
					if ((mapnode->first)->getName() == name) {
						currScore = mapnode->second;
						numOut = ((mapnode->first)->getOutgoing()).size();
						break;
					}
				}

				//cout << "currScore: " << currScore << endl;
				//cout << "currScore: " << currScore << ", numOut: " << numOut << endl;
				sum += currScore * (1 / numOut);
				
				//cout << "currScore: " << currScore << endl;
				//cout << "numOut: " << numOut << endl;
				
			}
			newNodes[*nodeit] = (probability / (double)nodes.size()) + (1 - probability) * sum;
			//cout << newNodes[*nodeit] << endl;

		}

		oldNodes = newNodes;
	}



	vector<sortHelper*> sortVec;
	for (mapnode = newNodes.begin(); mapnode != newNodes.end(); ++mapnode) {
		sortHelper* sortme = new sortHelper(mapnode->first, mapnode->second);
		sortVec.push_back(sortme);
		//cout << (mapnode->first)->getName() << " " << mapnode->second << endl;
	}
	//cout << endl;
	sortCompare compare;
	mergeSort(sortVec, compare);

	for (unsigned int i = 0 ; i < sortVec.size(); i++) {
		for (it = pages.begin(); it != pages.end(); ++it) {
			if (sortVec[i]->getName() == (*it)->filename()) {
				result.push_back(*it);
			}
		}
	}

	

	for (unsigned int i = 0; i < result.size(); i++) {
		//cout << result[i]->filename() << endl;
	}
	


return result;

}

