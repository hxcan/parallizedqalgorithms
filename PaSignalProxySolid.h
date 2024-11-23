#ifndef PASIGNALPROXYSOLID_H
#define PASIGNALPROXYSOLID_H

#include <QTimer> //QTimer
#include <QDate> //QDate

#include "PaPreCompile.h" //QStringList
#include "PaGlobal.h" //XYSHARED_EXPORT
#include "RangeSortSearch.h" //RangeSortSearch

template <typename T>
class RangeSortSearch;

/*!
 * \brief The XyBoat class 船。用来连接到灯塔。相当于客户端。
 */
template<typename T>
class PARALLIZEDALGORITHM_SHARED_EXPORT PaSignalProxySolid : public PaSignalProxy
{
public:
    /*!
     * \brief emitProgress 发射信号，进度。
     * \param alreadyFoundListListsize 已经完成的数量。
     */
    void emitProgress(quint64 alreadyFoundListListsize )
    {
        emit progressChanged(alreadyFoundListListsize);
    } //void emitProgress(quint64 alreadyFoundListListsize )

    void emitFinished()
    {
        emit finished();
    } //void emitFinished()

    /*!
     * \brief processSubComparePickResult 子代搜索完成，则处理子代搜索结果。
     */
    void processSubComparePickResult()
    {
        proxyee->processSubComparePickResult(); //处理子代搜索结果。
    } //void processSubComparePickResult()


    /*!
     * \brief processComparePickResult 处理比较分捡结果。
     */
    void processComparePickResult()
    {
        proxyee->processComparePickResult(); //处理比较分捡结果。
    } //void processComparePickResult()


    void SetServerIp(QString LgnWdgtGetServerIp); //!<设置公网服务器的IP。

    RangeSortSearch<T> * getProxyee() const
    {
    return proxyee;
    }

    void setProxyee(RangeSortSearch<T> *value)
    {
    proxyee = value;
    }




    void DefaultsContentReceived(QByteArray DftsCtt); //!<信号，接收到了Defaults文件的内容。
    void BroadcastDataContentReceived(QByteArray BrdcstDtCtt); //!<信号，接收到了BroadcastData内容。
    void MetadataContentReceived(QByteArray MtdtCtt); //!<信号，接收到了Metadata内容。
    void ShouldReadFromBeacon(); //!<应当读取数据。

public slots:
    void StartConnect(); //!<启动连接过程。


private:
    RangeSortSearch<T> * proxyee; //!<被代理对象。

    QTimer HeartBitTimer; //!<用来发送心跳包的定时器。
    quint32 SocketBlockSize; //!<数据流的大小（不包括本变量）。
    quint16 Version; //!<版本号。
    QString ServerIp; //!<服务器的IP.
    QTimer ConnTimer; //!<用来启动连接过程的定时器。

private slots:
    void SendMetadataRequest(); //!<连接成功之后，发送Metadata请求。
    void SendHeartBit(); //!<定时发送心跳包。
    void ReadFromBeacon(); //!<有数据到达，则读取数据。
};

#endif // WUDISKBOAT_H

