/* 作者：司雯文
 * 管理界面图片（皮肤），自动选择原图或自定义图片
 */

#include "skinmanager.h"
#include <QPixmap>
#include <QFileInfo>
#include <QTime>
#include "songinfo.h"

SkinManager::SkinManager(QObject *parent): QObject(parent) {
    custom = false;
    selbox1 = oselbox1 = new QPixmap;
    selbox2 = oselbox2 = new QPixmap;
    bottom = obottom = new QPixmap;
    star[0] = ostar[0] = new QPixmap;
    star[1] = ostar[1] = new QPixmap;
    star[2] = ostar[2] = new QPixmap;
    gameback = ogameback = new QPixmap;
    key = okey = new QPixmap;
    mark1 = omark1 = new QPixmap;
    mark2 = omark2 = new QPixmap;
    hilight = ohilight = new QPixmap;
    seiback = oseiback = new QPixmap;
    pbar = opbar = new QPixmap;
    pbaricon = opbaricon = new QPixmap;
    up = oup = new QPixmap;
    down = odown = new QPixmap;
    for(int i = 0; i < 26; i++)
        letter[i] = oletter[i] = new QPixmap;
    for(int i = 0; i < 4; i++)
        rx[i] = orx[i] = new QPixmap;

    cselbox1 = new QPixmap;
    cselbox2 = new QPixmap;
    cbottom = new QPixmap;
    cstar[0] = new QPixmap;
    cstar[1] = new QPixmap;
    cstar[2] = new QPixmap;
    cgameback = new QPixmap;
    ckey = new QPixmap;
    cmark1 = new QPixmap;
    cmark2 = new QPixmap;
    chilight = new QPixmap;
    cseiback = new QPixmap;
    cpbar = new QPixmap;
    cpbaricon = new QPixmap;
    cup = new QPixmap;
    cdown = new QPixmap;
    for(int i = 0; i < 26; i++) cletter[i] = new QPixmap;
    for(int i = 0; i < 4; i++) crx[i] = new QPixmap;
    oselbox1->load(tr("images/selbox1.png"));
    oselbox2->load(tr("images/selbox2.png"));
    obottom->load(tr("images/bottom.png"));
    ostar[0]->load(tr("images/star0.png"));
    ostar[1]->load(tr("images/star1.png"));
    ostar[2]->load(tr("images/star2.png"));
    ogameback->load(tr("images/game_back.png"));
    okey->load(tr("images/key.png"));
    omark1->load(tr("images/mark1.png"));
    omark2->load(tr("images/mark2.png"));
    ohilight->load(tr("images/hilight.png"));
    oseiback->load(tr("images/sei_back.png"));
    opbar->load(tr("images/pbar.png"));
    opbaricon->load(tr("images/pbaricon.png"));
    oup->load(tr("images/up.png"));
    odown->load(tr("images/down.png"));
    for(int i = 0; i < 26; i++)
        oletter[i]->load(tr("images/") + QString((char)('A' + i)) + tr(".png"));
    for(int i = 0; i < 4; i++)
        orx[i]->load(QString("images/r%1.png").arg(i));
    QTime time;
    time = QTime::currentTime();
    qsrand(time.msec() + time.second()*1000);
    excCounter = 0;
}

SkinManager::~SkinManager(){
    delete oselbox1;
    delete oselbox2;
    delete obottom;
    delete ostar[0];
    delete ostar[1];
    delete ostar[2];
    delete ogameback;
    delete okey;
    delete omark1;
    delete omark2;
    delete ohilight;
    delete oseiback;
    delete opbar;
    delete opbaricon;
    delete oup;
    delete odown;
    for(int i = 0; i < 26; i++)
        delete oletter[i];
    for(int i = 0; i < 4; i++)
        delete orx[i];
    delete cselbox1;
    delete cselbox2;
    delete cbottom;
    delete cstar[0];
    delete cstar[1];
    delete cstar[2];
    delete cgameback;
    delete ckey;
    delete cmark1;
    delete cmark2;
    delete chilight;
    delete cseiback;
    delete cpbar;
    delete cpbaricon;
    delete cup;
    delete cdown;
    for(int i = 0; i < 26; i++)
        delete cletter[i];
    for(int i = 0; i < 4; i++)
        delete crx[i];
}

