#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QStringList>
#include <QDebug>

QString get_filename(QString path)
{
    return path.remove(0, path.lastIndexOf(QString("/")) + 1);
}

// 播放进度改变(毫秒为单位)
void Widget::positionChanged(qint64 position)
{

    int total = player->duration() / 1000;  // 当前播放文件的总时长
    int cur = position / 1000;              // 当前播放的时长
    ui->hSlider->setMaximum(total);
    ui->hSlider->setMinimum(0);
    ui->hSlider->setValue(cur);
    ui->lbTotaltime->setText(QString::number(total));
    ui->lbCurtime->setText(QString::number(cur));
}

// 播放列表中的文件
void Widget::durationChanged(qint64 duration)
{
    QString filename = get_filename(player->currentMedia().canonicalUrl().toString());
    ui->lbFilename->setText(filename);
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    music_list.clear(); // 清空播放列表
    volume = 50;        // 设置默认音量
    player = new QMediaPlayer(this);    // 创建一个媒体播放器
    player->setPlaylist(&music_list);   // 设置媒体播放器的播放列表
    play_flag = 0;
    // 播放进度改变(以毫秒为单位)
    QObject::connect(player, &QMediaPlayer::positionChanged, this, &Widget::positionChanged);
    // 总时长改变(以毫秒为单位)    // 播放新文件是将产生该信号
    QObject::connect(player, &QMediaPlayer::durationChanged, this, &Widget::durationChanged);
    ui->hSlider->setMaximum(0); // 设置进度条的默认值
    ui->hSlider->setMinimum(0);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btOpen_clicked()
{
    // 获取一个外部文件
    QString path = QFileDialog::getOpenFileName();
    if (path.isNull())
        return;
    // 文件加入QMediaPlaylist的尾部
    music_list.addMedia(QUrl(path));

    // 设置播放列表的当前索引为新打开的音乐未知
    music_list.setCurrentIndex(music_list.mediaCount() -1);
    // 播放
    player->play();
    play_flag = 1;
}

void Widget::on_pushButton_clicked()
{
    QStringList list = QFileDialog::getOpenFileNames(); // 获取多个文件
    for (int i=0; i < list.size(); i++) {
        music_list.addMedia(QUrl(list.at(i)));      // 多个文件放入播放列表
    }
    if (!play_flag)
        player->play();
}

