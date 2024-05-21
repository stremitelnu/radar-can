/*#ifndef CAN_MSG_H
#define CAN_MSG_H

#include <QObject>

#define MAX_COUNT_MSG 250
#define STD_CAN_FRAME 0x74
#define CLUSTER_INF   0x701
#define CLUSTER_LIST  0x600
#define RADAR_STATE   0x201
#define SOFTWARE_ID   0x700
class can_msg
{

public:
    can_msg();
    void Can_msg_converter(QString msg);
private:
   typedef struct
    {
      char *data;
      char dlc;
      char id[4];
    }Msg;
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
       char cluster_id;
       short distlong;
       short distlat;
       short vrelLong;
       short vrelLat;
       char dynProp;
       char cluster_RCS;

    }cluster_inf;
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
        char RadarPowerCfg_lsb:1;
        char SortIndex:3;
        char res6:1;
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

};

#endif // CAN_MSG_H*/
