#include "CustomTree.h"

CustomTree::CustomTree(QWidget *parent)
	: QTreeWidget(parent)
{
    editable = false;
    curColumn = 0;
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


void CustomTree::removeItem(QTreeWidgetItem* item)
{
    int count = item->childCount();
    if (count == 0) {
        // 没有子节点，直接删除
        delete item;
        return;
    }
    for (int i = 0; i < count; i++) {
        QTreeWidgetItem* childItem = item->child(0); // 删除子节点
        removeItem(childItem);
    }
    delete item; // 最后将自己删除
}

void CustomTree::keyPressEvent(QKeyEvent * event)
{
    QList<QTreeWidgetItem*> selItems;
    //setCurrentItem(curItem, QItemSelectionModel::SelectCurrent);
    if (event->key() == Qt::Key_Left)
    {
        curColumn > 0 ? curColumn-- : curColumn;
        selItems = selectedItems();
        if (selItems.at(0))
        {
            if (selItems.at(0)->childCount() > 0)
            {
                //scrollToItem(selItems.at(0)->parent());
                selItems.at(0)->parent()->setExpanded(false);
                setItemSelected(selItems.at(0)->parent(), true);
            }
        }
    }
    else if (event->key() == Qt::Key_Right)
    {
        if (editable)
        {
            //3列
            curColumn < 2 ? curColumn++ : curColumn;
            selItems = selectedItems();
            if (selItems.at(0))
            {
                if (selItems.at(0)->childCount() > 0)
                {
                    scrollToItem(selItems.at(0)->child(0));
                    setItemSelected(selItems.at(0)->parent(), true);
                }
            }
        }
        else
        {
            //2列
            curColumn < 1 ? curColumn++ : curColumn;
            selItems = selectedItems();
            if (selItems.at(0))
            {
                if (selItems.at(0)->childCount() > 0)
                {
                    scrollToItem(selItems.at(0)->child(0));
                    setItemSelected(selItems.at(0)->parent(), true);
                }
            }
        }
    }
    else if (event->modifiers() & Qt::ControlModifier)
    {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)   //ctrl-enter选中
        {
            selItems = selectedItems();
            if (selItems.at(0))
            {
                scrollToItem(selItems.at(0));
                emit selWdChanged(selItems.at(0)->text(curColumn));
            }
        }
    }
    else if(event->modifiers() & Qt::AltModifier)   
    {
        if (editable)
        {
            if (event->key() == Qt::Key_A)  //增加（后面最好还是改成aa增加）
            {

            }
            else if (event->key() == Qt::Key_D) //删除(dd)
            {
                selItems = selectedItems();
                if (selItems.at(0))
                {
                    removeItem(selItems.at(0));
                }
            }
            else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)    //alt-enter修改（ww)
            {
                selItems = selectedItems();
                //curColumn = currentColumn();
                if (selItems.at(0))
                {
                    selItems.at(0)->setFlags(selItems.at(0)->flags() | Qt::ItemIsEditable);
                    selItems.at(0)->setSelected(true);
                    editItem(selItems.at(0), curColumn);
                }
            }
        }
    }
    else
    {
        QTreeWidget::keyPressEvent(event);
    }

}
