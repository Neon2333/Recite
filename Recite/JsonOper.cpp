#include "JsonOper.h"


JsonOper::JsonOper(QObject *parent)
	: QObject(parent)
{}

int JsonOper::getObjectCount(QString jsonPath)
{
    //读取已存在的json文件
    QFile jsonFile(jsonPath);
    if(!jsonFile.open(QFile::ReadOnly))
    {
        //ReadOnly，文件不存在不创建，返回false
        return -1;
    }
    QByteArray jsonStrOld = jsonFile.readAll();
    jsonFile.close();

    //反序列化为document
    QJsonDocument doc = QJsonDocument::fromJson(jsonStrOld);
    //因为规定了json是array类型
    if(!doc.isArray())
    {
        return -1;
    }
    //转成array
    QJsonArray jsonArr = doc.array();

    return jsonArr.count();
}

void JsonOper::writeConfig(QString configPath, int curPageIndex, int countWordList)
{
    //判断是否存在，不存在直接写，存在则先读取再写（修改）
    QJsonObject obj;
    obj.insert("curPageIndex", curPageIndex);
    obj.insert("countWordList", countWordList);

    QJsonDocument doc(obj);

    QFile configFile(configPath);
    if(!configFile.open(QFile::WriteOnly))
    {
        return;
    }

    configFile.write(doc.toJson());
    configFile.close();
}

QList<int> JsonOper::readConfig(QString configPath)
{
    //判断配置文件是否存在（第一次运行），没有则创建,写入0,0
    //有，则读取
    QFile configFile(configPath);
    if(!configFile.exists())
    {
        configFile.close();
        JsonOper::writeConfig(configPath,0,0);
        return QList<int>{0, 0};
    }
    else
    {
        if(!configFile.open(QFile::ReadOnly))
        {
            return QList<int>{-1,-1};
        }

        QByteArray jsonStr = configFile.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(jsonStr);

        if(!doc.isObject())
        {
            return QList<int>{-1,-1};
        }

        QJsonObject obj = doc.object();
        return QList<int>{obj.value("curPageIndex").toInt(), obj.value("countWordList").toInt()};
    }
}

void JsonOper::writeWords(const QHash<QString,Word> words, QString jsonPath)
{
    QJsonArray root;
    QList<QString> keys = words.keys();
    for(int i=0;i< keys.count();i++)
    {
        QJsonObject obj;
        const Word w = words.value(keys.at(i));
        obj.insert("pageIndex", w.pageIndex);
        obj.insert("spelling", w.spelling);

        QJsonArray meaningArr;
        for(int i=0;i<w.meanings.count();i++)
        {
            meaningArr.append(w.meanings.at(i));
        }
        obj.insert("meanings", meaningArr);

        obj.insert("type", w.type);

        QJsonArray synonymsArr;
        for(int i=0;i<w.synonyms.count();i++)
        {
            synonymsArr.append(w.synonyms.at(i));
        }
        obj.insert("synonyms",synonymsArr);

        QJsonArray antonymArr;
        for(int i=0;i<w.antonyms.count();i++)
        {
            antonymArr.append(w.antonyms.at(i));
        }
        obj.insert("antonym",antonymArr);

        QJsonArray nearSynonymsArr;
        for(int i=0;i<w.nearSynonyms.count();i++)
        {
            nearSynonymsArr.append(w.nearSynonyms.at(i));
        }
        obj.insert("nearSynonyms",nearSynonymsArr);

        QJsonArray similarArr;
        for(int i=0;i<w.similar.count();i++)
        {
            similarArr.append(w.similar.at(i));
        }
        obj.insert("similar",similarArr);

        QJsonArray nounArr;
        for(int i=0;i<w.noun.count();i++)
        {
            nounArr.append(w.noun.at(i));
        }
        obj.insert("noun",nounArr);

        QJsonArray verbArr;
        for(int i=0;i<w.verb.count();i++)
        {
            verbArr.append(w.verb.at(i));
        }
        obj.insert("verb",verbArr);

        QJsonArray adjArr;
        for(int i=0;i<w.adj.count();i++)
        {
            adjArr.append(w.adj.at(i));
        }
        obj.insert("adj",adjArr);

        QJsonArray advArr;
        for(int i=0;i<w.adv.count();i++)
        {
            advArr.append(w.adv.at(i));
        }
        obj.insert("adv",advArr);

        QJsonArray usefulExpressionsArr;
        for(int i=0;i<w.usefulExpressions.count();i++)
        {
            usefulExpressionsArr.append(w.usefulExpressions.at(i));
        }
        obj.insert("usefulExpressions",usefulExpressionsArr);

        root.append(obj);
    }

    QJsonDocument doc(root);
    QByteArray jsonStr = doc.toJson();

    QFile jsonFile(jsonPath);

    if(!jsonFile.open(QFile::WriteOnly)){
        //WriteOnly，文件不存在会创建
        return;
    }

    jsonFile.write(jsonStr);
    jsonFile.close();
}

