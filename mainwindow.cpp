/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"
#include "can_msg.h"
#include "can_message.h"
#include "get_radar_config.h"
#include "set_radar_config.h"
#include "set_radar_filter.h"

#include <QMessageBox>
#include <QLabel>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QString>
#include <QScrollArea>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

extern object_inf all_obj_inf[];
//! [0]
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    int w=105,h=16;
//! [0]
    ui->setupUi(this);
    //console = new Console;
    //console->setEnabled(false);
    //setCentralWidget(console);
//! [1]
    serial = new QSerialPort(this);
//! [1]
    settings = new SettingsDialog;

    raw_message = new can_message;

    radar_get_configDialog = new get_radar_config();
    radar_set_configDialog = new set_radar_config();
    radar_set_filterDialog = new set_radar_filter();
    position_viewDialog =new position_view();
    Clear_windows_timer =new QTimer(this);

    QObject::connect(raw_message,SIGNAL(get_config(radar_status*)),radar_get_configDialog,SLOT(show_radar_config(radar_status*)));
    QObject::connect(raw_message,SIGNAL(get_cluster_inf(cluster_inf)),SLOT(display_cluster_param(cluster_inf)));
    QObject::connect(raw_message,SIGNAL(get_num_cluster(cluster_list*)),SLOT(show_cluster_label(cluster_list*)));

    QObject::connect(raw_message,SIGNAL(get_object_inf(object_inf)),SLOT(display_object_param(object_inf)));
    QObject::connect(raw_message,SIGNAL(get_num_object(object_list*)),SLOT(show_object_label(object_list*)));

    QObject::connect(radar_set_configDialog,SIGNAL(signal_send_can_msg_radar_config(QString)),SLOT(send_can_msg(QString)));
    QObject::connect(radar_set_configDialog,SIGNAL(signal_hide_extended_fields()),SLOT(hide_extended_fields()));
    QObject::connect(radar_set_configDialog,SIGNAL(signal_show_all_fields()),SLOT(show_all_fields()));
    QObject::connect(radar_set_filterDialog,SIGNAL(signal_send_can_msg_filter_config(QString)),SLOT(send_can_msg(QString)));
    QObject::connect(raw_message,SIGNAL(signal_filter_config_state(radar_filter*)),radar_set_filterDialog,SLOT(filter_config_check(radar_filter *)));
    QObject::connect(raw_message,SIGNAL(signal_display_point(cluster_inf)),position_viewDialog,SLOT(display_object_point(cluster_inf)));
     QObject::connect(raw_message,SIGNAL(signal_filter_state()),radar_set_filterDialog->Event,SLOT(quit()));
     QObject::connect(Clear_windows_timer,SIGNAL(timeout()),SLOT(clear_data()));
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);
    ui->actionCAN_Connect->setEnabled(true);
    ui->actionDisconnect_CAN->setEnabled(false);
    status = new QLabel;
    ui->statusBar->addWidget(status);
    Clear_windows_timer->setInterval(60000);

    QGridLayout * gLayout=new QGridLayout(ui->centralWidget);
    QScrollArea * scroll_area=new QScrollArea(ui->centralWidget);
    scroll_area->setGeometry(0,55,1300,370);
    scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    gLayout->addWidget(scroll_area,0,0);
    QWidget * scroll_area_Widget=new QWidget(scroll_area);
    QGridLayout * gLayout_scrol_area=new QGridLayout(scroll_area_Widget);
    gLayout_scrol_area->setHorizontalSpacing(5);
    gLayout_scrol_area->setVerticalSpacing(10);
    for(int i=0;i<11;i++)
    {
        gLayout_scrol_area->setColumnMinimumWidth(i,105);
    }

    gLayout_scrol_area->addWidget(ui->num,0,0,Qt::AlignCenter);
    gLayout_scrol_area->addWidget(ui->distlong,0,1,Qt::AlignCenter);
    gLayout_scrol_area->addWidget(ui->distlat,0,2,Qt::AlignCenter);
    gLayout_scrol_area->addWidget(ui->vrellong,0,3,Qt::AlignCenter);
    gLayout_scrol_area->addWidget(ui->vrellat,0,4,Qt::AlignCenter);
    gLayout_scrol_area->addWidget(ui->rcs,0,5,Qt::AlignCenter);
    gLayout_scrol_area->addWidget(ui->angel,0,6,Qt::AlignCenter);
    gLayout_scrol_area->addWidget(ui->lenght,0,7,Qt::AlignCenter);
    gLayout_scrol_area->addWidget(ui->width,0,8,Qt::AlignCenter);
    gLayout_scrol_area->addWidget(ui->class_2,0,9,Qt::AlignCenter);
    gLayout_scrol_area->addWidget(ui->propertis,0,10,Qt::AlignCenter);


    for(int i=0,j=1,k=0;i<=COUNT_OBJ*FIELDS_FOR_OBJECT;i++)//создаем текстовые объекты для всех возможных объектов
    {
      text_object.append(new QLabel(scroll_area_Widget));
      text_object.at(i)->setGeometry(0,0,w,h);
      if(k==11)
      {
       j++;
       k=0;
      }
      gLayout_scrol_area->addWidget(text_object.at(i),j,k,Qt::AlignCenter);
      k++;

    }
    scroll_area->setWidget(scroll_area_Widget);
    Clear_windows_timer->start();
    initActionsConnections();
    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &MainWindow::handleError);

