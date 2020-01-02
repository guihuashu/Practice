#ifndef LIKE_H
#define LIKE_H

#include <QObject>
#include <QDebug>
class Like : public QObject
{
    Q_OBJECT
public:
    explicit Like(QObject *parent = nullptr);


signals:
    void changeText(QString s);

public slots:
    void slot1();
};

#endif // LIKE_H
