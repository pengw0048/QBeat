/* 作者：王昊
 * 储存一个谱面（歌曲）的相关信息
 */

#ifndef SONGINFO_H
#define SONGINFO_H

#include <QObject>

class SongInfo : public QObject
{
    Q_OBJECT
public:
    explicit SongInfo(QObject *parent = 0);
    QString name,music,pic,rec,alp,skin;
    int star,top[7];
signals:  
public slots:  
};

#endif // SONGINFO_H