//! [2]
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
//! [2]
    //connect(console, &Console::getData, this, &MainWindow::writeData);
//! [3]
}
//! [3]

MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
}

void MainWindow::connect_Can()
{
    QByteArray can_analyzer_init;

    can_analyzer_init.resize(5);

    can_analyzer_init[0]=0x53;
    can_analyzer_init[1]=0x36;
    can_analyzer_init[2]='\r';
    can_analyzer_init[3]=0x4F;
    can_analyzer_init[4]='\r';
    serial->write(can_analyzer_init);

    ui->actionCAN_Connect->setEnabled(false);
    ui->actionDisconnect_CAN->setEnabled(true);
    showStatusMessage(tr("CAN Connected  baud rate:500kbps"));
}

void MainWindow::disconnect_CAN()
{
    QByteArray can_analyzer_disconnect;

    can_analyzer_disconnect.resize(2);

    can_analyzer_disconnect[0]=0x43;
    can_analyzer_disconnect[1]='\r';


    serial->write(can_analyzer_disconnect);
    ui->actionCAN_Connect->setEnabled(true);
    ui->actionDisconnect_CAN->setEnabled(false);
    showStatusMessage(tr("CAN Disconnected"));

}

//! [4]
void MainWindow::openSerialPort()
{

    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        //console->setEnabled(true);
        //console->setLocalEchoEnabled(p.localEchoEnabled);
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        ui->actionConfigure->setEnabled(false);
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));

    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        showStatusMessage(tr("Open error"));
    }
}
//! [4]

//! [5]
void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    //console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);

    showStatusMessage(tr("Disconnected"));
}
//! [5]

void MainWindow::about()
{
    QMessageBox::about(this, tr("CAN Terminal"),
                       tr("The program for working with the radar ARS404."
                          "ver.1.0.5"));
}

//! [6]
void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}
//! [6]

//! [7]
void MainWindow::readData()
{
    QByteArray data;
    QString str_msg(data);



    char raw_msg[CAN_MSG_BUFER_LEN];
    char state=STATE_IDEAL,j=0;

    if(serial->bytesAvailable())
    {
      for(int i=0;i<serial->bytesAvailable();i++)
      {
          if(state==STATE_IDEAL)
          {
            serial->read(&raw_msg[j],1);
            if(raw_msg[j]=='t')//начало пакета
            {
              state=STATE_NEW_MSG;
            }
          }
           if(state==STATE_NEW_MSG)
           {
               j++;
               serial->read(&raw_msg[j],1);
               if(raw_msg[j]=='\r')//проверка на конец пакета
               {
                   state=STATE_END_MSG;
               }
           }
           else if(state==STATE_END_MSG)
          {
              raw_msg[j]=0;
              for(int i=0;i<j;i++)
              {
                  QChar str(raw_msg[i]);
                  str_msg.append(&str,1);
              }
             raw_message->Can_msg_converter(str_msg);
             str_msg.clear();
               j=0;
              state=STATE_IDEAL;
          }

      }
    }
}

