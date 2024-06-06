#include "CustomTree.h"
#include<QDebug>

CustomTree::CustomTree(QWidget *parent)
	: QTreeWidget(parent)
{
    editable = false;
    selColumn = 0;
    itemAddToTopLevel = new QTreeWidgetItem();
    itemAddToBottomLevel = new QTreeWidgetItem();

    addButNotModified = false;
    spellingBeforeModified = "";
    topSpellingOfModifiedItem = "";
    categoryOfModifiedItem = "";

    connect(this, &QTreeWidget::itemChanged, this, &CustomTree::onItemModified);

}

CustomTree::~CustomTree()
{}

void CustomTree::setEditable(bool e)
{
    editable = e;

}

bool CustomTree::getEditable()
{
    return editable;
}

void CustomTree::setCurPageIndex(int pageIndex)
{
    this->curPageIndex = pageIndex;
}

void CustomTree::setWords(QList<QHash<QString, Word>>* wds)
{
    if (wds == nullptr)
        return;
    this->words = wds;
}

void CustomTree::removeItemRecursion(QTreeWidgetItem* selItem)
{
    QHash<QString, Word>& curPageWords = (*words)[curPageIndex];
    
    int count = selItem->childCount();
    if (count == 0) {
        // û���ӽڵ㣬ֱ��ɾ��
        auto iter = curPageWords.find(selItem->parent()->parent()->text(0));
        QString category = selItem->parent()->text(0);
        wordDel(iter, category, selItem->text(1));
        delete selItem;
        return;
    }
    for (int i = 0; i < count; i++) {
        QTreeWidgetItem* childItem = selItem->child(0); // ɾ���ӽڵ�
        removeItemRecursion(childItem);
    }
    curPageWords.remove(selItem->text(0));
    delete selItem; // ����Լ�ɾ��
}

void CustomTree::addItem(QTreeWidgetItem* selItem)
{
    QHash<QString, Word>& curPageWords = (*words)[curPageIndex];

    if (selItem->parent() == nullptr)
    {
        if (addButNotModified)
        {
            return;
        }
        this->addTopLevelItem(itemAddToTopLevel);
        setItemSelected(itemAddToTopLevel, true);
        if (curPageWords.count() <= 60)
        {
            curPageWords.insert(wordAddToTopLevel->spelling, wordAddToTopLevel);
        }
        else
        {
            //add a json
            //countWordList++
        }

    }
    else if (selItem->childCount() == 0)
    {
        selItem->parent()->addChild(itemAddToBottomLevel);
        setItemSelected(itemAddToBottomLevel, true);
        auto iter = curPageWords.find(selItem->parent()->parent()->text(0));
        QString category = selItem->parent()->text(0);
        wordAdd(iter, category, wordAddToBottomLevel->spelling);
    }
}

void CustomTree::setAddItemTopLevel(Word* wd)
{
    if (wd != wordAddToTopLevel)
    {
        wordAddToTopLevel = wd;
        createItemTopFromWord(itemAddToTopLevel, wd);
    }
}

void CustomTree::setAddItemBottomLevel(Word* wd)
{
    if (wd != wordAddToBottomLevel)
    {
        wordAddToBottomLevel = wd;
        createItemTopFromWord(itemAddToBottomLevel, wd);
    }
}

void CustomTree::createItemTopFromWord(QTreeWidgetItem* wordRoot, Word* wd)
{
    wordRoot->setText(0, wd->spelling);

    QTreeWidgetItem* meanings = new QTreeWidgetItem();
    meanings->setText(0, "����");
    for (auto item : wd->meanings)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        meanings->addChild(tempItem);
    }
    wordRoot->addChild(meanings);

    QTreeWidgetItem* partSpeech = new QTreeWidgetItem();
    partSpeech->setText(0, wd->type);
    wordRoot->addChild(partSpeech);


    QTreeWidgetItem* synonyms = new QTreeWidgetItem();
    synonyms->setText(0, "ͬ���");
    for (auto item : wd->synonyms)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        synonyms->addChild(tempItem);
    }
    wordRoot->addChild(synonyms);


    QTreeWidgetItem* anotonyms = new QTreeWidgetItem();
    anotonyms->setText(0, "�����");
    for (auto item : wd->antonyms)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        anotonyms->addChild(tempItem);
    }
    wordRoot->addChild(anotonyms);


    QTreeWidgetItem* nearSynonyms = new QTreeWidgetItem();
    nearSynonyms->setText(0, "�����");
    for (auto item : wd->nearSynonyms)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        nearSynonyms->addChild(tempItem);
    }
    wordRoot->addChild(nearSynonyms);


    QTreeWidgetItem* similars = new QTreeWidgetItem();
    similars->setText(0, "�ν���");
    for (auto item : wd->similar)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        similars->addChild(tempItem);
    }
    wordRoot->addChild(similars);


    QTreeWidgetItem* noun = new QTreeWidgetItem();
    noun->setText(0, "����");
    for (auto item : wd->noun)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        noun->addChild(tempItem);
    }
    wordRoot->addChild(noun);


    QTreeWidgetItem* verb = new QTreeWidgetItem();
    verb->setText(0, "����");
    for (auto item : wd->verb)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        verb->addChild(tempItem);
    }
    wordRoot->addChild(verb);


    QTreeWidgetItem* adj = new QTreeWidgetItem();
    adj->setText(0, "���ݴ�");
    for (auto item : wd->adj)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        adj->addChild(tempItem);
    }
    wordRoot->addChild(adj);


    QTreeWidgetItem* adv = new QTreeWidgetItem();
    adv->setText(0, "����");
    for (auto item : wd->adv)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        adv->addChild(tempItem);
    }
    wordRoot->addChild(adv);


    QTreeWidgetItem* usefulExpressions = new QTreeWidgetItem();
    usefulExpressions->setText(0, "���ô���");
    for (auto item : wd->usefulExpressions)
    {
        QTreeWidgetItem* tempItem = new QTreeWidgetItem();
        tempItem->setText(1, item);
        usefulExpressions->addChild(tempItem);
    }
    wordRoot->addChild(usefulExpressions);
}

