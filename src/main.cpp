#include "widget.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gb18030"));
    QApplication a(argc, argv);
    Widget w;
    w.show();
    
    return a.exec();
}
