#include "CustomTreeWidget.h"

CustomTreeWidget::CustomTreeWidget(GlobalApplication* app, QWidget* parent)
    :QWidget(parent)
{
    ui.setupUi(this);

    editMode = false;
    curPageIndex = 0;
    countWordList = 0;
    wordListAll = new QList<QHash<QString, Word>>();

    initUi(app);

    rootEditMode->setWordsList(wordListAll);
    rootNoteditMode->setWordsList(wordListAll);
    
    connect(rootNoteditMode, &CustomTree::modeChanged, this, &CustomTreeWidget::onModeChanged);
    connect(rootEditMode, &CustomTree::modeChanged, this, &CustomTreeWidget::onModeChanged);

    connect(rootNoteditMode, &CustomTree::selWordChanged, this, &CustomTreeWidget::onSelectedWordChanged);
    connect(rootEditMode, &CustomTree::selWordChanged, this, &CustomTreeWidget::onSelectedWordChanged);
    
    connect(rootNoteditMode, &CustomTree::curPageIndexChanged, this, &CustomTreeWidget::onCurPageIndexChanged);
    connect(rootEditMode, &CustomTree::curPageIndexChanged, this, &CustomTreeWidget::onCurPageIndexChanged);
    
    connect(rootNoteditMode, &CustomTree::countWordListChanged, this, &CustomTreeWidget::onCountWordListChanged);
    connect(rootEditMode, &CustomTree::countWordListChanged, this, &CustomTreeWidget::onCountWordListChanged);

}

CustomTreeWidget::~CustomTreeWidget()
{
    //写入config.json，保存页码信息
    //遍历wordListAll，写入到1.json~count.json，保存单词表
    //后续优化：只写入被修改的页面，把修改的hash放入单独的list存储，写入后清空。

    JsonOper::writeConfig(configPath, curPageIndex, countWordList);
    probar->setVisible(true);
    for (int i = 0; i < wordListAll->count(); i++)
    {
        auto wordsPage = wordListAll->at(i);
        JsonOper::writeWords(wordsPage, wordListDir + "/" + QString::number(i + 1) + ".json");
        probar->setValue(100 * i / countWordList);  //写入时进度条
    }
    //probar->setVisible(false);

    delete wordListAll;
}

void CustomTreeWidget::setSize(int w, int h)
{
    this->resize(w, h);
    rootNoteditMode->resize(w - 4, h - 250);
    rootEditMode->resize(w - 4, h - 250);
    /*label_mode->resize(200, 250);
    btn_lastPage->resize(200, 250);
    btn_nextPage->resize(200, 250);
    label_curPage->resize(200, 250);
    probar->resize(300, 210);*/
}

void CustomTreeWidget::setPos(int x, int y)
{
    this->move(x, y);
    rootNoteditMode->move(4, 4);
    rootEditMode->move(4, 4);
    label_mode->move(4, 690);
    btn_lastPage->move(80, 690);
    label_curPage->move(140, 690);
    btn_nextPage->move(200, 690);
    probar->move(260, 690);
}

void CustomTreeWidget::initUi(GlobalApplication* app)
{
    rootNoteditMode = new CustomTree(app, this);
    rootNoteditMode->seteditMode(false);
    rootNoteditMode->setStyleSheet("background-color:rgb(0,255,0);color:rgb(255,0,0)");
    rootNoteditMode->setHeaderLabels(QStringList{ "单词表", "联想词" });
    rootNoteditMode->setColumnCount(2);

    rootEditMode = new CustomTree(app, this);
    rootEditMode->seteditMode(true);
    rootEditMode->setStyleSheet("background-color:rgb(255,0,0);color:rgb(0,255,0)");
    rootEditMode->setHeaderLabels(QStringList{ "单词表", "联想词" });
    rootEditMode->setColumnCount(2);

    rootNoteditMode->setVisible(true);
    rootEditMode->setVisible(false);

    label_mode = new QLabel(this);
    label_mode->setFixedSize(60, 25);
    label_mode->setFont(QFont("微软雅黑", 10));
    label_mode->setAlignment(Qt::AlignCenter);
    label_mode->setText(editMode ? "edit" : "recite");
    label_mode->setStyleSheet("background-color:rgb(0,0,0);color:rgb(255,255,255)");

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

    probar = new QProgressBar(this);
    probar->setFixedSize(150, 25);
    probar->setOrientation(Qt::Orientation::Horizontal);
    probar->setValue(0);
    probar->setTextVisible(true);
    probar->setVisible(true);
}

