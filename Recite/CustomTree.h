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
	/// �����Ƿ�༭ģʽ
	/// </summary>
	/// <param name="e"></param>
	void setEditable(bool e);

	/// <summary>
	/// �����Ƿ�༭ģʽ
	/// </summary>
	/// <returns></returns>
	bool getEditable();

	/// <summary>
	/// �ݹ��Ƴ�ָ��item������item
	/// </summary>
	/// <param name="item"></param>
	void removeItemRecursion(QTreeWidgetItem* item);

	void setAddItemTopLevel(QTreeWidgetItem* item);

	void setAddItemBottomLevel(QTreeWidgetItem* item);

	void addItem(QTreeWidgetItem* selItem);

private:

	bool editable;

	/// <summary>
	/// ��ǰѡ��item����ʾ����column
	/// </summary>
	int selColumn;	

	QTreeWidgetItem* ItemAddToTopLevel;	//Ҫ��ӵ�item
	QTreeWidgetItem* ItemAddToBottomLevel;	



protected:
	virtual void keyPressEvent(QKeyEvent* event) override;

signals:
	void selWdChanged(QString newWd);
};
