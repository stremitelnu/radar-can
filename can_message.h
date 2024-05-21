#ifndef CAN_MESSAGE_H
#define CAN_MESSAGE_H

#include <QObject>
#define COUNT_OBJ              250
#define FILTER_COUNT_OBJECT    16
#define FILTER_COUNT_CLASTER   6
#define FIELDS_FOR_OBJECT      11
#define CAN_MSG_BUFER_LEN      40
#define STATE_IDEAL            0
#define STATE_NEW_MSG          1
#define STATE_END_MSG          2

#define MAX_COUNT_MSG          250
#define STD_CAN_FRAME          0x74
#define CLUSTER_INF            0x701
#define CLUSTER_LIST           0x600
#define RADAR_STATE            0x201
#define RADAR_CONFIG           0x200
#define RADAR_FILTER           0x202
#define RADAR_FILTER_STATE     0x204
#define SOFTWARE_ID            0x700
#define OBJECT_INF             0x60B
#define OBJECT_LIST            0x60A
#define QUALITY_INFORMATION    0x60C
#define EXTENDED_INFORMATION   0x60D
#define HEADER_SIZE            0x05
#define TIME_STAMP_SIZE        0x04

typedef struct
{
    char num_cluster_near;
    char num_cluster_far;
    short cluster_count;
    char cluster_ver;
    char res1;
    char res2;
    char res3;

}cluster_list;
typedef struct
{
   char  num_object;
   short object_meascounter;
   char  object_interfaceversion;
   char  res1;
   char  res2;
   char  res3;
   char  res4;

}object_list;
typedef struct
{
   unsigned char cluster_id;
   float distlong;
   float distlat;
   float vrelLong;
   float vrelLat;
   char dynProp;
   float cluster_RCS;
   unsigned char show;

}cluster_inf;
typedef struct
{
   unsigned char obj_id;
   unsigned char obj_distLong_rms;
   unsigned char obj_distLat_rms;
   unsigned char obj_vrelLong_rms;
   unsigned char obj_vrelLat_rms;
   unsigned char obj_arelLong_rms;
   unsigned char obj_arelLat_rms;
   unsigned char obj_orientation_rms;
   unsigned char obj_probofexist;
   unsigned char obj_measstate;
}object_quality_inf;
typedef struct
{
    unsigned char obj_id;
    double arelLong;
    double arelLat;
    unsigned char odj_class;
    double obj_orientationangel;
    double object_length;
    double object_width;
}object_extended_inf;
typedef struct
{
    char res1:6;
    char NVMReadStatus:1;
    char NVMwriteStatus:1;
    char MaxDistanceCfg_msb;
    char res2:1;
    char Voltage_Error:1;
    char Temporary_Error:1;
    char Temperature_Error:1;
    char Interference:1;
    char Persistent_Error:1;
    char MaxDistanceCfg_lsb:2;
    char RadarPowerCfg_msb:2;
    char res4:6;
    char SensorID:3;
    char res6:1;
    char SortIndex:3;
    char RadarPowerCfg_lsb:1;
    char res7:1;
    char CtrlRelayCfg:1;
    char OutputTypeCfg:2;
    char SendQualityCfg:1;
    char SendExtInfoCfg:1;
    char MotionRxState:2;
    char res8:8;
    char res9:2;
    char RCS_Threshold:3;
    char res10:3;

}radar_status;
typedef struct
{  union//0 байт
    {
      unsigned char word;
     struct
     {
      unsigned char maxdistance_valid:1;
      unsigned char sensorID_valid:1;
      unsigned char radarpower_valid:1;
      unsigned char outputtype_valid:1;
      unsigned char sendquality_valid:1;
      unsigned char sendextinfo_valid:1;
      unsigned char sortindex_valid:1;
      unsigned char storeinNVM_valid:1;//
     }bit;
    }byte_0;

    unsigned short maxdistance;//1-2 байт

    unsigned char byte_3;//3 байт
    union//4 байт
    {
     unsigned char word;
     struct
     {
      unsigned char sensorID:3;
      unsigned char outputtype:2;
      unsigned char radarpower:3;//
     }bit;
    }byte_4;

    union// 5 байт
    {
     unsigned char word;
     struct
     {
      unsigned char ctrlrelay_valid:1;
      unsigned char ctrlrelay:1;
      unsigned char sendquality:1;
      unsigned char sendextinfo:1;
      unsigned char sortindex:3;
      unsigned char storeinNVM:1;
     }bit;
    }byte_5;
    union//6 байт
    {
     unsigned char word;
     struct
     {
      unsigned char RCS_threshold_valid:1;
      unsigned char RCS_Threshold:3;
      unsigned char res2:4;//
     }bit;
    }byte_6;
    unsigned char byte_7;//7байт

}radar_config;
typedef struct
{
    union//0 байт
        {
          unsigned char word;
         struct
         {
          unsigned char res:1;
          unsigned char FilterCfg_Valid:1;
          unsigned char FilterCfg_Active:1;
          unsigned char FilterCfg_Index:4;
          unsigned char FilterCfg_Type:1;
         }bit;
        }byte_0;
    short min_value;//байт 1-2
    short max_value;//байт 2-3
}radar_filter;
typedef struct
{
    cluster_inf general_inf;
    object_quality_inf quality_inf;
    object_extended_inf extended_inf;

}object_inf;
class can_message : public QObject
{
    Q_OBJECT
public:
    explicit can_message(QObject *parent = 0);
    void Can_msg_converter(QString msg);
    int package_validation(QString msg);
   typedef struct
    {
      unsigned char *data;
      char dlc;
      char id[4];
    }Msg;

signals:
   void signal_filter_config_state(radar_filter * data);
   void signal_filter_state();
   void get_config(radar_status *state);
    //по кластерам
   void get_cluster_inf(cluster_inf  object);
   void get_num_cluster(cluster_list *list);
    //по обектам
   void get_object_inf(object_inf  object);
   void get_num_object(object_list *list);

   void signal_display_point(cluster_inf  object);
public slots:
};

#endif // CAN_MESSAGE_H
