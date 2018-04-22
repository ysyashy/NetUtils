#include "NetUtils.h"
#include <QPainter>
#include <QBrush>

namespace yang {
NetUtils::NetUtils(QWidget *parent)
    : QWidget(parent),
      _tabWidget(nullptr),
      _btnMinimum(nullptr),
      _btnClose(nullptr)
{
    resize(854, 480);
    _topRect = QRect(0, 0, width(), 30);
    _tabWidget = new QTabWidget(this);
    _tabWidget->addTab(new QWidget(_tabWidget), "set1");
    _tabWidget->addTab(new QWidget(_tabWidget), "get1");
}

NetUtils::~NetUtils()
{
}

void NetUtils::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(QColor("#069dd5"));
    painter.drawRect(_topRect);
    QWidget::paintEvent(event);
}
void NetUtils::resizeEvent(QResizeEvent *event)
{
    _tabWidget->setGeometry(0, 20, width(), height()-20);
    QWidget::resizeEvent(event);
}


}
