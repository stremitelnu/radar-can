#ifndef SET_RADAR_CONFIG_H
#define SET_RADAR_CONFIG_H

#include <QDialog>
#include "can_message.h"
#include "QString"


namespace Ui {
class set_radar_config;
}

class set_radar_config : public QDialog
{
    Q_OBJECT

public:
    explicit set_radar_config(QWidget *parent = 0);

    ~set_radar_config();
signals:
    void signal_send_can_msg_radar_config(QString data);
    void signal_show_all_fields();
    void signal_hide_extended_fields();
protected:
    void showEvent(QShowEvent * EW);
private slots:
    void on_applyButton_clicked();

private:
    Ui::set_radar_config *ui;
};

#endif // SET_RADAR_CONFIG_H
