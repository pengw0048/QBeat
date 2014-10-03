/* 作者：汪芃
 * 主类，控制程序流程、响应重绘和键盘事件
 */

#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsOpacityEffect>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QVector>
#include <QDir>
#include <QFile>
#include <QFont>
#include <QImage>
#include <stdio.h>
#include "filehandler.h"
#include "sheet.h"
#include "explosion.h"
#include "fallletter.h"
#include "mmath.h"
#include "skinmanager.h"

const int xlist[7]={233,233,203,173,143,113,83};
const int mxlist[26]={470,612,546,536,526,569,602, 635,691,668,701,734,678,645, 724,757,460,559,503,592, 658,579,493,513,625,480};
const int mylist[26]={413,446,446,413,380,413,413, 413,380,413,413,413,446,446, 380,380,380,380,413,380, 380,446,380,446,380,446};

QTimer *utimer;
int scene=0;
int splashCounter=0,changeCounter=-1200,menuCounter=0,hlCounter=0,scoreCounter=0,perfCounter=0;
int selection=0,lastSelection=0;
int vstart=0,combo=0,r[4];
double score=0.0,duration;
bool drawing=false;
QGraphicsOpacityEffect *effect;
FileHandler file;
QPixmap *theme,*songPic,*change;
SongInfo *curSong;
QMediaPlayer *player;
QSoundEffect *ka;
QString rankStr[6]={QObject::tr("Ranking 1st:"),QObject::tr("Ranking 2nd:"),QObject::tr("Ranking 3rd:"),QObject::tr("Ranking 4th:"),QObject::tr("Ranking 5th:"),QObject::tr("Ranking 6th:")};
Sheet sheet;
Explosion explosion[2][6];
QVector<FallLetter *> fall;
QImage *performance,*ssongPic;
SkinManager *skin;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    skin=new SkinManager;
    ui->label->setAttribute(Qt::WA_TranslucentBackground);
    player=new QMediaPlayer;
    ka=new QSoundEffect;
    ka->setSource(QUrl::fromLocalFile("se/ka.wav"));
    theme=new QPixmap;
    songPic=new QPixmap;
    change=new QPixmap;
    theme->load(tr("images/theme.png"));
    change->load(tr("images/change.png"));
    performance=new QImage(800,150,QImage::Format_ARGB32_Premultiplied);
    ssongPic=new QImage(301,226,QImage::Format_ARGB32_Premultiplied);
    for(int i=0;i<5;i++){
        explosion[0][i].x=113+60*i;
        explosion[0][i].y=525;
    }
    for(int i=0;i<6;i++){
        explosion[1][i].x=83+60*i;
        explosion[1][i].y=525;
    }
    ui->label->setPixmap(*theme);
    effect=new QGraphicsOpacityEffect();
    effect->setOpacity(0.0);
    ui->label->setGraphicsEffect(effect);
    file.getAll(tr("songs"));
    utimer=new QTimer(this);
    connect(utimer,SIGNAL(timeout()),this,SLOT(update()));
    utimer->start(12);
}

Widget::~Widget()
{
    delete skin;
    delete theme;
    delete change;
    delete performance;
    delete ssongPic;
    delete player;
    delete ka;
    delete utimer;
    delete ui;
}

