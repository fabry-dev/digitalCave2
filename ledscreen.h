#ifndef LEDSCREEN_H
#define LEDSCREEN_H


#include <QWidget>
#include <qobject.h>
#include "qlabel.h"
#include "mpvwidget.h"
#include "alphaVideoPlayer.h"
#include "qtimer.h"
#include "yearbuttons.h"

class ledScreen : public QLabel
{
    Q_OBJECT
public:
    explicit ledScreen(QLabel *parent = nullptr, QString PATH="");

private:
    QString PATH;
    mpvWidget *bgVp,*introVp;
    yearButtons *yb;

private slots:
    void loadPlayer(void);
    void startIntroVideo(void);
    void stopIntroVideo(void);
    void gotTimeOut(void);

signals:
    void bgRestart(void);
    void yearMoveLeft(void);
    void yearMoveRight(void);


protected:
     void keyPressEvent(QKeyEvent *ev);
};

#endif // LEDSCREEN_H
