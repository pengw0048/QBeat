/* 作者：王昊
 * 储存一个小节的内容，以节拍（Beat）为单位
 */

#include "bar.h"
Bar::Bar(QObject *parent) :QObject(parent)
{}
Bar::~Bar()
{
    for(int i=0;i<beat.count();i++)
    {
        delete beat.at(i);
    }
}
/*void Bar::clear()
{
    for(int i=0;i<beat.count();i++)
    {
        delete beat.at(i);
    }
    beat.clear();
}*/
void Bar::append(Beat *tbeat)
{
    beat.append(tbeat);
}
int Bar::count()
{
    return beat.count();
}
Beat *Bar::at(int i)
{
    return beat.at(i);
}
