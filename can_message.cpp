#include "can_message.h"
#include <QDebug>
#include <qmath.h>

object_inf all_obj_inf[250];
can_message::can_message(QObject *parent) : QObject(parent)
{

}

double roundTo(double inpValue, int inpCount)
{
    switch (inpCount) {
    case 1:
        inpValue=((int)(inpValue*10+0.5))/10.0;
        break;
    case 2:
         inpValue=((int)(inpValue*100+0.5))/100.0;
        break;
    case 3:
         inpValue=((int)(inpValue*1000+0.5))/1000.0;
        break;
    default:
        break;
    }
    return inpValue;
}

int can_message:: package_validation(QString msg)
{
    unsigned char  dlc=0;
    unsigned char  packat_size=0;
    bool ok;

    dlc=msg.mid(4,1).toUInt(&ok,16);
    packat_size=HEADER_SIZE+(dlc*2);
    if(msg.count()!=packat_size)
    {
     return false;
    }
 return true;
}

void can_message::Can_msg_converter(QString msg)
{  
  long int temp=0;
  Msg Can_massege;
  unsigned char can_data_buf[16];
  QString id;
  QString dlc;
  QString data;
  int can_msg_ID=0;
  bool ok;
  //static unsigned char count_msg=0;

  if(msg[0]==STD_CAN_FRAME)
  {
     id=msg.mid(0,4);
     dlc=msg.mid(4,1);
     data=msg.mid(5);
  }
  else {
     id=msg.mid(0,8);
     dlc=msg.mid(8,1);
     data=msg.mid(9);
  }
   id[0]=0x30;//замена признака формата на 0
   //копируем и переводим из аски по полям
   for(int i=0;i<id.count();i+=2)
   {
     Can_massege.id[i>>1]=id.mid(i,2).toUInt(&ok,16);
   }
   for(int i=0;i<dlc.count();i++)
   {
     Can_massege.dlc=dlc.mid(i,1).toUInt(&ok,16);
   }
   Can_massege.data=can_data_buf;
   for(int i=0;i<data.count();i+=2)
   {
     Can_massege.data[i>>1]=data.mid(i,2).toUInt(&ok,16);
   }
  can_msg_ID=Can_massege.id[0]<<8;
  can_msg_ID|=Can_massege.id[1];
   switch (can_msg_ID)
   {
    //case SOFTWARE_ID:{

      //               }

        //    break;
   case CLUSTER_INF:{

                      cluster_inf  clustre_informetion;

                      float rsc_min=-64,rsc_max=63.5,distlong_min=-500,distlong_max=1138.2,distlat_min=-102.3,distlat_max=102.3;
                      float vrellong_min=-128,vrellong_max=127.75,vrellat_min=-64,vrellat_max=63.75;
                      int rsc_range=0xFF,distlong_range=0x1FFF,distlat_range=0x3FF,vrellong_range=0x3FF,vrellat_range=0x1FF;

                      clustre_informetion.cluster_id=can_data_buf[0];

                      temp=((can_data_buf[1]<<8)|(can_data_buf[2]))>>3;
                      clustre_informetion.distlong=(float)temp/(float)distlong_range;
                      clustre_informetion.distlong *=distlong_max-distlong_min;
                      clustre_informetion.distlong +=distlong_min;
                      clustre_informetion.distlong=roundTo(clustre_informetion.distlong,1);

                      temp=(((can_data_buf[2]&0x03)<<8)|(can_data_buf[3]));
                      clustre_informetion.distlat=(float)temp/(float)distlat_range;
                      clustre_informetion.distlat *=distlat_max-distlat_min;
                      clustre_informetion.distlat +=distlat_min;
                      clustre_informetion.distlat=roundTo(clustre_informetion.distlat,1);

                      temp=((can_data_buf[4]<<8)|(can_data_buf[5]))>>6;
                      clustre_informetion.vrelLong=(float)temp/(float)vrellong_range;
                      clustre_informetion.vrelLong *=vrellong_max-vrellong_min;
                      clustre_informetion.vrelLong +=vrellong_min;
                      clustre_informetion.vrelLong=roundTo(clustre_informetion.vrelLong,2);

                      temp=(((can_data_buf[5]&0x3f)<<8)|(can_data_buf[6]))>>5;
                      clustre_informetion.vrelLat=(float)temp/(float)vrellat_range;
                      clustre_informetion.vrelLat *=vrellat_max-vrellat_min;
                      clustre_informetion.vrelLat +=vrellat_min;
                      clustre_informetion.vrelLat=roundTo(clustre_informetion.vrelLat,2);

                      clustre_informetion.dynProp=can_data_buf[6]&0x07;


                      clustre_informetion.cluster_RCS=(float)can_data_buf[7]/(float)rsc_range;
                      clustre_informetion.cluster_RCS *=rsc_max-rsc_min;
                      clustre_informetion.cluster_RCS +=rsc_min;
                      clustre_informetion.cluster_RCS=roundTo(clustre_informetion.cluster_RCS,1);

                      clustre_informetion.show=1;
                      all_obj_inf[clustre_informetion.cluster_id].general_inf=clustre_informetion;
                      emit get_cluster_inf(clustre_informetion);
                      emit signal_display_point(clustre_informetion);
                     qDebug()<<"полученно сообщение о цели";
                    }
           break;
   case CLUSTER_LIST:{
                       cluster_list *list_of_cluster;

                       list_of_cluster=(cluster_list *)can_data_buf;
                       //for(int i=0;i<=COUNT_OBJ;i++)
                       //{
                        //  all_obj_inf[i].general_inf.show=0;
                       //}
                       emit get_num_cluster(list_of_cluster);
                       qDebug()<<"полученно сообщение кол-во объектов";
                     }
           break;
   case OBJECT_INF:{
                     cluster_inf  clustre_informetion;
                     float rsc_min=-64,rsc_max=63.5,distlong_min=-500,distlong_max=1138.2,distlat_min=-204.6,distlat_max=204.8;
                     float vrellong_min=-128,vrellong_max=127.75,vrellat_min=-64,vrellat_max=63.75;
                     int rsc_range=0xFF,distlong_range=0x1FFF,distlat_range=0x7FF,vrellong_range=0x3FF,vrellat_range=0x1FF;

                     clustre_informetion.cluster_id=can_data_buf[0];

                     temp=((can_data_buf[1]<<8)|(can_data_buf[2]))>>3;
                     clustre_informetion.distlong=(float)temp/(float)distlong_range;
                     clustre_informetion.distlong *=distlong_max-distlong_min;
                     clustre_informetion.distlong +=distlong_min;
                     clustre_informetion.distlong=roundTo(clustre_informetion.distlong,1);

                     temp=(((can_data_buf[2]&0x07)<<8)|(can_data_buf[3]));
                     clustre_informetion.distlat=(float)temp/(float)distlat_range;
                     clustre_informetion.distlat *=distlat_max-distlat_min;
                     clustre_informetion.distlat +=distlat_min;
                     clustre_informetion.distlat=roundTo(clustre_informetion.distlat,1);

                     temp=((can_data_buf[4]<<8)|(can_data_buf[5]))>>6;
                     clustre_informetion.vrelLong=(float)temp/(float)vrellong_range;
                     clustre_informetion.vrelLong *=vrellong_max-vrellong_min;
                     clustre_informetion.vrelLong +=vrellong_min;
                     clustre_informetion.vrelLong=roundTo(clustre_informetion.vrelLong,2);

                     temp=(((can_data_buf[5]&0x3f)<<8)|(can_data_buf[6]))>>5;
                     clustre_informetion.vrelLat=(float)temp/(float)vrellat_range;
                     clustre_informetion.vrelLat *=vrellat_max-vrellat_min;
                     clustre_informetion.vrelLat +=vrellat_min;
                     clustre_informetion.vrelLat=roundTo(clustre_informetion.vrelLat,2);

                     clustre_informetion.dynProp=can_data_buf[6]&0x07;


                     clustre_informetion.cluster_RCS=(float)can_data_buf[7]/(float)rsc_range;
                     clustre_informetion.cluster_RCS *=rsc_max-rsc_min;
                     clustre_informetion.cluster_RCS +=rsc_min;
                     clustre_informetion.cluster_RCS=roundTo(clustre_informetion.cluster_RCS,1);

                     clustre_informetion.show=1;

                     all_obj_inf[clustre_informetion.cluster_id].general_inf=clustre_informetion;
                     emit signal_display_point(clustre_informetion);
                     qDebug()<<"полученно сообщение о цели";
                   }
           break;
   case OBJECT_LIST:{
                      object_list *list_of_object;

                      list_of_object=(object_list *)can_data_buf;
                      //for(int i=0;i<=COUNT_OBJ;i++)
                      //{
                        // all_obj_inf[i].general_inf.show=0;
                      //}
                      emit get_num_object(list_of_object);
                      }
       break;
   case QUALITY_INFORMATION:{
                             object_quality_inf quality_information;

                             quality_information.obj_id=can_data_buf[0];
                             quality_information.obj_distLong_rms=can_data_buf[1]>>3;
                             quality_information.obj_distLat_rms=((can_data_buf[1]&0x07)<<2)|(can_data_buf[2]>>6);
                             quality_information.obj_vrelLong_rms=(can_data_buf[2]&0x3F)>>1;
                             quality_information.obj_vrelLat_rms=((can_data_buf[2]&0x01)<<4)|(can_data_buf[3]>>4);
                             quality_information.obj_arelLong_rms=((can_data_buf[3]&0x0F)<<1)|(can_data_buf[4]>>7);
                             quality_information.obj_arelLat_rms=(can_data_buf[4]&0x7F)>>2;
                             quality_information.obj_orientation_rms=((can_data_buf[4]&0x03)<<3)|(can_data_buf[5]>>5);
                             quality_information.obj_probofexist=can_data_buf[5]>>5;
                             quality_information.obj_arelLong_rms=(can_data_buf[5]&0x1C)>>2;

                             all_obj_inf[quality_information.obj_id].quality_inf=quality_information;
                            }
       break;
   case EXTENDED_INFORMATION:
        {
          object_extended_inf extended_information;
          unsigned short temp=0,range_aLong=0x7FF,range_aLat=0x1FF,range_angel=0x3FF,range_length=0xFF,rang_width=0xFF;
          float aLong_min=-10,aLong_max=10.47,aLat_min=-2.5,aLat_max=2.61,angel_min=-180,angel_max=180,length_max=51,width_max=51;

          extended_information.obj_id=can_data_buf[0];

          temp=((can_data_buf[1]<<8)|can_data_buf[2])>>5;
          extended_information.arelLong=(float)temp/(float)range_aLong;
          extended_information.arelLong *=aLong_max-aLong_min;
          extended_information.arelLong +=aLong_min;

          temp=(((can_data_buf[2]&0x1F)<<8)|can_data_buf[3])>>4;
          extended_information.arelLat=(float)temp/(float)range_aLat;
          extended_information.arelLat *=aLat_max-aLat_min;
          extended_information.arelLat +=aLat_min;

          extended_information.odj_class=can_data_buf[3]&0x07;

          temp=((can_data_buf[4]<<8)|can_data_buf[5])>>6;
          extended_information.obj_orientationangel=(float)temp/(float)range_angel;
          extended_information.obj_orientationangel *=angel_max-angel_min;
          extended_information.obj_orientationangel +=angel_min;
          extended_information.obj_orientationangel=roundTo(extended_information.obj_orientationangel,1);

          extended_information.object_length=(float)can_data_buf[6]/(float)range_length;
          extended_information.object_length *=length_max;
          extended_information.object_length=roundTo(extended_information.object_length,1);

          extended_information.object_width=(float)can_data_buf[7]/(float)rang_width;
          extended_information.object_width *=width_max;
          extended_information.object_width=roundTo(extended_information.object_width,1);

          all_obj_inf[extended_information.obj_id].extended_inf=extended_information;

          emit get_object_inf(all_obj_inf[extended_information.obj_id]);
          //emit signal_display_point(all_obj_inf[extended_information.obj_id].general_inf);
        }
       break;
   case RADAR_STATE:{
                      radar_status *state;

                      state=(radar_status *)can_data_buf;
                     qDebug()<<"полученно сообщение настроек";
                     emit get_config(state);
                     }

           break;
   case RADAR_FILTER_STATE:{
                      radar_filter *state;

                      state=(radar_filter *)can_data_buf;
                      emit signal_filter_config_state(state);
                      emit signal_filter_state();
                     }

           break;
    default:
            break;
   }
}
