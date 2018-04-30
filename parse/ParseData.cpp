#include <QTabBar>
#include <QProxyStyle>
#include <QStyleOptionTab>
#include <QPainter>
#include <QResizeEvent>
#include "ParseData.h"
#include "ParseDataTcp.h"
#include "ParseDataPlainText.h"

namespace yang {
class CustomTabStyle : public QProxyStyle
{
public:
    virtual QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const override;
    virtual void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const override;
};
QSize CustomTabStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const
{
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    if(QStyle::CT_TabBarTab == type) {
        s.transpose();
        s.rwidth() = 90;
        s.rheight() = 44;
    }
    return s;
}
void CustomTabStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    if(QStyle::CE_TabBarTabLabel == element) {
        if(const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab*>(option)){
            QRect allRect = tab->rect;

            if(tab->state & QStyle::State_Selected) {
                painter->save();
                painter->setPen(0x89cfff);
                painter->setBrush(QBrush(0x89cfff));
                painter->drawRect(allRect.adjusted(6, 6, -6, -6));
                painter->restore();
            }
            QTextOption option;
            option.setAlignment(Qt::AlignCenter);
            if(tab->state & QStyle::State_Selected) {
                painter->setPen(0xf8fcff);
            } else {
                painter->setPen(0x5d5d5d);
            }
            painter->drawText(allRect, tab->text, option);
            return;
        }
    }
    if(QStyle::CE_TabBarTab == element) {
        QProxyStyle::drawControl(element, option, painter, widget);
    }
}
ParseData::ParseData(QByteArray datas, QWidget *parent)
    : QWidget(parent),
      _tabWidget(nullptr)
{
    resize(854, 480);
    _tabWidget = new QTabWidget(this);
    _tabWidget->resize(size());
    _tabWidget->setTabPosition(QTabWidget::West);
    _tabWidget->tabBar()->setStyle(new CustomTabStyle());

    _tabWidget->addTab(new ParseDataPlainText(datas, _tabWidget), "纯文本");
    _tabWidget->addTab(new ParseDataTcp(datas, _tabWidget), "Struct");
}

void ParseData::resizeEvent(QResizeEvent *event)
{
    _tabWidget->resize(event->size());
}

ParseData::~ParseData()
{
}

}
