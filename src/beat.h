/* 作者：王昊
 * 储存一个节拍的内容，在字符数组中
 */

#ifndef BEAT_H
#define BEAT_H

#include <QObject>

class Beat : public QObject
{
    Q_OBJECT
public:
    explicit Beat(QObject *parent = 0);
    char letter[6];
    int len;
signals:
public slots:  
};

#endif // BEAT_H
