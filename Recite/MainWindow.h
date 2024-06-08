#pragma once
#pragma execution_character_set("utf-8")

#include <QMainWindow>
#include <QTextEdit>
#include <QWidget>
#include <QCoreApplication>
#include "Word.h"
#include "CustomTreeWidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QHBoxLayout* layout_main;    //整体布局，网格
    QWidget* widget_main;   //整体

    QVBoxLayout* layout_left;    //左侧布局
    QWidget* widget_left;   //左侧整体

    CustomTreeWidget* wordsTree;

    QVBoxLayout* layout_right;    //右侧布局，垂直
    QWidget* widget_right;   //右侧整体

    QHBoxLayout* layout_rightLine1;    //右侧第一行布局，水平
    QWidget* widget_spelling;   //右侧第一行
    QLabel* label_spelling;  //拼写
    QTextEdit* textEdit_meanings;   //释义
    QLabel* label_partOfSpeech;   //词性

    QHBoxLayout* layout_rightLine2;    //右侧第二行布局，水平
    QWidget* widget_synonyms;   //右侧第二行
    QTextEdit* textEdit_synonyms;   //同义词
    QTextEdit* textEdit_nearSynonyms;   //近义词
    QTextEdit* textEdit_antonym;   //反义词
    QTextEdit* textEdit_similar;   //形近词

    QHBoxLayout* layout_rightLine3;    //右侧第三行布局，水平
    QWidget* widget_noun;   //右侧第三行
    QTextEdit* textEdit_noun;   //名词
    QTextEdit* textEdit_verb;   //动词
    QTextEdit* textEdit_adj;   //形容词
    QTextEdit* textEdit_adv;   //副词

    QHBoxLayout* layout_rightLine4;    //右侧第三行布局，垂直
    QWidget* widget_usefulExpressions;   //右侧第四行
    QTextEdit* textEdit_usefulExpressions;   //常用搭配

private:
    GlobalApplication* app;    
    
    const QString wordListDir = QCoreApplication::applicationDirPath() + "/WordList";  //单词表目录
    const QString configPath = QCoreApplication::applicationDirPath() + "/config.json";    //配置文件路径

    bool editMode = false;      //处于编辑模式

private:

    void initUi();  //初始化页面，创建控件

    void connectEvents();   //所有信号和handler绑定

    void showSelectedWord(Word selectedWord);     //右侧显示选中词

public slots:
    void onModeChanged(bool isEditMode);
protected:
    void MainWindow::focusInEvent(QFocusEvent* event) override;
public:
    MainWindow(GlobalApplication* app, QWidget* parent = nullptr);
    ~MainWindow();
};
