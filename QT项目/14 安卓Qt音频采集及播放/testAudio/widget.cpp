#include "widget.h"
#include "ui_widget.h"
//using namespace std;

Ui::Widget *gui;


static void dump2(QString str)
{
    gui->textBrowser->append(str);
}

int audioTest(QIODevice *inIo, QIODevice *outIo)
{
    char buf[4096] = {0};
    qint64 size = sizeof(buf);
    qint64 len = 0;
    while (1)
    {
        len = 0;
        while (len < size){
            len += inIo->read(buf + len, size - len);
        }
        //qDebug()<<QString("read: ") + QString::number(len);
        len = 0;
        while (len < size){
            len += outIo->write(buf + len, size - len);
        }
    }
    return 0;
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    gui = ui;

    this->initInput();
    this->initOutput();
    std::thread *th = new std::thread(audioTest, inIo, outIo);
    th->detach();
}

void Widget::initInput()
{
    inFmt.setSampleRate(44100);
    inFmt.setChannelCount(2);
    inFmt.setSampleSize(16);
    inFmt.setSampleType(QAudioFormat::UnSignedInt);
    inFmt.setByteOrder(QAudioFormat::LittleEndian);
    inFmt.setCodec("audio/pcm");
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(inFmt)) {
        dump(QString("Default format not supported - trying to use nearest"));
        inFmt = info.nearestFormat(inFmt);
    }
    dump_fmt(inFmt);
    input = new QAudioInput(inFmt, this);
    inIo = input->start();
    if (!inIo) {
        dump("ERR: input->start()");
        exit(0);
    }
    if (!inIo->open(QIODevice::ReadWrite))  {
       dump("ERR: open io");
       exit(0);
    }
    dump("open input io ok");
}

void Widget::initOutput()
{
    outFmt.setSampleRate(44100);
    outFmt.setChannelCount(2);
    outFmt.setSampleSize(16);
    outFmt.setSampleType(QAudioFormat::UnSignedInt);
    outFmt.setByteOrder(QAudioFormat::LittleEndian);
    outFmt.setCodec("audio/pcm");
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultOutputDevice();
    if (!info.isFormatSupported(outFmt)) {
        dump(QString("Default format not supported - trying to use nearest"));
        outFmt = info.nearestFormat(outFmt);
    }
    dump_fmt(outFmt);
    output = new QAudioOutput(outFmt, this);
    outIo = output->start();
    if (!outIo) {
        dump("ERR: input->start()");
        exit(0);
    }
    if (!outIo->open(QIODevice::ReadWrite))  {
       dump("ERR: open io");
       exit(0);
    }
    dump("open output io ok");
    dump("------------------------------------------------");
}





Widget::~Widget()
{
    delete ui;
}

void Widget::dump(QString str)
{
    ui->textBrowser->append(str);
}

void Widget::dump_fmt(QAudioFormat &fmt)
{
    //QAudioFormat::SampleType type = fmt->SampleType();
    dump("--------------------- dump_fmt ---------------------");
    dump(QString("sampleRate:   ") + QString::number(fmt.sampleRate()));
    dump(QString("channelCount: ") + QString::number(fmt.channelCount()));
    dump(QString("sampleSize:   ") + QString::number(fmt.sampleSize()));

    dump(QString("SampleType:   "));
    if (fmt.sampleType() == QAudioFormat::UnSignedInt)
       dump("UnSignedInt:");
    else if ( fmt.sampleType() == QAudioFormat::Float)
       dump("Float ");
    else if ( fmt.sampleType() == QAudioFormat::SignedInt)
       dump("SignedInt");
    else
       dump("Unknown");
    dump(QString("byteOrder:    ") + QString::number(fmt.byteOrder()));
}