void JsonOper::insertWord(Word w, int index, QString jsonPath)
{
    //读取已存在的json文件
    QFile jsonFile(jsonPath);
    if(!jsonFile.open(QFile::ReadOnly))
    {
        //ReadOnly，文件不存在不创建，返回false
        return;
    }
    QByteArray jsonStrOld = jsonFile.readAll();
    jsonFile.close();

    // //反序列化为document
    QJsonDocument doc = QJsonDocument::fromJson(jsonStrOld);
    //因为规定了json是array类型
    if(!doc.isArray())
    {
        return;
    }
    //转成array
    QJsonArray jsonArr = doc.array();

    //创建1个object。把要append的word转成object。
    QJsonObject objInsert;
    objInsert.insert("pageIndex",w.pageIndex);
    objInsert.insert("spelling", w.spelling);

    QJsonArray meaningArr;
    for(int i=0;i<w.meanings.count();i++)
    {
        meaningArr.append(w.meanings.at(i));
    }
    objInsert.insert("meanings", meaningArr);

    objInsert.insert("type", w.type);

    QJsonArray synonymsArr;
    for(int i=0;i<w.synonyms.count();i++)
    {
        synonymsArr.append(w.synonyms.at(i));
    }
    objInsert.insert("synonyms",synonymsArr);

    QJsonArray antonymArr;
    for(int i=0;i<w.antonyms.count();i++)
    {
        antonymArr.append(w.antonyms.at(i));
    }
    objInsert.insert("antonym",antonymArr);

    QJsonArray nearSynonymsArr;
    for(int i=0;i<w.nearSynonyms.count();i++)
    {
        nearSynonymsArr.append(w.nearSynonyms.at(i));
    }
    objInsert.insert("nearSynonyms",nearSynonymsArr);

    QJsonArray similarArr;
    for(int i=0;i<w.similar.count();i++)
    {
        similarArr.append(w.similar.at(i));
    }
    objInsert.insert("similar",similarArr);

    QJsonArray nounArr;
    for(int i=0;i<w.noun.count();i++)
    {
        nounArr.append(w.noun.at(i));
    }
    objInsert.insert("noun",nounArr);

    QJsonArray verbArr;
    for(int i=0;i<w.verb.count();i++)
    {
        verbArr.append(w.verb.at(i));
    }
    objInsert.insert("verb",verbArr);

    QJsonArray adjArr;
    for(int i=0;i<w.adj.count();i++)
    {
        adjArr.append(w.adj.at(i));
    }
    objInsert.insert("adj",adjArr);

    QJsonArray advArr;
    for(int i=0;i<w.adv.count();i++)
    {
        advArr.append(w.adv.at(i));
    }
    objInsert.insert("adv",advArr);

    QJsonArray usefulExpressionsArr;
    for(int i=0;i<w.usefulExpressions.count();i++)
    {
        usefulExpressionsArr.append(w.usefulExpressions.at(i));
    }
    objInsert.insert("usefulExpressions",usefulExpressionsArr);

    //将新建的object添加到array[index]
    jsonArr.insert(index, objInsert);

    // 将修改后的JSON数组设置回JSON文档
    doc.setArray(jsonArr);
    //序列化成字符串
    QByteArray jsonStrNew = doc.toJson();


    //字符串写入文件
    if(!jsonFile.open(QFile::WriteOnly))
    {
        return;
    }

    jsonFile.write(jsonStrNew);
    jsonFile.close();
}

