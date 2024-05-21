#ifndef SET_RADAR_FILTER_H
#define SET_RADAR_FILTER_H

#include <QDialog>
#include <QDoubleSpinBox>
#include "can_message.h"
#include "QStatusBar"
#include "QLabel"
#include "QEventLoop"
#include "QTimer"

namespace Ui {
class set_radar_filter;
}

class set_radar_filter : public QDialog
{
    Q_OBJECT

public:
    explicit set_radar_filter(QWidget *parent = 0);
    ~set_radar_filter();
    QDoubleSpinBox * gate_min;
    QDoubleSpinBox * gate_max;
    QStatusBar *bar;
    QLabel     *status;
    QEventLoop *Event;
    QTimer *Timer;
signals:
    void signal_send_can_msg_filter_config(QString data);
public slots:
        void filter_config_check(radar_filter * data);
protected:
    void showEvent(QShowEvent * EW);
private slots:
    void on_filter_type_currentIndexChanged(int index);

    void on_filter_index_currentIndexChanged(int index);

    void on_pushButton_clicked();
    void on_clear_all_filters_clicked();

private:
    Ui::set_radar_filter *ui;
};

#endif // SET_RADAR_FILTER_H
