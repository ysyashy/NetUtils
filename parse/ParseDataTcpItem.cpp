#include "ParseDataTcpItem.h"
#include <QLabel>
#include <QResizeEvent>

namespace yang {
ParseDataTcpItem::ParseDataTcpItem(const QString &name, const QString &value, QWidget *parent)
    : QWidget(parent),
      _label(nullptr),
      _textBrowser(nullptr)
{
    _label = new QLabel(name, this);
    _label->setStyleSheet("background-color: #adb4b0;");
    _label->setAlignment(Qt::AlignHCenter);
    _textBrowser = new QTextBrowser(this);
    _textBrowser->setText(value);
}

void ParseDataTcpItem::resizeEvent(QResizeEvent *event)
{
    resize(event->size());
    _label->setGeometry(0, 0, width(), 15);
    _textBrowser->setGeometry(0, 15, width(), height()-15);
}
}