void MainWindow::clear_data()
{
    for(int i=0;i<COUNT_OBJ*FIELDS_FOR_OBJECT;i++)
    {
      if(!all_obj_inf[i].general_inf.show)
      {
       text_object.at(i)->clear();
      }
    }
}
//! [7]

//! [8]
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::display_cluster_param(cluster_inf object)
{
    unsigned int object_ptr=0;

    object_ptr=object.cluster_id*FIELDS_FOR_OBJECT;
    if((text_object.count()/FIELDS_FOR_OBJECT)>=object.cluster_id)
    {
     text_object.at(object_ptr)->setNum(object.cluster_id);
     text_object.at(object_ptr)->show();
     text_object.at(++object_ptr)->setNum(object.distlong);
     text_object.at(object_ptr)->show();
     text_object.at(++object_ptr)->setNum(object.distlat);
     text_object.at(object_ptr)->show();
     text_object.at(++object_ptr)->setNum(object.vrelLong);
     text_object.at(object_ptr)->show();
     text_object.at(++object_ptr)->setNum(object.vrelLat);
     text_object.at(object_ptr)->show();
     text_object.at(++object_ptr)->setNum(object.cluster_RCS);
     text_object.at(object_ptr)->show();
     switch (object.dynProp)
     {
          case 0:
               text_object.at(++object_ptr)->setText("moving");
              break;
          case 1:
              text_object.at(++object_ptr)->setText("stationary");
              break;
          case 2:
              text_object.at(++object_ptr)->setText("oncoming");
              break;
          case 3:
              text_object.at(++object_ptr)->setText("stationary candidate");
              break;
          case 4:
             text_object.at(++object_ptr)->setText("unknown");
              break;
          case 5:
              text_object.at(++object_ptr)->setText("crossing stationary");
              break;
          case 6:
              text_object.at(++object_ptr)->setText("crossing moving");
              break;
          case 7:
              text_object.at(++object_ptr)->setText("stopped");
              break;
          default:
              break;
     }
     text_object.at(object_ptr)->show();
     text_object.at(++object_ptr)->hide();
     text_object.at(++object_ptr)->hide();
     text_object.at(++object_ptr)->hide();
     text_object.at(++object_ptr)->hide();
   }
}

void MainWindow::show_cluster_label(cluster_list *list)
{
  static cluster_list old_list;

  old_list.cluster_count=old_list.num_cluster_far+old_list.num_cluster_near;
  list->cluster_count=list->num_cluster_far+list->num_cluster_near;

  /*if(old_list.cluster_count< list->cluster_count)
  {
      for(int i=0;i<(list->cluster_count*FIELDS_FOR_OBJECT);i++)
      {
        text_object.at(i)->show();
      }
   }
  if(old_list.cluster_count> list->cluster_count)
  {
      for(int i=list->cluster_count*FIELDS_FOR_OBJECT;i<old_list.cluster_count*FIELDS_FOR_OBJECT;i++)
      {
        text_object.at(i)->hide();
      }
  }
  //for(int i=0;i<COUNT_OBJ*FIELDS_FOR_OBJECT;i++)
  //{
   // text_object.at(i)->clear();
  //}
  old_list.num_cluster_far=list->num_cluster_far;
  old_list.num_cluster_near=list->num_cluster_near;
  old_list.cluster_count=list->cluster_count;*/
}

