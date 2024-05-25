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
    int pageIndex;      //����json��index
    QString spelling;   //ƴд
    QList<QString> meanings;    //����
    QString type;       //����
    QList<QString> synonyms;    //ͬ���
    QList<QString> antonyms;     //�����
    QList<QString> nearSynonyms;    //�����
    QList<QString> similar;     //�ν���
    QList<QString> noun;    //����
    QList<QString> verb;    //����
    QList<QString> adj;     //���ݴ�
    QList<QString> adv;     //����
    QList<QString> usefulExpressions;   //���ô���

};