void JsonOper::appendWord(Word w, QString jsonPath)
{
    QFile jsonFile(jsonPath);
    //读取已有json文件
    if(!jsonFile.open(QFile::ReadOnly))
    {
        //ReadOnly，文件不存在不创建，返回false
        return;
    }
    QByteArray jsonStrOld = jsonFile.readAll();
    jsonFile.close();

    // //反序列化为document
    QJsonDocument doc = QJsonDocument::fromJson(jsonStrOld);
    //因为规定了json是array类型
    if(!doc.isArray())
    {
        return;
    }
    //转成array
    QJsonArray jsonArr = doc.array();

    //创建1个object。把要append的word转成object。
    QJsonObject objAppend;
    objAppend.insert("pageIndex", w.pageIndex);
    objAppend.insert("spelling", w.spelling);

    QJsonArray meaningArr;
    for(int i=0;i<w.meanings.count();i++)
    {
        meaningArr.append(w.meanings.at(i));
    }
    objAppend.insert("meanings", meaningArr);

    objAppend.insert("type", w.type);

    QJsonArray synonymsArr;
    for(int i=0;i<w.synonyms.count();i++)
    {
        synonymsArr.append(w.synonyms.at(i));
    }
    objAppend.insert("synonyms",synonymsArr);

    QJsonArray antonymArr;
    for(int i=0;i<w.antonyms.count();i++)
    {
        antonymArr.append(w.antonyms.at(i));
    }
    objAppend.insert("antonym",antonymArr);

    QJsonArray nearSynonymsArr;
    for(int i=0;i<w.nearSynonyms.count();i++)
    {
        nearSynonymsArr.append(w.nearSynonyms.at(i));
    }
    objAppend.insert("nearSynonyms",nearSynonymsArr);

    QJsonArray similarArr;
    for(int i=0;i<w.similar.count();i++)
    {
        similarArr.append(w.similar.at(i));
    }
    objAppend.insert("similar",similarArr);

    QJsonArray nounArr;
    for(int i=0;i<w.noun.count();i++)
    {
        nounArr.append(w.noun.at(i));
    }
    objAppend.insert("noun",nounArr);

    QJsonArray verbArr;
    for(int i=0;i<w.verb.count();i++)
    {
        verbArr.append(w.verb.at(i));
    }
    objAppend.insert("verb",verbArr);

    QJsonArray adjArr;
    for(int i=0;i<w.adj.count();i++)
    {
        adjArr.append(w.adj.at(i));
    }
    objAppend.insert("adj",adjArr);

    QJsonArray advArr;
    for(int i=0;i<w.adv.count();i++)
    {
        advArr.append(w.adv.at(i));
    }
    objAppend.insert("adv",advArr);

    QJsonArray usefulExpressionsArr;
    for(int i=0;i<w.usefulExpressions.count();i++)
    {
        usefulExpressionsArr.append(w.usefulExpressions.at(i));
    }
    objAppend.insert("usefulExpressions",usefulExpressionsArr);

    //将新建的object添加到array末尾
    jsonArr.append(objAppend);

    // 将修改后的JSON数组设置回JSON文档
    doc.setArray(jsonArr);
    //序列化成字符串
    QByteArray jsonStrNew = doc.toJson();


    //字符串写入文件
    if(!jsonFile.open(QFile::WriteOnly))
    {
        return;
    }

    jsonFile.write(jsonStrNew);
    jsonFile.close();
}

void JsonOper::updateWord(QString spelling, Word w, QString jsonPath)
{
    if(w.spelling!=spelling)
    {
        return; //改词的属性，但是不能把词的spelling给改了。改spelling是一个新的词。
    }

    //读取已存在的json文件
    QFile jsonFile(jsonPath);
    if(!jsonFile.open(QFile::ReadOnly))
    {
        //ReadOnly，文件不存在不创建，返回false
        return;
    }
    QByteArray jsonStrOld = jsonFile.readAll();
    jsonFile.close();

    // //反序列化为document
    QJsonDocument doc = QJsonDocument::fromJson(jsonStrOld);
    //因为规定了json是array类型
    if(!doc.isArray())
    {
        return;
    }
    //转成array
    QJsonArray jsonArr = doc.array();

    int index=0;
    for(int i=0;i<jsonArr.count();i++)
    {
        QJsonValue updateObject = jsonArr.at(i);
        if(!updateObject.isObject())
        {
            return;
        }
        QJsonObject temp = updateObject.toObject();
        if(temp.value("spelling") == spelling)
        {
            //把找到的object删掉
            jsonArr.removeAt(i);
            index=i;
            break;
        }
    }

    doc.setArray(jsonArr);
    if(!jsonFile.open(QFile::WriteOnly))
    {
        return;
    }
    jsonFile.write(doc.toJson());
    jsonFile.close();

    //在i位置前添加新的word
    insertWord(w, index, jsonPath);
}

