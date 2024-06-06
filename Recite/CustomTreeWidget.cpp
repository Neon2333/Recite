#include "CustomTreeWidget.h"

CustomTreeWidget::CustomTreeWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    editable = false;
	words = nullptr;

    rootNotEditable = new CustomTree(this);
    rootNotEditable->setEditable(false);
    rootNotEditable->setHeaderLabels(QStringList{ "单词表", "联想词" });
    rootNotEditable->setColumnCount(2);

    rootEditable = new CustomTree(this);
    rootEditable->setEditable(true);
    rootEditable->setHeaderLabels(QStringList{ "单词表", "联想词"});
    rootEditable->setColumnCount(2);
    
    rootEditable->stackUnder(rootNotEditable);
    rootNotEditable->setVisible(true);
    rootEditable->setVisible(false);

    connect(rootNotEditable, &CustomTree::selWordChanged, this, &CustomTreeWidget::onSelectedWordChanged);
    connect(rootEditable, &CustomTree::selWordChanged, this, &CustomTreeWidget::onSelectedWordChanged);

}


CustomTreeWidget::~CustomTreeWidget()
{}

void CustomTreeWidget::setSize(int w, int h)
{
    this->resize(w, h);
    rootNotEditable->resize(w - 4, h - 4);
    rootEditable->resize(w - 4, h - 4);
}

void CustomTreeWidget::setPos(int x, int y)
{
    this->move(x, y);
    rootNotEditable->move(4, 4);
    rootEditable->move(4, 4);
}

void CustomTreeWidget::setEditable(bool e)
{
	if (this->editable != e)
	{
		this->editable = e;
        if (this->editable)
        {
            rootEditable->setVisible(true);
            rootNotEditable->setVisible(false);
        }
        else
        {
            rootEditable->setVisible(false);
            rootNotEditable->setVisible(true);
        }
	}

	emit editableChanged();
}

void CustomTreeWidget::setWords(QHash<QString, Word>* wds)
{
    if (wds == nullptr)
        return;
    this->words = wds;
    rootEditable->setWords(wds);
}

void CustomTreeWidget::setWordAddFillItemTop(Word* wd)
{
    if (wd)
    {
        rootEditable->setAddItemTopLevel(wd);
    }
}

void CustomTreeWidget::setWordAddFillItemBottom(Word* wd)
{
    if (wd)
    {
        rootEditable->setAddItemBottomLevel(wd);
    }
}

void CustomTreeWidget::showWWords()
{
    if (words == nullptr)
    {
        return;
    }

    if (editable)   
    {
        //编辑模式，显示分类，便于按分类编辑
        for (auto iter = words->begin(); iter!=words->end();iter++)
        {
            QTreeWidgetItem* wordRoot = new QTreeWidgetItem();
            
            wordRoot->setText(0, iter->spelling);

            QTreeWidgetItem* meanings = new QTreeWidgetItem();
            meanings->setText(0, "释义");
            for (auto item : iter->meanings)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                meanings->addChild(tempItem);
            }
            wordRoot->addChild(meanings);

            QTreeWidgetItem* partSpeech = new QTreeWidgetItem();
            partSpeech->setText(0, iter->type);
            wordRoot->addChild(partSpeech);


            QTreeWidgetItem* synonyms = new QTreeWidgetItem();
            synonyms->setText(0, "同义词");
            for (auto item : iter->synonyms)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                synonyms->addChild(tempItem);
            }
            wordRoot->addChild(synonyms);


            QTreeWidgetItem* anotonyms = new QTreeWidgetItem();
            anotonyms->setText(0, "反义词");
            for (auto item : iter->antonyms)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                anotonyms->addChild(tempItem);
            }
            wordRoot->addChild(anotonyms);


            QTreeWidgetItem* nearSynonyms = new QTreeWidgetItem();
            nearSynonyms->setText(0, "近义词");
            for (auto item : iter->nearSynonyms)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                nearSynonyms->addChild(tempItem);
            }
            wordRoot->addChild(nearSynonyms);


            QTreeWidgetItem* similars = new QTreeWidgetItem();
            similars->setText(0, "形近词");
            for (auto item : iter->similar)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                similars->addChild(tempItem);
            }
            wordRoot->addChild(similars);


            QTreeWidgetItem* noun = new QTreeWidgetItem();
            noun->setText(0, "名词");
            for (auto item : iter->noun)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                noun->addChild(tempItem);
            }
            wordRoot->addChild(noun);


            QTreeWidgetItem* verb = new QTreeWidgetItem();
            verb->setText(0, "动词");
            for (auto item : iter->verb)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                verb->addChild(tempItem);
            }
            wordRoot->addChild(verb);


            QTreeWidgetItem* adj = new QTreeWidgetItem();
            adj->setText(0, "形容词");
            for (auto item : iter->adj)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                adj->addChild(tempItem);
            }
            wordRoot->addChild(adj);


            QTreeWidgetItem* adv = new QTreeWidgetItem();
            adv->setText(0, "副词");
            for (auto item : iter->adv)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                adv->addChild(tempItem);
            }
            wordRoot->addChild(adv);


            QTreeWidgetItem* usefulExpressions = new QTreeWidgetItem();
            usefulExpressions->setText(0, "常用搭配");
            for (auto item : iter->usefulExpressions)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                usefulExpressions->addChild(tempItem);
            }
            wordRoot->addChild(usefulExpressions);

            rootEditable->addTopLevelItem(wordRoot);
            wordRootsEditable.append(wordRoot);
        }
    }
    else
    {
        //显示模式：不显示分类
        for (auto iter=words->begin();iter!=words->end();iter++)
        {
            QTreeWidgetItem* wordRoot = new QTreeWidgetItem();
            wordRoot->setText(0, iter->spelling);

            for (auto item : iter->meanings)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                wordRoot->addChild(tempItem);
            }
            QTreeWidgetItem* wordTypeItem = new QTreeWidgetItem();
            wordTypeItem->setText(1, iter->type);
            wordRoot->addChild(wordTypeItem);
            for (auto item : iter->synonyms)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                wordRoot->addChild(tempItem);
            }
            for (auto item : iter->antonyms)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                wordRoot->addChild(tempItem);
            }
            for (auto item : iter->nearSynonyms)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                wordRoot->addChild(tempItem);
            }
            for (auto item : iter->similar)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                wordRoot->addChild(tempItem);
            }
            for (auto item : iter->noun)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                wordRoot->addChild(tempItem);
            }
            for (auto item : iter->verb)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                wordRoot->addChild(tempItem);
            }
            for (auto item : iter->adj)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                wordRoot->addChild(tempItem);
            }
            for (auto item : iter->adv)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                wordRoot->addChild(tempItem);
            }
            for (auto item : iter->usefulExpressions)
            {
                QTreeWidgetItem* tempItem = new QTreeWidgetItem();
                tempItem->setText(1, item);
                wordRoot->addChild(tempItem);
            }

            rootNotEditable->addTopLevelItem(wordRoot);
            wordRootsNotEditable.append(wordRoot);
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

void CustomTreeWidget::keyPressEvent(QKeyEvent* event)
{

}

void CustomTreeWidget::onSelectedWordChanged(QString wd)
{
    selectedWord = wd;
    emit selectedWordChanged(selectedWord);
}

