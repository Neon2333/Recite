#include "MainWindow.h"

void MainWindow::focusInEvent(QFocusEvent* event)
{
    if (event->gotFocus())
    {
        wordsTree->setFocusOnCustomTree(event); //Ê¼ÖÕ±£³Ö½¹µã
    }
    MainWindow::focusInEvent(event);
}

MainWindow::MainWindow(GlobalApplication* a, QWidget* parent)
    :app(a), QMainWindow(parent)
{
    initUi();

    connectEvents();

    wordsTree->setConfigPath(configPath);
    wordsTree->setWordListDir(wordListDir);
    wordsTree->readConfig();
    wordsTree->createDirWordList();
    wordsTree->readWordListAll();
    wordsTree->showWords();

    Word emptyWd;
    emptyWd.pageIndex = 1;
    emptyWd.spelling = "NaN";
    emptyWd.meanings = QList<QString>{ "NaN" };
    emptyWd.type = "n";
    emptyWd.synonyms = QList<QString>{ "NaN" };
    emptyWd.nearSynonyms = QList<QString>{ "NaN" };
    emptyWd.antonyms = QList<QString>{ "NaN" };
    emptyWd.similar = QList<QString>{ "NaN" };
    emptyWd.noun = QList<QString>{ "NaN" };
    emptyWd.verb = QList<QString>{ "NaN" };
    emptyWd.adj = QList<QString>{ "NaN" };
    emptyWd.adv = QList<QString>{ "NaN" };
    emptyWd.usefulExpressions = QList<QString>{ "NaN" };
    wordsTree->setWordAddFillItemTop(&emptyWd);
    wordsTree->setWordAddFillItemBottom(&emptyWd);
   
}

MainWindow::~MainWindow()
{}

void MainWindow::connectEvents()
{
    connect(wordsTree, &CustomTreeWidget::editModeChanged, this, &MainWindow::onModeChanged);
    connect(wordsTree, &CustomTreeWidget::selectedWordChanged, this, [this](Word wd) {
        showSelectedWord(wd);
        });
}

