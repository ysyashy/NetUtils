#ifndef __SENDDATAITEM_H
#define __SENDDATAITEM_H

#include <QWidget>
#include <QEvent>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

namespace yang {
class SendDataItem : public QWidget
{
    Q_OBJECT
public:
    explicit SendDataItem(const QSize &size = QSize(200, 20), QWidget *parent = nullptr);
    virtual ~SendDataItem();
    QByteArray getItemData();
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
private:
    QComboBox *_comboBox;
    QLineEdit *_lineEdit;
    QPushButton *_btn_remove;
signals:
    void removeItemSignal();
    void insertItemSignal();
private slots:
    void remove_btn_clicked();
};
}

#endif
