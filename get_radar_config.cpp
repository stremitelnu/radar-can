#include "get_radar_config.h"
#include "ui_get_radar_config.h"
#include <QLabel>

get_radar_config::get_radar_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::get_radar_config)
{
    ui->setupUi(this);
    connect(ui->OkButton,&QPushButton::pressed,this,&get_radar_config::close);
}

get_radar_config::~get_radar_config()
{
    delete ui;

}

void get_radar_config::show_radar_config(radar_status *radar_config)
{
    short MaxDistanceCfg=(radar_config->MaxDistanceCfg_msb<<2)|(radar_config->MaxDistanceCfg_lsb&0x03);
    char RadarPowerCfg=((radar_config->RadarPowerCfg_msb&0x03)<<1)|(radar_config->RadarPowerCfg_lsb&0x01);
    //char temp=0;
      /*            */
    if(radar_config->NVMReadStatus)
    {
        ui->read_status->setText("Successful");
     }
    else
    {
        ui->read_status->setText("Failed");
    }
      /*            */
    if(radar_config->NVMwriteStatus)
    {
        ui->write_status->setText("Successful");
     }
    else
    {
        ui->write_status->setText("Failed");
    }
      /*            */
    if(radar_config->Persistent_Error)
    {
        ui->persistent_err->setText("error active");
     }
    else
    {
        ui->persistent_err->setText("No error");
    }
      /*            */
    if(radar_config->Interference)
    {
        ui->interference->setText("Interference detected");
     }
    else
    {
        ui->interference->setText("No interference");
    }
      /*            */
    if(radar_config->Temperature_Error)
    {
        ui->temp_err->setText("error active");
     }
    else
    {
        ui->temp_err->setText("No error");
    }
      /*            */
    if(radar_config->Temporary_Error)
    {
        ui->temporary_err->setText("error active");
     }
    else
    {
        ui->temporary_err->setText("No error");
    }
      /*            */
    if(radar_config->Voltage_Error)
    {
        ui->voltage_err->setText("error active");
     }
    else
    {
        ui->voltage_err->setText("No error");
    }
      /*            */
    switch ((radar_config->SortIndex&0x07)) {
    case 0:
        ui->sort_index->setText("no sorting");
        break;
    case 1:
        ui->sort_index->setText("sorted by range");
        break;
    case 2:
        ui->sort_index->setText("sorted by RCS");
        break;
    default:
        break;
    }
      /*            */
    switch (RadarPowerCfg) {
    case 0:
        ui->power_cfg->setText("Standard");
        break;
    case 1:
        ui->power_cfg->setText("-3dB Tx gain");
        break;
    case 2:
        ui->power_cfg->setText("-6dB Tx gain");
        break;
    case 3:
        ui->power_cfg->setText("-9dB Tx gain");
        break;
    default:
        break;
    }
      /*            */
    if(radar_config->CtrlRelayCfg)
    {
        ui->relay_cfg->setText("active");
     }
    else
    {
        ui->relay_cfg->setText("inactive");
    }
      /*            */
    switch ((radar_config->OutputTypeCfg&0x03)) {
    case 0:
        ui->output_type->setText("none");
        break;
    case 1:
        ui->output_type->setText("send objects");
        break;
    case 2:
        ui->output_type->setText("send clusters");
        break;
    default:
        break;
    }
     /*            */
    if(radar_config->SendQualityCfg)
    {
        ui->send_qality->setText("active");
     }
    else
    {
        ui->send_qality->setText("inactive");
    }
  /*            */
    if(radar_config->SendExtInfoCfg)
    {
        ui->send_ext->setText("active");
     }
    else
    {
        ui->send_ext->setText("inactive");
    }
  /*            */
    switch ((radar_config->MotionRxState&0x03)) {
    case 0:
        ui->motion_state->setText("input ok");
        break;
    case 1:
        ui->motion_state->setText("speed missing");
        break;
    case 2:
        ui->motion_state->setText("yaw rate missing");
        break;
    case 3:
        ui->motion_state->setText("speed and yaw rate missing");
        break;
    default:
        break;
    }
      /*            */
    if(radar_config->RCS_Threshold)
    {
        ui->rcs_threshold->setText("High sensitivity");
     }
    else
    {
        ui->rcs_threshold->setText("Standard");
    }

    ui->distanse->setNum(MaxDistanceCfg/2);
    ui->sensor_id->setNum(radar_config->SensorID);
}