void SkinManager::loadSkin(SongInfo *song) {
    if(QFileInfo(song->skin).exists() == false){
        custom = false;
        selbox1 = oselbox1;
        selbox2 = oselbox2;
        bottom = obottom;
        star[0] = ostar[0];
        star[1] = ostar[1];
        star[2] = ostar[2];
        gameback = ogameback;
        key = okey;
        mark1 = omark1;
        mark2 = omark2;
        hilight = ohilight;
        seiback = oseiback;
        pbar = opbar;
        pbaricon = opbaricon;
        up = oup;
        down = odown;
        for(int i = 0; i < 26; i++)
            letter[i] = oletter[i];
        for(int i = 0; i < 4; i++)
            rx[i] = orx[i];
    }else{
        custom = true;
        selbox1 = process(oselbox1, cselbox1, "selbox1", song->skin);
        selbox2 = process(oselbox2, cselbox2, "selbox2", song->skin);
        bottom = process(obottom, cbottom, "bottom", song->skin);
        for(int i = 0; i < 3; i++)
            star[i] = process(ostar[i], cstar[i], QString("star%1").arg(i), song->skin);
        gameback = process(ogameback, cgameback, "game_back", song->skin);
        key = process(okey, ckey, "key", song->skin);
        mark1 = process(omark1, cmark1, "mark1", song->skin);
        mark2 = process(omark2, cmark2, "mark2", song->skin);
        hilight = process(ohilight, chilight, "hilight", song->skin);
        seiback = process(oseiback, cseiback, "sei_back", song->skin);
        pbar = process(opbar, cpbar, "pbar", song->skin);
        pbaricon = process(opbaricon, cpbaricon, "pbaricon", song->skin);
        up = process(oup, cup, "up", song->skin);
        down = process(odown, cdown, "down", song->skin);
        for(int i = 0; i < 26; i++)
            letter[i] = process(oletter[i], cletter[i], QString((char)('A'+i)), song->skin);
        for(int i = 0; i < 4; i++)
            rx[i] = process(orx[i],crx[i], QString("r%1").arg(i), song->skin);
    }
}

QPixmap *SkinManager::process(QPixmap *o, QPixmap *c, QString name, QString path){
    if(QFileInfo(path + "/" + name + ".png").exists()){
        c->load(path + "/" + name + ".png");
        return c;
    }else
        return o;
}

QString SkinManager::getPj(double score){
    QString pj;
    if(score < 500000)
        pj = QObject::tr("F");
    else if(score < 600000)
        pj = QObject::tr("E");
    else if(score < 700000)
        pj = QObject::tr("D");
    else if(score < 800000)
        pj = QObject::tr("C");
    else if(score < 850000)
        pj = QObject::tr("B");
    else if(score < 900000)
        pj = QObject::tr("A");
    else if(score < 950000)
        pj = QObject::tr("S");
    else if(score < 975000)
        pj = QObject::tr("SS");
    else if(score < 1000000)
        pj = QObject::tr("SSS");
    else
        pj = QObject::tr("EXC");
    return pj;
}

QColor SkinManager::getPjPen(double score){
    if(score < 700000)
        return (Qt::black);
    else if(score < 800000)
        return (Qt::blue);
    else if(score < 850000)
        return (Qt::green);
    else if(score < 900000)
        return (Qt::yellow);
    else if(score < 950000)
        return (QColor(255,128,0));
    else if(score < 999999.99)
        return (Qt::red);
    else{
        if(excCounter % 10 == 0){
            excColor = QColor(qrand() % 256, qrand() % 256, qrand() % 256);
            excCounter = 0;
        }
        excCounter++;
        return (excColor);
    }
}

QColor SkinManager::getComboPen(int combo){
    if(combo < 40)
        return (QColor(0,0, (int)255.0/30.0*(combo-10)));
    else if(combo < 70)
        return (QColor(0, (int)255.0/30.0*(combo-40), (int)(255-255.0/30.0*(combo-40))));
    else if(combo < 100)
        return (QColor((int)255.0/30.0*(combo-70), 255, 0));
    else if(combo < 150)
        return (QColor(255, (int)(255-255.0/50.0*(combo-100)), 0));
    else
        return (Qt::red);
}
