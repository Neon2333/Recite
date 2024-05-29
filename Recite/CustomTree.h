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
	//�Լ�����ǰѡ��item��column����2��ԭ�򣺣�1��int col = currentColumn();��ͨ�����ҷ����������뿪�ӽڵ�ʱ���ı䣻
	//��2��Ҫ��editable�ɱ༭ģʽ�£����ܱ༭��1�У�3���м�����д�������
	int curColumn;	

	void removeItem(QTreeWidgetItem* item);

protected:
	virtual void keyPressEvent(QKeyEvent* event) override;

signals:
	void selWdChanged(QString newWd);
};