void CustomTreeWidget::readConfig()
{
    //读配置文件
    QList<int> configParas = JsonOper::readConfig(configPath);
    curPageIndex = configParas.at(0);
    rootEditMode->setCurPageIndex(curPageIndex);
    rootNoteditMode->setCurPageIndex(curPageIndex);
    countWordList = configParas.at(1);
    rootEditMode->setCountWordList(countWordList);
    rootNoteditMode->setCountWordList(countWordList);
}

void CustomTreeWidget::createDirWordList()
{
    //创建wordlist目录
    QDir wordListDirTemp(wordListDir);
    if (!wordListDirTemp.exists())
    {
        wordListDirTemp.mkdir(wordListDir);
    }
}

void CustomTreeWidget::setEditMode(bool e)
{
	if (this->editMode != e)
	{
		this->editMode = e;
        if (this->editMode)
        {
            this->showWords();  //从Edit切换Recite时重新显示
            rootNoteditMode->stackUnder(rootEditMode);
            rootEditMode->setVisible(true);
            rootNoteditMode->setVisible(false);
        }
        else
        {
            this->showWords();  //从Edit切换Recite时重新显示
            rootEditMode->stackUnder(rootNoteditMode);
            rootNoteditMode->setVisible(true);
            rootEditMode->setVisible(false);
        }
	    emit editModeChanged(this->editMode);
	}
}

void CustomTreeWidget::setWordAddFillItemTop(Word* wd)
{
    if (wd)
    {
        rootEditMode->setAddItemTopLevel(wd);
    }
}

void CustomTreeWidget::setWordAddFillItemBottom(Word* wd)
{
    if (wd)
    {
        rootEditMode->setAddItemBottomLevel(wd);
    }
}

void CustomTreeWidget::setFocusOnCustomTree(QFocusEvent* event)
{
    if (editMode)
    {
        rootEditMode->setFocus();
    }
    else
    {
        rootNoteditMode->setFocus();
    }
}

void CustomTreeWidget::setConfigPath(const QString configPath)
{
    this->configPath = configPath;
}

void CustomTreeWidget::setWordListDir(const QString wordListDir)
{
    this->wordListDir = wordListDir;
}

