#include "set_radar_filter.h"
#include "ui_set_radar_filter.h"

set_radar_filter::set_radar_filter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::set_radar_filter)
{


    ui->setupUi(this);

    bar = new QStatusBar(this);
    status = new QLabel;
    Event = new QEventLoop(this);
    Timer = new QTimer(this);
    Timer->setInterval(1000);
    connect(Timer,SIGNAL(timeout()),Event,SLOT(quit()));
    bar->addWidget(status);
    bar->setGeometry(0,275,400,20);

    gate_min = new QDoubleSpinBox(this);
    gate_max = new QDoubleSpinBox(this);
    gate_min->setGeometry(60,170,60,20);
    gate_max->setGeometry(175,170,60,20);
    gate_max->setDecimals(4);
    gate_min->setDecimals(4);
    gate_max->hide();
    gate_min->hide();

}

set_radar_filter::~set_radar_filter()
{
    delete ui;
}

void set_radar_filter::filter_config_check(radar_filter *data)
{
  if(data->byte_0.bit.FilterCfg_Active)
  {
      switch (data->byte_0.bit.FilterCfg_Index) {
      case  0:
          status->setText("Filter NofObj was applied");
          break;
      case  1:
          status->setText("Filter Distance was applied");
          break;
      case  2:
          status->setText("Filter Azimuth was applied");
          break;
      case  3:
          status->setText("Filter VrelOncome was applied");
          break;
      case  4:
          status->setText("Filter VrelDepart was applied");
          break;
      case  5:
          status->setText("Filter RCS was applied");
          break;
      case 6:
          status->setText("Filter Lifetime was applied");
          break;
      case  7:
          status->setText("Filter Size was applied");
          break;
      case  8:
          status->setText("Filter ProbExists was applied");
          break;
      case  9:
          status->setText("Filter Y was applied");
          break;
      case  10:
          status->setText("Filter X was applied");
          break;
      case  11:
          status->setText("Filter VYRightLeft was applied");
          break;
      case  12:
          status->setText("Filter VXOncome was applied");
          break;
      case  13:
          status->setText("Filter VYLeftRight was applied");
          break;
      case  14:
          status->setText("Filter VXDepart was applied");
          break;
      case  15:
          status->setText("Filter Object_Class was applied");
          break;
      default:
          break;
      }
  }
  else
  {
      switch (data->byte_0.bit.FilterCfg_Index) {
      case  0:
          status->setText("Filter NofObj was canceled");
          break;
      case  1:
          status->setText("Filter Distance was canceled");
          break;
      case  2:
          status->setText("Filter Azimuth was canceled");
          break;
      case  3:
          status->setText("Filter VrelOncome was canceled");
          break;
      case  4:
          status->setText("Filter VrelDepart was canceled");
          break;
      case  5:
          status->setText("Filter RCS was canceled");
          break;
      case 6:
          status->setText("Filter Lifetime was canceled");
          break;
      case  7:
          status->setText("Filter Size was canceled");
          break;
      case  8:
          status->setText("Filter ProbExists was canceled");
          break;
      case  9:
          status->setText("Filter Y was canceled");
          break;
      case  10:
          status->setText("Filter X was canceled");
          break;
      case  11:
          status->setText("Filter VYRightLeft was canceled");
          break;
      case  12:
          status->setText("Filter VXOncome was canceled");
          break;
      case  13:
          status->setText("Filter VYLeftRight was canceled");
          break;
      case  14:
          status->setText("Filter VXDepart was canceled");
          break;
      case  15:
          status->setText("Filter Object_Class was canceled");
          break;
      default:
          break;
      }
  }
}

void set_radar_filter::showEvent(QShowEvent *EW)
{
    QDialog::showEvent(EW);

    ui->filter_type->setCurrentIndex(0);
    ui->filter_index->clear();
    ui->filter_active->setChecked(false);
    ui->filter_valid->setChecked(false);
    gate_max->clear();
    gate_min->clear();
    gate_max->hide();
    gate_min->hide();
    ui->unit->clear();
    status->setText("");
}

