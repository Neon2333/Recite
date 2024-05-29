#pragma once

#include <QWidget>
#include "ui_CustomTreeWidget.h"
#include "Word.h"
#include <QTreeWidget>

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

private:
	Ui::CustomTreeWidgetClass ui;

	bool editable;

	QList<Word>* words;

	//�Ǳ༭ģʽ
	QTreeWidget* rootNotEditable;
	QList< QTreeWidgetItem*> rootChildren;

	//�༭ģʽ
	QTreeWidget* rootEditable;

	QList<QTreeWidgetItem*> wordRoots;

	/*QTreeWidgetItem* meanings;
	QList< QTreeWidgetItem*> meaningsChildren;

	QTreeWidgetItem* partSpeech;

	QTreeWidgetItem* synonyms;
	QList< QTreeWidgetItem*> synonymsChildren;

	QTreeWidgetItem* anotonyms;
	QList< QTreeWidgetItem*> anotonymsChildren;

	QTreeWidgetItem* nearSynonyms;
	QList< QTreeWidgetItem*> nearSynonymsChildren;

	QTreeWidgetItem* similars;
	QList< QTreeWidgetItem*> similarsChildren;

	QTreeWidgetItem* noun;
	QList< QTreeWidgetItem*> nounChildren;

	QTreeWidgetItem* verb;
	QList< QTreeWidgetItem*> verbChildren;

	QTreeWidgetItem* adj;
	QList< QTreeWidgetItem*> adjChildren;

	QTreeWidgetItem* adv;
	QList< QTreeWidgetItem*> advChildren;

	QTreeWidgetItem* usefulExpressions;
	QList< QTreeWidgetItem*> usefulExpressionsChildren;*/


protected:
	virtual void resizeEvent(QResizeEvent* event) override;
	virtual void moveEvent(QMoveEvent* event) override;

signals:
	void editableChanged();
};