void CustomTreeWidget::readWordListAll()
{
    QDir dir(this->wordListDir);
    if (!dir.exists())
    {
        dir.mkdir(this->wordListDir); //创建目录
    }

    

    if (curPageIndex > countWordList || curPageIndex < 0 || countWordList < 0)
    {
        return;
    }

    //若curPageIndex=countWordList=0，第一次打开，添加NaN到wordListAll
    if (curPageIndex == 0 && countWordList == 0)
    {
        Word wd;
        wd.pageIndex = 1;
        wd.spelling = "NaN";
        wd.meanings = QList<QString>{ "NaN" };
        wd.type = "NaN";
        wd.synonyms = QList<QString>{ "NaN" };
        wd.nearSynonyms = QList<QString>{ "NaN" };
        wd.antonyms = QList<QString>{ "NaN" };
        wd.similar = QList<QString>{ "NaN" };
        wd.noun = QList<QString>{ "NaN" };
        wd.verb = QList<QString>{ "NaN" };
        wd.adj = QList<QString>{ "NaN" };
        wd.adv = QList<QString>{ "NaN" };
        wd.usefulExpressions = QList<QString>{ "NaN" };

        wordListCurPage.insert(wd.spelling, wd);
        wordListAll->append(wordListCurPage);
        updateConfig(curPageIndex + 1, countWordList + 1);  //更新页码信息
        return;
        ////创建1.json，添加NaN单词
        //QHash<QString, Word> temp;
        //temp->insert(wd.spelling, wd);
        //JsonOper::writeWords(temp, wordListDir + "/" + "1.json");
    }

    //不是第一次打开，遍历wordList目录下所有json，添加1.json~countWordList.json到wordListAll
    QString curPageJsonPath;
    probar->setVisible(true);
    for (int i = 1; i <= countWordList; i++)
    {
        curPageJsonPath = this->wordListDir + "/" + QString::number(i) + ".json";
        JsonOper::readWords(&wordListCurPage, curPageJsonPath);
        wordListAll->append(wordListCurPage);
        probar->setValue(100 * i / countWordList);    //读取时进度条
    }
    //probar->setVisible(false);

    updateConfig(curPageIndex, wordListAll->count());
    wordListCurPage = (*wordListAll)[curPageIndex - 1];

    ////将当前页添加到wordListCurrentPage
    //wordListCurrentPage = (*wordListAll)[curPageIndex];

    //QFileInfoList fileInfoList = dir.entryInfoList();
    //for (auto item : fileInfoList)
    //{
    //    if (!item.isFile() || item.suffix().toLower() != "json")
    //    {
    //        continue;
    //    }

    //    QString jsonPath = item.absoluteFilePath();
    //    QFile jsonFile(jsonPath);
    //    if (!jsonFile.open(QFile::ReadOnly))
    //    {
    //        return;
    //    }
    //    QByteArray jsonArr = jsonFile.readAll();
    //    jsonFile.close();
    //    QJsonDocument doc = QJsonDocument::fromJson(jsonArr);
    //    if (!doc.isArray())
    //    {
    //        return;
    //    }

    //    QJsonObject obj = doc.object();
    //    QStringList keys = obj.keys();

    //    for (int i = 0; i < keys.count(); i++)
    //    {
    //        QString key = keys.at(i);
    //        QJsonValue value = obj.value(key);

    //        if (!value.isObject())
    //        {
    //            continue;
    //        }
    //        QJsonObject obj = value.toObject();
    //        Word wd = JsonOper::readWord(obj);
    //    }
    //}
}

void CustomTreeWidget::updateConfig(int curPage, int countWord)
{
    if (curPage == curPageIndex && countWord == countWordList) return;
    curPageIndex = curPage;
    rootEditMode->setCurPageIndex(curPageIndex);
    rootNoteditMode->setCurPageIndex(curPageIndex);
    
    countWordList = countWord;
    rootEditMode->setCountWordList(countWordList);
    rootNoteditMode->setCountWordList(countWordList);

    label_curPage->setText(QString::number(curPageIndex) + "/" + QString::number(countWordList));
    JsonOper::writeConfig(configPath, curPageIndex, countWordList);
}

