#include "touchscreen.h"
#include "math.h"
#include "qdebug.h"

#define TIMEOUT_DELAY 10*1000

std::vector<int> yearWidths={200,200,200,200,200,900,200,200,200,200,200};
std::vector<int> yearXs={-200,-200,-200,-200,-200,90,1280,1280,1280,1280,1280};

touchScreen::touchScreen(QLabel *parent, QString PATH) : QLabel(parent),PATH(PATH)
{
    resize(1080,1920);

    timeOutTimer = new QTimer(this);
    connect(timeOutTimer,SIGNAL(timeout()),this,SLOT(timeoutReset()));

    bgVp = new mpvWidget(this);
    bgVp->resize(size());
    bgVp->setProperty("keep-open","yes");
    bgVp->setLoop(false);
    bgVp->show();

    connect(this,SIGNAL(bgShouldRestart()),bgVp,SLOT(rewindAndPlay()));


    introVp = new mpvWidget(this);
    introVp->resize(size());
    introVp->setProperty("keep-open","yes");
    introVp->setLoop(false);
    introVp->lower();
    introVp->setMute(true);
    introVp->show();


    yb = new yearButtons(this,PATH,yearWidths,yearXs,1440);
    yb->show();
    connect(yb,SIGNAL(movingLeft()),this,SIGNAL(yearMoveLeft()));
    connect(yb,SIGNAL(movingRight()),this,SIGNAL(yearMoveRight()));
    connect(yb,SIGNAL(yearSelected(int)),this,SLOT(showContent(int)));


    alphaVp = new alphaVideo(this);
    alphaVp->resize(860,800);
    alphaVp->move((width()-alphaVp->width())/2,(height()-alphaVp->height())/2-100);
    alphaVp->setLoop(true);
    alphaVp->setAttribute( Qt::WA_TransparentForMouseEvents );



    dataLbl = new QLabel(this);
    dataLbl->setScaledContents(true);
    dataLbl->setAttribute( Qt::WA_TransparentForMouseEvents );
    dataLbl->show();
    dataLblAnim = new QPropertyAnimation(dataLbl,"geometry");
    dataLblAnim->setDuration(200);
    dataLblAnim->setEasingCurve(QEasingCurve::InCurve);
    connect(dataLblAnim,SIGNAL(finished()),this,SLOT(doneShowingContent()));
    showContent(2);

    QLabel *iktvaLbl = new QLabel(this);
    QImage iktva(PATH+"iktva.png");
    iktvaLbl->resize(iktva.size());
    iktvaLbl->setPixmap(QPixmap::fromImage(iktva));
    iktvaLbl->move((width()-iktvaLbl->width())/2,1920-iktvaLbl->height()/2-100);
    iktvaLbl->show();



    QTimer::singleShot(10,this,SLOT(loadPlayer()));

}



void touchScreen::loadPlayer()
{

    bgVp->loadFilePaused(PATH+"touchBg2.mp4");
    bgVp->play();

    introVp->loadFilePaused(PATH+"touchIntro2.mp4");
}


void touchScreen::startIntroVideo()
{
    introVp->playAndRaise();
    introVp->raise();

}

void touchScreen::stopIntroVideo()
{
    introVp->lower();
    introVp->pause();
    introVp->rewind();
}
void touchScreen::timeoutReset()
{
    emit timeOut();
    timeOutTimer->stop();
    showContent(2);
    yb->reset();

}




void touchScreen::showContent(int contentId)
{
    if(contentId>5)
        return;
    if(contentId<0)
        return;


    if(contentId == activeContent)
        return;

    timeOutTimer->start(TIMEOUT_DELAY);

    QImage data(PATH+"data"+QString::number(contentId)+".png");

    int yc;
    if(contentId==5)
        yc = 340;
    else
        yc = 520;

    alphaVp->hide();

    dataLbl->setPixmap(QPixmap::fromImage(data));


    dataLblAnim->setStartValue(dataLbl->geometry());
    QRect geo=QRect((1080-data.width())/2,yc-data.height()/2,data.width(),data.height());
    dataLblAnim->setEndValue(geo);
    dataLblAnim->start(QAbstractAnimation::KeepWhenStopped);

    activeContent = contentId;
}

void touchScreen::doneShowingContent()
{

    if(activeContent == 5)
    {
        alphaVp->addMedia(PATH+"2021.mp4");
        alphaVp->play();
        alphaVp->show();

    }
    else
    {


    }

}

