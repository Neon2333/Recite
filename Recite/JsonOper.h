#pragma once
#pragma execution_character_set("utf-8")

#include <QObject>
#include "word.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

///固定格式json文件解析类
class JsonOper  : public QObject
{
	Q_OBJECT

public:
	JsonOper(QObject *parent);
public:
    static int getObjectCount(QString jsonPath);   //获取json文件数组中元素个数

    static QList<int> readConfig(QString configPath);   //读取config.json，返回上次关闭时的页码

    static void writeConfig(QString configPath, int curPageIndex, int countWordList);         //将index写入config.json

    static void writeWords(QHash<QString,Word> words, QString jsonPath);    //清空当前json并写入
    
    static void appendWord(Word w, QString jsonPath);   //在json数组后面添加word

    static void insertWord(Word w, int index, QString jsonPath);    //把word添加到数组index位置

    static void updateWord(QString spelling, Word w, QString jsonPath);   //修改json文件某个word的属性

    static bool readWords(QHash<QString,Word>* words, QString jsonPath);  //读取json返回word列表

    static Word readWord(QJsonObject obj);  //从QJsonObject构建1个word

	~JsonOper();
};
