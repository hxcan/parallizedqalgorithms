#ifndef PASIGNALPROXY_H
#define PASIGNALPROXY_H

#include <QTimer> //QTimer
#include <QDate> //QDate

#include "PaPreCompile.h" //QStringList
#include "PaGlobal.h" //XYSHARED_EXPORT

/*!
 * \brief The XyBoat class 船。用来连接到灯塔。相当于客户端。
 */
class PARALLIZEDALGORITHM_SHARED_EXPORT PaSignalProxy : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief updateProgressValue 进度值发生变化，则更新进度值。
     * \param progressValue 新的进度值。
     */
    void updateProgressValue(int progressValue)
    {
        Q_UNUSED(progressValue); //不使用勒个参数。
    } //void updateProgressValue(int progressValue)

    virtual void processSubComparePickResult()=0; //子代搜索完成，则处理子代搜索结果。
    virtual void processComparePickResult()=0; // 处理比较分捡结果。


    void SetServerIp(QString LgnWdgtGetServerIp); //!<设置公网服务器的IP。

    /*!
     * \brief PaSignalProxy 构造函数。
     * \param parent 亲代对象。
     */
    PaSignalProxy(QObject *parent = 0):QObject(parent)
    {
        Q_UNUSED(parent); //不使用勒个参数。

    } //explicit PaSignalProxy(QObject *parent = 0)

signals:
    void finished(); //!<工作完成。
    void progressChanged(quint64 progressValue); //!<进度变更。
    void BroadcastDataContentReceived(QByteArray BrdcstDtCtt); //!<信号，接收到了BroadcastData内容。
    void MetadataContentReceived(QByteArray MtdtCtt); //!<信号，接收到了Metadata内容。
    void ShouldReadFromBeacon(); //!<应当读取数据。

private:
    QTimer HeartBitTimer; //!<用来发送心跳包的定时器。
    quint32 SocketBlockSize; //!<数据流的大小（不包括本变量）。
    quint16 Version; //!<版本号。
    QString ServerIp; //!<服务器的IP.
    QTimer ConnTimer; //!<用来启动连接过程的定时器。
};

#endif // WUDISKBOAT_H
