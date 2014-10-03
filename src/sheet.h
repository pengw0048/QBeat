/* 作者：王昊
 * 储存一个谱面的内容，以小节（Bar）为单位
 */

#ifndef SHEET_H
#define SHEET_H

#include <QObject>
#include <QVector>
#include "bar.h"

class Sheet : public QObject
{
    Q_OBJECT
public:
    explicit Sheet(QObject *parent = 0);
    ~Sheet();
    double bpm,delay,total,pscore;
    void clear();
    void append(Bar *);
    int count();
    Bar *at(int);
protected:
    QVector<Bar *> bar; 
signals:  
public slots:  
};

#endif // SHEET_H
