#ifndef __CAPTUREITEM_H
#define __CAPTUREITEM_H

#include <QWidget>

namespace Ui {
class CaptureItem;
}

class CaptureItem : public QWidget
{
    Q_OBJECT

public:
    explicit CaptureItem(QWidget *parent = 0);
    ~CaptureItem();

private slots:
    void on_btnDetial_clicked();

private:
    Ui::CaptureItem *ui;
};

#endif // CAPTUREITEM_H
