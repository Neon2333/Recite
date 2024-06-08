#pragma once
#pragma execution_character_set("utf-8")

#include <QObject>
#include "word.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

///�̶���ʽjson�ļ�������
class JsonOper  : public QObject
{
	Q_OBJECT

public:
	JsonOper(QObject *parent);
public:
    static int getObjectCount(QString jsonPath);   //��ȡjson�ļ�������Ԫ�ظ���

    static QList<int> readConfig(QString configPath);   //��ȡconfig.json�������ϴιر�ʱ��ҳ��

    static void writeConfig(QString configPath, int curPageIndex, int countWordList);         //��indexд��config.json

    static void writeWords(QHash<QString,Word> words, QString jsonPath);    //��յ�ǰjson��д��
    
    static void appendWord(Word w, QString jsonPath);   //��json����������word

    static void insertWord(Word w, int index, QString jsonPath);    //��word��ӵ�����indexλ��

    static void updateWord(QString spelling, Word w, QString jsonPath);   //�޸�json�ļ�ĳ��word������

    static bool readWords(QHash<QString,Word>* words, QString jsonPath);  //��ȡjson����word�б�

    static Word readWord(QJsonObject obj);  //��QJsonObject����1��word

	~JsonOper();
};
