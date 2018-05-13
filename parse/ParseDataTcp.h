#ifndef __PARSEDATATCP_H
#define __PARSEDATATCP_H

#include <QWidget>
#include <QByteArray>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <cinttypes>
#include <string>

namespace yang {
class ParseDataTcp : public QWidget
{
    Q_OBJECT
public:
    explicit ParseDataTcp(const QByteArray &datas, QWidget *parent = 0);
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
signals:

public slots:
private:
    void initTableWidget();
    void initComboBox();
    void addCustomerItem();
    char* getDigital(int length);
    inline bool isLittleEndian() {
        int32_t a = 1;
        char *p = (char *)&a;
        return (1 == *p);
    }

private:
    int COLUMN_COUNT;
    int ROW_COUNT;
    int64_t _currCount;
    int64_t _currIndex;
    QByteArray _datas;
    QComboBox *_comboBox;
    QLineEdit *_lineEdit;
    QPushButton *_btnAdd;
    QTableWidget *_tableWidget;
};

}
#endif // PARSEDATATCP_H
