#ifndef WORDMAKEMANAGER_H
#define WORDMAKEMANAGER_H
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QThread>
#include <QProcess>
#include <QUuid>
#include <QMap>

class ProcessManager : public QObject
{
    Q_OBJECT
public:
    ProcessManager(QObject *parent = 0);
    ~ProcessManager();
    QString getUuid();
signals:
    void sigProcessExit(QString id);
public slots:
    void onStartProcess(QStringList praList);
    void onOut();
private:
    QProcess *m_process;
    QString m_uuid;
};

class WordMakeManager : public QObject
{
    Q_OBJECT
public:
    ~WordMakeManager();
    static WordMakeManager &getInstance();
    void startMakeWord(QString jsonStr);
signals:
    void sigSendToMakeWord(QStringList jsonStrList);
private:
    WordMakeManager(QObject *parent = 0);
private:
    static WordMakeManager m_instance;
    QMap<QString, QThread *> m_mapThread;
};


#endif // WORDMAKEMANAGER_H