void Widget::paintEvent(QPaintEvent *){
    if(drawing)return;
    drawing=true;
    QPainter painter(this);
    switch(scene){
    case 0:
        if(splashCounter<=50||splashCounter>=100){
            effect->setOpacity((splashCounter>=100?150-splashCounter:splashCounter)/50.0);
            ui->label->setGraphicsEffect(effect);
        }
        splashCounter++;
        if(splashCounter>=150){
            initScene1();
            scene=1;
        }
        break;
    case 1:
    {
        painter.drawPixmap(QRect(0,0,800,600),*songPic);
        if(menuCounter==20)painter.drawPixmap(QRect(620,150,262,350),*skin->selbox2);
        else painter.drawPixmap(QRect(620,150,262,(int)(17.5*menuCounter)),*skin->selbox2,QRect(0,0,(skin->selbox2)->width(),(int)((double)(skin->selbox2)->height()*menuCounter/20.0)));
        painter.setPen(Qt::black);
        QFont font(tr("Courier"),16);
        painter.setFont(font);
        if(menuCounter==20){
            for(int i=0;i<6;i++){
                painter.drawText(QPoint(630,i*50+190),rankStr[i]);
                painter.drawText(QPoint(652,i*50+190+25),QString("%1").arg(curSong->top[i]));
            }
            if(curSong->top[0]!=0){
                QString pj=skin->getPj(curSong->top[0]);
                painter.setPen(skin->getPjPen(curSong->top[0]));
                QFont font3(tr("Courier"),56);
                painter.setFont(font3);
                painter.drawText(QPoint(630,168),pj);
            }
        }
        painter.setPen(Qt::black);
        painter.setFont(font);
        int start=selection-2;
        if(start<0)start=0;
        if(file.songs.count()<=7)start=0;
        else if(start+6>=file.songs.count())start=file.songs.count()-7;
        for(int i=start;i<mmin(start+7,file.songs.count());i++){
            if(i==selection){
                painter.drawPixmap(QRect(70,100+(i-start)*60,200+(int)(6.5*menuCounter),60),*skin->selbox1);
                if(menuCounter==20){
                    painter.drawPixmap(QRect(80+2*hlCounter,100+(i-start)*60,14,7),*skin->hilight);
                    painter.drawPixmap(QRect(380-2*hlCounter,153+(i-start)*60,14,7),*skin->hilight);
                    hlCounter++;
                    if(hlCounter>150)hlCounter=0;
                }
                painter.setPen(Qt::red);
                painter.drawText(QPoint(85,145+(i-start)*60),shorten(file.songs.at(i)->name,24));
            }else{
                painter.drawPixmap(QRect(70-5*mabs(i-selection),100+(i-start)*60,i==lastSelection?330-(int)(6.5*menuCounter):200,60),*skin->selbox1);
                painter.setPen(Qt::black);
                painter.drawText(QPoint(85-5*mabs(i-selection),145+(i-start)*60),shorten(file.songs.at(i)->name,14));
            }
        }
        painter.drawPixmap(QRect(0,600-5*menuCounter,800,100),*skin->bottom);
        if(menuCounter==20){
            painter.setPen(Qt::black);
            painter.drawText(QPoint(400,575),tr("Level ="));
            for(int i=0;i<curSong->star;i++)painter.drawPixmap(QRect(500+28*i,560,16,16),*skin->star[0]);
            if(start>0)painter.drawPixmap(QRect(140,35,60,30),*skin->up);
            if(start+7<file.songs.count())painter.drawPixmap(QRect(140,543,60,30),*skin->down);
        }
        if(changeCounter!=-1200){
            painter.drawPixmap(QRect(0,changeCounter,801,1201),*change);
            changeCounter+=30;
            if(changeCounter>-300){
                initScene2();
                scene=2;
            }
        }
        if(menuCounter!=20)menuCounter++;
        if(menuCounter>20)menuCounter=20;
        break;
    }
    case 2:
    {
        painter.drawPixmap(QRect(0,0,800,600),*skin->gameback);
        painter.drawImage(QRect(475,100,300,225),*ssongPic);
        painter.setPen(Qt::black);
        QFont font(tr("Courier"),16);
        painter.setFont(font);
        painter.drawText(QPoint(475,25),curSong->name);
        char tc[10];
        sprintf(tc,"%7.0lf",score);
        QFont font2(tr("Courier"),40);
        painter.setFont(font2);
        painter.drawText(QPoint(550,68),QString(tc));
        if(combo>=10){
            painter.setPen(skin->getComboPen(combo));
            QFont font3(tr("Courier"),72);
            painter.setFont(font3);
            painter.drawText(QRect(130,120,200,100),Qt::AlignHCenter,QString("%1").arg(combo));
        }
        for(int i=0;i<10;i++)painter.drawPixmap(QRect(460+33*i,380,30,30),*skin->key);
        for(int i=0;i<9;i++)painter.drawPixmap(QRect(470+33*i,413,30,30),*skin->key);
        for(int i=0;i<7;i++)painter.drawPixmap(QRect(480+33*i,446,30,30),*skin->key);

        int you[26];
        for(int i=0;i<26;i++)you[i]=0;
        double nowpos=(double)player->position()/1000.0;
        for(int i=vstart;i<fall.count();i++){
            double tpos=500.0-(fall.at(i)->atime-nowpos)/(60.0*2.5/sheet.bpm)*500.0;
            if(tpos<-70.0)break;
            if(tpos>600.0){
                vstart=i;
                if(!fall.at(i)->pressed)combo=0;
            }else if(!fall.at(i)->pressed){
                painter.drawPixmap(QRect(fall.at(i)->x-25,(int)tpos,50.0,50.0),*skin->letter[fall.at(i)->letter-'A']);
                if(tpos<500.0&&tpos>0){
                    painter.drawPixmap(QRect(mxlist[fall.at(i)->letter-'A']-tpos/500.0*15.0+16,mylist[fall.at(i)->letter-'A']-tpos/500.0*15.0+16,tpos/500.0*30.0,tpos/500.0*30.0),you[fall.at(i)->letter-'A']%2==1?*skin->mark2:*skin->mark1);
                    you[fall.at(i)->letter-'A']++;
                }
            }
        }
        painter.drawPixmap(QRect(0,550,800,50),*skin->pbar);
        painter.drawPixmap(QRect((double)player->position()/(double)player->duration()*750.0,550,50,50),*skin->pbaricon);

        for(int i=0;i<2;i++)for(int j=0;j<6;j++)explosion[i][j].paint(painter,skin->star[explosion[i][j].color]);
        if(changeCounter!=-1200){
            painter.drawPixmap(QRect(0,changeCounter,801,1201),*change);
            changeCounter+=30;
            if(changeCounter>4000){
                changeCounter=-1200;
                player->play();
                duration=(double)player->duration()/1000;
                connect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(songEnd(QMediaPlayer::MediaStatus)));
            }
        }
        if(scoreCounter!=-1200){
            painter.drawPixmap(QRect(0,scoreCounter,801,1201),*change);
            scoreCounter+=60;
            if(scoreCounter>-300){
                initScene3();
                scene=3;
            }
        }
        break;
    }
    case 3:
    {
        painter.drawPixmap(QRect(0,0,800,600),*skin->seiback);
        painter.drawImage(QRect(50,187,301,226),*ssongPic);
        painter.setPen(Qt::black);
        QFont font(tr("Courier"),36);
        painter.setFont(font);
        painter.drawText(QPoint(20,80),curSong->name);
        QFont font2(tr("Courier"),24);
        painter.setFont(font2);
        painter.drawText(QPoint(20,132),QString("Your score = %1").arg(mround(score)));
        for(int i=0;i<4;i++){
            painter.drawPixmap(QRect(420,200+50*i,150,50),*skin->rx[i]);
            painter.drawText(QPoint(600,240+50*i),QString("%1").arg(r[i]));
        }
        if(perfCounter!=0){
            painter.drawImage(QRect(0,451,8*perfCounter,150),*performance,QRect(0,0,8*perfCounter,150));
            perfCounter++;
            if(perfCounter>100)perfCounter=0;
        }else if(scoreCounter==-1200)painter.drawImage(QRect(0,451,800,150),*performance);
        painter.setPen(Qt::gray);
        painter.drawText(QPoint(12,492),tr("Performance"));
        QString pj=skin->getPj(score);
        painter.setPen(skin->getPjPen(score));
        QFont font3(tr("Courier"),72);
        painter.setFont(font3);
        painter.drawText(QPoint(524,131),pj);
        if(scoreCounter!=-1200){
            painter.drawPixmap(QRect(0,scoreCounter,801,1201),*change);
            scoreCounter+=60;
            if(scoreCounter>1200){
                scoreCounter=-1200;
                perfCounter=1;
            }
        }
        break;
    }
    }
    drawing=false;
}

