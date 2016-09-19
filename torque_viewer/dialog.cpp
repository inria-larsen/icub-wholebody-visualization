#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "dialog.h"
#include "ui_dialog.h"
#include "torqueview.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);    

    view=new TorqueView();
    ui->gridLayout->addWidget(view);        
}

Dialog::~Dialog()
{
    delete ui;
    delete view;
}