Word JsonOper::readWord(QJsonObject obj)
{
    Word wordTemp;

    wordTemp.pageIndex = obj.value("pageIndex").toInt();

    wordTemp.spelling=obj.value("spelling").toString();

    QJsonArray meaningArr = obj.value("meanings").toArray();

    for(int i=0;i<meaningArr.count();i++)
    {
        QJsonValue val = meaningArr.at(i);
        if(!val.isString())
        {
            return Word(-1, "");
        }
        wordTemp.meanings.append(val.toString());
    }

    wordTemp.type=obj.value("type").toString();

    QJsonArray synonymsArr = obj.value("synonyms").toArray();
    for(int i=0;i<synonymsArr.count();i++)
    {
        QJsonValue val = synonymsArr.at(i);
        if(!val.isString())
        {
            return Word(-1, "");
        }
        wordTemp.synonyms.append(val.toString());
    }

    QJsonArray antonymsArr = obj.value("antonyms").toArray();
    for(int i=0;i<antonymsArr.count();i++)
    {
        QJsonValue val = antonymsArr.at(i);
        if(!val.isString())
        {
            return Word(-1, "");
        }
        wordTemp.antonyms.append(val.toString());
    }

    QJsonArray nearSynonymsArr = obj.value("nearSynonyms").toArray();
    for(int i=0;i<nearSynonymsArr.count();i++)
    {
        QJsonValue val = nearSynonymsArr.at(i);
        if(!val.isString())
        {
            return Word(-1, "");
        }
        wordTemp.nearSynonyms.append(val.toString());
    }

    QJsonArray similarArr = obj.value("similar").toArray();
    for(int i=0;i<similarArr.count();i++)
    {
        QJsonValue val = similarArr.at(i);
        if(!val.isString())
        {
            return Word(-1, "");
        }
        wordTemp.similar.append(val.toString());
    }

    QJsonArray nounArr = obj.value("noun").toArray();
    for(int i=0;i<nounArr.count();i++)
    {
        QJsonValue val = nounArr.at(i);
        if(!val.isString())
        {
            return Word(-1, "");
        }
        wordTemp.noun.append(val.toString());
    }

    QJsonArray verbArr = obj.value("verb").toArray();
    for(int i=0;i<nounArr.count();i++)
    {
        QJsonValue val = verbArr.at(i);
        if(!val.isString())
        {
            return Word(-1, "");
        }
        wordTemp.verb.append(val.toString());
    }

    QJsonArray adjArr = obj.value("adj").toArray();
    for(int i=0;i<adjArr.count();i++)
    {
        QJsonValue val = adjArr.at(i);
        if(!val.isString())
        {
            return Word(-1, "");
        }
        wordTemp.adj.append(val.toString());
    }

    QJsonArray advArr = obj.value("adv").toArray();
    for(int i=0;i<advArr.count();i++)
    {
        QJsonValue val = advArr.at(i);
        if(!val.isString())
        {
            return Word(-1, "");
        }
        wordTemp.adv.append(val.toString());
    }

    QJsonArray usefulExpressionsArr = obj.value("usefulExpressions").toArray();
    for(int i=0;i<usefulExpressionsArr.count();i++)
    {
        QJsonValue val = usefulExpressionsArr.at(i);
        if(!val.isString())
        {
            return Word(-1, "");
        }
        wordTemp.usefulExpressions.append(val.toString());
    }

    return wordTemp;
}

bool JsonOper::readWords(QHash<QString, Word>* words, QString jsonPath)
{
    if (words == nullptr)  return false;

    QFile jsonFile(jsonPath);
    if(!jsonFile.open(QFile::ReadOnly))
    {
        return false;
    }
    QByteArray jsonStrOld = jsonFile.readAll();
    jsonFile.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonStrOld);

    if(!doc.isArray())
    {
        return false;
    }

    QJsonArray jsonArr = doc.array();

    for(int i=0;i<jsonArr.count();i++)
    {
        QJsonValue updateObject = jsonArr.at(i);
        if(!updateObject.isObject())
        {
            return false;
        }
        QJsonObject temp = updateObject.toObject();
        Word wd = JsonOper::readWord(temp);
        words->insert(wd.spelling, wd);
    }
    return true;
}


JsonOper::~JsonOper()
{
}
