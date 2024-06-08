#pragma once

#include <QTreeWidget>
#include <QKeyEvent>
#include <QString>
#include <QMetaObject>
#include "Word.h"
#include "GlobalApplication.h"


class CustomTree : public QTreeWidget
{
	Q_OBJECT

public:
	CustomTree(GlobalApplication* a, QWidget* parent = nullptr);

	~CustomTree();
	
	void seteditMode(bool e);
	bool geteditMode();

	void setCurPageIndex(int pageIndex);
	int getCurPageIndex();

	void setCountWordList(int countWordList);
	int getCountWordList();

	void setWordsList(QList<QHash<QString, Word>>* wds);

	void removeItemRecursion(QTreeWidgetItem* selItem);
	
	void addItem(QTreeWidgetItem* selItem);

	void setAddItemTopLevel(Word* wd);

	void setAddItemBottomLevel(Word* wd);


private:

	bool isEditMode;

	int curPageIndex = 0;   //当前页码（改变，要写入config）

	int countWordList = 0;  //单词表个数（改变，要写入config）

	QList<QHash<QString, Word>>* wordsList;

	int selColumn;	

	Word* wordAddToTopLevel;	

	Word* wordAddToBottomLevel;	

	QTreeWidgetItem* itemAddToTopLevel;	//要添加的item

	QTreeWidgetItem* itemAddToBottomLevel;

	void createItemTopFromWord(QTreeWidgetItem* wordRoot, Word* wd);

	void createItemBottomFromWord(QTreeWidgetItem* wordRoot, Word* wd);

	void wordAdd(QHash<QString, Word>::iterator& iter, QString category, QString item);
	void wordDel(QHash<QString, Word>::iterator& iter, QString category, QString item);
	QString spellingBeforeModified;
	QString topSpellingOfModifiedItem;
	QString categoryOfModifiedItem;
	void wordModify(QHash<QString, Word>::iterator& iter, QString category, QString item);

protected:
	virtual void keyPressEvent(QKeyEvent* event) override;
	
signals:
	void modeChanged(bool isEditMode);
	void selWordChanged(Word wd);
	void curPageIndexChanged(int newIndex);
	void countWordListChanged(int newCount);

private slots:
	void onKeyIPressed();
	void onKeyRPressed();
	void onItemModified(QTreeWidgetItem* item, int col);
};
