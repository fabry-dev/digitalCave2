#ifndef MAINSCREEN_H
#define MAINSCREEN_H


#include <QWidget>
#include <qobject.h>
#include "qlabel.h"
#include "mpvwidget.h"
#include "qtimer.h"
#include "alphaVideoPlayer.h"
#include "rotativebutton.h"
#include "yearbuttons.h"
#include "QPropertyAnimation"

class touchScreen : public QLabel
{
    Q_OBJECT
public:
    explicit touchScreen(QLabel *parent = nullptr, QString PATH="");

private:
    QString PATH;
    mpvWidget *bgVp,*introVp;
    yearButtons *yb;
    QLabel *dataLbl;
    QPropertyAnimation *dataLblAnim;
    int activeContent;
    alphaVideo *alphaVp;

    QTimer *timeOutTimer;
private slots:
    void loadPlayer(void);
    void showContent(int contentId);
    void doneShowingContent(void);
    void startIntroVideo(void);
    void stopIntroVideo(void);
    void timeoutReset(void);
signals:
    void bgShouldRestart(void);
    void yearMoveLeft(void);
    void yearMoveRight(void);
    void timeOut(void);
};

#endif // MAINSCREEN_H