void MainWindow::display_object_param(object_inf object)
{
    unsigned int object_ptr=0;


    object_ptr=object.general_inf.cluster_id*FIELDS_FOR_OBJECT;
    if((text_object.count()/FIELDS_FOR_OBJECT)>=object.general_inf.cluster_id)
    {
     text_object.at(object_ptr)->show();
     text_object.at(object_ptr)->setNum(object.general_inf.cluster_id);

     text_object.at(++object_ptr)->setNum(object.general_inf.distlong);
     text_object.at(object_ptr)->show();

     text_object.at(++object_ptr)->setNum(object.general_inf.distlat);
     text_object.at(object_ptr)->show();

     text_object.at(++object_ptr)->setNum(object.general_inf.vrelLong);
     text_object.at(object_ptr)->show();

     text_object.at(++object_ptr)->setNum(object.general_inf.vrelLat);
     text_object.at(object_ptr)->show();

     text_object.at(++object_ptr)->setNum(object.general_inf.cluster_RCS);
     text_object.at(object_ptr)->show();

     text_object.at(++object_ptr)->setNum(object.extended_inf.obj_orientationangel);
     text_object.at(object_ptr)->show();

     text_object.at(++object_ptr)->setNum(object.extended_inf.object_length);
     text_object.at(object_ptr)->show();

     text_object.at(++object_ptr)->setNum(object.extended_inf.object_width);
     text_object.at(object_ptr)->show();

     switch (object.extended_inf.odj_class) {

     case 0:
         text_object.at(++object_ptr)->setText("point");
         break;
     case 1:
         text_object.at(++object_ptr)->setText("car");
         break;
     case 2:
         text_object.at(++object_ptr)->setText("truck");
         break;
     case 3:
         text_object.at(++object_ptr)->setText("pedestrian");
         break;
     case 4:
         text_object.at(++object_ptr)->setText("motorcycle");
         break;
     case 5:
         text_object.at(++object_ptr)->setText("bicycle");
         break;
     case 6:
         text_object.at(++object_ptr)->setText("wide");
         break;
     default:
         break;
     }
     text_object.at(object_ptr)->show();

     switch (object.general_inf.dynProp)
     {
          case 0:
               text_object.at(++object_ptr)->setText("moving");
              break;
          case 1:
              text_object.at(++object_ptr)->setText("stationary");
              break;
          case 2:
              text_object.at(++object_ptr)->setText("oncoming");
              break;
          case 3:
              text_object.at(++object_ptr)->setText("stationary candidate");
              break;
          case 4:
             text_object.at(++object_ptr)->setText("unknown");
              break;
          case 5:
              text_object.at(++object_ptr)->setText("crossing stationary");
              break;
          case 6:
              text_object.at(++object_ptr)->setText("crossing moving");
              break;
          case 7:
              text_object.at(++object_ptr)->setText("stopped");
              break;
          default:
              break;
     }
     text_object.at(object_ptr)->show();

   }
}

void MainWindow::show_object_label(object_list *list)
{
    //for(int i=0;i<COUNT_OBJ*FIELDS_FOR_OBJECT;i++)
    //{
     // text_object.at(i)->clear();
    //}
}

void MainWindow::send_can_msg(QString data)
{
    QByteArray send_data;

    send_data +=data;
    send_data[0]='t';
    send_data[send_data.count()-1]='\r';
    serial->write(send_data);
}

void MainWindow::show_all_fields()
{
    ui->lenght->show();
    ui->width->show();
    ui->class_2->show();
    ui->propertis->show();
    ui->angel->setText("Angel");
}

void MainWindow::hide_extended_fields()
{
    ui->lenght->hide();
    ui->width->hide();
    ui->class_2->hide();
    ui->propertis->hide();
    ui->angel->setText("Propertis");
}
//! [8]

void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::openSerialPort);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::closeSerialPort);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionConfigure, &QAction::triggered, settings, &MainWindow::show);
    connect(ui->actionClear, &QAction::triggered, this,&MainWindow::clear_data);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(ui->actionCAN_Connect,&QAction::triggered,this,&MainWindow::connect_Can);
    connect(ui->actionDisconnect_CAN,&QAction::triggered,this,&MainWindow::disconnect_CAN);
    connect(ui->actionGet_radar_config,&QAction::triggered,radar_get_configDialog,&MainWindow::show);
    connect(ui->actionSet_radar_config,&QAction::triggered,radar_set_configDialog,&MainWindow::show);
    connect(ui->actionSet_radar_filter,&QAction::triggered,radar_set_filterDialog,&MainWindow::show);
    connect(ui->actionPosition_view,&QAction::triggered,position_viewDialog,&MainWindow::show);
}

void MainWindow::showStatusMessage(const QString &message)
{
    status->setText(message);
}


