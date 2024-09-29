#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QTcpSocket *socket,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
  ,m_psocket(socket)
{
    ui->setupUi(this);
    connect(m_psocket,&QTcpSocket::readyRead,this,&Chat::serverInfoSlit);
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_pushButton_send_clicked()
{
    QString text=ui->lineEdit_text->text();
    QByteArray ba;
    ba.append(text);
    m_psocket->write(ba);
    ui->lineEdit_text->clear();

//    m_psocket=(QTcpSocket*)sender();
//    QByteArray Text=m_psocket->readAll();
//    ui->textEdit_Text->setText(QString(Text));

}

void Chat::serverInfoSlit()
{
    ui->textEdit->append(QString(m_psocket->readAll()));
}
