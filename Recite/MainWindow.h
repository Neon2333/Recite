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
    QHBoxLayout* layout_main;    //���岼�֣�����
    QWidget* widget_main;   //����

    QVBoxLayout* layout_left;    //��಼��
    QWidget* widget_left;   //�������

    QHBoxLayout* layout_leftLine1;
    QWidget* widget_leftLine1;
    QTreeWidget* treeWidget_wordsTree; //���ε��ʱ�
    QStandardItemModel* model;

    QHBoxLayout* layout_leftLine2;
    QWidget* widget_leftLine2;

    QHBoxLayout* layout_leftLine3;
    QWidget* widget_leftLine3;

    QPushButton* btn_lastPage;  //��һҳ
    QPushButton* btn_nextPage;  //��һҳ
    QLabel* label_curPage;  //��ǰҳ
    QProgressBar* probar;   //������
    QLabel* label_status;   //״̬

    QVBoxLayout* layout_right;    //�Ҳ಼�֣���ֱ
    QWidget* widget_right;   //�Ҳ�����

    QHBoxLayout* layout_rightLine1;    //�Ҳ��һ�в��֣�ˮƽ
    QWidget* widget_spelling;   //�Ҳ��һ��
    QLabel* label_spelling;  //ƴд
    QTextEdit* textEdit_meanings;   //����
    QLabel* label_partOfSpeech;   //����

    QHBoxLayout* layout_rightLine2;    //�Ҳ�ڶ��в��֣�ˮƽ
    QWidget* widget_synonyms;   //�Ҳ�ڶ���
    QTextEdit* textEdit_synonyms;   //ͬ���
    QTextEdit* textEdit_nearSynonyms;   //�����
    QTextEdit* textEdit_antonym;   //�����
    QTextEdit* textEdit_similar;   //�ν���

    QHBoxLayout* layout_rightLine3;    //�Ҳ�����в��֣�ˮƽ
    QWidget* widget_noun;   //�Ҳ������
    QTextEdit* textEdit_noun;   //����
    QTextEdit* textEdit_verb;   //����
    QTextEdit* textEdit_adj;   //���ݴ�
    QTextEdit* textEdit_adv;   //����

    QHBoxLayout* layout_rightLine4;    //�Ҳ�����в��֣���ֱ
    QWidget* widget_usefulExpressions;   //�Ҳ������
    QTextEdit* textEdit_usefulExpressions;   //���ô���

private:
    bool editMode = false;      //���ڱ༭ģʽ
    GlobalApplication* app;     

    QHash<QString, Word>* wordListCurrentPage;   //��ǰ��һҳ�ĵ��ʱ���1��json��ȡ���ϼ�50������
    QHash<QString, Word>* wordListAll;   //��������json�ļ�����ȡ���е��ʣ����ڲ�ѯ��
    const QString wordListDir = QCoreApplication::applicationDirPath() + "/WordList";  //���ʱ�Ŀ¼

    const QString configPath = QCoreApplication::applicationDirPath() + "/config.json";    //�����ļ�·��
    int curPageIndex = 0;   //��ǰҳ�루�ı䣬Ҫд��config��
    int countWordList = 0;  //���ʱ�������ı䣬Ҫд��config��

    Word selectedWord;      //��ǰѡ�еĴ�

    QTimer* timer_probar;       //���ƽ�������ʱ��

private:
    void init();    //��ʼ��

    void initMainWindow();  //��ʼ��ҳ�棬�����ؼ�

    void connectEvents();   //�����źź�handler��

    void readWordListCurrentPage();    //����index��ȡ��ǰҳ��json�洢��WordListCurrentPage

    void updateConfig(int curPage, int countWord);  //�޸������ļ�����ֹ����д�����ã�

    void readWordListAll(QString jsonDir);  //������������ȡ���е��ʱ����̣߳�

    void treeShowCurrentPageModeEdit();   //(Edit)������ʾWordListCurrentPage

    void addWordToTreeModeEdit(Word wd); //(Edit)���1���ʵ���״Ŀ¼

    void treeShowCurrentPageModeRecite();   //(Recite)������ʾWordListCurrentPage
    
    void addWordToTreeModeRecite(Word wd); //(Edit)���1���ʵ���״Ŀ¼
    
    Word searchWordListAll(QString spelling);   //��wordListAll�в��Ҵ�

    void showSelectedWord();     //�Ҳ���ʾѡ�д�

    void expandWord(Word wd);    //չ����״Ŀ¼��ĳ���ʵ���������

    void collapaseWord(Word wd); //�۵�ĳ���ʵ���������


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