void set_radar_filter::on_filter_type_currentIndexChanged(int index)
{
    QStringList str_cluster;
    QStringList str_object;


    str_cluster<<"NofObj"<<"Distance"<<"Azimuth"<<"VrelOncome"<<"VrelDepart"<<"RCS";
    str_object<<"NofObj"<<"Distance"<<"Azimuth"<<"VrelOncome"<<"VrelDepart"<<"RCS"
             <<"Lifetime"<<"Size"<<"ProbExists"<<"Y"<<"X"<<"VYRightLeft"<<"VXOncome"<<"VYLeftRight"<<"VXDepart"<<"Object_Class";

    switch (index) {
    case 0:

        break;
    case 1:
        if(!ui->filter_index->count())
         {
           ui->filter_index->addItems(str_cluster);
         }
        else
        {
            ui->filter_index->clear();
            ui->filter_index->addItems(str_cluster);
        }
        break;
    case 2:
        if(!ui->filter_index->count())
         {
           ui->filter_index->addItems(str_object);
        }
        else
        {
            ui->filter_index->clear();
            ui->filter_index->addItems(str_object);
        }
        break;
    default:
        break;
    }



}

void set_radar_filter::on_filter_index_currentIndexChanged(int index)
{

    switch (index) {
    case 0:
          ui->unit->setText("ignored");
          gate_min->setRange(0.0,4095.0);
          gate_max->setRange(0.0,4095.0);
          gate_max->setSingleStep(1.0);
          gate_min->setSingleStep(1.0);
          gate_max->setValue(0);
          gate_min->setValue(0);
          gate_max->show();
          gate_min->show();
        break;
    case 1:
          ui->unit->setText("m");
          gate_min->setRange(0.0,409.5);
          gate_max->setRange(0.0,409.5);
          gate_max->setSingleStep(0.1);
          gate_min->setSingleStep(0.1);
          gate_max->setValue(0);
          gate_min->setValue(0);
          gate_max->show();
          gate_min->show();
        break;
    case 2:
        ui->unit->setText("deg");
        gate_min->setRange(-50.0,52.375);
        gate_max->setRange(-50.0,52.375);
        gate_max->setSingleStep(0.025);
        gate_min->setSingleStep(0.025);
        gate_max->setValue(0);
        gate_min->setValue(0);
        gate_max->show();
        gate_min->show();
        break;
    case 3:
        ui->unit->setText("m/s");
        gate_min->setRange(0.0,128.993);
        gate_max->setRange(0.0,128.993);
        gate_max->setSingleStep(0.0315);
        gate_min->setSingleStep(0.0315);
        gate_max->setValue(0);
        gate_min->setValue(0);
        gate_max->show();
        gate_min->show();
        break;
    case 4:
        ui->unit->setText("m/s");
        gate_min->setRange(0.0,128.993);
        gate_max->setRange(0.0,128.993);
        gate_max->setSingleStep(0.0315);
        gate_min->setSingleStep(0.0315);
        gate_max->setValue(0);
        gate_min->setValue(0);
        gate_max->show();
        gate_min->show();
        break;
    case 5:
        ui->unit->setText("dBm*dBm");
        gate_min->setRange(-50.0,52.375);
        gate_max->setRange(-50.0,52.375);
        gate_max->setSingleStep(0.025);
        gate_min->setSingleStep(0.025);
        gate_max->setValue(0);
        gate_min->setValue(0);
        gate_max->show();
        gate_min->show();
        break;
    case 6:
        ui->unit->setText("s");
        gate_min->setRange(0.0,409.5);
        gate_max->setRange(0.0,409.5);
        gate_max->setSingleStep(0.1);
        gate_min->setSingleStep(0.1);
        gate_max->setValue(0);
        gate_min->setValue(0);
        gate_max->show();
        gate_min->show();
        break;
    case 7:
        ui->unit->setText("m*m");
        gate_min->setRange(0.0,102.375);
        gate_max->setRange(0.0,102.375);
        gate_max->setSingleStep(0.025);
        gate_min->setSingleStep(0.025);
        gate_max->setValue(0);
        gate_min->setValue(0);
        gate_max->show();
        gate_min->show();
        break;
    case 8:
        ui->unit->setText("");
        gate_min->setRange(0.0,7.0);
        gate_max->setRange(0.0,7.0);
        gate_max->setSingleStep(1.0);
        gate_min->setSingleStep(1.0);
        gate_max->setValue(0);
        gate_min->setValue(0);
        gate_max->show();
        gate_min->show();
        break;
    case 9:
        ui->unit->setText("m");
        gate_min->setRange(-409.5,409.5);
        gate_max->setRange(-409.5,409.5);
        gate_max->setSingleStep(0.02);
        gate_min->setSingleStep(0.02);
        gate_max->setValue(0);
        gate_min->setValue(0);
        gate_max->show();
        gate_min->show();
        break;
    case 10:
        ui->unit->setText("m");
        gate_min->setRange(-500.0,1138.2);
        gate_max->setRange(-500.0,1138.2);
        gate_max->setSingleStep(0.02);
        gate_min->setSingleStep(0.02);
        gate_max->setValue(0);
        gate_min->setValue(0);
        gate_max->show();
        gate_min->show();
        break;
    case 11:
        ui->unit->setText("m/s");
        gate_min->setRange(0.0,128.993);
        gate_max->setRange(0.0,128.993);
        gate_max->setSingleStep(0.0315);
        gate_min->setSingleStep(0.0315);
        gate_max->setValue(0);
        gate_min->setValue(0);
        gate_max->show();
        gate_min->show();
        break;
    case 12:
        ui->unit->setText("m/s");
        gate_min->setRange(0.0,128.993);
        gate_max->setRange(0.0,128.993);
        gate_max->setSingleStep(0.0315);
        gate_min->setSingleStep(0.0315);
        gate_max->setValue(0);
        gate_min->setValue(0);
        gate_max->show();
        gate_min->show();
        break;
    case 13:
        ui->unit->setText("m/s");
        gate_min->setRange(0.0,128.993);
        gate_max->setRange(0.0,128.993);
        gate_max->setSingleStep(0.0315);
        gate_min->setSingleStep(0.0315);
        gate_max->setValue(0);
        gate_min->setValue(0);
        gate_max->show();
        gate_min->show();
        break;
    case 14:
        ui->unit->setText("m/s");
        gate_min->setRange(0.0,128.993);
        gate_max->setRange(0.0,128.993);
        gate_max->setSingleStep(0.0315);
        gate_min->setSingleStep(0.0315);
        gate_max->setValue(0);
        gate_min->setValue(0);
        gate_max->show();
        gate_min->show();
        break;
    case 15:
        gate_min->setRange(0,7);
        gate_max->setRange(0,7);
        gate_max->setSingleStep(1);
        gate_min->setSingleStep(1);
        gate_max->setValue(0);
        gate_min->setValue(0);
        gate_max->show();
        gate_min->show();
        break;
    default:
        break;
    }
}

