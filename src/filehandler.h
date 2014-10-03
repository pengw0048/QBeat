/* 作者：王昊
 * 处理文件相关操作：列目录、存取最高纪录、读取谱面
 */

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QVector>
#include "songinfo.h"
#include "sheet.h"

class FileHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileHandler(QObject *parent = 0);
    ~FileHandler();
    QVector<SongInfo *> &getAll(QString);
    QVector<SongInfo *> songs;
    void getTop(SongInfo *);
    void loadSheet(SongInfo *, Sheet *);
    void saveTop(int, SongInfo *);
private:
    QString trim(QString);
signals:    
public slots:    
};

#endif // FILEHANDLER_H
