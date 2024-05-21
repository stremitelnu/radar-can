#ifndef GET_RADAR_CONFIG_H
#define GET_RADAR_CONFIG_H


#include <QDialog>
#include "can_message.h"

namespace Ui {
class get_radar_config;
}

class get_radar_config : public QDialog
{
    Q_OBJECT

public:
    explicit get_radar_config(QWidget *parent = 0);
    ~get_radar_config();
public slots:
    void show_radar_config(radar_status *radar_config);
private:
    Ui::get_radar_config *ui;
};

#endif // GET_RADAR_CONFIG_H
