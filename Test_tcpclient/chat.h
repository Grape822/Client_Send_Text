#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QTcpSocket>
namespace Ui {
class Chat;
}

class Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Chat(QTcpSocket *socket,QWidget *parent = nullptr);
    ~Chat();

private slots:
    void on_pushButton_send_clicked();
    void serverInfoSlit();


private:
    Ui::Chat *ui;
    QTcpSocket *m_psocket;
};

#endif // CHAT_H
