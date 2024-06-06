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

	void setWords(QHash<QString, Word>* wds);

	/// <summary>
	/// �ô����word���һ��editģʽ�µ�itemTop
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

	QString selectedWord;	//reciteģʽʹ��
	
	CustomTree* rootNotEditable;	//reciteģʽ

	QList<QTreeWidgetItem*> wordRootsNotEditable;

	CustomTree* rootEditable;	//editģʽ

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
