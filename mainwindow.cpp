#include "mainwindow.h"
#include <QDebug>
#include <QBuffer>
#include <QLabel>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "wordmakemanager.h"

MainWindow::MainWindow(QWidget *parent)
    :QWidget(parent)
{
    QString cmd = "exeTest.exe";
//    QStringList args;
//    QImage image("2.jpg", "JPG");
////    QLabel
//    qDebug()<< image.save("3.jpg", "JPG");
//    QByteArray ba;
//    QBuffer buffer(&ba);
//    buffer.open(QIODevice::WriteOnly);
//    image.save(&buffer, "jpg");

//    args.push_back(ba.toBase64());
    QJsonArray array;
    QJsonObject jsonTitle;
    jsonTitle.insert("Title", "Document Title");
    jsonTitle.insert("Type", 0);
    array.push_back(jsonTitle);

    QJsonObject jsonWordText;
    jsonWordText.insert("Paragraph", "A plain paragraph having some ");
    jsonWordText.insert("Bold", true);
    jsonWordText.insert("Italic", false);
    array.push_back(jsonWordText);

    QJsonObject jsonTable;
    QJsonArray arrayTable;
    int num = 5;
    QStringList tableTitle;
    tableTitle<<"Qt"<<"id"<<"type"<<"Num"<<"Time";
    for(int i=0; i<num; i++)
    {
        QJsonArray arrayTableInfo;
        for(int j=0; j<tableTitle.size(); j++)
        {
            if(i==0)
            {
                arrayTableInfo.append(tableTitle.at(j));
            }
            else
            {
                arrayTableInfo.append(i*10 + j );
            }
        }
        arrayTable.push_back(arrayTableInfo);
    }
    jsonTable.insert("Table", arrayTable);
    array.push_back(jsonTable);

    QJsonObject jsonPixMap;
    jsonPixMap.insert("PixMapName", "testPixMap.jpg");
    jsonPixMap.insert("Inches", 1.25);
    array.push_back(jsonPixMap);

    // 构建 JSON 文档
    QJsonDocument document;
    document.setArray(array);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);
    qDebug()<<strJson;
    WordMakeManager::getInstance().startMakeWord(strJson);

}

MainWindow::~MainWindow()
{

}
