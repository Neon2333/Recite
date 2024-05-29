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

	void setWords(QList<Word>* wds);

	void showWWords();

	void onSelectedWordChanged(QString wd);

private:
	Ui::CustomTreeWidgetClass ui;

	bool editable;

	QList<Word>* words;

	QString selectedWord;
	
	CustomTree* rootNotEditable;	//�Ǳ༭ģʽ

	QList< QTreeWidgetItem*> rootChildren;

	CustomTree* rootEditable;	//�༭ģʽ

	QList<QTreeWidgetItem*> wordRoots;

protected:
	virtual void resizeEvent(QResizeEvent* event) override;
	virtual void moveEvent(QMoveEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;


signals:
	void editableChanged();
	void selectedWordChanged(QString wd);

public slots:

};
