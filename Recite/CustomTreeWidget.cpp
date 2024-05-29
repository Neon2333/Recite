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

    connect(rootNotEditable, &CustomTree::selWdChanged, this, &CustomTreeWidget::onSelectedWordChanged);
    connect(rootEditable, &CustomTree::selWdChanged, this, &CustomTreeWidget::onSelectedWordChanged);

    /*wordRoot = nullptr;
    meanings = nullptr;
    partSpeech = nullptr;
    synonyms = nullptr;
    anotonyms = nullptr;
    nearSynonyms = nullptr;
    similars = nullptr;
    noun = nullptr;
    verb = nullptr;
    adj = nullptr;
    adv = nullptr;
    usefulExpressions = nullptr;*/

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

void CustomTreeWidget::setWords(QList<Word>* wds)
{
    if (wds == nullptr)
        return;
    this->words = wds;
}

void CustomTreeWidget::showWWords()
{
    if (words == nullptr)
    {
        return;
    }

    if (editable)
    {
        for (int i = 0; i < words->count(); i++)
        {
            Word wd = words->at(i);

            QTreeWidgetItem* wordRoot = new QTreeWidgetItem();
            wordRoot->setText(0, wd.spelling);

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

           /* wordRoot->addChildren(QList<QTreeWidgetItem*>{meanings, partSpeech,
                synonyms, anotonyms, nearSynonyms, similars,
                noun, verb, adj, adv,
                usefulExpressions});*/
            rootEditable->addTopLevelItem(wordRoot);
            wordRoots.append(wordRoot);
        }
    }
    else
    {
        for (int i = 0; i < words->count(); i++)
        {
            Word wd = words->at(i);

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

            rootNotEditable->addTopLevelItem(wordRoot);
            rootChildren.append(wordRoot);
        }
    }
}
void CustomTreeWidget::onSelectedWordChanged(QString wd)
{
    selectedWord = wd;
    emit selectedWordChanged(selectedWord);
}
//
//void CustomTreeWidget::setSelectedWord(QString wd)
//{
//    if (wd != selectedWord)
//    {
//        selectedWord = wd;
//        
//        emit selectedWordChanged(selectedWord);
//    }
//}

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
