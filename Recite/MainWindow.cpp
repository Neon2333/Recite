#include "MainWindow.h"

MainWindow::MainWindow(GlobalApplication* a, QWidget* parent)
    :app(a), QMainWindow(parent)
{
    wordListCurrentPage = new QHash<QString, Word>();
    wordListAll = new QHash<QString, Word>();

    init();
}

MainWindow::~MainWindow()
{
    //写入配置文件
    JsonOper::writeConfig(configPath, curPageIndex, countWordList);

    //释放资源
    delete wordListAll;
    delete wordListCurrentPage;

}

void MainWindow::editModeSetter(bool isEditMode)
{
    if (editMode != isEditMode)
    {
        editMode = isEditMode;
        emit modeChanged(editMode);
    }
}

void MainWindow::init()
{
    //初始化窗口控件
    initMainWindow();

    //关联事件handler
    connectEvents();    

#if 1
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
    wordListCurrentPage->insert("person", wd);
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
    wordListCurrentPage->insert("person", wd1);
    selectedWord = wd1;

#endif

    //读配置文件
    QList<int> configParas = JsonOper::readConfig(configPath);
    curPageIndex = configParas.at(0);
    countWordList = configParas.at(1);

    //创建wordlist目录
    QDir wordListDirTemp(wordListDir);
    if (!wordListDirTemp.exists())
    {
        wordListDirTemp.mkdir(wordListDir);
    }

    //读取当前页单词表
    readWordListCurrentPage();

    //树状显示当前页
    treeShowCurrentPageModeRecite();

    //右侧显示选中单词详细
    showSelectedWord();

    //子线程读取所有单词表，进度条显示
    readWordListAll(wordListDir);
}

void MainWindow::connectEvents()
{
    connect(this, &MainWindow::modeChanged, this, &MainWindow::onModeChanged);
    connect(app, &GlobalApplication::keyIPressed, this, &MainWindow::onKeyIPressed);
    connect(app, &GlobalApplication::keyRPressed, this, &MainWindow::onKeyRPressed);
    connect(app, &GlobalApplication::keyEnterPressed, this, &MainWindow::onKeyEnterPressed);
    connect(app, &GlobalApplication::keyCtrlEnterPressed, this, &MainWindow::onKeyCtrlEnterPressed);

}

