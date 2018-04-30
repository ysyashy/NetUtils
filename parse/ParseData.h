#ifndef __PARSEDATA_H
#define __PARSEDATA_H

#include <QWidget>
#include <QTabWidget>
#include <QByteArray>

namespace yang {
class ParseData : public QWidget
{
public:
    explicit ParseData(QByteArray datas, QWidget *parent = nullptr);
    ~ParseData();
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
private slots:
private:

private:
    QTabWidget *_tabWidget;

};

}

#endif // PARSEDATA_H
