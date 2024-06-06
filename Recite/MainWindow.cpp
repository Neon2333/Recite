#include "MainWindow.h"

MainWindow::MainWindow(GlobalApplication* a, QWidget* parent)
    :app(a), QMainWindow(parent)
{

    init();
}

MainWindow::~MainWindow()
{
    //д�������ļ�
    JsonOper::writeConfig(configPath, curPageIndex, countWordList);

    //�ͷ���Դ
    delete wordListAll;
}

void MainWindow::editModeSetter(bool isEditMode)
{
    if (editMode != isEditMode)
    {
        editMode = isEditMode;
        emit modeChanged(editMode);
    }
}

void MainWindow::init()
{
    //��ʼ�����ڿؼ�
    initMainWindow();

    //�����¼�handler
    connectEvents();    

#if 0
    Word wd;
    wd.pageIndex = 1;
    wd.spelling = "person";
    wd.meanings = QList<QString>{ "����" };
    wd.type = "n";
    wd.synonyms = QList<QString>{ "lilin","lilin" };
    wd.nearSynonyms = QList<QString>{ "person","people" };
    wd.antonyms = QList<QString>{ "haha","www" };
    wd.similar = QList<QString>{ "people","people" };
    wd.noun = QList<QString>{ "person","person" };
    wd.verb = QList<QString>{ "person","person" };
    wd.adj = QList<QString>{ "person","person" };
    wd.adv = QList<QString>{ "person","person" };
    wd.usefulExpressions = QList<QString>{ "person","hahah","wwww" };
    wordListCurrentPage.insert("person", wd);
    Word wd1;
    wd1.pageIndex = 1;
    wd1.spelling = "person";
    wd1.meanings = QList<QString>{ "����2" };
    wd1.type = "n";
    wd1.synonyms = QList<QString>{ "lilin","lilin" };
    wd1.nearSynonyms = QList<QString>{ "person","people" };
    wd1.antonyms = QList<QString>{ "haha","www" };
    wd1.similar = QList<QString>{ "people","people" };
    wd1.noun = QList<QString>{ "person","person" };
    wd1.verb = QList<QString>{ "person","person" };
    wd1.adj = QList<QString>{ "person","person" };
    wd1.adv = QList<QString>{ "person","person" };
    wd1.usefulExpressions = QList<QString>{ "person","hahah","wwww" };
    wordListCurrentPage.insert("person", wd1);
    selectedWord = wd1;

#endif

    //�������ļ�
    QList<int> configParas = JsonOper::readConfig(configPath);
    curPageIndex = configParas.at(0);
    countWordList = configParas.at(1);

    //����wordlistĿ¼
    QDir wordListDirTemp(wordListDir);
    if (!wordListDirTemp.exists())
    {
        wordListDirTemp.mkdir(wordListDir);
    }

    wordListAll = new QList<QHash<QString, Word>>();
    //���̶߳�ȡ���е��ʱ���������ʾ
    readWordListAll(wordListDir);

    wordsTree->setWords(wordListAll);

    wordsTree->showWords();

    Word wd;
    wd.pageIndex = 1;
    wd.spelling = "NaN";
    wd.meanings = QList<QString>{ "NaN" };
    wd.type = "n";
    wd.synonyms = QList<QString>{ "NaN" };
    wd.nearSynonyms = QList<QString>{ "NaN"};
    wd.antonyms = QList<QString>{ "NaN"};
    wd.similar = QList<QString>{ "NaN" };
    wd.noun = QList<QString>{ "NaN" };
    wd.verb = QList<QString>{ "NaN" };
    wd.adj = QList<QString>{ "NaN" };
    wd.adv = QList<QString>{ "NaN" };
    wd.usefulExpressions = QList<QString>{ "NaN" };
    wordsTree->setWordAddFillItemTop(&wd);
    wordsTree->setWordAddFillItemBottom(&wd);

    //�Ҳ���ʾѡ�е�����ϸ
    showSelectedWord();
        
}

void MainWindow::connectEvents()
{
    connect(this, &MainWindow::modeChanged, this, &MainWindow::onModeChanged);
    connect(app, &GlobalApplication::keyIPressed, this, &MainWindow::onKeyIPressed);
    connect(app, &GlobalApplication::keyRPressed, this, &MainWindow::onKeyRPressed);
    connect(wordsTree, &CustomTreeWidget::selectedWordChanged, this, &MainWindow::onSelectedWordChanged);
}

