#include "main_window.h"
//#include <iostream>
#include <sstream>
#include "pagerank.h"

using namespace std;

struct strCompare {
	bool operator()(WebPage* webpage1, WebPage* webpage2) {
		return webpage1->filename() < webpage2->filename();
	}
};

struct outCompare {
	bool operator()(WebPage* webpage1, WebPage* webpage2) {
		MySet<WebPage*> pages1 = webpage1->outgoing_links();
		MySet<WebPage*> pages2 = webpage2->outgoing_links();
		int numPages1 = pages1.size();
		int numPages2 = pages2.size();
		return numPages1 <= numPages2;
	}
};

struct incCompare {
	bool operator()(WebPage* webpage1, WebPage* webpage2) {
		MySet<WebPage*> pages1 = webpage1->incoming_links();
		MySet<WebPage*> pages2 = webpage2->incoming_links();
		int numPages1 = pages1.size();
		int numPages2 = pages2.size();
		return numPages1 <= numPages2;
	}
};


MainWindow::MainWindow(SearchEng searcheng, int n, double probability) {

	searchengine = searcheng;
	// These two variables read in from input file (private vars)
	numSteps = n;
	prob = probability;

	// Title
	setWindowTitle("Search Engine");

	// Overall Layout
	overallLayout = new QHBoxLayout();


	// WebPage Display Layout
	webpageDisplayLayout = new QVBoxLayout();
	overallLayout->addLayout(webpageDisplayLayout);


	// WebPage name
	webpageNameDisplay = new QLabel();
	webpageDisplayLayout->addWidget(webpageNameDisplay);

	// List of webpages
	webpageListWidget = new QListWidget();
	overallLayout->addWidget(webpageListWidget);


	// Form Layout
	formLayout = new QVBoxLayout();
	overallLayout->addLayout(formLayout);

	/*
	*** Add Search Options as Radio Buttons *** 
	*/
	searchGroup = new QGroupBox("Search Options");
	searchLayout = new QHBoxLayout();
	formLayout->addWidget(searchGroup);

	radioSingle = new QRadioButton("Single");
	radioAND = new QRadioButton("AND");
	radioOR = new QRadioButton("OR");

	radioSingle->setChecked(true);

	connect(radioSingle,SIGNAL(clicked(bool)),this,SLOT(clickSingle()));
	connect(radioAND,SIGNAL(clicked(bool)),this,SLOT(clickAND()));
	connect(radioOR,SIGNAL(clicked(bool)),this,SLOT(clickOR()));

	searchLayout->addWidget(radioSingle);
	searchLayout->addWidget(radioAND);
	searchLayout->addWidget(radioOR);

	searchGroup->setLayout(searchLayout);

	/*
	*** Add Sorting Options as Radio Buttons ***
	*/
	sortGroup = new QGroupBox("Sort Options");
	sortLayout = new QHBoxLayout();
	formLayout->addWidget(sortGroup);

	rank = new QRadioButton("PageRank");
	filename = new QRadioButton("Filename");
	outgoing = new QRadioButton("# Outgoing");
	incoming = new QRadioButton("# Incoming");

	rank->setChecked(true);

	connect(rank,SIGNAL(clicked(bool)),this,SLOT(clickRank()));
	connect(filename,SIGNAL(clicked(bool)),this,SLOT(clickFilename()));
	connect(outgoing,SIGNAL(clicked(bool)),this,SLOT(clickOutgoing()));
	connect(incoming,SIGNAL(clicked(bool)),this,SLOT(clickIncoming()));

	sortLayout->addWidget(rank);
	sortLayout->addWidget(filename);
	sortLayout->addWidget(outgoing);
	sortLayout->addWidget(incoming);

	sortGroup->setLayout(sortLayout);


	// Search Label
	searchLabel = new QLabel("Enter words to search:");
	formLayout->addWidget(searchLabel);


	// Search Input. If user hits enter, will initiate function of the search button
	searchInput = new QLineEdit();
	formLayout->addWidget(searchInput);
	connect(searchInput, SIGNAL(returnPressed()), this, SLOT(search()));

	// Add Search Button
	addButton = new QPushButton("Search");
	connect(addButton, SIGNAL(clicked()), this, SLOT(search()));
	formLayout->addWidget(addButton);

	// Add Quit Button to main window
	quitButton = new QPushButton("Quit");
	connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
	formLayout->addWidget(quitButton);



	/*
	*** Setting up a new window ***
	*/

	// Webapge contents
	windowLayout = new QHBoxLayout; // Layout that contains two different layouts
	otherLayout = new QVBoxLayout;
	outgoingLayout = new QVBoxLayout;
	incomingLayout = new QVBoxLayout;



	// Updating windowlayout (layout of the new window)
	windowLayout->addLayout(otherLayout);
	windowLayout->addLayout(outgoingLayout);
	windowLayout->addLayout(incomingLayout);

	pageLabel = new QLabel("Contents:");
	pageContents = new QTextEdit();
	otherLayout->addWidget(pageLabel);
	otherLayout->addWidget(pageContents);

	// Outgoing links list
	outgoingList = new QListWidget();
	outgoingLabel = new QLabel("Outgoing:");
	outgoingLayout->addWidget(outgoingLabel);
	outgoingLayout->addWidget(outgoingList);


	// Incoming links list
	incomingList = new QListWidget();
	incomingLabel = new QLabel("Incoming:");
	incomingLayout->addWidget(incomingLabel);
	incomingLayout->addWidget(incomingList);



	// Constructing close button
	otherButton = new QPushButton("Close");
	otherWin = new QWidget;
	otherLayout->addWidget(otherButton);

	// Setting layout of new window
	otherWin->setLayout(windowLayout);

	// If Close is pressed, hide
	connect(otherButton, SIGNAL(clicked()), this, SLOT(hideWindow()));
	// When a webpage is clicked on, show its contents
	connect(webpageListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(showWindow(int)), Qt::UniqueConnection);

	// Set Overall Layout
	setLayout(overallLayout);
}

