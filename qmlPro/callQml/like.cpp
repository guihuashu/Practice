#include "like.h"

Like::Like(QObject *parent) : QObject(parent)
{

}
int i = 0;
void Like::slot1()
{
    qDebug()<<"Like::slot1()";
    emit changeText(QString("changeText:") + QString::number(i++));
}