void MainWindow::initMainWindow()
{
    //�Ҳ��һ��
    label_spelling = new QLabel(this);
    label_spelling->setFixedSize(350, 200);
    label_spelling->setText("annynomous");  //���ܷ������塢Alignment�Ⱥ��棬�������ò���
    label_spelling->setAlignment(Qt::AlignCenter);
    label_spelling->setFont(QFont("΢���ź�", 30));
    label_spelling->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    textEdit_meanings = new QTextEdit();
    textEdit_meanings->setFixedSize(300, 200);
    textEdit_meanings->setReadOnly(true);
    textEdit_meanings->append("����");
    textEdit_meanings->setFont(QFont("΢���ź�", 15));
    textEdit_meanings->setAlignment(Qt::AlignCenter);
    textEdit_meanings->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    label_partOfSpeech = new QLabel(this);
    label_partOfSpeech->setFixedSize(100, 200);
    label_partOfSpeech->setText("n");
    label_partOfSpeech->setFont(QFont("΢���ź�", 15));
    label_partOfSpeech->setAlignment(Qt::AlignCenter);
    label_partOfSpeech->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    layout_rightLine1 = new QHBoxLayout();
    layout_rightLine1->setMargin(5);
    layout_rightLine1->setSpacing(5);
    layout_rightLine1->addWidget(label_spelling);
    layout_rightLine1->addWidget(textEdit_meanings);
    layout_rightLine1->addWidget(label_partOfSpeech);

    widget_spelling = new QWidget();
    widget_spelling->setFixedSize(780, 210);
    widget_spelling->setLayout(layout_rightLine1);


    //�Ҳ�ڶ���
    textEdit_synonyms = new QTextEdit(this);
    textEdit_synonyms->setFixedSize(185, 200);
    textEdit_synonyms->setReadOnly(true);
    textEdit_synonyms->setFont(QFont("΢���ź�", 10));
    textEdit_synonyms->setAlignment(Qt::AlignCenter);
    textEdit_synonyms->append("distinguish");
    textEdit_synonyms->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    textEdit_nearSynonyms = new QTextEdit(this);
    textEdit_nearSynonyms->setFixedSize(185, 200);
    textEdit_nearSynonyms->setReadOnly(true);
    textEdit_nearSynonyms->append("�����");
    textEdit_nearSynonyms->setFont(QFont("΢���ź�", 10));
    textEdit_nearSynonyms->setAlignment(Qt::AlignCenter);
    textEdit_nearSynonyms->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    textEdit_antonym = new QTextEdit(this);
    textEdit_antonym->setFixedSize(185, 200);
    textEdit_antonym->setReadOnly(true);
    textEdit_antonym->append("�����");
    textEdit_antonym->setFont(QFont("΢���ź�", 10));
    textEdit_antonym->setAlignment(Qt::AlignCenter);
    textEdit_antonym->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    textEdit_similar = new QTextEdit(this);
    textEdit_similar->setFixedSize(185, 200);
    textEdit_similar->setReadOnly(true);
    textEdit_similar->append("�ν���");
    textEdit_similar->setFont(QFont("΢���ź�", 10));
    textEdit_similar->setAlignment(Qt::AlignCenter);
    textEdit_similar->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    layout_rightLine2 = new QHBoxLayout();
    layout_rightLine2->setMargin(5);
    layout_rightLine2->setSpacing(5);
    layout_rightLine2->addWidget(textEdit_synonyms);
    layout_rightLine2->addWidget(textEdit_nearSynonyms);
    layout_rightLine2->addWidget(textEdit_antonym);
    layout_rightLine2->addWidget(textEdit_similar);

    widget_synonyms = new QWidget();
    widget_synonyms->setFixedSize(780, 210);
    widget_synonyms->setLayout(layout_rightLine2);


    //�Ҳ������
    textEdit_noun = new QTextEdit(this);
    textEdit_noun->setFixedSize(185, 80);
    textEdit_noun->setReadOnly(true);
    textEdit_noun->setText("n");
    textEdit_noun->setFont(QFont("΢���ź�", 10));
    textEdit_noun->setAlignment(Qt::AlignCenter);
    textEdit_noun->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    textEdit_verb = new QTextEdit(this);
    textEdit_verb->setFixedSize(185, 80);
    textEdit_verb->setReadOnly(true);
    textEdit_verb->setText("v");
    textEdit_verb->setFont(QFont("΢���ź�", 10));
    textEdit_verb->setAlignment(Qt::AlignCenter);
    textEdit_verb->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    textEdit_adj = new QTextEdit(this);
    textEdit_adj->setFixedSize(185, 80);
    textEdit_adj->setReadOnly(true);
    textEdit_adj->setText("adj");
    textEdit_adj->setFont(QFont("΢���ź�", 10));
    textEdit_adj->setAlignment(Qt::AlignCenter);
    textEdit_adj->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    textEdit_adv = new QTextEdit(this);
    textEdit_adv->setFixedSize(185, 80);
    textEdit_adv->setReadOnly(true);
    textEdit_adv->setText("adv");
    textEdit_adv->setFont(QFont("΢���ź�", 10));
    textEdit_adv->setAlignment(Qt::AlignCenter);
    textEdit_adv->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    layout_rightLine3 = new QHBoxLayout();
    layout_rightLine3->setMargin(5);
    layout_rightLine3->setSpacing(5);
    layout_rightLine3->addWidget(textEdit_noun);
    layout_rightLine3->addWidget(textEdit_verb);
    layout_rightLine3->addWidget(textEdit_adj);
    layout_rightLine3->addWidget(textEdit_adv);

    widget_noun = new QWidget();
    widget_noun->setFixedSize(780, 90);
    widget_noun->setLayout(layout_rightLine3);


    //�Ҳ������
    textEdit_usefulExpressions = new QTextEdit(this);
    textEdit_usefulExpressions->setFixedSize(770, 200);
    textEdit_usefulExpressions->setReadOnly(true);
    textEdit_usefulExpressions->setText("���ô���");
    textEdit_usefulExpressions->setFont(QFont("΢���ź�", 10));
    textEdit_usefulExpressions->setAlignment(Qt::AlignCenter);
    textEdit_usefulExpressions->setStyleSheet("background-color:rgb(99,107,118);color:rgb(255,255,255)");

    layout_rightLine4 = new QHBoxLayout();
    layout_rightLine4->setMargin(5);
    layout_rightLine4->setSpacing(5);
    layout_rightLine4->addWidget(textEdit_usefulExpressions);

    widget_usefulExpressions = new QWidget();
    widget_usefulExpressions->setFixedSize(780, 200);
    widget_usefulExpressions->setLayout(layout_rightLine4);


    //�Ҳ�����
    layout_right = new QVBoxLayout();
    layout_right->setSpacing(5);
    layout_right->setMargin(5);
    layout_right->addWidget(widget_spelling);
    layout_right->addWidget(widget_synonyms);
    layout_right->addWidget(widget_noun);
    layout_right->addWidget(widget_usefulExpressions);

    widget_right = new QWidget();
    widget_right->setFixedSize(800, 730);
    widget_right->setLayout(layout_right);

    //�������
    wordsTree = new CustomTreeWidget(this);
    wordsTree->setSize(400, 630);

    layout_leftLine1 = new QHBoxLayout();
    layout_leftLine1->setMargin(5);
    layout_leftLine1->setSpacing(5);
    layout_leftLine1->addWidget(wordsTree);
    widget_leftLine1 = new QWidget();
    widget_leftLine1->setFixedSize(400, 630);
    widget_leftLine1->setLayout(layout_leftLine1);

    btn_lastPage = new QPushButton(this);
    btn_lastPage->setFixedSize(50, 25);
    btn_lastPage->setText("��һҳ");

    btn_nextPage = new QPushButton(this);
    btn_nextPage->setFixedSize(50, 25);
    btn_nextPage->setText("��һҳ");

    label_curPage = new QLabel(this);
    label_curPage->setFixedSize(50, 25);
    label_curPage->setFont(QFont("΢���ź�", 10));
    label_curPage->setAlignment(Qt::AlignCenter);
    label_curPage->setText(QString::number(curPageIndex) + "/" + QString::number(countWordList));

    layout_leftLine2 = new QHBoxLayout();
    layout_leftLine2->setMargin(5);
    layout_leftLine2->setSpacing(5);
    layout_leftLine2->addWidget(btn_lastPage);
    layout_leftLine2->addWidget(label_curPage);
    layout_leftLine2->addWidget(btn_nextPage);
    widget_leftLine2 = new QWidget();
    widget_leftLine2->setFixedSize(400, 30);
    widget_leftLine2->setLayout(layout_leftLine2);

    label_status = new QLabel(this);
    label_status->setFixedSize(50, 20);
    label_status->setFont(QFont("΢���ź�", 10));
    label_status->setAlignment(Qt::AlignCenter);
    label_status->setText(editMode ? "edit" : "recite");
    label_status->setStyleSheet("background-color:rgb(0,0,0);color:rgb(255,255,255)");

    probar = new QProgressBar(this);
    probar->setFixedSize(300, 20);
    probar->setOrientation(Qt::Orientation::Horizontal);
    probar->setValue(50);
    probar->setTextVisible(true);

    layout_leftLine3 = new QHBoxLayout();
    layout_leftLine3->setMargin(5);
    layout_leftLine3->setSpacing(5);
    layout_leftLine3->addWidget(label_status);
    layout_leftLine3->addWidget(probar);
    widget_leftLine3 = new QWidget();
    widget_leftLine3->setFixedSize(400, 30);
    widget_leftLine3->setLayout(layout_leftLine3);
    

    layout_left = new QVBoxLayout();
    layout_left->addWidget(widget_leftLine1);
    layout_left->addWidget(widget_leftLine2);
    layout_left->addWidget(widget_leftLine3);
    layout_left->setMargin(5);
    layout_left->setSpacing(5);


    widget_left = new QWidget();
    widget_left->setFixedSize(420, 730);
    widget_left->setLayout(layout_left);

    //Recite
    this->setFixedSize(1230, 740);
    this->setWindowTitle("Recite");

    layout_main = new QHBoxLayout();
    layout_main->setSpacing(5);
    layout_main->setMargin(5);
    layout_main->addWidget(widget_left);
    layout_main->addWidget(widget_right);

    widget_main = new QWidget();
    widget_main->setFixedSize(1230, 740);
    widget_main->setLayout(layout_main);
    this->setCentralWidget(widget_main);
}

