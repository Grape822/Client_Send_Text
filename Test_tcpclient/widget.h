#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include "chat.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    void do_connected();
    void do_unconnected();
private slots:
    void on_pushButton_connect_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket *m_psocket;
    Chat* m_pchatwidget;
};
#endif // WIDGET_H
