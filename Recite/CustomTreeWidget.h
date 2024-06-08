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
/// mode1：传入参数&wordListCurrentPage，2列显示
/// mode2：传入参数&wordListCurrentPage，可增、删、改
/// mode3：传入word，同上
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

	void readWordListAll();  //程序启动，读取所有单词表（子线程）

	void updateConfig(int curPage, int countWord);  //修改配置文件（防止忘记写入配置）

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
	QLabel* label_mode;   //状态
	QPushButton* btn_lastPage;  //上一页
	QPushButton* btn_nextPage;  //下一页
	QLabel* label_curPage;  //当前页
	QProgressBar* probar;   //进度条
	QTimer* timer_probar;       //控制进度条计时器


	QHash<QString, Word> wordListCurPage;   //当前这一页的单词表，从1个json读取，合计50个单词

	QList<QHash<QString, Word>>* wordListAll;   //加载所有json文件，读取所有单词，用于查询。

	bool editMode;

	Word selectedWord;	//recite使用

	int curPageIndex = 0;   //当前页码（改变，要写入config）
	
	int countWordList = 0;  //单词表个数（改变，要写入config）

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
