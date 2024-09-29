#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

#define PORT 8083

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    void newClientHandler();
    void clientInfoSlot();
    void onClientDisconnected();
    void sendToAllClients(const QByteArray &message);
private:
    Ui::Widget *ui;
    QTcpServer *m_pserver;
    QList<QTcpSocket*> clients;
};
#endif // WIDGET_H
