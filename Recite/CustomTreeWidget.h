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

	void setWords(QHash<QString, Word>* wds);

	/// <summary>
	/// 用传入的word填充一个edit模式下的itemTop
	/// </summary>
	/// <param name="wordRoot"></param>
	/// <param name="wd"></param>
	void setWordAddFillItemTop(Word* wd);

	void setWordAddFillItemBottom(Word* wd);

	void showWWords();

private:
	Ui::CustomTreeWidgetClass ui;

	bool editable;

	QHash<QString, Word>* words;

	QString selectedWord;	//recite模式使用
	
	CustomTree* rootNotEditable;	//recite模式

	QList<QTreeWidgetItem*> wordRootsNotEditable;

	CustomTree* rootEditable;	//edit模式

	QList<QTreeWidgetItem*> wordRootsEditable;

protected:
	virtual void resizeEvent(QResizeEvent* event) override;
	virtual void moveEvent(QMoveEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;


signals:
	void editableChanged();
	void selectedWordChanged(QString wd);

public slots:
	void onSelectedWordChanged(QString wd);
};
