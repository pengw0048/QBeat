/* 作者：司雯文
 * 处理爆炸动画
 */

#include "explosion.h"
#include <math.h>

Explosion::Explosion (QObject * parent):QObject(parent) {
    stage = 0;
    x = y = 0;
}

void Explosion::update() {
    stage++;
    if(stage > 15)
        stage = 0;
}

void Explosion::paint(QPainter & painter, QPixmap * star) {
    if(stage == 0) return;
    for (int i = 0; i < 12; i++){
        double cx = x + stage*2*cos(i*30.0/180.0*PI);
        double cy = y + stage*2*sin(i*30.0/180.0*PI);
        painter.drawPixmap( QRect(cx-5,cy-5,10,10), *star);
    }
    update();
}
