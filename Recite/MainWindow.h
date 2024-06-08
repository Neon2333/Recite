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
    QHBoxLayout* layout_main;    //���岼�֣�����
    QWidget* widget_main;   //����

    QVBoxLayout* layout_left;    //��಼��
    QWidget* widget_left;   //�������

    CustomTreeWidget* wordsTree;

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
    GlobalApplication* app;    
    
    const QString wordListDir = QCoreApplication::applicationDirPath() + "/WordList";  //���ʱ�Ŀ¼
    const QString configPath = QCoreApplication::applicationDirPath() + "/config.json";    //�����ļ�·��

    bool editMode = false;      //���ڱ༭ģʽ

private:

    void initUi();  //��ʼ��ҳ�棬�����ؼ�

    void connectEvents();   //�����źź�handler��

    void showSelectedWord(Word selectedWord);     //�Ҳ���ʾѡ�д�

public slots:
    void onModeChanged(bool isEditMode);
protected:
    void MainWindow::focusInEvent(QFocusEvent* event) override;
public:
    MainWindow(GlobalApplication* app, QWidget* parent = nullptr);
    ~MainWindow();
};