void CustomTree::createItemBottomFromWord(QTreeWidgetItem* wordRoot, Word* wd)
{
    wordRoot->setText(1, wd->spelling);
}

void CustomTree::wordAdd(QHash<QString,Word>::iterator& iter, QString category, QString item)
{
    if (category == "����")
    {
        iter->meanings.append(item);
    }
    else if (category == "ͬ���")
    {
        iter->synonyms.append(item);
    }
    else if (category == "�����")
    {
        iter->antonyms.append(item);
    }
    else if (category == "�����")
    {
        iter->nearSynonyms.append(item);
    }
    else if (category == "�ν���")
    {
        iter->similar.append(item);
    }
    else if (category == "����")
    {
        iter->noun.append(item);
    }
    else if (category == "����")
    {
        iter->verb.append(item);
    }
    else if (category == "���ݴ�")
    {
        iter->adj.append(item);
    }
    else if (category == "����")
    {
        iter->adv.append(item);
    }
    else if (category == "���ô���")
    {
        iter->usefulExpressions.append(item);
    }
}

void CustomTree::wordDel(QHash<QString, Word>::iterator& iter, QString category, QString item)
{
    if (category == "����")
    {
        iter->meanings.removeOne(item);
    }
    else if (category == "ͬ���")
    {
        iter->synonyms.removeOne(item);
    }
    else if (category == "�����")
    {
        iter->antonyms.removeOne(item);
    }
    else if (category == "�����")
    {
        iter->nearSynonyms.removeOne(item);
    }
    else if (category == "�ν���")
    {
        iter->similar.removeOne(item);
    }
    else if (category == "����")
    {
        iter->noun.removeOne(item);
    }
    else if (category == "����")
    {
        iter->verb.removeOne(item);
    }
    else if (category == "���ݴ�")
    {
        iter->adj.removeOne(item);
    }
    else if (category == "����")
    {
        iter->adv.removeOne(item);
    }
    else if (category == "���ô���")
    {
        iter->usefulExpressions.removeOne(item);
    }
}

void CustomTree::wordModify(QHash<QString, Word>::iterator& iter, QString category, QString item)
{
    if (category == "����")
    {
        iter->meanings.replace(iter->meanings.indexOf(item), item);
    }
    else if (category == "ͬ���")
    {
        iter->synonyms.replace(iter->meanings.indexOf(item), item);
    }
    else if (category == "�����")
    {
        iter->antonyms.replace(iter->meanings.indexOf(item), item);
    }
    else if (category == "�����")
    {
        iter->nearSynonyms.replace(iter->meanings.indexOf(item), item);
    }
    else if (category == "�ν���")
    {
        iter->similar.replace(iter->meanings.indexOf(item), item);
    }
    else if (category == "����")
    {
        iter->noun.replace(iter->meanings.indexOf(item), item);
    }
    else if (category == "����")
    {
        iter->verb.replace(iter->meanings.indexOf(item), item);
    }
    else if (category == "���ݴ�")
    {
        iter->adj.replace(iter->meanings.indexOf(item), item);
    }
    else if (category == "����")
    {
        iter->adv.replace(iter->meanings.indexOf(item), item);
    }
    else if (category == "���ô���")
    {
        iter->usefulExpressions.replace(iter->meanings.indexOf(item), item);
    }
}

