/* 作者：司雯文
 * 处理爆炸动画
 */

#ifndef PI
#define PI 3.1415926535897932
#endif

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QObject>
#include <QPainter>
#include <QPixmap>

class Explosion : public QObject
{
    Q_OBJECT
public:
    explicit Explosion(QObject *parent = 0);
    int color,stage;
    double x,y;
    void update();
    void paint(QPainter &,QPixmap *);
    
signals:
    
public slots:
    
};

#endif // EXPLOSION_H
