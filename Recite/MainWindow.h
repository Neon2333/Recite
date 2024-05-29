#pragma once
#pragma execution_character_set("utf-8")

#include <QMainWindow>
#include "GlobalApplication.h"
#include "Word.h"
#include "JsonOper.h"

#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QWidget>
#include <QLayout>
#include <QTreeWidget>
#include <QHash>
#include <QStandardItemModel>
#include <QProgressBar>

#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFileInfoList>

#include <QKeyEvent>
#include <QCloseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QHBoxLayout* layout_main;    //整体布局，网格
    QWidget* widget_main;   //整体

    QVBoxLayout* layout_left;    //左侧布局
    QWidget* widget_left;   //左侧整体

    QHBoxLayout* layout_leftLine1;
    QWidget* widget_leftLine1;
    QTreeWidget* treeWidget_wordsTree; //树形单词表
    QStandardItemModel* model;

    QHBoxLayout* layout_leftLine2;
    QWidget* widget_leftLine2;

    QHBoxLayout* layout_leftLine3;
    QWidget* widget_leftLine3;

    QPushButton* btn_lastPage;  //上一页
    QPushButton* btn_nextPage;  //下一页
    QLabel* label_curPage;  //当前页
    QProgressBar* probar;   //进度条
    QLabel* label_status;   //状态

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
    bool editMode = false;      //处于编辑模式
    GlobalApplication* app;     

    QHash<QString, Word>* wordListCurrentPage;   //当前这一页的单词表，从1个json读取，合计50个单词
    QHash<QString, Word>* wordListAll;   //加载所有json文件，读取所有单词，用于查询。
    const QString wordListDir = QCoreApplication::applicationDirPath() + "/WordList";  //单词表目录

    const QString configPath = QCoreApplication::applicationDirPath() + "/config.json";    //配置文件路径
    int curPageIndex = 0;   //当前页码（改变，要写入config）
    int countWordList = 0;  //单词表个数（改变，要写入config）

    Word selectedWord;      //当前选中的词

    QTimer* timer_probar;       //控制进度条计时器

private:
    void init();    //初始化

    void initMainWindow();  //初始化页面，创建控件

    void connectEvents();   //所有信号和handler绑定

    void readWordListCurrentPage();    //按照index读取当前页的json存储到WordListCurrentPage

    void updateConfig(int curPage, int countWord);  //修改配置文件（防止忘记写入配置）

    void readWordListAll(QString jsonDir);  //程序启动，读取所有单词表（子线程）

    void treeShowCurrentPageModeEdit();   //(Edit)树形显示WordListCurrentPage

    void addWordToTreeModeEdit(Word wd); //(Edit)添加1个词到树状目录

    void treeShowCurrentPageModeRecite();   //(Recite)树形显示WordListCurrentPage
    
    void addWordToTreeModeRecite(Word wd); //(Edit)添加1个词到树状目录
    
    Word searchWordListAll(QString spelling);   //从wordListAll中查找词

    void showSelectedWord();     //右侧显示选中词

    void expandWord(Word wd);    //展开树状目录中某个词的所有属性

    void collapaseWord(Word wd); //折叠某个词的所有属性


signals:
    void modeChanged(bool isEditMode);


public slots:
    void onModeChanged(bool isEditMode);
    void onKeyIPressed();
    void onKeyRPressed();
    void onKeyEnterPressed();
    void onKeyCtrlEnterPressed();

protected:
    //void keyPressEvent(QKeyEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

public:
    MainWindow(GlobalApplication* app, QWidget* parent = nullptr);
    ~MainWindow();

    void editModeSetter(bool isEditMode);

};
