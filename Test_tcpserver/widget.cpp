#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_pserver (new QTcpServer)//创建一个服务器用来和客户端通信的套接字
{
    ui->setupUi(this);
    m_pserver->listen(QHostAddress::AnyIPv4,PORT);//等待客户端的链接到来

    connect(m_pserver, &QTcpServer::newConnection, this, &Widget::newClientHandler);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::newClientHandler()
{
    // 获取新连接的客户端套接字
    QTcpSocket *socket = m_pserver->nextPendingConnection();

    // 将新连接的客户端加入到列表
    clients.append(socket);

    // 获取客户端的 IP 和端口信息
    QHostAddress ip = socket->peerAddress();
    quint16 port = socket->peerPort();

    QString ip_show = "客户端ip: " + ip.toString();
    QString port_show = "端口号port: " + QString::number(port);

    ui->textEdit_ip->setText(ip_show);
    ui->textEdit_port->setText(port_show);

    // 连接 readyRead 信号，用于读取客户端发送的数据
    connect(socket, &QTcpSocket::readyRead, this, &Widget::clientInfoSlot);

    // 连接客户端断开连接的信号，移除客户端
    connect(socket, &QTcpSocket::disconnected, this, &Widget::onClientDisconnected);
}

void Widget::clientInfoSlot()
{
    // 获取发送消息的客户端套接字
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    // 获取客户端的 IP 和端口
    QHostAddress ip = socket->peerAddress();
    quint16 port = socket->peerPort();

    qDebug() << "收到来自客户端" << ip << ":" << port << "的消息";

    // 读取客户端发送的所有数据
    QByteArray ba = socket->readAll();

    // 在界面的 textEdit_3 中显示收到的消息
    ui->textEdit_3->append(QString("客户端 %1:%2 发来的消息: %3").arg(ip.toString()).arg(port).arg(QString(ba)));

    // 准备要发送的响应消息
    QString strtext = QString("收到来自 %1:%2 的消息: %3").arg(ip.toString()).arg(port).arg(QString(ba));

    // 将消息发送给所有客户端
    sendToAllClients(strtext.toUtf8());
}

void Widget::onClientDisconnected()
{
    // 获取断开连接的客户端套接字
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        // 从客户端列表中移除断开连接的客户端
        clients.removeAll(socket);
        socket->deleteLater();
    }
}

void Widget::sendToAllClients(const QByteArray &message)
{
    // 遍历所有客户端，将消息发送给每个客户端
    for (QTcpSocket *client : clients) {
        if (client->state() == QAbstractSocket::ConnectedState) {
            client->write(message);  // 发送消息
        }
    }
}
