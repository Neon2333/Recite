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

	void setCurPageIndex(int pageIndex);

	void setWords(QList<QHash<QString, Word>>* wds);

	void removeItemRecursion(QTreeWidgetItem* selItem);
	
	void addItem(QTreeWidgetItem* selItem);

	void setAddItemTopLevel(Word* wd);

	void setAddItemBottomLevel(Word* wd);


private:

	bool editable;

	int curPageIndex = 0;

	//QHash<QString, Word>* words;
	QList<QHash<QString, Word>>* words;

	int selColumn;	

	Word* wordAddToTopLevel;	

	Word* wordAddToBottomLevel;	

	QTreeWidgetItem* itemAddToTopLevel;//ÒªÌí¼ÓµÄitem

	QTreeWidgetItem* itemAddToBottomLevel;

	void createItemTopFromWord(QTreeWidgetItem* wordRoot, Word* wd);

	void createItemBottomFromWord(QTreeWidgetItem* wordRoot, Word* wd);

	bool addButNotModified;
	void wordAdd(QHash<QString, Word>::iterator& iter, QString category, QString item);
	void wordDel(QHash<QString, Word>::iterator& iter, QString category, QString item);
	QString spellingBeforeModified;
	QString topSpellingOfModifiedItem;
	QString categoryOfModifiedItem;
	void wordModify(QHash<QString, Word>::iterator& iter, QString category, QString item);

protected:
	virtual void keyPressEvent(QKeyEvent* event) override;
	
signals:
	void selWordChanged(Word wd);

private slots:
	void onItemModified(QTreeWidgetItem* item, int col);
};
