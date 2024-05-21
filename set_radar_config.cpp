#include "set_radar_config.h"
#include "ui_set_radar_config.h"



set_radar_config::set_radar_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::set_radar_config)
{
    ui->setupUi(this);
}

set_radar_config::~set_radar_config()
{
    delete ui;
}

void set_radar_config::showEvent(QShowEvent *EW)
{
    QDialog::showEvent(EW);
    ui->maxDist->clear();
    ui->sensor_id->clear();

    ui->output_type->setCurrentIndex(0);
    ui->radar_power->setCurrentIndex(0);
    ui->sort_index->setCurrentIndex(0);

    ui->CtrlRelay->setChecked(false);
    ui->SendExInfo->setChecked(false);
    ui->SendQuality->setChecked(false);
    ui->StoreInNVM->setChecked(false);
    ui->RCS_Threshold->setChecked(false);
}

void set_radar_config::on_applyButton_clicked()
{
  radar_config config={0,0,0,0,0,0,0};
  char prefix=0;
  char postfix=0;
  short msg_id=RADAR_CONFIG;
  char dlc=0x8;

  QString send_msg_data;

  if(ui->maxDist->value())
  {
      config.byte_0.bit.maxdistance_valid=1;
      config.maxdistance=ui->maxDist->value();
  }
  if(ui->sensor_id->value())
  {
      config.byte_4.bit.sensorID=ui->sensor_id->value();
      config.byte_0.bit.sensorID_valid=1;
  }
  if(ui->output_type->currentIndex())
  {
     config.byte_4.bit.outputtype=ui->output_type->currentIndex();
     config.byte_0.bit.outputtype_valid=1;
     switch (config.byte_4.bit.outputtype) {
     case 1:
          emit signal_show_all_fields();
         break;
     case 2:
          emit signal_hide_extended_fields();
         break;
     default:
         break;
     }
  }
  if(ui->radar_power->currentIndex())
  {
   config.byte_4.bit.radarpower=ui->radar_power->currentIndex()-1;
   config.byte_0.bit.radarpower_valid=1;
  }
  if(ui->sort_index->currentIndex())
  {
      config.byte_5.bit.sortindex=ui->sort_index->currentIndex();
      config.byte_0.bit.sortindex_valid=1;
  }
  if(ui->CtrlRelay->isChecked())
  {
    config.byte_5.bit.ctrlrelay=ui->CtrlRelay->isChecked();
    config.byte_5.bit.ctrlrelay_valid=1;
  }
  if(ui->SendQuality->isChecked())
  {
    config.byte_5.bit.sendquality=ui->SendQuality->isChecked();
    config.byte_0.bit.sendquality_valid=1;
  }
  if(ui->SendExInfo->isChecked())
  {
      config.byte_5.bit.sendextinfo=ui->SendExInfo->isChecked();
      config.byte_0.bit.sendextinfo_valid=1;
  }
  if(ui->StoreInNVM->isChecked())
  {
      config.byte_5.bit.storeinNVM=ui->StoreInNVM->isChecked();
      config.byte_0.bit.storeinNVM_valid=1;
  }
  if(ui->RCS_Threshold->isChecked())
  {
      config.byte_6.bit.RCS_Threshold=ui->RCS_Threshold->isChecked();
      config.byte_6.bit.RCS_threshold_valid=1;
  }
  send_msg_data=QString("%1%2%3%4%5%6%7%8%9%10%11").arg(prefix,1,16,QChar('0'))
                                      .arg(msg_id,3,16,QChar('0'))
                                      .arg(dlc,1,16,QChar('0'))
                                      .arg((unsigned int)config.byte_0.word,2,16,QChar('0'))
                                      .arg((unsigned int)config.maxdistance,4,16,QChar('0'))
                                      .arg((unsigned int)config.byte_3,2,16,QChar('0'))
                                      .arg((unsigned int)config.byte_4.word,2,16,QChar('0'))
                                      .arg((unsigned int)config.byte_5.word,2,16,QChar('0'))
                                      .arg((unsigned int)config.byte_6.word,2,16,QChar('0'))
                                      .arg((unsigned int)config.byte_7,2,16,QChar('0'))
                                      .arg(postfix,1,16,QChar('0'));
  emit signal_send_can_msg_radar_config(send_msg_data);
}
