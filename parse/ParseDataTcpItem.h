#ifndef __PARSEDATATCPITEM_H
#define __PARSEDATATCPITEM_H

#include <QWidget>
#include <QLabel>
#include <QTextBrowser>

namespace yang {

class ParseDataTcpItem : public QWidget
{
    Q_OBJECT
public:
    explicit ParseDataTcpItem(const QString &name, const QString &value, QWidget *parent = nullptr);
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
signals:

public slots:
private:
    QLabel *_label;
    QTextBrowser *_textBrowser;
};

}

#endif // PARSEDATATCPITEM_H
