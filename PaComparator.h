#ifndef PACOMPARATOR_H
#define PACOMPARATOR_H

#include "PaPreCompile.h" //QNetworkReply

#include "PaGlobal.h" //XYSHARED_EXPORT
#include "CompareResultRelation.h" //CompareResultRelation

using namespace ParallelizedAlgorithm;

/*!
 * \brief The BroadcastDataParser class 用来分析服务器广播消息文件的类。
 */
template<typename T>
class PARALLIZEDALGORITHM_SHARED_EXPORT PaComparator
{
public:
    /*!
     * \brief getDifference 获取差值。
     * \param dir2Scan 当前元素。
     * \param compareBase 基准元素。
     * \return 当前元素减去基准元素的差值。
     */
    virtual int getDifference(T dir2Scan,T compareBase)=0;
    
    /*!
     * \brief PaComparator::paCompare Compare
     * \param FlIfoUrl2St 要设置的URL。
     */
    virtual CompareResultRelation paCompare(T currentElement, T baseElement)=0;

private:
    quint16 Version; //!<版本号。
    QUrl FlIfoUrl; //!<完整信息的URL。
    QString Ttl; //!<消息的标题。
};

#endif // BROADCASTDATAPARSER_H