void Widget::keyPressEvent(QKeyEvent *event){
    switch(scene){
    case 0:
        if(event->key()==Qt::Key_Escape||event->key()==Qt::Key_Enter)splashCounter=150;
        break;
    case 1:
        if(changeCounter!=-1200||menuCounter!=20)return;
        if(event->key()==Qt::Key_Up){
            lastSelection=selection;
            selection--;
            if(selection<0)selection=file.songs.count()-1;
            ka->play();
            updateMenu();
        }else if(event->key()==Qt::Key_Down){
            lastSelection=selection;
            selection++;
            if(selection>=file.songs.count())selection=0;
            ka->play();
            updateMenu();
        }else if(event->key()==Qt::Key_Return||event->key()==Qt::Key_Enter){
            changeCounter++;
        }
        break;
    case 2:
        if(scoreCounter!=-1200)return;
        if(event->key()==Qt::Key_Escape){
            disconnect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(songEnd(QMediaPlayer::MediaStatus)));
            scene=1;
            player->stop();
            initScene1();
        }else if(event->key()>=Qt::Key_A&&event->key()<=Qt::Key_Z){
            bool got=false;
            double nowpos=(double)player->position()/1000.0;
            for(int i=vstart;i<fall.count();i++){
                double tpos=500.0-(fall.at(i)->atime-nowpos)/(60.0*3.0/sheet.bpm)*500.0;
                if(tpos<200.0)break;
                if((fall.at(i)->letter-'A')==(event->key()-Qt::Key_A)&&fall.at(i)->pressed==false){
                    if(abs(tpos-500.0)<=25.0){
                        got=true;
                        score+=sheet.pscore;
                        explosion[fall.at(i)->eslot1][fall.at(i)->eslot2].stage=1;
                        explosion[fall.at(i)->eslot1][fall.at(i)->eslot2].color=0;
                        r[0]++;
                        fall.at(i)->result=1;
                    }else if(abs(tpos-500.0)<=35.0){
                        got=true;
                        score+=sheet.pscore/1.5;
                        explosion[fall.at(i)->eslot1][fall.at(i)->eslot2].stage=1;
                        explosion[fall.at(i)->eslot1][fall.at(i)->eslot2].color=1;
                        r[1]++;
                        fall.at(i)->result=2;
                    }else if(abs(tpos-500.0)<=45.0){
                        got=true;
                        score+=sheet.pscore/2.0;
                        explosion[fall.at(i)->eslot1][fall.at(i)->eslot2].stage=1;
                        explosion[fall.at(i)->eslot1][fall.at(i)->eslot2].color=2;
                        r[2]++;
                        fall.at(i)->result=3;
                    }
                }
                if(got){
                    combo++;
                    fall.at(i)->pressed=true;
                    break;
                }
            }
        }
        break;
    case 3:
        if(scoreCounter==-1200){
            initScene1();
            scene=1;
        }
    }
}

