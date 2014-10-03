/* 作者：司雯文
 * 表示一个显示在游戏画面上的字母
 */

#ifndef FALLLETTER_H
#define FALLLETTER_H

#include <QObject>

class FallLetter : public QObject
{
    Q_OBJECT
public:
    explicit FallLetter(QObject *parent = 0);
    bool pressed;
    char letter;
    double x,atime;
    int eslot1,eslot2,result;
    
signals:
    
public slots:
    
};

#endif // FALLLETTER_H
