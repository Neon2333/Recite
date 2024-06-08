#pragma once

#include <QWidget>
#include "ui_CustomTreeWidget.h"
#include "GlobalApplication.h"

#include "Word.h"
#include <QLayout>
#include <QTreeWidget>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QDir>
#include <QHash>

#include "CustomTree.h"
#include "JsonOper.h"


/// <summary>
/// mode1���������&wordListCurrentPage��2����ʾ
/// mode2���������&wordListCurrentPage��������ɾ����
/// mode3������word��ͬ��
/// </summary>
class CustomTreeWidget : public QWidget
{
	Q_OBJECT

public:
	CustomTreeWidget::CustomTreeWidget(GlobalApplication* a, QWidget* parent = nullptr);
	~CustomTreeWidget();

	void setSize(int w = 400, int h = 630);
	
	void setPos(int x, int y);

	void initUi(GlobalApplication* app);

	void setConfigPath(const QString configPath);

	void setWordListDir(const QString wordListDir);

	void readWordListAll();  //������������ȡ���е��ʱ����̣߳�

	void updateConfig(int curPage, int countWord);  //�޸������ļ�����ֹ����д�����ã�

	void readConfig();

	void createDirWordList();

	void setEditMode(bool editMode);

	void showWords();

	void setWordAddFillItemTop(Word* wd);

	void setWordAddFillItemBottom(Word* wd);

	void setFocusOnCustomTree(QFocusEvent* event);

private:
	Ui::CustomTreeWidgetClass ui;

	CustomTree* rootNoteditMode;	//recite
	CustomTree* rootEditMode;	//edit
	QLabel* label_mode;   //״̬
	QPushButton* btn_lastPage;  //��һҳ
	QPushButton* btn_nextPage;  //��һҳ
	QLabel* label_curPage;  //��ǰҳ
	QProgressBar* probar;   //������
	QTimer* timer_probar;       //���ƽ�������ʱ��


	QHash<QString, Word> wordListCurPage;   //��ǰ��һҳ�ĵ��ʱ���1��json��ȡ���ϼ�50������

	QList<QHash<QString, Word>>* wordListAll;   //��������json�ļ�����ȡ���е��ʣ����ڲ�ѯ��

	bool editMode;

	Word selectedWord;	//reciteʹ��

	int curPageIndex = 0;   //��ǰҳ�루�ı䣬Ҫд��config��
	
	int countWordList = 0;  //���ʱ�������ı䣬Ҫд��config��

	QString configPath;

	QString wordListDir;


protected:
	virtual void resizeEvent(QResizeEvent* event) override;
	virtual void moveEvent(QMoveEvent* event) override;

signals:
	void editModeChanged(bool isEditMode);
	void selectedWordChanged(Word wd);

public slots:
	void onModeChanged(bool isEditMode);
	void onSelectedWordChanged(Word wd);
	void onCurPageIndexChanged(int newIndex);
	void onCountWordListChanged(int newCount);

};
