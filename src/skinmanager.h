/* 作者：司雯文
 * 管理界面图片（皮肤），自动选择原图或自定义图片
 */

#ifndef SKINMANAGER_H
#define SKINMANAGER_H

#include <QObject>
#include <QColor>
#include <QString>

class QPixmap;
class SongInfo;

class SkinManager : public QObject
{
    Q_OBJECT
public:
    explicit SkinManager(QObject *parent = 0);
    ~SkinManager();
    void loadSkin(SongInfo *);
    QPixmap *selbox1,*selbox2,*bottom,*star[3],*gameback,*key,*mark1,*mark2,*hilight,*letter[26],*seiback,*rx[4],*pbar,*pbaricon,*up,*down;
    QString getPj(double);
    QColor getPjPen(double);
    QColor getComboPen(int);

private:
    QPixmap *cselbox1,*cselbox2,*cbottom,*cstar[3],*cgameback,*ckey,*cmark1,*cmark2,*chilight,*cletter[26],*cseiback,*crx[4],*cpbar,*cpbaricon,*cup,*cdown;
    QPixmap *oselbox1,*oselbox2,*obottom,*ostar[3],*ogameback,*okey,*omark1,*omark2,*ohilight,*oletter[26],*oseiback,*orx[4],*opbar,*opbaricon,*oup,*odown;
    bool custom;
    QPixmap *process(QPixmap *, QPixmap *, QString, QString);
    int excCounter;
    QColor excColor;

signals:
    
public slots:
    
};

#endif // SKINMANAGER_H