void set_radar_filter::on_pushButton_clicked()
{
    QString send_msg_data;
    radar_filter msg_filter={0,0,0};
    float dist_min=0,dist_max=409.5,rsc_min=-50,rsc_max=52.375;
    float obj_min=0,obj_max=4095,azimuth_min=-50,azimuth_max=50.375;
    float oncome_min=0,oncome_max=128.993,depart_min=0,depart_max=128.993;
    float lifetime_min=0,lifetime_max=409.5,size_min=0,size_max=102.375;
    float Ypos_min=-409.5,Ypos_max=409.5,Xpos_min=-500,Xpos_max=1138.2;
    float V_min=0,V_max=128.993;
    int range=0xFFF;
    int range2=0x1FFF;
    char prefix=0;
    char postfix=0;
    short msg_id=RADAR_FILTER;
    char dlc=0x5;
    float temp;

    if(ui->filter_active->isChecked())
    {
        msg_filter.byte_0.bit.FilterCfg_Active=1;
    }
    if(ui->filter_valid->isChecked())
    {
        msg_filter.byte_0.bit.FilterCfg_Valid=1;
    }
    msg_filter.byte_0.bit.FilterCfg_Type=ui->filter_type->currentIndex()-1;
    msg_filter.byte_0.bit.FilterCfg_Index=ui->filter_index->currentIndex();
    switch (ui->filter_index->currentIndex()) {
    case 0:
        temp=gate_min->value();
        temp +=obj_min;
        temp *=range;
        temp /=(obj_max-obj_min);
        msg_filter.min_value=(short)temp;

        temp=gate_max->value();
        temp +=obj_min;
        temp *=range;
        temp /=(obj_max-obj_min);
        msg_filter.max_value=(short)temp;
        break;
    case 1:
        temp=gate_min->value();
        temp +=dist_min;
        temp *=range;
        temp /=(dist_max-dist_min);
        msg_filter.min_value=(short)temp;

        temp=gate_max->value();
        temp +=dist_min;
        temp *=range;
        temp /=(dist_max-dist_min);
        msg_filter.max_value=(short)temp;
        break;
    case 2:
        temp=gate_min->value();
        temp +=azimuth_min;
        temp *=range;
        temp /=(azimuth_max-azimuth_min);
        msg_filter.min_value=(short)temp;

        temp=gate_max->value();
        temp +=azimuth_min;
        temp *=range;
        temp /=(azimuth_max-azimuth_min);
        msg_filter.max_value=(short)temp;
        break;
    case 3:
        temp=gate_min->value();
        temp +=oncome_min;
        temp *=range;
        temp /=(oncome_max-oncome_min);
        msg_filter.min_value=(short)temp;

        temp=gate_max->value();
        temp +=oncome_min;
        temp *=range;
        temp /=(oncome_max-oncome_min);
        msg_filter.max_value=(short)temp;
        break;
    case 4:
        temp=gate_min->value();
        temp +=depart_min;
        temp *=range;
        temp /=(depart_max-depart_min);
        msg_filter.min_value=(short)temp;

        temp=gate_max->value();
        temp +=depart_min;
        temp *=range;
        temp /=(depart_max-depart_min);
        msg_filter.max_value=(short)temp;
        break;
    case 5:
        temp=gate_min->value();
        temp +=rsc_min;
        temp *=range;
        temp /=(rsc_max-rsc_min);
        msg_filter.min_value=(short)temp;
        temp=gate_max->value();
        temp +=rsc_min;
        temp *=range;
        temp /=(rsc_max-rsc_min);
        msg_filter.max_value=(short)temp;
        break;
    case 6:
        temp=gate_min->value();
        temp +=lifetime_min;
        temp *=range;
        temp /=(lifetime_max-lifetime_min);
        msg_filter.min_value=(short)temp;
        temp=gate_max->value();
        temp +=lifetime_min;
        temp *=range;
        temp /=(lifetime_max-lifetime_min);
        msg_filter.max_value=(short)temp;
        break;
    case 7:
        temp=gate_min->value();
        temp +=size_min;
        temp *=range;
        temp /=(size_max-size_min);
        msg_filter.min_value=(short)temp;
        temp=gate_max->value();
        temp +=size_min;
        temp *=range;
        temp /=(size_max-size_min);
        msg_filter.max_value=(short)temp;
        break;
    case 8:
        msg_filter.min_value=gate_min->value();
        msg_filter.max_value=gate_max->value();
        break;
    case 9:
        temp=gate_min->value();
        temp +=Ypos_min;
        temp *=range;
        temp /=(Ypos_max-Ypos_min);
        msg_filter.min_value=(short)temp;
        temp=gate_max->value();
        temp +=Ypos_min;
        temp *=range;
        temp /=(Ypos_max-Ypos_min);
        msg_filter.max_value=(short)temp;
        break;
    case 10:
        temp=gate_min->value();
        temp +=Xpos_min;
        temp *=range2;
        temp /=(Xpos_max-Xpos_min);
        msg_filter.min_value=(short)temp;
        temp=gate_max->value();
        temp +=Xpos_min;
        temp *=range2;
        temp /=(Xpos_max-Xpos_min);
        msg_filter.max_value=(short)temp;
        break;
    case 11:
        temp=gate_min->value();
        temp +=V_min;
        temp *=range;
        temp /=(V_max-V_min);
        msg_filter.min_value=(short)temp;

        temp=gate_max->value();
        temp +=V_min;
        temp *=range;
        temp /=(V_max-V_min);
        msg_filter.max_value=(short)temp;
        break;
    case 12:
        temp=gate_min->value();
        temp +=V_min;
        temp *=range;
        temp /=(V_max-V_min);
        msg_filter.min_value=(short)temp;

        temp=gate_max->value();
        temp +=V_min;
        temp *=range;
        temp /=(V_max-V_min);
        msg_filter.max_value=(short)temp;
        break;
    case 13:
        temp=gate_min->value();
        temp +=V_min;
        temp *=range;
        temp /=(V_max-V_min);
        msg_filter.min_value=(short)temp;

        temp=gate_max->value();
        temp +=V_min;
        temp *=range;
        temp /=(V_max-V_min);
        msg_filter.max_value=(short)temp;
        break;
    case 14:
        temp=gate_min->value();
        temp +=V_min;
        temp *=range;
        temp /=(V_max-V_min);
        msg_filter.min_value=(short)temp;

        temp=gate_max->value();
        temp +=V_min;
        temp *=range;
        temp /=(V_max-V_min);
        msg_filter.max_value=(short)temp;
        break;
    case 15:
        msg_filter.min_value=gate_min->value();
        msg_filter.max_value=gate_max->value();
        break;
    default:
        break;
    }
 msg_filter.max_value &=0xFFF;
 msg_filter.min_value &=0xFFF;
 send_msg_data=QString("%1%2%3%4%5%6%7").arg(prefix,1,16,QChar('0'))
                                     .arg(msg_id,3,16,QChar('0'))
                                     .arg(dlc,1,16,QChar('0'))
                                     .arg((unsigned int)msg_filter.byte_0.word,2,16,QChar('0'))
                                     .arg((int)msg_filter.min_value,4,16,QChar('0'))
                                     .arg((int)msg_filter.max_value,4,16,QChar('0'))
                                     .arg(postfix,1,16,QChar('0'));
 emit signal_send_can_msg_filter_config(send_msg_data);
}

