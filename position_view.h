#ifndef POSITION_VIEW_H
#define POSITION_VIEW_H

#include <QDialog>
#include <QString>
#include <QRadioButton>
#include <QStyle>
#include <QStyleFactory>
#include "can_message.h"
#include "QTimer"

namespace Ui {
class position_view;
}

class position_view : public QDialog
{
    Q_OBJECT

public:
    explicit position_view(QWidget *parent = 0);
    ~position_view();

    QTimer *Timer_redrawing_position;
protected:
    void showEvent(QShowEvent * EW);
public slots:
    void display_object_point(cluster_inf object);
    void redrawing_object_point();
private:
    Ui::position_view *ui;
    QList<QRadioButton*> point_object;
};

#endif // POSITION_VIEW_H
