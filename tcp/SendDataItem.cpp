#include "SendDataItem.h"
#include <QDebug>
namespace yang {
SendDataItem::SendDataItem(int index, const QSize &size, QWidget *parent)
    : QWidget(parent),
      _labelNumber(nullptr),
      _comboBox(nullptr),
      _lineEdit(nullptr),
      _btn_remove(nullptr)
{
    resize(size);
    _labelNumber = new QLabel(this);
    _labelNumber->setText(std::to_string(index).c_str());
    _btn_remove = new QPushButton(tr("删除"), this);
    _lineEdit = new QLineEdit(this);
    _comboBox = new QComboBox(this);
    initComboBox();
    connect(_btn_remove, &QPushButton::clicked, this, &SendDataItem::remove_btn_clicked);
    connect(_lineEdit, &QLineEdit::textChanged, this, &SendDataItem::text_value_changed);
}

SendDataItem::~SendDataItem()
{
}
void SendDataItem::updateIndex(int index)
{
    _labelNumber->setText(std::to_string(index).c_str());
}

void SendDataItem::resizeEvent(QResizeEvent *event)
{
    int wd = size().width();
    int ht = size().height();
    _labelNumber->setGeometry(0, 0.1*ht, 0.05*wd, 0.9*ht);
    _comboBox->setGeometry(0.05*wd, 0.1*ht, 0.15*wd, 0.9*ht);
    _lineEdit->setGeometry(0.22*wd, 0.1*ht, 0.71*wd, 0.9*ht);
    _btn_remove->setGeometry(0.95*wd, 0.1*ht, 0.05*wd, 0.9*ht);

    QWidget::resizeEvent(event);
}
void SendDataItem::remove_btn_clicked()
{
    emit removeItemSignal();
}

QByteArray SendDataItem::getItemData()
{
    QByteArray bytes;
    bytes.clear();
    std::string typeName = _comboBox->currentText().toStdString();
    QString value = _lineEdit->text();

    QDataStream out(&bytes, QIODevice::WriteOnly);
    if(0 == typeName.compare("string")) {
        for(int i=0; i<value.size(); i++) {
            bytes.append(value.at(i));
        }
        return bytes;
    }
    value = value.trimmed();
    if(0 == value.size()) {
        return bytes;
    }
    if(0 == typeName.compare("char") || 0 == typeName.compare("u_char")) {
        out << (signed char)value.toStdString().at(0);
    } else if(0 == typeName.compare("int8_t")) {
        out << (qint8)value.toLongLong();
    } else if(0 == typeName.compare("int16_t")) {
        out << (qint16)value.toLongLong();
    } else if(0 == typeName.compare("int32_t")) {
        out << (qint32)value.toLongLong();
    } else if(0 == typeName.compare("int64_t")) {
        out << (int64_t)value.toLongLong();
    } else if(0 == typeName.compare("uint8_t")) {
        out << (uint8_t)value.toLongLong();
    } else if(0 == typeName.compare("uint16_t")) {
        out << (int16_t)value.toLongLong();
    } else if(0 == typeName.compare("uint32_t")) {
        out << (int32_t)value.toLongLong();
    } else if(0 == typeName.compare("uint64_t")) {
        out << (int64_t)value.toLongLong();
    } else if(0 == typeName.compare("float")) {
        char ptr[4];    memset(ptr, 0x00, sizeof(ptr));
        float f = value.toFloat();
        memcpy(ptr, &f, sizeof(float));
        for(int i=3; i>=0; i--)  bytes.append(ptr[i]);
    } else if(0 == typeName.compare("double")) {
        out << (double)value.toDouble();
    }
    qDebug() << bytes.size();
    return bytes;
}

void SendDataItem::text_value_changed(const QString &text)
{
    text.size();
}

void SendDataItem::initComboBox()
{
    _comboBox->addItem(tr("string"), QVariant(INT_MIN));
    _comboBox->addItem(tr("char"), QVariant(1));
    _comboBox->addItem(tr("int8_t"), QVariant(1));
    _comboBox->addItem(tr("int16_t"), QVariant(2));
    _comboBox->addItem(tr("int32_t"), QVariant(4));
    _comboBox->addItem(tr("int64_t"), QVariant(8));
    _comboBox->addItem(tr("float"), QVariant(4));
    _comboBox->addItem(tr("double"), QVariant(8));

    _comboBox->addItem(tr("u_char"), QVariant(1));
    _comboBox->addItem(tr("uint8_t"), QVariant(1));
    _comboBox->addItem(tr("uint16_t"), QVariant(2));
    _comboBox->addItem(tr("uint32_t"), QVariant(4));
    _comboBox->addItem(tr("uint64_t"), QVariant(8));
}
}