void MainWindow::readWordListAll(QString jsonDir)
{
    QDir dir(jsonDir);
    if (!dir.exists())
    {
        //����Ŀ¼

    }

    if (curPageIndex > countWordList || curPageIndex < 0 || countWordList < 0)
    {
        return;
    }

    //��curPageIndex=countWordList=0����һ�δ򿪡��򴴽�1.json
    ////��curPageIndex=countWordList=1����ȡ���ʱ�wordListCurrentPage
    if (curPageIndex == 0 && countWordList == 0)
    {
        updateConfig(++curPageIndex, ++countWordList);
    }

    QString curPageJsonPath;
    //��������ҳ����ӵ�wordListAll
    for (int i = 1; i <= countWordList; i++)
    {
        curPageJsonPath = wordListDir + "/" + QString::number(i) + ".json";
        JsonOper::readWords(&wordListCurrentPage, curPageJsonPath);
        wordListAll->append(wordListCurrentPage);
        probar->setValue(i / countWordList);    //������
    }
    wordListCurrentPage = (*wordListAll)[curPageIndex - 1];
    label_curPage->setText(QString::number(curPageIndex) + "/" + QString::number(countWordList));

    ////����ǰҳ��ӵ�wordListCurrentPage
    //wordListCurrentPage = (*wordListAll)[curPageIndex];

    //QFileInfoList fileInfoList = dir.entryInfoList();
    //for (auto item : fileInfoList)
    //{
    //    if (!item.isFile() || item.suffix().toLower() != "json")
    //    {
    //        continue;
    //    }

    //    QString jsonPath = item.absoluteFilePath();
    //    QFile jsonFile(jsonPath);
    //    if (!jsonFile.open(QFile::ReadOnly))
    //    {
    //        return;
    //    }
    //    QByteArray jsonArr = jsonFile.readAll();
    //    jsonFile.close();
    //    QJsonDocument doc = QJsonDocument::fromJson(jsonArr);
    //    if (!doc.isArray())
    //    {
    //        return;
    //    }

    //    QJsonObject obj = doc.object();
    //    QStringList keys = obj.keys();

    //    for (int i = 0; i < keys.count(); i++)
    //    {
    //        QString key = keys.at(i);
    //        QJsonValue value = obj.value(key);

    //        if (!value.isObject())
    //        {
    //            continue;
    //        }
    //        QJsonObject obj = value.toObject();
    //        Word wd = JsonOper::readWord(obj);
    //    }
    //}
}

