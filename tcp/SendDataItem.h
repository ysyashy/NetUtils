#ifndef __SENDDATAITEM_H
#define __SENDDATAITEM_H

#include <unordered_map>
#include <cinttypes>
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
private:
    void initComboBox();
signals:
    void removeItemSignal();
    void insertItemSignal();
private slots:
    void remove_btn_clicked();
    void text_value_changed(const QString &text);   /* 编辑框内容发生变化时，调用 */
};
}

#endif