void MainWindow::initMainWindow()
{
    //右侧第一行
    label_spelling = new QLabel(this);
    label_spelling->setFixedSize(350, 200);
    label_spelling->setText("annynomous");  //不能放在字体、Alignment等后面，否则设置不了
    label_spelling->setAlignment(Qt::AlignCenter);
    label_spelling->setFont(QFont("微软雅黑", 30));
    label_spelling->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    textEdit_meanings = new QTextEdit();
    textEdit_meanings->setFixedSize(300, 200);
    textEdit_meanings->setReadOnly(true);
    textEdit_meanings->append("人类");
    textEdit_meanings->setFont(QFont("微软雅黑", 15));
    textEdit_meanings->setAlignment(Qt::AlignCenter);
    textEdit_meanings->setStyleSheet("background-color:rgb(0,0,0);color:rgb(255,255,255)");

    label_partOfSpeech = new QLabel(this);
    label_partOfSpeech->setFixedSize(100, 200);
    label_partOfSpeech->setText("n");
    label_partOfSpeech->setFont(QFont("微软雅黑", 15));
    label_partOfSpeech->setAlignment(Qt::AlignCenter);
    label_partOfSpeech->setStyleSheet("background-color:rgb(0,0,0);color:rgb(255,255,255)");

    layout_rightLine1 = new QHBoxLayout();
    layout_rightLine1->setMargin(5);
    layout_rightLine1->setSpacing(5);
    layout_rightLine1->addWidget(label_spelling);
    layout_rightLine1->addWidget(textEdit_meanings);
    layout_rightLine1->addWidget(label_partOfSpeech);

    widget_spelling = new QWidget();
    widget_spelling->setFixedSize(780, 210);
    widget_spelling->setLayout(layout_rightLine1);


    //右侧第二行
    textEdit_synonyms = new QTextEdit(this);
    textEdit_synonyms->setFixedSize(185, 200);
    textEdit_synonyms->setReadOnly(true);
    textEdit_synonyms->setFont(QFont("微软雅黑", 10));
    textEdit_synonyms->setAlignment(Qt::AlignCenter);
    textEdit_synonyms->append("distinguish");
    // textEdit_synonyms->setStyleSheet("background-color:rgb(0,0,0);color:rgb(255,255,255)");

    textEdit_nearSynonyms = new QTextEdit(this);
    textEdit_nearSynonyms->setFixedSize(185, 200);
    textEdit_nearSynonyms->setReadOnly(true);
    textEdit_nearSynonyms->append("近义词");
    textEdit_nearSynonyms->setFont(QFont("微软雅黑", 10));
    textEdit_nearSynonyms->setAlignment(Qt::AlignCenter);
    // textEdit_nearSynonyms->setStyleSheet("background-color:rgb(0,0,0);color:rgb(255,255,255)");

    textEdit_antonym = new QTextEdit(this);
    textEdit_antonym->setFixedSize(185, 200);
    textEdit_antonym->setReadOnly(true);
    textEdit_antonym->append("反义词");
    textEdit_antonym->setFont(QFont("微软雅黑", 10));
    textEdit_antonym->setAlignment(Qt::AlignCenter);
    // textEdit_antonym->setStyleSheet("background-color:rgb(0,0,0);color:rgb(255,255,255)");

    textEdit_similar = new QTextEdit(this);
    textEdit_similar->setFixedSize(185, 200);
    textEdit_similar->setReadOnly(true);
    textEdit_similar->append("形近词");
    textEdit_similar->setFont(QFont("微软雅黑", 10));
    textEdit_similar->setAlignment(Qt::AlignCenter);
    // textEdit_similar->setStyleSheet("background-color:rgb(0,0,0);color:rgb(255,255,255)");

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


    //右侧第三行
    textEdit_noun = new QTextEdit(this);
    textEdit_noun->setFixedSize(185, 80);
    textEdit_noun->setReadOnly(true);
    textEdit_noun->setText("n");
    textEdit_noun->setFont(QFont("微软雅黑", 10));
    textEdit_noun->setAlignment(Qt::AlignCenter);
    // textEdit_noun->setStyleSheet("background-color:rgb(0,0,0);color:rgb(255,255,255)");

    textEdit_verb = new QTextEdit(this);
    textEdit_verb->setFixedSize(185, 80);
    textEdit_verb->setReadOnly(true);
    textEdit_verb->setText("v");
    textEdit_verb->setFont(QFont("微软雅黑", 10));
    textEdit_verb->setAlignment(Qt::AlignCenter);
    // textEdit_verb->setStyleSheet("background-color:rgb(0,0,0);color:rgb(255,255,255)");

    textEdit_adj = new QTextEdit(this);
    textEdit_adj->setFixedSize(185, 80);
    textEdit_adj->setReadOnly(true);
    textEdit_adj->setText("adj");
    textEdit_adj->setFont(QFont("微软雅黑", 10));
    textEdit_adj->setAlignment(Qt::AlignCenter);
    // textEdit_adj->setStyleSheet("background-color:rgb(0,0,0);color:rgb(255,255,255)");

    textEdit_adv = new QTextEdit(this);
    textEdit_adv->setFixedSize(185, 80);
    textEdit_adv->setReadOnly(true);
    textEdit_adv->setText("adv");
    textEdit_adv->setFont(QFont("微软雅黑", 10));
    textEdit_adv->setAlignment(Qt::AlignCenter);
    // textEdit_adv->setStyleSheet("background-color:rgb(0,0,0);color:rgb(255,255,255)");

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


    //右侧第四行
    textEdit_usefulExpressions = new QTextEdit(this);
    textEdit_usefulExpressions->setFixedSize(770, 200);
    textEdit_usefulExpressions->setReadOnly(true);
    textEdit_usefulExpressions->setText("常用搭配");
    textEdit_usefulExpressions->setFont(QFont("微软雅黑", 10));
    textEdit_usefulExpressions->setAlignment(Qt::AlignCenter);

    layout_rightLine4 = new QHBoxLayout();
    layout_rightLine4->setMargin(5);
    layout_rightLine4->setSpacing(5);
    layout_rightLine4->addWidget(textEdit_usefulExpressions);

    widget_usefulExpressions = new QWidget();
    widget_usefulExpressions->setFixedSize(780, 200);
    widget_usefulExpressions->setLayout(layout_rightLine4);


    //右侧整体
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

    //左侧整体
    treeWidget_wordsTree = new QTreeWidget(this);
    model = new QStandardItemModel();
    treeWidget_wordsTree->setFixedSize(400, 630);
    treeWidget_wordsTree->setHeaderLabels(QStringList{ "单词表","联想词" });
    treeWidget_wordsTree->setColumnCount(2);

    layout_leftLine1 = new QHBoxLayout();
    layout_leftLine1->setMargin(5);
    layout_leftLine1->setSpacing(5);
    layout_leftLine1->addWidget(treeWidget_wordsTree);
    widget_leftLine1 = new QWidget();
    widget_leftLine1->setFixedSize(400, 630);
    widget_leftLine1->setLayout(layout_leftLine1);

    btn_lastPage = new QPushButton(this);
    btn_lastPage->setFixedSize(50, 25);
    btn_lastPage->setText("上一页");

    btn_nextPage = new QPushButton(this);
    btn_nextPage->setFixedSize(50, 25);
    btn_nextPage->setText("下一页");

    label_curPage = new QLabel(this);
    label_curPage->setFixedSize(50, 25);
    label_curPage->setFont(QFont("微软雅黑", 10));
    label_curPage->setAlignment(Qt::AlignCenter);
    label_curPage->setText(QString::number(curPageIndex) + "/" + QString::number(countWordList));

    layout_leftLine2 = new QHBoxLayout();
    layout_leftLine2->setMargin(5);
    layout_leftLine2->setSpacing(5);
    layout_leftLine2->addWidget(btn_lastPage);
    layout_leftLine2->addWidget(label_curPage);
    layout_leftLine2->addWidget(btn_nextPage);
    widget_leftLine2 = new QWidget();
    widget_leftLine2->setFixedSize(400, 30);
    widget_leftLine2->setLayout(layout_leftLine2);

    label_status = new QLabel(this);
    label_status->setFixedSize(50, 20);
    label_status->setFont(QFont("微软雅黑", 10));
    label_status->setAlignment(Qt::AlignCenter);
    label_status->setText(editMode ? "edit" : "recite");
    label_status->setStyleSheet("background-color:rgb(0,0,0);color:rgb(255,255,255)");

    probar = new QProgressBar(this);
    probar->setFixedSize(300, 20);
    probar->setOrientation(Qt::Orientation::Horizontal);
    probar->setValue(50);
    probar->setTextVisible(true);

    layout_leftLine3 = new QHBoxLayout();
    layout_leftLine3->setMargin(5);
    layout_leftLine3->setSpacing(5);
    layout_leftLine3->addWidget(label_status);
    layout_leftLine3->addWidget(probar);
    widget_leftLine3 = new QWidget();
    widget_leftLine3->setFixedSize(400, 30);
    widget_leftLine3->setLayout(layout_leftLine3);
    

    layout_left = new QVBoxLayout();
    layout_left->addWidget(widget_leftLine1);
    layout_left->addWidget(widget_leftLine2);
    layout_left->addWidget(widget_leftLine3);
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

void MainWindow::treeShowCurrentPageModeRecite()
{
    //从wordListCurrentPage读取单词显示
    QList<QString> keys = wordListCurrentPage->keys();
    for (int i = 0; i < keys.count(); i++)
    {
        addWordToTreeModeRecite(wordListCurrentPage->value(keys.at(i)));
    }
    treeWidget_wordsTree->expandAll();
}

void MainWindow::addWordToTreeModeRecite(Word wd)
{
    QTreeWidgetItem* wordRoot = new QTreeWidgetItem();
    wordRoot->setText(0, wd.spelling);
    for (auto item : wd.meanings)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        wordRoot->addChild(tempItem);
    }
    QTreeWidgetItem* wordTypeItem = new QTreeWidgetItem();
    wordTypeItem->setText(1, wd.type);
    wordRoot->addChild(wordTypeItem);
    for (auto item : wd.synonyms)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        wordRoot->addChild(tempItem);
    }
    for (auto item : wd.antonyms)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        wordRoot->addChild(tempItem);
    }
    for (auto item : wd.nearSynonyms)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        wordRoot->addChild(tempItem);
    }
    for (auto item : wd.similar)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        wordRoot->addChild(tempItem);
    }
    for (auto item : wd.noun)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        wordRoot->addChild(tempItem);
    }
    for (auto item : wd.verb)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        wordRoot->addChild(tempItem);
    }
    for (auto item : wd.adj)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        wordRoot->addChild(tempItem);
    }
    for (auto item : wd.adv)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        wordRoot->addChild(tempItem);
    }
    for (auto item : wd.usefulExpressions)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        wordRoot->addChild(tempItem);
    }
    treeWidget_wordsTree->addTopLevelItem(wordRoot);
}