void MainWindow::updateConfig(int curPage, int countWord)
{
    curPageIndex = curPage;
    countWordList = countWord;
    JsonOper::writeConfig(configPath, curPageIndex, countWordList);
}

void MainWindow::showSelectedWord()
{
    label_spelling->setText(selectedWord.spelling);

    textEdit_meanings->clear();
    textEdit_meanings->append("���壺");
    for (auto item : selectedWord.meanings)
    {
        textEdit_meanings->append(item);
        textEdit_meanings->setAlignment(Qt::AlignCenter);
    }

    label_partOfSpeech->setText("���ԣ�\n" + selectedWord.type);

    textEdit_synonyms->clear();
    textEdit_synonyms->append("ͬ��ʣ�");
    for (auto item : selectedWord.synonyms)
    {
        textEdit_synonyms->append(item);
        textEdit_synonyms->setAlignment(Qt::AlignCenter);
    }

    textEdit_nearSynonyms->clear();
    textEdit_nearSynonyms->append("����ʣ�");
    for (auto item : selectedWord.nearSynonyms)
    {
        textEdit_nearSynonyms->append(item);
        textEdit_nearSynonyms->setAlignment(Qt::AlignCenter);
    }

    textEdit_antonym->clear();
    textEdit_antonym->append("����ʣ�");
    for (auto item : selectedWord.antonyms)
    {
        textEdit_antonym->append(item);
        textEdit_antonym->setAlignment(Qt::AlignCenter);
    }

    textEdit_similar->clear();
    textEdit_similar->append("�ν��ʣ�");
    for (auto item : selectedWord.similar)
    {
        textEdit_similar->append(item);
        textEdit_similar->setAlignment(Qt::AlignCenter);
    }

    textEdit_noun->clear();
    textEdit_noun->append("n��");
    for (auto item : selectedWord.noun)
    {
        textEdit_noun->append(item);
        textEdit_noun->setAlignment(Qt::AlignCenter);
    }

    textEdit_verb->clear();
    textEdit_verb->append("v��");
    for (auto item : selectedWord.verb)
    {
        textEdit_verb->append(item);
        textEdit_verb->setAlignment(Qt::AlignCenter);
    }

    textEdit_adj->clear();
    textEdit_adj->append("adj��");
    for (auto item : selectedWord.adj)
    {
        textEdit_adj->append(item);
        textEdit_adj->setAlignment(Qt::AlignCenter);
    }

    textEdit_adv->clear();
    textEdit_adv->append("adv��");
    for (auto item : selectedWord.adv)
    {
        textEdit_adv->append(item);
        textEdit_adv->setAlignment(Qt::AlignCenter);
    }

    textEdit_usefulExpressions->clear();
    textEdit_usefulExpressions->append("���ô��䣺");
    for (auto item : selectedWord.usefulExpressions)
    {
        textEdit_usefulExpressions->append(item);
        textEdit_usefulExpressions->setAlignment(Qt::AlignCenter);
    }
}

void MainWindow::onKeyIPressed() 
{
    editModeSetter(true);
}

void MainWindow::onKeyRPressed()
{
    editModeSetter(false);
}

void MainWindow::onSelectedWordChanged(Word wd)
{
    this->selectedWord = wd;
    showSelectedWord();
}

void MainWindow::paintEvent(QPaintEvent* event)
{

}

void MainWindow::closeEvent(QCloseEvent* event)
{
    //����json����
}

void MainWindow::onModeChanged(bool isEditMode)
{
    label_status->setText(isEditMode ? "Edit" : "Recite");
    if (isEditMode)
    {
        wordsTree->setEditable(true);
    }
    else
    {
        wordsTree->setEditable(false);
    }

}