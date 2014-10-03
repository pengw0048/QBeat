/* 作者：汪芃
 * 实现基本的数学函数
 */

#include <QString>

#ifndef MMATH_H
#define MMATH_H

int mmin(int a,int b){
    if(a<=b)return a;
    return b;
}

int mround(double a){
    if(a-(int)a<0.5)return (int)a;
    return (int)a+1;
}

double mfabs(double a){
    if(a>=0)return a;
    return -a;
}

int mabs(int a){
    if(a>=0)return a;
    return -a;
}

QString shorten(QString &s,int len){
    if(s.length()<=len)return s;
    return s.left(len-2)+QString("..");
}

#endif // MMATH_H
