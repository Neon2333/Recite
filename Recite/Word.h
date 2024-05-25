#pragma once
#pragma execution_character_set("utf-8")

#include <QObject>
#include<QString>
#include<QStringList>
#include <QJsonObject>

class Word  : public QObject
{
	Q_OBJECT

public:
	Word(QObject *parent);
    
    Word();
	Word(int pageIndex, QString spelling);
    Word(const Word& another);
    Word& operator=(const Word& another);
	~Word();

public:
    int pageIndex;      //所属json的index
    QString spelling;   //拼写
    QList<QString> meanings;    //释义
    QString type;       //词性
    QList<QString> synonyms;    //同义词
    QList<QString> antonyms;     //反义词
    QList<QString> nearSynonyms;    //近义词
    QList<QString> similar;     //形近词
    QList<QString> noun;    //名词
    QList<QString> verb;    //动词
    QList<QString> adj;     //形容词
    QList<QString> adv;     //副词
    QList<QString> usefulExpressions;   //常用搭配

};
