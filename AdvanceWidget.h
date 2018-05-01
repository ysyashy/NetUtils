#ifndef ADVANCEWIDGET_H
#define ADVANCEWIDGET_H

#include <QWidget>

namespace Ui {
class AdvanceWidget;
}

class AdvanceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdvanceWidget(QWidget *parent = 0);
    ~AdvanceWidget();

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::AdvanceWidget *ui;
};

#endif // ADVANCEWIDGET_H
