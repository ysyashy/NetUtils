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
    /* 拖动上方的蓝色边框，可以移动窗口 */
    bool _isPressedInTop;
    QPoint _mouseMovePoint;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
private slots:
    void onBtnCloseClick();
    void onBtnMinimumClick();
private:
    /* ui private variables */
    QRect _topRect;
    QTabWidget *_tabWidget;
    QWidget *_mainWidget;
    QPushButton *_btnMinimum;
    QPushButton *_btnClose;
};
}

#endif // NETUTILS_H
