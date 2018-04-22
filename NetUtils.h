#ifndef NETUTILS_H
#define NETUTILS_H

#include <QWidget>
#include <QTabWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QPushButton>

namespace yang {
class NetUtils : public QWidget
{
    Q_OBJECT

public:
    NetUtils(QWidget *parent = 0);
    ~NetUtils();
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
private:
    /* ui private variables */
    QRect _topRect;
    QTabWidget *_tabWidget;
    QPushButton *_btnMinimum;
    QPushButton *_btnClose;
};
}

#endif // NETUTILS_H
