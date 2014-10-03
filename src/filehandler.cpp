/* 作者：王昊
 * 处理文件相关操作：列目录、存取最高纪录、读取谱面
 */
#include "filehandler.h"
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <stdio.h>
#include <string.h>
#include "sheet.h"
#include "bar.h"
#include "beat.h"
QString readline(FILE *fp)
{
    char t[300];
    fgets(t,300,fp);
    return QString::fromLocal8Bit(t).trimmed();
}
FileHandler::FileHandler(QObject *parent) :QObject(parent)
{}
QVector<SongInfo *> &FileHandler::getAll(QString path)
{
    for(int i=0;i<songs.count();i++)
    	delete songs.at(i);
    songs.clear();
    QDir dir(path);
    QString fpath=path;
    if(!(fpath.endsWith("/")||fpath.endsWith("\\")))
    {
        fpath+="/";
    }
    foreach(QFileInfo info, dir.entryInfoList())
    {
        if(!info.isFile())
        {
            continue;
        }
        if(!info.fileName().endsWith(tr(".alp.info")))
        {
            continue;
        }
        SongInfo *tinfo=new SongInfo;
        FILE *fp=fopen(qPrintable(fpath+info.fileName()),"rb");
        tinfo->music=trim(fpath+readline(fp));
        tinfo->pic=trim(fpath+readline(fp));
        tinfo->star=readline(fp).toInt();
        tinfo->name=trim(readline(fp));
        fclose(fp);
        tinfo->rec=fpath+info.fileName().left(info.fileName().length()-4)+tr("dat");
        tinfo->alp=fpath+info.fileName().left(info.fileName().length()-5);
        tinfo->skin=fpath+info.fileName().left(info.fileName().length()-8)+tr("skin");
        qDebug()<<tinfo->skin;
        songs.append(tinfo);
    }
    return songs;
}
FileHandler::~FileHandler()
{
    for(int i=0;i<songs.count();i++)
    {
        delete songs.at(i);
    }
    songs.clear();
}
QString FileHandler::trim(QString s)
{
    if(s.endsWith('\n'))return s.left(s.length()-2);
    return s;
}
void FileHandler::getTop(SongInfo *song)
{
    QFile record(song->rec);
    if (record.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&record);
        for(int i=0;i<6;i++)
        {
            song->top[i]=in.readLine().toInt();
        }
        record.close();
    }
}
void FileHandler::loadSheet(SongInfo *song, Sheet *sheet)
{
    sheet->clear();
    QFile file(song->alp);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    sheet->bpm=file.readLine().trimmed().toDouble();
    sheet->delay=file.readLine().trimmed().toDouble()/1000.0;
    file.readLine();
    while(!file.atEnd())
    {
        QString tLine=QString(file.readLine()).trimmed().remove('\"');
        if(tLine.indexOf(',')==-1)
        {
            continue;
        }
        QByteArray qb=tLine.toLatin1();
        char *tc=qb.data();
        int len=strlen(tc);
        Bar *tbar=new Bar();
        sheet->append(tbar);
        Beat *tbeat=new Beat();
        for(int i=0;i<len;i++)
        {
            if(tc[i]==',')
            {
                tbar->append(tbeat);
                tbeat=new Beat();
            }
            else if(tc[i]>='A'&&tc[i]<='Z')
            {
                tbeat->letter[tbeat->len]=tc[i];
                tbeat->len++;
                sheet->total++;
            }
        }
        delete tbeat;
    }
    file.close();
    sheet->pscore=1000000.0/sheet->total;
}
void FileHandler::saveTop(int score, SongInfo *song)
{
    if(score<=song->top[5])
    {
        return;
    }
    int i=6;
    while(i>0)
    {
        if(score>song->top[i-1])
        {
            song->top[i]=song->top[i-1];
            i--;
        }
        else
        {
            break;
        }
    }
    song->top[i]=score;
    QFile file(song->rec);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);
    for(i=0;i<6;i++)
    {
        out<<song->top[i]<<"\n";
    }
    file.close();
}
