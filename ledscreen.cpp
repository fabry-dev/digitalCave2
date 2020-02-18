#include "ledscreen.h"
#include "math.h"
#include "qdebug.h"
#include "qthread.h"
#include "qlayout.h"

#include "qmediaplayer.h"

std::vector<int> ledYearWidths={111,111,111,131,151,191,151,131,111,111,111};
std::vector<int> ledYearXs={-111,-111,-111,20,191,382,613,804,960,960,960};

double Touch2Led = (double)53.1/250; //size led = size touch * Touch2Led
ledScreen::ledScreen(QLabel *parent, QString PATH) : QLabel(parent),PATH(PATH)
{

    resize(960,1152);

    bgVp = new mpvWidget(this);
    bgVp->resize(size());
    bgVp->setProperty("keep-open","yes");
    bgVp->setLoop(true);
    bgVp->show();

    connect(bgVp,SIGNAL(videoRestart()),this,SIGNAL(bgRestart()));

    QTimer::singleShot(10,this,SLOT(loadPlayer()));

    yb = new yearButtons(this,PATH,ledYearWidths,ledYearXs,height()/2+Touch2Led*480,"_2");
    yb->show();
    connect(this,SIGNAL(yearMoveLeft()),yb,SLOT(moveLeft()));
    connect(this,SIGNAL(yearMoveRight()),yb,SLOT(moveRight()));

    QLabel *touchLbl = new QLabel(this);
    touchLbl->resize(1080*Touch2Led,1920*Touch2Led);
    touchLbl->move((width()-touchLbl->width())/2,(height()-touchLbl->height())/2);
    touchLbl->setStyleSheet("border: 1px solid red");
    touchLbl->show();


}

void ledScreen::loadPlayer()
{
    bgVp->lower();
    bgVp->loadFilePaused(PATH+"ledBg2.mp4");
    bgVp->play();
}









void ledScreen::startVideo(void)
{
}


void ledScreen::stopVideo(void)
{
}











void ledScreen::keyPressEvent(QKeyEvent *ev)
{
  if(ev->key() == 16777216)
        exit(0);

  if(ev->key()==16777234)
      emit yearMoveLeft();
  else if(ev->key()==16777236)
      emit yearMoveRight();

  //qDebug()<<ev->key();
}



