#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QRadioButton>
#include <QCoreApplication>
#include <QGroupBox>

#include "searcheng.h"
#include "msort.h"
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"
#include <sstream>

class MainWindow : public QWidget {
	Q_OBJECT
public:
	MainWindow(SearchEng searchengine, int n, double probability);
	~MainWindow();
	void updateWindow(WebPage* wp);

private slots:
	void search();

	void clickSingle();
	void clickAND();
	void clickOR();

	void clickRank();
	void clickFilename();
	void clickOutgoing();
	void clickIncoming();

	void clickFilename2();
	void clickOutgoing2();
	void clickIncoming2();

	void mainButtonClicked();
	void otherButtonClicked();

	void showWindow(int index);
	void showOutgoing(int index);
	void showIncoming(int index);
	void hideWindow();

private:

	// // UI

	// New Window stuff
	//QPushButton* mainButton;
	QWidget* otherWin;
	QPushButton* otherButton;
	QTextEdit* pageContents;
	QListWidget* incomingList;
	QListWidget* outgoingList;

	QHBoxLayout* windowLayout; // Layout that contains two different layouts
	QVBoxLayout* otherLayout;
	QVBoxLayout* outgoingLayout;
	QVBoxLayout* incomingLayout;

	QLabel* pageLabel;
	QLabel* outgoingLabel;
	QLabel* incomingLabel;

	// Layouts
	QHBoxLayout* overallLayout;

	// Displayed WebPages
	QVBoxLayout* webpageDisplayLayout;
	QLabel* webpageNameDisplay;

	// List of quotes
	QListWidget* webpageListWidget;

	// Groups
	QGroupBox* searchGroup;
	QGroupBox* sortGroup;
	QGroupBox* newSortGroup;

	// Form for new quote
	QVBoxLayout* formLayout;
	QHBoxLayout* searchLayout;
	QHBoxLayout* sortLayout;
	QHBoxLayout* newSortLayout;
	QLabel* searchLabel;
	QLineEdit* searchInput;
	QPushButton* addButton;
	QPushButton* quitButton;

	// Radio Buttons
	QRadioButton* radioSingle;
	QRadioButton* radioAND;
	QRadioButton* radioOR;

	QRadioButton* rank;
	QRadioButton* filename;
	QRadioButton* outgoing;
	QRadioButton* incoming;

	QRadioButton* newFilename;
	QRadioButton* newOutgoing;
	QRadioButton* newIncoming;

	// Data members for searchengine
	MySet<WebPage*> pages;
	SearchEng searchengine;
	std::string myline;

	// // Data
	// note: the index of each name in `pokemonNames`
	// corresponds with the index of that pokemon's
	// image in `pokemonImages`

	std::vector<std::string> webpageNames;
	std::vector<WebPage*> webpageVec;
	std::vector<WebPage*> outgoingVec;
	std::vector<WebPage*> incomingVec;

	int numSteps;
	double prob;

};