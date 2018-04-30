#include <QResizeEvent>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDebug>
#include <cstdlib>
#include <QBrush>
#include <QColor>
#include "ParseDataTcp.h"
#include "ParseDataTcpItem.h"

namespace yang {
ParseDataTcp::ParseDataTcp(const QByteArray &datas, QWidget *parent)
    : QWidget(parent),
      COLUMN_COUNT(4),
      ROW_COUNT(8),
      _currCount(0),
      _currIndex(0),
      _datas(datas),
      _comboBox(nullptr),
      _lineEdit(nullptr),
      _btnAdd(nullptr),
      _tableWidget(nullptr)
{
    resize(parent->size());
    _comboBox = new QComboBox(this);
    _lineEdit = new QLineEdit(this);
    _btnAdd = new QPushButton(tr("Add"), this);
    _tableWidget = new QTableWidget(this);
    initComboBox();
    initTableWidget();
    connect(_btnAdd, &QPushButton::clicked, this, &ParseDataTcp::addCustomerItem);
}
void ParseDataTcp::initTableWidget()
{
    _tableWidget->setColumnCount(COLUMN_COUNT);
    _tableWidget->verticalHeader()->hide();
    _tableWidget->horizontalHeader()->hide();
    _tableWidget->horizontalHeader()->setDefaultSectionSize(_tableWidget->width()/COLUMN_COUNT);
    _tableWidget->verticalHeader()->setDefaultSectionSize(_tableWidget->height()/ROW_COUNT);
    _tableWidget->setGridStyle(Qt::SolidLine);
}
void ParseDataTcp::initComboBox()
{
    _comboBox->addItem("string", QVariant(INT_MAX));
    _comboBox->addItem("char", QVariant(1));
    _comboBox->addItem("int16_t", QVariant(2));
    _comboBox->addItem("int32_t", QVariant(4));
    _comboBox->addItem("int64_t", QVariant(8));
    _comboBox->addItem("float", QVariant(4));
    _comboBox->addItem("double", QVariant(8));
    _comboBox->addItem("int8_t", QVariant(1));
    _comboBox->addItem("uchar", QVariant(1));
    _comboBox->addItem("uint8_t", QVariant(1));
    _comboBox->addItem("uint16_t", QVariant(2));
    _comboBox->addItem("uint32_t", QVariant(4));
    _comboBox->addItem("uint64_t", QVariant(8));

    _comboBox->setCurrentText("string");
    _lineEdit->setEnabled(true);
    _lineEdit->setPlaceholderText("4");

    connect(_comboBox, &QComboBox::currentTextChanged, [this](const QString &type){
        if(0 == type.compare("string")) {
            _lineEdit->setEnabled(true);
        } else {
            _lineEdit->setEnabled(false);
        }
    });
}
char* ParseDataTcp::getDigital(int length)
{
    if(length + _currIndex > _datas.size()) return NULL;
    int r_idx;
    char *ret = new char[16];
    memset(ret, 0x00, 8);
    if(!isBigEndian()) { /* 小端 */
        for(r_idx=0; r_idx<length; r_idx++) {
            ret[r_idx] = _datas.at(_currIndex + r_idx);
        }
    } else { /* 大端 */
        for(r_idx = length-1; r_idx>=0; r_idx--) {
            ret[r_idx] = _datas.at(_currIndex + length - r_idx -1);
        }
    }
    _currIndex += length;
    return ret;
}

void ParseDataTcp::addCustomerItem()
{
    QString type = _comboBox->currentText();
    char value[256];
    memset(value, 0x00, sizeof(value));
    char *ptr = NULL;
    if(0 == type.compare("string")) {
        QString s_length = _lineEdit->text();
        if(s_length.isEmpty())    s_length = _lineEdit->placeholderText();
        int length = s_length.toInt();
        int len = 0;
        char c[2]; c[1] = '\0';
        std::string ret;
        for(len=0; len<length && len+_currIndex < _datas.size(); len++) {
            if('\0' == _datas.at(_currIndex + len)) {
                c[0] = '.';
            } else {
                c[0] = _datas.at(_currIndex + len);
            }
            ret.append(c);
        }
        _currIndex += len;
        qDebug() << ret.c_str();
        snprintf(value, ret.length()+1, "%s", ret.c_str());
    } else if(0 == type.compare("char")) {
        ptr = getDigital(1);
        if(NULL == ptr) return;
        snprintf(value, sizeof(value), "%c", *((char*)ptr));
    } else if(0 == type.compare("uchar")) {
        ptr = getDigital(1);
        if(NULL == ptr) return;
        snprintf(value, sizeof(value), "%c", *((uchar*)ptr));
    } else if(0 == type.compare("int8_t")) {
        ptr = getDigital(1);
        if(NULL == ptr) return;
        snprintf(value, sizeof(value), "%d", *((int8_t*)ptr));
    } else if(0 == type.compare("int16_t")) {
        ptr = getDigital(2);
        if(NULL == ptr) return;
        snprintf(value, sizeof(value), "%d", *((int16_t*)ptr));
    } else if(0 == type.compare("int32_t")) {
        ptr = getDigital(4);
        if(NULL == ptr) return;
        snprintf(value, sizeof(value), "%d", *((int32_t*)ptr));
    } else if(0 == type.compare("int64_t")) {
        ptr = getDigital(8);
        if(NULL == ptr) return;
        snprintf(value, sizeof(value), "%lld", *((int64_t*)ptr));
    } else if(0 == type.compare("uint8_t")) {
        ptr = getDigital(1);
        if(NULL == ptr) return;
        snprintf(value, sizeof(value), "%u", *((uint8_t *)ptr));
    } else if(0 == type.compare("uint16_t")) {
        ptr = getDigital(2);
        if(NULL == ptr) return;
        snprintf(value, sizeof(value), "%u", *((uint16_t *)ptr));
    } else if(0 == type.compare("uint32_t")) {
        ptr = getDigital(4);
        if(NULL == ptr) return;
        snprintf(value, sizeof(value), "%u", *((uint32_t *)ptr));
    } else if(0 == type.compare("uint64_t")) {
        ptr = getDigital(8);
        if(NULL == ptr) return;
        snprintf(value, sizeof(value), "%llu", *((uint64_t *)ptr));
    } else if(0 == type.compare("float")) {
        ptr = getDigital(4);
        if(NULL == ptr) return;
        snprintf(value, sizeof(value), "%lf", *((float *)ptr));
    } else if(0 == type.compare("double")) {
        ptr = getDigital(8);
        if(NULL == ptr) return;
        snprintf(value, sizeof(value), "%lf", *((double *)ptr));
    } else {
        qDebug() << "unknow";
    }
    delete []ptr;
    qDebug() << value;

    /* 添加到_tableWidget中去 */
    if(_currCount/_tableWidget->columnCount() >= _tableWidget->rowCount()) {
        _tableWidget->insertRow(_tableWidget->rowCount());
    }
    int row = _currCount/_tableWidget->columnCount();
    int column = _currCount%_tableWidget->columnCount();
    ParseDataTcpItem *item = new ParseDataTcpItem(type, value);
    _tableWidget->setCellWidget(row, column, item);
    if(0 != row%2) {
        item->setStyleSheet("background-color: #e9f5fc;");
    }
    _currCount++;
}

void ParseDataTcp::resizeEvent(QResizeEvent *event)
{
    int wd = event->size().width();
    int ht = event->size().height();

    _comboBox->setGeometry(0, 0.02*ht, 0.15*wd, 0.06*ht);
    _lineEdit->setGeometry(0.20*wd, 0.02*ht, 0.2*wd, 0.06*ht);
    _btnAdd->setGeometry(0.45*wd, 0.02*ht, 0.1*wd, 0.06*ht);

    _tableWidget->setGeometry(0, 0.1*ht, wd, 0.9*ht);
    _tableWidget->horizontalHeader()->setDefaultSectionSize((_tableWidget->width()-30)/COLUMN_COUNT);
    _tableWidget->verticalHeader()->setDefaultSectionSize(_tableWidget->height() / ROW_COUNT);
}

}