void CustomTreeWidget::showWords()
{
    if (wordListAll == nullptr)
    {
        return;
    }

    if (editMode)   
    {
        rootEditMode->clear();  //清空树
        //编辑模式，显示分类，便于按分类编辑
        QHash<QString, Word> curPageWords = (*wordListAll)[curPageIndex - 1];
        QList<QString> keys = curPageWords.keys();
        for (int i = 0; i < keys.count(); i++)
        {
            QTreeWidgetItem* wordRoot = new QTreeWidgetItem();
            const Word wd = curPageWords.value(keys.at(i));
            wordRoot->setText(0, wd.spelling);
            //wordRoot->setData(0, Qt::UserRole, wd);

            QTreeWidgetItem* meanings = new QTreeWidgetItem();
            meanings->setText(0, "释义");
            for (auto item : wd.meanings)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                meanings->addChild(tempItem);
            }
            wordRoot->addChild(meanings);

            QTreeWidgetItem* partSpeech = new QTreeWidgetItem();
            partSpeech->setText(0, wd.type);
            wordRoot->addChild(partSpeech);


            QTreeWidgetItem* synonyms = new QTreeWidgetItem();
            synonyms->setText(0, "同义词");
            for (auto item : wd.synonyms)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                synonyms->addChild(tempItem);
            }
            wordRoot->addChild(synonyms);


            QTreeWidgetItem* anotonyms = new QTreeWidgetItem();
            anotonyms->setText(0, "反义词");
            for (auto item : wd.antonyms)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                anotonyms->addChild(tempItem);
            }
            wordRoot->addChild(anotonyms);


            QTreeWidgetItem* nearSynonyms = new QTreeWidgetItem();
            nearSynonyms->setText(0, "近义词");
            for (auto item : wd.nearSynonyms)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                nearSynonyms->addChild(tempItem);
            }
            wordRoot->addChild(nearSynonyms);


            QTreeWidgetItem* similars = new QTreeWidgetItem();
            similars->setText(0, "形近词");
            for (auto item : wd.similar)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                similars->addChild(tempItem);
            }
            wordRoot->addChild(similars);


            QTreeWidgetItem* noun = new QTreeWidgetItem();
            noun->setText(0, "名词");
            for (auto item : wd.noun)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                noun->addChild(tempItem);
            }
            wordRoot->addChild(noun);


            QTreeWidgetItem* verb = new QTreeWidgetItem();
            verb->setText(0, "动词");
            for (auto item : wd.verb)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                verb->addChild(tempItem);
            }
            wordRoot->addChild(verb);


            QTreeWidgetItem* adj = new QTreeWidgetItem();
            adj->setText(0, "形容词");
            for (auto item : wd.adj)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                adj->addChild(tempItem);
            }
            wordRoot->addChild(adj);


            QTreeWidgetItem* adv = new QTreeWidgetItem();
            adv->setText(0, "副词");
            for (auto item : wd.adv)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                adv->addChild(tempItem);
            }
            wordRoot->addChild(adv);


            QTreeWidgetItem* usefulExpressions = new QTreeWidgetItem();
            usefulExpressions->setText(0, "常用搭配");
            for (auto item : wd.usefulExpressions)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                usefulExpressions->addChild(tempItem);
            }
            wordRoot->addChild(usefulExpressions);

            rootEditMode->addTopLevelItem(wordRoot);
            rootEditMode->setItemSelected(wordRoot, true);  //选中
            rootEditMode->setFocus();
        }
    }
    else
    {
        rootNoteditMode->clear();   //清空树
        //显示模式：不显示分类
        QHash<QString, Word> curPageWords = (*wordListAll)[curPageIndex - 1];
        QList<QString> keys = curPageWords.keys();
        for (int i = 0; i < keys.count(); i++)
        {
            QTreeWidgetItem* wordRoot = new QTreeWidgetItem();
            const Word wd = curPageWords.value(keys.at(i));
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

            rootNoteditMode->addTopLevelItem(wordRoot);
            rootNoteditMode->setItemSelected(wordRoot, true);
            rootNoteditMode->setFocus();
        }
    }
}

void CustomTreeWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
}

void CustomTreeWidget::moveEvent(QMoveEvent* event)
{
    QWidget::moveEvent(event);
}

void CustomTreeWidget::onModeChanged(bool isEditMode)
{
    this->setEditMode(isEditMode);
    label_mode->setText(isEditMode ? "Edit" : "Recite");
}

void CustomTreeWidget::onSelectedWordChanged(Word wd)
{
    selectedWord = wd;
    emit selectedWordChanged(selectedWord);
}

void CustomTreeWidget::onCurPageIndexChanged(int newIndex)
{
    this->curPageIndex = newIndex;
}

void CustomTreeWidget::onCountWordListChanged(int newCount)
{
    this->countWordList = newCount;
}
