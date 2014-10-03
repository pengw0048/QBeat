/* 作者：司雯文
 * 表示一个显示在游戏画面上的字母
 */

#include "fallletter.h"

FallLetter::FallLetter(QObject *parent): QObject(parent) {
    pressed = false;
    result = 0;
}
