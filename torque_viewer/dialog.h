#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "torquegetter.h"
#include "torqueview.h"

namespace Ui {
class Dialog;
}
/**
 * @brief The Dialog class is the default top level widget.
 */
class Dialog : public QDialog      
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    TorqueView *getView()
    {
        return view;
    }

private:
    Ui::Dialog *ui;
    TorqueView *view;
};

#endif // DIALOG_H
