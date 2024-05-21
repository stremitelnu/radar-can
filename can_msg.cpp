/*#include "can_msg.h"

can_msg::can_msg()
{

}

void can_msg::Can_msg_converter(QString msg)
{
  Msg Can_massege[250];
  char can_data_buf[8];
  QString id;
  QString dlc;
  QString data;
  int can_msg_ID=0;
  bool ok;
  static unsigned char count_msg=0;

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
  if(count_msg<MAX_COUNT_MSG)
  {
   //копируем и переводим из аски по полям
   for(int i=0;i<id.count();i+=2)
   {
     Can_massege[count_msg].id[i>>1]=id.mid(i,2).toUInt(&ok,16);
   }
   for(int i=0;i<dlc.count();i++)
   {
     Can_massege[count_msg].dlc=dlc.mid(i,1).toUInt(&ok,16);
   }
   Can_massege[count_msg].data=can_data_buf;
   for(int i=0;i<data.count();i+=2)
   {
     Can_massege[count_msg].data[i>>1]=data.mid(i,2).toUInt(&ok,16);
   }
  can_msg_ID=Can_massege[count_msg].id[0]<<8;
  can_msg_ID|=Can_massege[count_msg].id[1];
   switch (can_msg_ID)
   {
    //case SOFTWARE_ID:{

      //               }

        //    break;
   case CLUSTER_INF:{

                      cluster_inf  clustre_informetion;

                     clustre_informetion.cluster_id=can_data_buf[0];
                     clustre_informetion.distlong=((can_data_buf[1]<<5)|(can_data_buf[2]>>3))/5;
                     clustre_informetion.distlat=(((can_data_buf[2]&0x03)<<8)|(can_data_buf[3]))/5;
                     clustre_informetion.vrelLong=((can_data_buf[4]<<2)|(can_data_buf[5]>>6))/4;
                     clustre_informetion.vrelLat=((can_data_buf[5]<<3)|(can_data_buf[6]>>5))/4;
                     clustre_informetion.dynProp=can_data_buf[6]&0x07;
                     clustre_informetion.cluster_RCS=can_data_buf[7];
                    }
           break;
   case CLUSTER_LIST:{
                       cluster_list *list_of_cluster;

                       list_of_cluster=(cluster_list *)can_data_buf;

                     }
           break;
   case RADAR_STATE:{
                      radar_status *state;

                      state=(radar_status *)can_data_buf;

                     }

           break;
    default:
            break;
   }

   //увеличим счетчик сообщений
   count_msg++;
   //проверка на переполнение
   if(count_msg>MAX_COUNT_MSG) count_msg=0;
  }

}*/
