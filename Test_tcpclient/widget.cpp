#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)

    , ui(new Ui::Widget)
    ,m_psocket(new QTcpSocket)

{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_connect_clicked()
{
    QString ip =ui->lineEdit_ip->text();
    QString port =ui->lineEdit_port->text();

    //客户端三次握手
    m_psocket->connectToHost(QHostAddress(ip),port.toShort());
    connect(m_psocket,&QTcpSocket::connected,this,&Widget::do_connected);
    connect(m_psocket,static_cast<void(QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error),this,&Widget::do_unconnected);
}

void Widget::do_connected()
{
    QMessageBox::information(this,"连接","连接成功");
    this->hide();


    m_pchatwidget = new Chat(m_psocket);
    m_pchatwidget->show();
}

void Widget::do_unconnected()
{
       QMessageBox::warning(this,"连接提示","连接服务器失败");
}

void Widget::on_pushButton_cancel_clicked()
{
    close();
}