void Widget::initScene1(){
    ui->label->setVisible(false);
    selection=lastSelection=0;
    changeCounter=-1200;
    updateMenu();
}

void Widget::initScene2(){
    drawing=true;
    scoreCounter=-1200;
    player->setMedia(QUrl::fromLocalFile(curSong->music));
    score=0.0;
    vstart=0;
    combo=0;
    sheet.clear();
    for(int i=0;i<fall.count();i++)delete fall.at(i);
    fall.clear();
    for(int i=0;i<4;i++)r[i]=0;
    file.loadSheet(curSong,&sheet);
    for(int i=0;i<6;i++)explosion[0][i].stage=explosion[1][i].stage=0;
    for(int i=0;i<sheet.count();i++){
        Bar *tbar=sheet.at(i);
        for(int j=0;j<tbar->count();j++){
            Beat *tbeat=tbar->at(j);
            if(tbeat->len==0)continue;
            for(int k=0;k<tbeat->len;k++){
                FallLetter *tletter=new FallLetter;
                tletter->letter=tbeat->letter[k];
                tletter->x=xlist[tbeat->len]+60*k;
                tletter->atime=60.0*4.0/sheet.bpm*((double)j/tbar->count()+i)+sheet.delay;
                if(tbeat->len%2==0){
                    tletter->eslot1=1;
                    if(tbeat->len==2)tletter->eslot2=2+k;
                    else if(tbeat->len==4)tletter->eslot2=1+k;
                    else if(tbeat->len==6)tletter->eslot2=k;
                }else{
                    tletter->eslot1=0;
                    if(tbeat->len==1)tletter->eslot2=2+k;
                    else if(tbeat->len==3)tletter->eslot2=1+k;
                    else if(tbeat->len==5)tletter->eslot2=k;
                }
                fall.append(tletter);
            }
        }
    }
    drawing=false;
}

