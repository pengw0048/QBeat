/* 作者：王昊
 * 储存一个小节的内容，以节拍（Beat）为单位
 */

#ifndef BAR_H
#define BAR_H

#include <QObject>
#include <QVector>
#include "beat.h"

class Bar : public QObject
{
    Q_OBJECT
public:
    explicit Bar(QObject *parent = 0);
    ~Bar();
    //void clear();
    void append(Beat *);
    int count();
    Beat *at(int);
protected:
    QVector<Beat *> beat;
signals:  
public slots:  
};

#endif // BAR_H
