//#include "testWindow.h"
//
//testWindow::testWindow(QWidget *parent)
//	: QMainWindow(parent)
//{
//	ui.setupUi(this);
//
//	this->resize(800, 800);
//	CustomTreeWidget* aaa = new CustomTreeWidget(this);
//	aaa->setPos(100, 100);
//	aaa->setSize(300, 600);
//    connect(aaa, &CustomTreeWidget::selectedWordChanged, this, &testWindow::onSelWordChanged);
//
//    selWord = new QLabel(this);
//    selWord->resize(100, 50);
//    selWord->move(600, 600);
//    selWord->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");
//
//
//    Word wd;
//    wd.pageIndex = 1;
//    wd.spelling = "person1";
//    wd.meanings = QList<QString>{ "人类1" };
//    wd.type = "n";
//    wd.synonyms = QList<QString>{ "lilin","lilin" };
//    wd.nearSynonyms = QList<QString>{ "person","people" };
//    wd.antonyms = QList<QString>{ "haha","www" };
//    wd.similar = QList<QString>{ "people","people" };
//    wd.noun = QList<QString>{ "person","person" };
//    wd.verb = QList<QString>{ "person","person" };
//    wd.adj = QList<QString>{ "person","person" };
//    wd.adv = QList<QString>{ "person","person" };
//    wd.usefulExpressions = QList<QString>{ "person","hahah","wwww" };
//    Word wd1;
//    wd1.pageIndex = 1;
//    wd1.spelling = "person2";
//    wd1.meanings = QList<QString>{ "人类2" };
//    wd1.type = "n";
//    wd1.synonyms = QList<QString>{ "lilin","lilin" };
//    wd1.nearSynonyms = QList<QString>{ "person","people" };
//    wd1.antonyms = QList<QString>{ "haha","www" };
//    wd1.similar = QList<QString>{ "people","people" };
//    wd1.noun = QList<QString>{ "person","person" };
//    wd1.verb = QList<QString>{ "person","person" };
//    wd1.adj = QList<QString>{ "person","person" };
//    wd1.adv = QList<QString>{ "person","person" };
//    wd1.usefulExpressions = QList<QString>{ "person","hahah","wwww" };
//    
//    wdblank = new Word;
//    wdblank->pageIndex = 1;
//    wdblank->spelling = "add";
//    wdblank->meanings = QList<QString>{ "" };
//    wdblank->type = "n";
//    wdblank->synonyms = QList<QString>{ "" };
//    wdblank->nearSynonyms = QList<QString>{ "", };
//    wdblank->antonyms = QList<QString>{ "" };
//    wdblank->similar = QList<QString>{ "" };
//    wdblank->noun = QList<QString>{ "" };
//    wdblank->verb = QList<QString>{ "" };
//    wdblank->adj = QList<QString>{ "" };
//    wdblank->adv = QList<QString>{ "" };
//    wdblank->usefulExpressions = QList<QString>{ "" };
//
//    QHash<QString, Word> listtemp;
//    listtemp.insert(wd.spelling, wd);
//    listtemp.insert(wd1.spelling, wd1);
//    QList<QHash<QString, Word>>* list = new QList<QHash<QString, Word>>();
//    list->append(listtemp);
//    aaa->setWords(list);
//    aaa->setWordAddFillItemTop(wdblank);
//    aaa->setWordAddFillItemBottom(wdblank);
//    aaa->setEditable(true);
//    aaa->showWords();
//}
//
//testWindow::~testWindow()
//{
//    delete wdblank;
//}
//
//void testWindow::onSelWordChanged(QString wd)
//{
//    selWord->setText(wd);
//}