void MainWindow::initUi()
{
    //ÓÒ²àµÚÒ»ÐÐ
    label_spelling = new QLabel(this);
    label_spelling->setFixedSize(350, 200);
    label_spelling->setAlignment(Qt::AlignCenter);
    label_spelling->setFont(QFont("Î¢ÈíÑÅºÚ", 30));
    label_spelling->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    textEdit_meanings = new QTextEdit();
    textEdit_meanings->setFixedSize(300, 200);
    textEdit_meanings->setReadOnly(true);
    textEdit_meanings->setFont(QFont("Î¢ÈíÑÅºÚ", 15));
    textEdit_meanings->setAlignment(Qt::AlignCenter);
    textEdit_meanings->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    label_partOfSpeech = new QLabel(this);
    label_partOfSpeech->setFixedSize(100, 200);
    label_partOfSpeech->setFont(QFont("Î¢ÈíÑÅºÚ", 15));
    label_partOfSpeech->setAlignment(Qt::AlignCenter);
    label_partOfSpeech->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    layout_rightLine1 = new QHBoxLayout();
    layout_rightLine1->setMargin(5);
    layout_rightLine1->setSpacing(5);
    layout_rightLine1->addWidget(label_spelling);
    layout_rightLine1->addWidget(textEdit_meanings);
    layout_rightLine1->addWidget(label_partOfSpeech);

    widget_spelling = new QWidget();
    widget_spelling->setFixedSize(780, 210);
    widget_spelling->setLayout(layout_rightLine1);


    //ÓÒ²àµÚ¶þÐÐ
    textEdit_synonyms = new QTextEdit(this);
    textEdit_synonyms->setFixedSize(185, 200);
    textEdit_synonyms->setReadOnly(true);
    textEdit_synonyms->setFont(QFont("Î¢ÈíÑÅºÚ", 10));
    textEdit_synonyms->setAlignment(Qt::AlignCenter);
    textEdit_synonyms->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    textEdit_nearSynonyms = new QTextEdit(this);
    textEdit_nearSynonyms->setFixedSize(185, 200);
    textEdit_nearSynonyms->setReadOnly(true);
    textEdit_nearSynonyms->setFont(QFont("Î¢ÈíÑÅºÚ", 10));
    textEdit_nearSynonyms->setAlignment(Qt::AlignCenter);
    textEdit_nearSynonyms->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    textEdit_antonym = new QTextEdit(this);
    textEdit_antonym->setFixedSize(185, 200);
    textEdit_antonym->setReadOnly(true);
    textEdit_antonym->setFont(QFont("Î¢ÈíÑÅºÚ", 10));
    textEdit_antonym->setAlignment(Qt::AlignCenter);
    textEdit_antonym->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    textEdit_similar = new QTextEdit(this);
    textEdit_similar->setFixedSize(185, 200);
    textEdit_similar->setReadOnly(true);
    textEdit_similar->setFont(QFont("Î¢ÈíÑÅºÚ", 10));
    textEdit_similar->setAlignment(Qt::AlignCenter);
    textEdit_similar->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    layout_rightLine2 = new QHBoxLayout();
    layout_rightLine2->setMargin(5);
    layout_rightLine2->setSpacing(5);
    layout_rightLine2->addWidget(textEdit_synonyms);
    layout_rightLine2->addWidget(textEdit_nearSynonyms);
    layout_rightLine2->addWidget(textEdit_antonym);
    layout_rightLine2->addWidget(textEdit_similar);

    widget_synonyms = new QWidget();
    widget_synonyms->setFixedSize(780, 210);
    widget_synonyms->setLayout(layout_rightLine2);


    //ÓÒ²àµÚÈýÐÐ
    textEdit_noun = new QTextEdit(this);
    textEdit_noun->setFixedSize(185, 80);
    textEdit_noun->setReadOnly(true);
    textEdit_noun->setFont(QFont("Î¢ÈíÑÅºÚ", 10));
    textEdit_noun->setAlignment(Qt::AlignCenter);
    textEdit_noun->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    textEdit_verb = new QTextEdit(this);
    textEdit_verb->setFixedSize(185, 80);
    textEdit_verb->setReadOnly(true);
    textEdit_verb->setFont(QFont("Î¢ÈíÑÅºÚ", 10));
    textEdit_verb->setAlignment(Qt::AlignCenter);
    textEdit_verb->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    textEdit_adj = new QTextEdit(this);
    textEdit_adj->setFixedSize(185, 80);
    textEdit_adj->setReadOnly(true);
    textEdit_adj->setFont(QFont("Î¢ÈíÑÅºÚ", 10));
    textEdit_adj->setAlignment(Qt::AlignCenter);
    textEdit_adj->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    textEdit_adv = new QTextEdit(this);
    textEdit_adv->setFixedSize(185, 80);
    textEdit_adv->setReadOnly(true);
    textEdit_adv->setFont(QFont("Î¢ÈíÑÅºÚ", 10));
    textEdit_adv->setAlignment(Qt::AlignCenter);
    textEdit_adv->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    layout_rightLine3 = new QHBoxLayout();
    layout_rightLine3->setMargin(5);
    layout_rightLine3->setSpacing(5);
    layout_rightLine3->addWidget(textEdit_noun);
    layout_rightLine3->addWidget(textEdit_verb);
    layout_rightLine3->addWidget(textEdit_adj);
    layout_rightLine3->addWidget(textEdit_adv);

    widget_noun = new QWidget();
    widget_noun->setFixedSize(780, 90);
    widget_noun->setLayout(layout_rightLine3);


    //ÓÒ²àµÚËÄÐÐ
    textEdit_usefulExpressions = new QTextEdit(this);
    textEdit_usefulExpressions->setFixedSize(770, 200);
    textEdit_usefulExpressions->setReadOnly(true);
    textEdit_usefulExpressions->setFont(QFont("Î¢ÈíÑÅºÚ", 10));
    textEdit_usefulExpressions->setAlignment(Qt::AlignCenter);
    textEdit_usefulExpressions->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    layout_rightLine4 = new QHBoxLayout();
    layout_rightLine4->setMargin(5);
    layout_rightLine4->setSpacing(5);
    layout_rightLine4->addWidget(textEdit_usefulExpressions);

    widget_usefulExpressions = new QWidget();
    widget_usefulExpressions->setFixedSize(780, 200);
    widget_usefulExpressions->setLayout(layout_rightLine4);


    //ÓÒ²àÕûÌå
    layout_right = new QVBoxLayout();
    layout_right->setSpacing(5);
    layout_right->setMargin(5);
    layout_right->addWidget(widget_spelling);
    layout_right->addWidget(widget_synonyms);
    layout_right->addWidget(widget_noun);
    layout_right->addWidget(widget_usefulExpressions);

    widget_right = new QWidget();
    widget_right->setFixedSize(800, 730);
    widget_right->setLayout(layout_right);

    //×ó²àÕûÌå
    wordsTree = new CustomTreeWidget(app, this);

    wordsTree->setSize(400, 930);
    wordsTree->setPos(4, 4);

    layout_left = new QVBoxLayout();
    layout_left->addWidget(wordsTree);
    layout_left->setMargin(5);
    layout_left->setSpacing(5);

    widget_left = new QWidget();
    widget_left->setFixedSize(420, 730);
    widget_left->setLayout(layout_left);

    //Recite
    this->setFixedSize(1230, 740);
    this->setWindowTitle("Recite");

    layout_main = new QHBoxLayout();
    layout_main->setSpacing(5);
    layout_main->setMargin(5);
    layout_main->addWidget(widget_left);
    layout_main->addWidget(widget_right);

    widget_main = new QWidget();
    widget_main->setFixedSize(1230, 740);
    widget_main->setLayout(layout_main);
    this->setCentralWidget(widget_main);
}