void Widget::initScene3(){
    drawing=true;
    file.saveTop(mround(score),curSong);
    r[3]=sheet.total-r[0]-r[1]-r[2];
    perfCounter=0;
    performance->fill(Qt::white);
    QPainter painter(performance);
    QPen pen1(Qt::blue,3),pen2(Qt::green,3),pen3(Qt::red,3);
    painter.setPen(pen1);
    double ly=148.0;
    for(int i=2;i<=800;i+=2){
        int j;
        double scoreSum=0,ty,ttime=duration/800.0*i;
        for(j=0;j<fall.count();j++){
            if(fall.at(j)->atime>=ttime)break;
            scoreSum+=sheet.pscore;
        }
        ty=(148.0-scoreSum/1000000.0*148.0);
        painter.drawLine(QPointF(i-1,ly),QPointF(i,ty));
        ly=ty;
    }
    ly=148.0;
    int lastEnd=0,end=0;
    for(int i=2;i<=800;i+=2){
        int j;
        bool ok=true;
        double scoreSum=0,ty,ttime=duration/800.0*i;
        for(j=0;j<fall.count();j++){
            if(fall.at(j)->atime>=ttime)break;
            end=j;
            if(fall.at(j)->result==1)scoreSum+=sheet.pscore;
            else if(fall.at(j)->result==2)scoreSum+=sheet.pscore/1.5;
            else if(fall.at(j)->result==3)scoreSum+=sheet.pscore/2.0;
            else if(j>lastEnd&&fall.at(j)->result!=1)ok=false;
        }
        lastEnd=end;
        ty=(148.0-scoreSum/1000000.0*148.0);
        if(!ok)painter.setPen(pen3);
        else painter.setPen(pen2);
        painter.drawLine(QPointF(i-1,ly),QPointF(i,ty));
        ly=ty;
    }
    drawing=false;
}

void Widget::updateMenu(){
    drawing=true;
    menuCounter=hlCounter=0;
    curSong=file.songs.at(selection);
    file.getTop(curSong);
    skin->loadSkin(curSong);
    songPic->load(curSong->pic);
    QPainter painter(ssongPic);
    painter.drawPixmap(QRect(0,0,301,226),*songPic);
    player->stop();
    player->setMedia(QUrl::fromLocalFile(curSong->music));
    player->play();
    drawing=false;
}

void Widget::songEnd(QMediaPlayer::MediaStatus status){
    if(status!=QMediaPlayer::EndOfMedia)return;
    disconnect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(songEnd(QMediaPlayer::MediaStatus)));
    scoreCounter++;
}
