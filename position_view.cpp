#include "position_view.h"
#include "ui_position_view.h"
#include "can_message.h"
extern object_inf all_obj_inf[];
position_view::position_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::position_view)
{
    ui->setupUi(this);

    for(int i=0;i<=COUNT_OBJ;i++)
    {
        point_object.append(new QRadioButton(this));
    }
    Timer_redrawing_position=new QTimer(this);
    Timer_redrawing_position->setInterval(60000);
    Timer_redrawing_position->start();
    connect(Timer_redrawing_position,SIGNAL(timeout()),this,SLOT(redrawing_object_point()));
}

position_view::~position_view()
{
    delete ui;
}

void position_view::showEvent(QShowEvent *EW)
{
     QDialog::showEvent(EW);

     for(int i=0;i<=COUNT_OBJ;i++)
     {
         point_object.at(i)->hide();
     }
}

void position_view::display_object_point(cluster_inf object)
{
    QPalette pal(palette());

    unsigned int X0=217,Y0=921,range_dist_long=2500,range_cited_long=874;
    unsigned int range_dist_lat=1000,range_cited_lat=245,range_cited_lat1=130;
    float y=0,x=0;
    unsigned char w=40,h=17;

    object.distlong *=10;
    object.distlat *=10;
    x=object.distlat;
    if(object.distlong<700)
    {
        x /=(float)range_dist_lat;
        x *=(float)range_cited_lat;
        x=(int)(X0-x);
    }
    else
    {
        x /=(float)range_dist_lat;
        x *=(float)range_cited_lat1;
        x=(int)(X0-x);
    }

    y=object.distlong;
    y /=(float)range_dist_long;
    y *=(float)range_cited_long;
    y=(int)(Y0-y);
    point_object.at(object.cluster_id)->setGeometry(x,y,w,h);
    point_object.at(object.cluster_id)->setText(QString("%1").arg(object.cluster_id,1,10,QChar('0')));
    //point_object.at(object.cluster_id)->setStyleSheet("background-color:green;");//
    point_object.at(object.cluster_id)->setStyleSheet("color: yellow");
    point_object.at(object.cluster_id)->show();


}

void position_view::redrawing_object_point()
{
    for(int i=0;i<=COUNT_OBJ;i++)
     {
         if(!all_obj_inf[i].general_inf.show)
         {
            point_object.at(i)->hide();
         }
         else
         {
           point_object.at(i)->show();
           all_obj_inf[i].general_inf.show=0;
         }

     }
}