void CustomTree::keyPressEvent(QKeyEvent * event)
{
    static int keyAPressCount = 0;
    static int keyDPressCount = 0;
    static int keyWPressCount = 0;

    QList<QTreeWidgetItem*> selItems;

    if (event->key() == Qt::Key_Left && !event->isAutoRepeat())
    {
        QTreeWidget::keyPressEvent(event);

        selItems = selectedItems();
        if (selItems.count() == 0)
        {
            return;
        }

        if (selItems.at(0))
        {
            if (selItems.at(0)->childCount() > 0)
            {
                selColumn = 0;
            }
            else
            {
                selColumn = 1;
            }
        }
    }

    else if (event->key() == Qt::Key_Right && !event->isAutoRepeat())
    {
        QTreeWidget::keyPressEvent(event);
        
        selItems = selectedItems();
        if (selItems.count() == 0)
        {
            return;
        }

#if 0
        //͵���ˣ���Ϊ���ӽڵ��item���ڵ�һ����ʾ��û���ӽڵ��item���ڵڶ��У�������ôд
        if (selItems.at(0) && selItems.at(0)->childCount() > 0)
        {
            if (selItems.at(0)->isExpanded())
            {
                /* scrollToItem(selItems.at(0)->child(0));
                 setItemSelected(selItems.at(0)->child(0), true);*/

                if (editable)
                {
                    //3��
                    selColumn < 2 ? selColumn++ : selColumn;

                }
                else
                {
                    //2��
                    selColumn < 1 ? selColumn++ : selColumn;
                }
            }
        }
#endif

        if (selItems.at(0))
        {
            if (selItems.at(0)->childCount() > 0)
            {
                selColumn = 0;
            }
            else
            {
                selColumn = 1;
            }
        }
    }

    else if (event->key() == Qt::Key_Up && !event->isAutoRepeat())
    {
        QTreeWidget::keyPressEvent(event);

        selItems = selectedItems();
        if (selItems.count() == 0)
        {
            return;
        }

        if (selItems.at(0))
        {
            if (selItems.at(0)->childCount() > 0)
            {
                selColumn = 0;
            }
            else
            {
                selColumn = 1;
            }
        }
    }

    else if (event->key() == Qt::Key_Down)
    {
        QTreeWidget::keyPressEvent(event);

        selItems = selectedItems();
        if (selItems.count() == 0)
        {
            return;
        }

        if (selItems.at(0))
        {
            if (selItems.at(0)->childCount() > 0)
            {
                selColumn = 0;
            }
            else
            {
                selColumn = 1;
            }
        }
    }

    else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return && !event->isAutoRepeat())
    {
        if (editable)
        {
            //ȷ���޸�
            QTreeWidget::keyPressEvent(event);
        }
        else
        {
            //��ʾ
            selItems = selectedItems();
            if (selItems.count() == 0)
            {
                return;
            }
            if (selItems.at(0))
            {
                scrollToItem(selItems.at(0));
                Word selWord = (*words)[curPageIndex][selItems.at(0)->text(selColumn)];
                emit selWordChanged(selWord);
            }
        }
    }

    //����
    else if(editable && event->key()==Qt::Key_A && !event->isAutoRepeat())
    {
        if(!editable)   return;
            
        keyDPressCount = 0;  //��հ�������
        keyWPressCount = 0;
        keyAPressCount++;

        if (keyAPressCount == 1)
        {
            selItems = selectedItems();
            if (selItems.count() == 0)
            {
                return;
            }
            addItem(selItems.at(0));
            keyAPressCount = 0;
        }
    }

    //ɾ��(dd)
    else if (editable && event->key() == Qt::Key_D && !event->isAutoRepeat()) 
    {
        if (!editable)   return;

        keyAPressCount = 0;
        keyWPressCount = 0;
        keyDPressCount++;

        if (keyDPressCount == 1)
        {
            selItems = selectedItems();
            if (selItems.count() == 0)
            {
                return;
            }
            if (selItems.at(0))
            {
                removeItemRecursion(selItems.at(0));
                keyDPressCount = 0;
            }
        }
    }

    //�޸ģ�ww)
    else if (event->key() == Qt::Key_W && !event->isAutoRepeat())    
    {
        if (!editable)   return;

        keyAPressCount = 0;
        keyDPressCount = 0;
        keyWPressCount++;

        if (keyWPressCount == 1)
        {
            selItems = selectedItems();
            if (selItems.count() == 0)
            {
                return;
            }
            if (selItems.at(0))
            {
                selItems.at(0)->setFlags(selItems.at(0)->flags() | Qt::ItemIsEditable);
                selItems.at(0)->setSelected(true);
                if (selItems.at(0)->parent() == nullptr)
                {
                    spellingBeforeModified = selItems.at(0)->text(0);
                }
                else if (selItems.at(0)->childCount() == 0)
                {
                    topSpellingOfModifiedItem = selItems.at(0)->parent()->parent()->text(0);
                    categoryOfModifiedItem = selItems.at(0)->parent()->text(0);
                    spellingBeforeModified = selItems.at(0)->text(1);
                }
                editItem(selItems.at(0), selColumn);
                keyWPressCount = 0;
            }
        }
    }

    else
    {
        QTreeWidget::keyPressEvent(event);
    }

}

void CustomTree::onItemModified(QTreeWidgetItem* item, int col)
{
    if (item->parent() == nullptr)
    {
        (*words)[curPageIndex][spellingBeforeModified].spelling = item->text(col);
    }
    else if (item->childCount() == 0)
    {
        auto iter = (*words)[curPageIndex].find(topSpellingOfModifiedItem);
        wordModify(iter, categoryOfModifiedItem, spellingBeforeModified);
    }
}
