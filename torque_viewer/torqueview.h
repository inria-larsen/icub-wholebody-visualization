#ifndef TORQUEVIEW_H
#define TORQUEVIEW_H

#include <QGraphicsView>
#include <yarp/os/all.h>
/**
 * @brief TorqueView is a QGraphicsView subclass with an icub drawing as a background
 *
 */

class TorqueView : public QGraphicsView
{    
public:
    explicit TorqueView();
    ~TorqueView();
    QGraphicsScene * getScene();
protected:
    void resizeEvent(QResizeEvent *event);
    int width;  /// the background width
    int height; /// the background height
    QGraphicsScene * scene;
};

#endif
