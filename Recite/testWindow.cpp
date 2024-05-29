#include "testWindow.h"


testWindow::testWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->resize(800, 800);
	CustomTreeWidget* aaa = new CustomTreeWidget(this);
	aaa->setPos(100, 100);
	aaa->setSize(300, 600);
    connect(aaa, &CustomTreeWidget::selectedWordChanged, this, &testWindow::onSelWordChanged);

    selWord = new QLabel(this);
    selWord->resize(100, 50);
    selWord->move(600, 600);
    selWord->setStyleSheet("background-color:rgb(0,0,0);color:rgb(255,255,255)");


    Word wd;
    wd.pageIndex = 1;
    wd.spelling = "person";
    wd.meanings = QList<QString>{ "人类" };
    wd.type = "n";
    wd.synonyms = QList<QString>{ "lilin","lilin" };
    wd.nearSynonyms = QList<QString>{ "person","people" };
    wd.antonyms = QList<QString>{ "haha","www" };
    wd.similar = QList<QString>{ "people","people" };
    wd.noun = QList<QString>{ "person","person" };
    wd.verb = QList<QString>{ "person","person" };
    wd.adj = QList<QString>{ "person","person" };
    wd.adv = QList<QString>{ "person","person" };
    wd.usefulExpressions = QList<QString>{ "person","hahah","wwww" };
    Word wd1;
    wd1.pageIndex = 1;
    wd1.spelling = "person";
    wd1.meanings = QList<QString>{ "人类2" };
    wd1.type = "n";
    wd1.synonyms = QList<QString>{ "lilin","lilin" };
    wd1.nearSynonyms = QList<QString>{ "person","people" };
    wd1.antonyms = QList<QString>{ "haha","www" };
    wd1.similar = QList<QString>{ "people","people" };
    wd1.noun = QList<QString>{ "person","person" };
    wd1.verb = QList<QString>{ "person","person" };
    wd1.adj = QList<QString>{ "person","person" };
    wd1.adv = QList<QString>{ "person","person" };
    wd1.usefulExpressions = QList<QString>{ "person","hahah","wwww" };
    
    QList<Word>* list = new QList<Word>();
    list->append(wd);
    list->append(wd1);
    aaa->setWords(list);
    aaa->setEditable(true);
    aaa->showWWords();


}

testWindow::~testWindow()
{}

void testWindow::onSelWordChanged(QString wd)
{
    selWord->setText(wd);
}