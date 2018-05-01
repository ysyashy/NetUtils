#ifndef __CAPTUREWIDGET_H
#define __CAPTUREWIDGET_H

#include <QWidget>

namespace Ui {
class CaptureWidget;
}

class CaptureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CaptureWidget(QWidget *parent = 0);
    ~CaptureWidget();

private slots:
    void on_btnStop_clicked();

    void on_btnStart_clicked();

    void on_pushButton_clicked();

private:
    Ui::CaptureWidget *ui;
};

#endif // CAPTUREWIDGET_H
