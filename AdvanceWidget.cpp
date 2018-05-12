#include "AdvanceWidget.h"
#include "ui_AdvanceWidget.h"
#include "common/UtilsConfigure.h"

AdvanceWidget::AdvanceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdvanceWidget)
{
    ui->setupUi(this);
    yang::UtilsConfigure *config = yang::UtilsConfigure::getInstance();

    if(yang::SecretType::RC4 == config->getSecretType()) {
        ui->cboxSecret->setCurrentText("RC4");
        ui->lineEditSecret->setText(config->getSecretKey().c_str());
    }
    if(yang::CompressType::QuickLZ == config->getCompressType()) {
        ui->cboxCompress->setCurrentText("quicklz");
    }
}

AdvanceWidget::~AdvanceWidget()
{
    delete ui;
}

void AdvanceWidget::on_btnCancel_clicked()
{
    close();
}

void AdvanceWidget::on_btnOk_clicked()
{
    yang::UtilsConfigure *config = yang::UtilsConfigure::getInstance();

    QString currSecret = ui->cboxSecret->currentText();
    QString sec_txt = ui->lineEditSecret->text();
    QString currCompress = ui->cboxCompress->currentText();

    if(0 == currSecret.compare("none")) {
        config->setSecretType(yang::SecretType::NoSecret);
    } else if(0 == currSecret.compare("RC4")) {
        if(!sec_txt.isEmpty()) {
            config->setSecretType(yang::SecretType::RC4);
            config->setSecretKey(sec_txt.toStdString());
        }
    } else {
    }

    if(0 == currCompress.compare("none")) {
        config->setCompressType(yang::CompressType::NoCompress);
    } else if(0 == currCompress.compare("quicklz")){
        config->setCompressType(yang::CompressType::QuickLZ);
    }
    close();
}
