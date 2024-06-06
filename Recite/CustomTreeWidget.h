#pragma once

#include <QWidget>
#include "ui_CustomTreeWidget.h"
#include "Word.h"
#include <QTreeWidget>
#include "CustomTree.h"

/// <summary>
/// mode1：传入参数&wordListCurrentPage，2列显示
/// mode2：传入参数&wordListCurrentPage，可增、删、改
/// mode3：传入word，同上
/// </summary>
class CustomTreeWidget : public QWidget
{
	Q_OBJECT

public:
	CustomTreeWidget(QWidget *parent = nullptr);
	~CustomTreeWidget();

	void setSize(int w = 400, int h = 630);
	
	void setPos(int x, int y);

	void setEditable(bool editable);

	void setWords(QList<QHash<QString, Word>>* wds);

	void showWords();

	/// <summary>
	/// 用传入的word填充一个edit模式下的itemTop
	/// </summary>
	/// <param name="wordRoot"></param>
	/// <param name="wd"></param>
	void setWordAddFillItemTop(Word* wd);

	void setWordAddFillItemBottom(Word* wd);


private:
	Ui::CustomTreeWidgetClass ui;

	//QHash<QString, Word>* words;
	QList<QHash<QString, Word>>* words;

	bool editable;

	int curPageIndex;  

	CustomTree* rootNotEditable;	//recite
	QList<QTreeWidgetItem*> wordRootsNotEditable;
	Word selectedWord;	//recite使用
	

	CustomTree* rootEditable;	//edit
	QList<QTreeWidgetItem*> wordRootsEditable;

protected:
	virtual void resizeEvent(QResizeEvent* event) override;
	virtual void moveEvent(QMoveEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;


signals:
	void editableChanged();
	void selectedWordChanged(Word wd);

public slots:
	void onSelectedWordChanged(Word wd);
};
