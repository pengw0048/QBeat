/* 作者：汪芃
 * 主类，控制程序流程、响应重绘和键盘事件
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    void initScene1();
    void initScene2();
    void initScene3();
    void updateMenu();

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);

private slots:
    void songEnd(QMediaPlayer::MediaStatus);
};

#endif // WIDGET_H