void set_radar_filter::on_clear_all_filters_clicked()
{
 radar_filter msg_clear_filter;
 QString send_msg_data;
 char prefix=0;
 char postfix=0;
 short msg_id=RADAR_FILTER;
 char dlc=0x5;

 msg_clear_filter.byte_0.word=0;
 msg_clear_filter.max_value=0;
 msg_clear_filter.min_value=0;
 msg_clear_filter.byte_0.bit.FilterCfg_Valid=1;
 for(msg_clear_filter.byte_0.bit.FilterCfg_Index=0;msg_clear_filter.byte_0.bit.FilterCfg_Index<FILTER_COUNT_CLASTER;msg_clear_filter.byte_0.bit.FilterCfg_Index++)
 {
  send_msg_data=QString("%1%2%3%4%5%6%7").arg(prefix,1,16,QChar('0'))
                                     .arg(msg_id,3,16,QChar('0'))
                                     .arg(dlc,1,16,QChar('0'))
                                     .arg((unsigned int)msg_clear_filter.byte_0.word,2,16,QChar('0'))
                                     .arg((int)msg_clear_filter.min_value,4,16,QChar('0'))
                                     .arg((int)msg_clear_filter.max_value,4,16,QChar('0'))
                                     .arg(postfix,1,16,QChar('0'));
  Timer->start();
  emit signal_send_can_msg_filter_config(send_msg_data);
  Event->exec();
  Timer->stop();
 }

 msg_clear_filter.byte_0.bit.FilterCfg_Type=1;
 for(msg_clear_filter.byte_0.bit.FilterCfg_Index=0;msg_clear_filter.byte_0.bit.FilterCfg_Index<FILTER_COUNT_OBJECT;msg_clear_filter.byte_0.bit.FilterCfg_Index++)
 {
  send_msg_data=QString("%1%2%3%4%5%6%7").arg(prefix,1,16,QChar('0'))
                                     .arg(msg_id,3,16,QChar('0'))
                                     .arg(dlc,1,16,QChar('0'))
                                     .arg((unsigned int)msg_clear_filter.byte_0.word,2,16,QChar('0'))
                                     .arg((int)msg_clear_filter.min_value,4,16,QChar('0'))
                                     .arg((int)msg_clear_filter.max_value,4,16,QChar('0'))
                                     .arg(postfix,1,16,QChar('0'));
  emit signal_send_can_msg_filter_config(send_msg_data);
  Event->exec();
 }
}
