#pragma once

#include <QTreeWidget>
#include "ui_CustomTree.h"
#include <QKeyEvent>
#include <QString>
class CustomTree : public QTreeWidget
{
	Q_OBJECT

public:
	CustomTree(QWidget *parent = nullptr);
	~CustomTree();

	void setEditable(bool e);

	bool getEditable();

private:
	Ui::CustomTreeClass ui;

	bool editable;
	//自己管理当前选中item的column出于2个原因：（1）int col = currentColumn();在通过左右方向键进入和离开子节点时不改变；
	//（2）要在editable可编辑模式下，不能编辑第1列（3列中间那列写的是类别）
	int curColumn;	

	void removeItem(QTreeWidgetItem* item);

protected:
	virtual void keyPressEvent(QKeyEvent* event) override;

signals:
	void selWdChanged(QString newWd);
};
