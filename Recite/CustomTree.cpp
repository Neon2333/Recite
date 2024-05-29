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
        // û���ӽڵ㣬ֱ��ɾ��
        delete item;
        return;
    }
    for (int i = 0; i < count; i++) {
        QTreeWidgetItem* childItem = item->child(0); // ɾ���ӽڵ�
        removeItem(childItem);
    }
    delete item; // ����Լ�ɾ��
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
            //3��
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
            //2��
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
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)   //ctrl-enterѡ��
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
            if (event->key() == Qt::Key_A)  //���ӣ�������û��Ǹĳ�aa���ӣ�
            {

            }
            else if (event->key() == Qt::Key_D) //ɾ��(dd)
            {
                selItems = selectedItems();
                if (selItems.at(0))
                {
                    removeItem(selItems.at(0));
                }
            }
            else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)    //alt-enter�޸ģ�ww)
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