void MainWindow::treeShowCurrentPageModeEdit()
{
    QList<QString> keys = wordListCurrentPage->keys();
    for (int i = 0; i < keys.count(); i++)
    {
        addWordToTreeModeRecite(wordListCurrentPage->value(keys.at(i)));
    }
    treeWidget_wordsTree->expandAll();
}

void MainWindow::addWordToTreeModeEdit(Word wd)
{
     QTreeWidgetItem* wordspellingItem = new QTreeWidgetItem();
    wordspellingItem->setText(0, wd.spelling);

    QTreeWidgetItem* meaningsItem = new QTreeWidgetItem();
    meaningsItem->setText(1, "释义");
    for (auto item : wd.meanings)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(2, item);
        meaningsItem->addChild(tempItem);
    }

    QTreeWidgetItem* partSpeechItem = new QTreeWidgetItem();
    partSpeechItem->setText(1, wd.type);


    QTreeWidgetItem* synonymsItem = new QTreeWidgetItem();
    synonymsItem->setText(1, "同义词");
    for (auto item : wd.synonyms)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(2, item);
        synonymsItem->addChild(tempItem);
    }

    QTreeWidgetItem* anotonymsItem = new QTreeWidgetItem();
    anotonymsItem->setText(1, "反义词");
    for (auto item : wd.antonyms)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(2, item);
        anotonymsItem->addChild(tempItem);
    }

    QTreeWidgetItem* nearSynonymsItem = new QTreeWidgetItem();
    nearSynonymsItem->setText(1, "近义词");
    for (auto item : wd.nearSynonyms)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(2, item);
        nearSynonymsItem->addChild(tempItem);
    }

    QTreeWidgetItem* similarsItem = new QTreeWidgetItem();
    similarsItem->setText(1, "形近词");
    for (auto item : wd.similar)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(2, item);
        similarsItem->addChild(tempItem);
    }

    QTreeWidgetItem* nounItem = new QTreeWidgetItem();
    nounItem->setText(1, "名词");
    for (auto item : wd.noun)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(2, item);
        nounItem->addChild(tempItem);
    }

    QTreeWidgetItem* verbItem = new QTreeWidgetItem();
    verbItem->setText(1, "动词");
    for (auto item : wd.verb)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(2, item);
        verbItem->addChild(tempItem);
    }

    QTreeWidgetItem* adjItem = new QTreeWidgetItem();
    adjItem->setText(1, "形容词");
    for (auto item : wd.adj)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(2, item);
        adjItem->addChild(tempItem);
    }

    QTreeWidgetItem* advItem = new QTreeWidgetItem();
    advItem->setText(1, "副词");
    for (auto item : wd.adv)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(2, item);
        advItem->addChild(tempItem);
    }

    QTreeWidgetItem* usefulExpressionsItem = new QTreeWidgetItem();
    usefulExpressionsItem->setText(1, "常用搭配");
    for (auto item : wd.usefulExpressions)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(2, item);
        usefulExpressionsItem->addChild(tempItem);
    }

    wordspellingItem->addChildren(QList<QTreeWidgetItem*>{meaningsItem, partSpeechItem,
        synonymsItem, anotonymsItem, nearSynonymsItem, similarsItem,
        nounItem, verbItem, adjItem, advItem,
        usefulExpressionsItem});

    treeWidget_wordsTree->addTopLevelItem(wordspellingItem);
}