MainWindow::~MainWindow() {
	delete radioSingle;
	delete radioAND;
	delete radioOR;
	delete searchLayout;
	delete searchGroup;

	delete rank;
	delete filename;
	delete outgoing;
	delete incoming;
	delete sortLayout;
	delete sortGroup;

	delete searchLabel;
	delete searchInput;
	delete addButton;
	delete quitButton;

	delete pageLabel;
	delete pageContents;

	delete outgoingList;
	delete outgoingLabel;
	delete outgoingLayout;

	delete incomingList;
	delete incomingLabel;
	delete incomingLayout;

	delete otherLayout;
	delete windowLayout;
	delete otherButton;


	delete webpageListWidget;
	delete webpageNameDisplay;
	delete webpageDisplayLayout;
	delete formLayout;
	delete otherWin;
	delete overallLayout;

}

void MainWindow::updateWindow(WebPage* wp) {
	// Handling title of window and clearing its contents
	// cout << wp->filename() << endl; // Function used to test my connections
	pageContents->clear();
	incomingList->clear();
	outgoingList->clear();
	outgoingVec.clear();
	incomingVec.clear();

	QString contents;
	QString title;
	title = QString::fromStdString(wp->filename());
	otherWin->setWindowTitle(title);

	stringstream ss;
	ss << *wp;
	contents = QString::fromStdString(ss.str());
	pageContents->append(contents);

	// Updating the outgoing and incoming lists


	// These contain WebPage*
	MySet<WebPage*> allOutgoing = wp->outgoing_links();
	MySet<WebPage*> allIncoming = wp->incoming_links();
	typename MySet<WebPage*>::iterator it; // Iterator for MySetWebPage


	for (it = allOutgoing.begin(); it != allOutgoing.end(); ++it) {
		outgoingVec.push_back(*it);
	}

	for (it = allIncoming.begin(); it != allIncoming.end(); ++it) {
		incomingVec.push_back(*it);
	}

	// Sort based on which radio button was checked in first/main window
	if (outgoing->isChecked()) {
		outCompare compare;
		mergeSort(outgoingVec, compare);
		mergeSort(incomingVec, compare);
	} else if (incoming->isChecked()) {
		incCompare compare;
		mergeSort(outgoingVec, compare);
		mergeSort(incomingVec, compare);
	} else {
		strCompare compare;
		mergeSort(outgoingVec, compare);
		mergeSort(incomingVec, compare);
	}

	// Updating outgoing links list
	for (unsigned int i = 0; i < outgoingVec.size(); i++) {
		int sizeOutgoing = (outgoingVec[i]->outgoing_links()).size();
		int sizeIncoming = (outgoingVec[i]->incoming_links()).size();
		stringstream ss;
		ss << outgoingVec[i]->filename() << " Outgoing:" << sizeOutgoing << " Incoming:" << sizeIncoming;
		QString filename = QString::fromStdString(ss.str());
		outgoingList->addItem(filename);
	}

	// Updating incoming links list
	for (unsigned int i = 0; i < incomingVec.size(); i++) {
		int sizeOutgoing = (incomingVec[i]->outgoing_links()).size();
		int sizeIncoming = (incomingVec[i]->incoming_links()).size();
		stringstream ss;
		ss << incomingVec[i]->filename() << " Outgoing:" << sizeOutgoing << " Incoming:" << sizeIncoming;
		QString filename = QString::fromStdString(ss.str());
		incomingList->addItem(filename);
	}
}

void MainWindow::showWindow(int index) {
	if (index < 0) {
		return;
	} else {
		updateWindow(webpageVec[index]);

		connect(outgoingList, SIGNAL(currentRowChanged(int)), this, SLOT(showOutgoing(int)), Qt::UniqueConnection);
		connect(incomingList, SIGNAL(currentRowChanged(int)), this, SLOT(showIncoming(int)), Qt::UniqueConnection);

		otherWin->show();
	}

}

