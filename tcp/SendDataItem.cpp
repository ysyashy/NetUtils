#include "SendDataItem.h"
namespace yang {
SendDataItem::SendDataItem(const QSize &size, QWidget *parent)
    : QWidget(parent),
      _comboBox(nullptr),
      _lineEdit(nullptr),
      _btn_remove(nullptr)
{
    resize(size);
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

void SendDataItem::resizeEvent(QResizeEvent *event)
{
    int wd = size().width();
    int ht = size().height();
    _comboBox->setGeometry(0, 0.1*ht, 0.2*wd, 0.9*ht);
    _lineEdit->setGeometry(0.22*wd, 0.1*ht, 0.71*wd, 0.9*ht);
    _btn_remove->setGeometry(0.95*wd, 0.1*ht, 0.05*wd, 0.9*ht);

    QWidget::resizeEvent(event);
}
void SendDataItem::remove_btn_clicked()
{
    emit removeItemSignal();
}

void SendDataItem::text_value_changed(const QString &text)
{

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