void MainWindow::showSelectedWord(Word selectedWord)
{
    label_spelling->setText(selectedWord.spelling);

    textEdit_meanings->clear();
    textEdit_meanings->append("ÊÍÒå£º");
    for (auto item : selectedWord.meanings)
    {
        textEdit_meanings->append(item);
        textEdit_meanings->setAlignment(Qt::AlignCenter);
    }

    label_partOfSpeech->setText("´ÊÐÔ£º\n" + selectedWord.type);

    textEdit_synonyms->clear();
    textEdit_synonyms->append("Í¬Òå´Ê£º");
    for (auto item : selectedWord.synonyms)
    {
        textEdit_synonyms->append(item);
        textEdit_synonyms->setAlignment(Qt::AlignCenter);
    }

    textEdit_nearSynonyms->clear();
    textEdit_nearSynonyms->append("½üÒå´Ê£º");
    for (auto item : selectedWord.nearSynonyms)
    {
        textEdit_nearSynonyms->append(item);
        textEdit_nearSynonyms->setAlignment(Qt::AlignCenter);
    }

    textEdit_antonym->clear();
    textEdit_antonym->append("·´Òå´Ê£º");
    for (auto item : selectedWord.antonyms)
    {
        textEdit_antonym->append(item);
        textEdit_antonym->setAlignment(Qt::AlignCenter);
    }

    textEdit_similar->clear();
    textEdit_similar->append("ÐÎ½ü´Ê£º");
    for (auto item : selectedWord.similar)
    {
        textEdit_similar->append(item);
        textEdit_similar->setAlignment(Qt::AlignCenter);
    }

    textEdit_noun->clear();
    textEdit_noun->append("n£º");
    for (auto item : selectedWord.noun)
    {
        textEdit_noun->append(item);
        textEdit_noun->setAlignment(Qt::AlignCenter);
    }

    textEdit_verb->clear();
    textEdit_verb->append("v£º");
    for (auto item : selectedWord.verb)
    {
        textEdit_verb->append(item);
        textEdit_verb->setAlignment(Qt::AlignCenter);
    }

    textEdit_adj->clear();
    textEdit_adj->append("adj£º");
    for (auto item : selectedWord.adj)
    {
        textEdit_adj->append(item);
        textEdit_adj->setAlignment(Qt::AlignCenter);
    }

    textEdit_adv->clear();
    textEdit_adv->append("adv£º");
    for (auto item : selectedWord.adv)
    {
        textEdit_adv->append(item);
        textEdit_adv->setAlignment(Qt::AlignCenter);
    }

    textEdit_usefulExpressions->clear();
    textEdit_usefulExpressions->append("³£ÓÃ´îÅä£º");
    for (auto item : selectedWord.usefulExpressions)
    {
        textEdit_usefulExpressions->append(item);
        textEdit_usefulExpressions->setAlignment(Qt::AlignCenter);
    }
}

void MainWindow::onModeChanged(bool isEditMode)
{}