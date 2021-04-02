#include "wordmakemanager.h"
#include <QDebug>

ProcessManager::ProcessManager(QObject *parent)
    :QObject(parent)
    ,m_process(nullptr)
{

}

ProcessManager::~ProcessManager()
{
    if (m_process)
    {
        m_process->close();
        delete m_process;
        m_process = nullptr;
        qDebug()<<"close process wordExe";
    }
}

QString ProcessManager::getUuid()
{
    m_uuid = QUuid::createUuid().toString();
    return m_uuid;
}

void ProcessManager::onStartProcess(QStringList praList)
{
    m_process = new QProcess();
    m_process->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_process , &QProcess::readyReadStandardOutput , this , &ProcessManager::onOut);
    connect(m_process, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
          [this](int exitCode, QProcess::ExitStatus exitStatus){
        qDebug()<<"process exitCode is: "<<exitCode;
        qDebug()<<"QProcess ExitStatus is"<<exitStatus;
        emit sigProcessExit(m_uuid);
    });

    if(m_process != nullptr)
    {
        QString exeName = "wordMake.exe";
        m_process->start(exeName, praList);
    }
}

void ProcessManager::onOut()
{
    qDebug() << m_process->readAllStandardOutput().data();
}

WordMakeManager WordMakeManager::m_instance;
WordMakeManager::WordMakeManager(QObject *parent)
    :QObject(parent)
{

}

WordMakeManager::~WordMakeManager()
{

}

WordMakeManager &WordMakeManager::getInstance()
{
    return m_instance;
}

void WordMakeManager::startMakeWord(QString jsonStr)
{
    QThread *thread = new QThread;
    ProcessManager *pm = new ProcessManager;
    m_mapThread.insert(pm->getUuid(), thread);
    pm->moveToThread(thread);
    connect(thread, &QThread::finished, pm, &ProcessManager::deleteLater);
    connect(this, &WordMakeManager::sigSendToMakeWord, pm, &ProcessManager::onStartProcess);
    connect(pm, &ProcessManager::sigProcessExit, [this](QString uuid){
        if(m_mapThread.contains(uuid))
        {
            QThread *thread = m_mapThread.value(uuid);
            thread->wait();
            thread->quit();
            thread->deleteLater();
            m_mapThread.remove(uuid);
        }
    });
    thread->start();
    emit sigSendToMakeWord(QStringList()<<jsonStr);
}

