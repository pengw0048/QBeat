/* 作者：王昊
 * 储存一个谱面（歌曲）的相关信息
 */

#include "songinfo.h"

SongInfo::SongInfo(QObject *parent) :QObject(parent)
{
    for(int i=0;i<6;i++)
    {
        top[i]=0;
    }
}