void MainWindow::readWordListAll(QString jsonDir)
{
    //不存在，则创建空的0.json
    //否则，遍历读取到wordListAll

    QDir dir(jsonDir);
    if (!dir.exists())
    {
        //创建目录

    }

    QFileInfoList fileInfoList = dir.entryInfoList();
    for (auto item : fileInfoList)
    {
        if (!item.isFile() || item.suffix().toLower() != "json")
        {
            continue;
        }

        QString jsonPath = item.absoluteFilePath();
        QFile jsonFile(jsonPath);
        if (!jsonFile.open(QFile::ReadOnly))
        {
            return;
        }
        QByteArray jsonArr = jsonFile.readAll();
        jsonFile.close();
        QJsonDocument doc = QJsonDocument::fromJson(jsonArr);
        if (!doc.isArray())
        {
            return;
        }

        QJsonObject obj = doc.object();
        QStringList keys = obj.keys();

        for (int i = 0; i < keys.count(); i++)
        {
            QString key = keys.at(i);
            QJsonValue value = obj.value(key);

            if (!value.isObject())
            {
                continue;
            }
            QJsonObject obj = value.toObject();
            Word wd = JsonOper::readWord(obj);
            wordListAll->insert(wd.spelling, wd);
        }
        
        //加个进度计算
        
    }
}

