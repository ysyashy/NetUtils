#include <QResizeEvent>
#include "ParseDataPlainText.h"

namespace yang {
ParseDataPlainText::ParseDataPlainText(const QByteArray &datas, QWidget *parent)
    : QWidget(parent),
      _textArea(nullptr)
{
    resize(parent->size());
    _textArea = new QTextBrowser(this);
    _textArea->setFontPointSize(12);
    _textArea->setGeometry(0, 0, width(), height());

    QString str;
    char c;
    for(int i=0; i<datas.size(); i++) {
        c = datas.at(i);
        if('\0' == c) {
            str.append(".");
        } else {
            str.append(c);
        }
    }
    _textArea->setText(str);
}

void ParseDataPlainText::resizeEvent(QResizeEvent *event)
{
    _textArea->resize(event->size());
}

}
