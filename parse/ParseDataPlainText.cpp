#include <QResizeEvent>
#include "ParseDataPlainText.h"
#include "inline/utilsinline.h"

namespace yang {
ParseDataPlainText::ParseDataPlainText(const QByteArray &datas, QWidget *parent)
    : QWidget(parent),
      _textArea(nullptr)
{
    resize(parent->size());
    _textArea = new QTextBrowser(this);
    _textArea->setFontPointSize(12);
    _textArea->setGeometry(0, 0, width(), height());
    _textArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    QString str;
    char c;
    for(int i=0; i<datas.size(); i++) {
        c = datas.at(i);
        if('\n' == c || isvAscii(c)) {
            str.append(c);
        } else {
            str.append(".");
        }
    }
    _textArea->setText(str);
}

void ParseDataPlainText::resizeEvent(QResizeEvent *event)
{
    _textArea->resize(event->size());
}

}