void MainWindow::readWordListCurrentPage()
{
    //若curPageIndex=countWordList=0，第一次打开。则创建1.json
    //将curPageIndex=countWordList=1。读取单词表到wordListCurrentPage
    QString curPageJsonPath;
    if (curPageIndex == 0 && countWordList == 0)
    {
        updateConfig(1, countWordList + 1);
        curPageJsonPath = wordListDir + "/" + QString::number(curPageIndex) + ".json";
        //QList<Word> wl{ Word(1,"") };
        //JsonOper::writeWords(wl, curPageJsonPath);
    }
    //若curPageIndex<=countWordList >0，不是第一次打开。则打开curPageIndex.json文件，读取单词表到wordListCurrentPage。

    if (curPageIndex > countWordList || curPageIndex < 0 || countWordList < 0)
    {
        return;
    }

    curPageJsonPath = wordListDir + "/" + QString::number(curPageIndex) + ".json";
    QList<Word> wordListCurPageTemp = JsonOper::readWords(curPageJsonPath);

    wordListCurrentPage->clear();
    for (auto wd : wordListCurPageTemp)
    {
        wordListCurrentPage->insert(wd.spelling, wd);
    }
}

void MainWindow::updateConfig(int curPage, int countWord)
{
    curPageIndex = curPage;
    countWordList = countWord;
    JsonOper::writeConfig(configPath, curPageIndex, countWordList);
}