void MainWindow::showOutgoing(int index) {
	if (index < 0) {
		return;
	} else {
		updateWindow(outgoingVec[index]);

		connect(outgoingList, SIGNAL(currentRowChanged(int)), this, SLOT(showOutgoing(int)), Qt::UniqueConnection);
		connect(incomingList, SIGNAL(currentRowChanged(int)), this, SLOT(showIncoming(int)), Qt::UniqueConnection);

		otherWin->show();
	}
}

void MainWindow::showIncoming(int index) {
	if (index < 0) {
		return;
	} else {
		updateWindow(incomingVec[index]);

		connect(outgoingList, SIGNAL(currentRowChanged(int)), this, SLOT(showOutgoing(int)), Qt::UniqueConnection);
		connect(incomingList, SIGNAL(currentRowChanged(int)), this, SLOT(showIncoming(int)), Qt::UniqueConnection);

		otherWin->show();
	}
}

void MainWindow::hideWindow() {
	otherWin->hide();
}

void MainWindow::mainButtonClicked() {
	otherWin->show();
}

void MainWindow::otherButtonClicked() {
	otherWin->hide();
}

void MainWindow::clickSingle() {
	radioSingle->setChecked(true);
}

void MainWindow::clickAND() {
	radioAND->setChecked(true);
}

void MainWindow::clickOR() {
	radioOR->setChecked(true);
}

void MainWindow::clickRank() {
	rank->setChecked(true);
}

void MainWindow::clickFilename() {
	filename->setChecked(true);
}

void MainWindow::clickOutgoing() {
	outgoing->setChecked(true);
}

void MainWindow::clickIncoming() {
	incoming->setChecked(true);
}



void MainWindow::clickFilename2() {
	newFilename->setChecked(true);
}

void MainWindow::clickOutgoing2() {
	newOutgoing->setChecked(true);
}

void MainWindow::clickIncoming2() {
	newIncoming->setChecked(true);
}

// Main function of the program. Search, display results, etc.
void MainWindow::search() {
	webpageListWidget->clear();
	// Comparator comp;
	myline = searchInput->text().toStdString();
	string searchType = "";

	// Checking whih radio button is checked. Search type is single by default
	if (radioOR->isChecked()) searchType = "or";
	else if (radioAND->isChecked()) searchType = "and";

	// Checking which radio button is checked. Sort type is filename by default

	bool success = searchengine.query(pages, searchType, myline);


	// If valid input was given for the search type
	if (success) {
		webpageListWidget->clear();
		webpageVec.clear();
		typename MySet<WebPage*>::iterator it;
		for (it = pages.begin(); it != pages.end(); ++it) {
			webpageVec.push_back(*it);
		}

		// Begin Step 4 HW 6
		for (unsigned int i = 0; i < webpageVec.size(); i++) {
			MySet<WebPage*> allOutgoing = webpageVec[i]->outgoing_links();
			MySet<WebPage*> allIncoming = webpageVec[i]->incoming_links();
			pages = pages.set_union(allOutgoing);
			pages = pages.set_union(allIncoming);
		}

		vector<WebPage*> emptyVec;
		webpageVec = emptyVec;

		for (it = pages.begin(); it != pages.end(); ++it) {
			webpageVec.push_back(*it);
		}
		// END OF Step 4 HW 6



		// Sort according to which option is checked
		if (filename->isChecked()) {
			strCompare compare;
			mergeSort(webpageVec, compare);
		} else if (outgoing->isChecked()) {
			outCompare compare;
			mergeSort(webpageVec, compare);
		} else if (rank->isChecked()) {
			webpageVec = pagerank(pages, numSteps, prob); // Should be sorted in pagerank

		} else {
			incCompare compare;
			mergeSort(webpageVec, compare);
		}
		

		// mergeSort(webpageNames, comp);

		// Display results in the scrolling list
		for (unsigned int i = 0; i < webpageVec.size(); i++) {
			int sizeOutgoing = (webpageVec[i]->outgoing_links()).size();
			int sizeIncoming = (webpageVec[i]->incoming_links()).size();
			stringstream ss;
			ss << webpageVec[i]->filename() << " Outgoing:" << sizeOutgoing << " Incoming:" << sizeIncoming;
			QString filename = QString::fromStdString(ss.str());
			webpageListWidget->addItem(filename);
		}

		/* for (unsigned int i = 0; i < webpageNames.size(); i++) {
			QString filename = QString::fromStdString(webpageNames[i]);
			webpageListWidget->addItem(filename);
		} */

	} else {
		webpageListWidget->clear();
		QString result = QString::fromStdString("Error: improper search. Try again");
		webpageListWidget->addItem(result);
	}

}
