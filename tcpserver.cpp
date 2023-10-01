#include "tcpserver.h"
#include "ui_tcpserver.h"
#include "mytcpserver.h"
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>
#include <QHostAddress>

TcpServer::TcpServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    loadConfig();
    MyTcpServer::getInstance().listen(QHostAddress(m_strIP), m_usPort);
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::loadConfig()
{
    // 拿到配置文件
    QFile file(":/server.config");
    // 尝试读取配置文件
    if(file.open(QIODevice::ReadOnly))
    {
        // 读取成功
        // 以二进制数组形式读取配置文件内所有内容
        QByteArray baData = file.readAll();
        // 将读到的二进制数组转化为字符串类型
        QString strData = baData.toStdString().c_str();
        // 关闭读取流
        file.close();
        // 将字符串内的“\r\n”转化为“ ”
        strData.replace("\r\n"," ");
        // 将字符串通过“ ”分割，转化为字符串数组类型
        QStringList strList = strData.split(" ");
        // 将第0个值赋给 m_strIP
        m_strIP = strList.at(0);
        // 将第一个值赋给 m_usPort
        m_usPort = strList.at(1).toUShort();
        // 输出此 ip 和 port 配置
        qDebug() << "ip: " << m_strIP << "port: " << m_usPort;
    }
    else
    {
        // 获取失败
        QMessageBox::critical(this,"open config","open config failed");
    }
}