void MainWindow::expandWord(Word wd)
{

}

void MainWindow::collapaseWord(Word wd)
{

}

void MainWindow::showSelectedWord()
{
    label_spelling->setText(selectedWord.spelling);

    textEdit_meanings->clear();
    textEdit_meanings->append("释义：");
    for (auto item : selectedWord.meanings)
    {
        textEdit_meanings->append(item);
        textEdit_meanings->setAlignment(Qt::AlignCenter);
    }

    label_partOfSpeech->setText("词性：\n" + selectedWord.type);

    textEdit_synonyms->clear();
    textEdit_synonyms->append("同义词：");
    for (auto item : selectedWord.synonyms)
    {
        textEdit_synonyms->append(item);
        textEdit_synonyms->setAlignment(Qt::AlignCenter);
    }

    textEdit_nearSynonyms->clear();
    textEdit_nearSynonyms->append("近义词：");
    for (auto item : selectedWord.nearSynonyms)
    {
        textEdit_nearSynonyms->append(item);
        textEdit_nearSynonyms->setAlignment(Qt::AlignCenter);
    }

    textEdit_antonym->clear();
    textEdit_antonym->append("反义词：");
    for (auto item : selectedWord.antonyms)
    {
        textEdit_antonym->append(item);
        textEdit_antonym->setAlignment(Qt::AlignCenter);
    }

    textEdit_similar->clear();
    textEdit_similar->append("形近词：");
    for (auto item : selectedWord.similar)
    {
        textEdit_similar->append(item);
        textEdit_similar->setAlignment(Qt::AlignCenter);
    }

    textEdit_noun->clear();
    textEdit_noun->append("名词：");
    for (auto item : selectedWord.noun)
    {
        textEdit_noun->append(item);
        textEdit_noun->setAlignment(Qt::AlignCenter);
    }

    textEdit_verb->clear();
    textEdit_verb->append("动词：");
    for (auto item : selectedWord.verb)
    {
        textEdit_verb->append(item);
        textEdit_verb->setAlignment(Qt::AlignCenter);
    }

    textEdit_adj->clear();
    textEdit_adj->append("形容词：");
    for (auto item : selectedWord.adj)
    {
        textEdit_adj->append(item);
        textEdit_adj->setAlignment(Qt::AlignCenter);
    }

    textEdit_adv->clear();
    textEdit_adv->append("副词：");
    for (auto item : selectedWord.adv)
    {
        textEdit_adv->append(item);
        textEdit_adv->setAlignment(Qt::AlignCenter);
    }

    textEdit_usefulExpressions->clear();
    textEdit_usefulExpressions->append("常用搭配：");
    for (auto item : selectedWord.usefulExpressions)
    {
        textEdit_usefulExpressions->append(item);
        textEdit_usefulExpressions->setAlignment(Qt::AlignCenter);
    }
}

void MainWindow::onKeyIPressed() 
{
    editModeSetter(true);
}

void MainWindow::onKeyRPressed()
{
    editModeSetter(false);
}

void MainWindow::onKeyEnterPressed()
{
    showSelectedWord();
}

void MainWindow::onKeyCtrlEnterPressed()
{
    qDebug() << "alt+enter\n";
}


void MainWindow::paintEvent(QPaintEvent* event)
{

}

void MainWindow::closeEvent(QCloseEvent* event)
{
    //如果ReciteMode，nothing
    //若EditMode，转换到ReciteMode，发出ModeChange信号，进行json保存动作
}

void MainWindow::onModeChanged(bool isEditMode)
{
    label_status->setText(isEditMode ? "Edit" : "Recite");
    if (isEditMode)
    {
        treeShowCurrentPageModeRecite();
    }
    else
    {
        treeShowCurrentPageModeEdit();
    }

}