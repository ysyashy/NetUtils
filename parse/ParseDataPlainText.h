#ifndef __PARSEDATAPLAINTEXT_H
#define __PARSEDATAPLAINTEXT_H

#include <QWidget>
#include <QByteArray>
#include <QTextBrowser>

namespace yang {
class ParseDataPlainText : public QWidget
{
    Q_OBJECT
public:
    explicit ParseDataPlainText(const QByteArray &datas, QWidget *parent = 0);
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
signals:
public slots:
private:
    QTextBrowser *_textArea;
};

}

#endif // PARSEDATAPLAINTEXT_H
