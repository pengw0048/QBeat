/* 作者：王昊
 * 储存一个谱面的内容，以小节（Bar）为单位
 */

#include "sheet.h"

Sheet::Sheet(QObject *parent) :QObject(parent)
{
    total=0;
}
Sheet::~Sheet()
{
    for(int i=0;i<bar.count();i++)
    {
        delete bar.at(i);
    }
}
void Sheet::clear()
{
    total=0;
    for(int i=0;i<bar.count();i++)
    {
        delete bar.at(i);
    }
    bar.clear();
}
void Sheet::append(Bar *tbar)
{
    bar.append(tbar);
}
int Sheet::count()
{
    return bar.count();
}
Bar *Sheet::at(int i)
{
    return bar.at(i);
}
