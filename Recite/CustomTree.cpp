#include "CustomTree.h"
#include<QDebug>

CustomTree::CustomTree(QWidget *parent)
	: QTreeWidget(parent)
{
    editable = false;
    selColumn = 0;
    ItemAddToTopLevel = nullptr;
    ItemAddToBottomLevel = nullptr;
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


void CustomTree::removeItemRecursion(QTreeWidgetItem* item)
{
    int count = item->childCount();
    if (count == 0) {
        // 没有子节点，直接删除
        delete item;
        return;
    }
    for (int i = 0; i < count; i++) {
        QTreeWidgetItem* childItem = item->child(0); // 删除子节点
        removeItemRecursion(childItem);
    }
    delete item; // 最后将自己删除
}

void CustomTree::setAddItemTopLevel(QTreeWidgetItem* item)
{
    if (item != ItemAddToTopLevel)
    {
        ItemAddToTopLevel = item;
    }
}

void CustomTree::setAddItemBottomLevel(QTreeWidgetItem* item)
{
    if (item != ItemAddToBottomLevel)
    {
        ItemAddToBottomLevel = item;
    }
}

void CustomTree::addItem(QTreeWidgetItem* selItem)
{
    if (selItem->parent() == nullptr)
    {
        this->addTopLevelItem(ItemAddToTopLevel);
        setItemSelected(ItemAddToTopLevel, true);
    }
    else if (selItem->childCount() == 0)  
    {
        selItem->parent()->addChild(ItemAddToBottomLevel);
    }
}

void CustomTree::keyPressEvent(QKeyEvent * event)
{
    static int keyACount = 0;
    static int keyDCount = 0;
    static int keyWCount = 0;

    //QTreeWidget::keyPressEvent(event);  //使用原本的方向键功能
    
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
        //偷懒了：因为有子节点的item都在第一列显示，没有子节点的item都在第二列，所以这么写
        if (selItems.at(0) && selItems.at(0)->childCount() > 0)
        {
            if (selItems.at(0)->isExpanded())
            {
                /* scrollToItem(selItems.at(0)->child(0));
                 setItemSelected(selItems.at(0)->child(0), true);*/

                if (editable)
                {
                    //3列
                    selColumn < 2 ? selColumn++ : selColumn;

                }
                else
                {
                    //2列
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
    }

    else if (event->key() == Qt::Key_Down)
    {
        QTreeWidget::keyPressEvent(event);
    }

    else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return && !event->isAutoRepeat())
    {
        if (editable)
        {
            //确认修改
            QTreeWidget::keyPressEvent(event);
        }
        else
        {
            //显示
            selItems = selectedItems();
            if (selItems.count() == 0)
            {
                return;
            }
            if (selItems.at(0))
            {
                scrollToItem(selItems.at(0));
                emit selWdChanged(selItems.at(0)->text(selColumn));
            }
        }
    }

    //增加
    else if(editable && event->key()==Qt::Key_A && !event->isAutoRepeat())
    {
        keyDCount = 0;  //清空按键残留
        keyWCount = 0;
        keyACount++;

        if (keyACount == 2)  
        {
            selItems = selectedItems();
            if (selItems.count() == 0)
            {
                return;
            }
            addItem(selItems.at(0));
            keyACount = 0;
        }
    }

    //删除(dd)
    else if (editable && event->key() == Qt::Key_D && !event->isAutoRepeat()) 
    {
        keyACount = 0;
        keyWCount = 0;
        keyDCount++;

        if (keyDCount == 2)
        {
            selItems = selectedItems();
            if (selItems.count() == 0)
            {
                return;
            }
            if (selItems.at(0))
            {
                removeItemRecursion(selItems.at(0));
                keyDCount = 0;
            }
        }
    }

    //修改（ww)
    else if (event->key() == Qt::Key_W && !event->isAutoRepeat())    
    {
        keyACount = 0;
        keyDCount = 0;
        keyWCount++;

        if (keyWCount == 2)
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
                editItem(selItems.at(0), selColumn);
                keyWCount = 0;
            }
        }
    }

    else
    {
        QTreeWidget::keyPressEvent(event);
    }

}
