#include "NetUtils.h"
#include "http/SendDataHttp.h"
#include "tcp/SendDataTcp.h"
#include <QPainter>
#include <QBrush>

namespace yang {
NetUtils::NetUtils(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint),
      _isPressedInTop(false),
      _tabWidget(nullptr),
      _mainWidget(nullptr),
      _btnMinimum(nullptr),
      _btnClose(nullptr)
{
    resize(854, 480);
    setStyleSheet("QCheckBox{font-family:arial;font-size:13px;border-radius:2px;color:#000000;}"
                  "QCheckBox::indicator:checked{color:#FF0000}"
                  "QTabWidget::pane{border:none;}"
                  "QTabWidget::tab-bar{alignment:center;}"
                  "QTabBar::tab{background:transparent;color:#000000;min-width:200px;min-height:35px;font-size:25px}"
                  "QTabBar::tab:hover{background:rgb(6, 157, 213, 100);}"
                  "QTabBar::tab:selected{color:white;padding-left:5px;background:rgb(6, 157, 213, 200)}"
                  "QListWidget{background:rgba(240,240,240,255);color:#000000;border:0px solid gray;padding:0px;}"
                  "QListWidget::item{width:94px;height:38px;border:0px solid gray;padding-left:24px;}"
                  "QListWidget::item:selected:active{background:#FFFFFF;color:#19649F;border-width:-1;}"
                  "QListWidget::item:selected{background:#FFFFFF;color:#19649F;}"
                  "QLabel,QRadioButton{background:transparent;color:#000000;font-family:arial;font-size:13px;}"

                  "QComboBox{border:1px solid #d7d7d7; border-radius: 3px; padding: 1px 3px 1px 3px;}"
                  "QComboBox:editable{background:transparent;}"
                  "QComboBox:!editable{background: #fbfbfb;color:#666666}"
                  "QComboBox::down-arrow:on {top: 1px;left: 1px;}"
                  "QComboBox QAbstractItemView::item{max-width:30px;min-height:20px;}"
                  );
    _btnClose = new QPushButton(QIcon(":/common/top/btn_close"), "", this);
    _btnMinimum = new QPushButton(QIcon(":/common/top/btn_minimum"), "", this);
    _btnClose->setToolTip(tr("close"));
    _btnMinimum->setToolTip(tr("minimum"));
    connect(_btnClose, &QPushButton::clicked, this, &NetUtils::onBtnCloseClick);
    connect(_btnMinimum, &QPushButton::clicked, this, &NetUtils::onBtnMinimumClick);

    _topRect = QRect(0, 0, width(), 30);
    _mainWidget = new QWidget(this);

    _tabWidget = new QTabWidget(_mainWidget);
    _tabWidget->addTab(new SendDataHttp(_tabWidget), "http");
    _tabWidget->addTab(new SendDataTcp(_tabWidget), "tcp");
    _tabWidget->addTab(new QWidget(_tabWidget), "capture");
    _tabWidget->setCurrentIndex(1);
}

NetUtils::~NetUtils()
{
}

void NetUtils::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QColor("#069dd5"));
    painter.setBrush(QColor("#069dd5"));
    painter.drawRect(_topRect);
    QWidget::paintEvent(event);
}
void NetUtils::resizeEvent(QResizeEvent *event)
{
    _btnClose->setGeometry(width() - 35, 0, 30, 30);
    _btnClose->setMaximumSize(_btnClose->size());
    _btnClose->setMinimumSize(_btnClose->size());
    _btnClose->setIconSize(_btnClose->size());
    _btnMinimum->setGeometry(width() - _btnClose->width() - 45, 0, 30, 30);
    _btnMinimum->setMaximumSize(_btnMinimum->size());
    _btnMinimum->setMinimumSize(_btnMinimum->size());
    _btnMinimum->setIconSize(_btnMinimum->size());

    _mainWidget->setGeometry(0, _topRect.height(), width(), height() - _topRect.height());
    _tabWidget->setGeometry(0, 0, _mainWidget->width(), _mainWidget->height());
    QWidget::resizeEvent(event);
}

void NetUtils::onBtnCloseClick()
{
    close();
}
void NetUtils::onBtnMinimumClick()
{
    showMinimized();
}

void NetUtils::mousePressEvent(QMouseEvent *event)
{
    if(Qt::LeftButton == event->button() && _topRect.contains(event->pos())){
        _isPressedInTop = true;
    }
    _mouseMovePoint = event->pos();
    QWidget::mousePressEvent(event);
}

void NetUtils::mouseMoveEvent(QMouseEvent *event)
{
    if(_isPressedInTop){
        this->move((event->globalPos() - _mouseMovePoint));
    }
    QWidget::mouseMoveEvent(event);
}

void NetUtils::mouseReleaseEvent(QMouseEvent *event)
{
    _isPressedInTop = false;
    QWidget::mouseReleaseEvent(event);
}


}
