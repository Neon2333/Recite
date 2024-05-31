#pragma once

#include <QTreeWidget>
#include <QKeyEvent>
#include <QString>
class CustomTree : public QTreeWidget
{
	Q_OBJECT

public:
	CustomTree(QWidget *parent = nullptr);
	~CustomTree();

	/// <summary>
	/// 设置是否编辑模式
	/// </summary>
	/// <param name="e"></param>
	void setEditable(bool e);

	/// <summary>
	/// 返回是否编辑模式
	/// </summary>
	/// <returns></returns>
	bool getEditable();

	/// <summary>
	/// 递归移除指定item下所有item
	/// </summary>
	/// <param name="item"></param>
	void removeItemRecursion(QTreeWidgetItem* item);

	void setAddItemTopLevel(QTreeWidgetItem* item);

	void setAddItemBottomLevel(QTreeWidgetItem* item);

	void addItem(QTreeWidgetItem* selItem);

private:

	bool editable;

	/// <summary>
	/// 当前选中item的显示所在column
	/// </summary>
	int selColumn;	

	QTreeWidgetItem* ItemAddToTopLevel;	//要添加的item
	QTreeWidgetItem* ItemAddToBottomLevel;	



protected:
	virtual void keyPressEvent(QKeyEvent* event) override;

signals:
	void selWdChanged(QString newWd);
};
