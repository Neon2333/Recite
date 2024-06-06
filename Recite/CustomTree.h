#pragma once

#include <QTreeWidget>
#include <QKeyEvent>
#include <QString>
#include <QMetaObject>
#include "Word.h"

class CustomTree : public QTreeWidget
{
	Q_OBJECT

public:
	CustomTree(QWidget *parent = nullptr);
	~CustomTree();

	
	void setEditable(bool e);

	bool getEditable();

	void setWords(QHash<QString, Word>* wds);

	void removeItemRecursion(QTreeWidgetItem* selItem);
	
	void addItem(QTreeWidgetItem* selItem);

	void setAddItemTopLevel(Word* wd);

	void setAddItemBottomLevel(Word* wd);


private:

	bool editable;

	QHash<QString, Word>* words;

	int selColumn;	

	Word* wordAddToTopLevel;	

	Word* wordAddToBottomLevel;	

	QTreeWidgetItem* itemAddToTopLevel;//ÒªÌí¼ÓµÄitem

	QTreeWidgetItem* itemAddToBottomLevel;

	void createItemTopFromWord(QTreeWidgetItem* wordRoot, Word* wd);

	void createItemBottomFromWord(QTreeWidgetItem* wordRoot, Word* wd);

	const QMetaObject* metaObject;

	void wordAdd(QHash<QString, Word>::iterator iter, QString category, QString item);
	void wordDel(QHash<QString, Word>::iterator iter, QString category, QString item);
	void wordModify(QHash<QString, Word>::iterator iter, QString category, QString item);

protected:
	virtual void keyPressEvent(QKeyEvent* event) override;
	
signals:
	void selWordChanged(QString wd);
	void wordAdded(bool isTopItem, QString wd, QString category);	
	void wordDeleted();
	void wordModified();

private slots:
	void onItemModified(QTreeWidgetItem* item, int col);
};
