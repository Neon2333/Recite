#pragma once

#include <QWidget>
#include "ui_CustomTreeWidget.h"
#include "Word.h"
#include <QTreeWidget>
#include "CustomTree.h"

/// <summary>
/// mode1���������&wordListCurrentPage��2����ʾ
/// mode2���������&wordListCurrentPage��������ɾ����
/// mode3������word��ͬ��
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
	/// �ô����word���һ��editģʽ�µ�itemTop
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
	Word selectedWord;	//reciteʹ��
	

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
