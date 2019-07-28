#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlaylist>
#include <QMediaPlayer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btOpen_clicked();
    void on_pushButton_clicked();
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);


private:
    Ui::Widget *ui;
    QMediaPlaylist music_list;    // 音乐播放列表
    QMediaPlayer *player;
    int volume;
    int play_flag;
};

#endif // WIDGET_H
