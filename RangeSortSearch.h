#ifndef RANGESORTSEARCH_H
#define RANGESORTSEARCH_H

#include "PaPreCompile.h" //QDate

#include "PaGlobal.h" //XYSHARED_EXPORT
#include "PaComparator.h" //PaComparator

#include "PaMapReduceFunctions.h"
#include "CompareWithComparatorMap.h" //CompareWithComparatorMap
#include "PickComparedDataReduce.h" //PickComparedDataReduce
#include "PaSignalProxy.h" //PaSignalProxy
#include "PaSignalProxySolid.h" //PaSignalProxySolid

/*!
 * \brief The XyBeacon class 灯塔对象。也就是服务器。
 */
template<typename T>
class PARALLIZEDALGORITHM_SHARED_EXPORT RangeSortSearch
{
public:
    /*!
     * \brief getResult 返回最终搜索结果。
     * \return 最终搜索结果。
     */
    QList<T> getResult()
    {
        return alreadyFoundListList;
    } //QList<T> getResult()

    /*!
     * \brief processSubComparePickResult 子代搜索完成，则处理子代搜索结果。
     */
    void processSubComparePickResult()
    {
        QList<T> lessThanList=subRangeSortSearch->getResult(); //获取小于标准值的值列表。

        alreadyFoundListList .append( lessThanList); //已经找到的列表加入到已有元素列表中。
        signalProxy->emitProgress(alreadyFoundListList.size ()); //发射信号，进度。

        signalProxy->emitFinished(); //完成。
    } //void processSubComparePickResult()

    /*!
     * \brief processComparePickResult 处理比较分捡结果。
     */
    void processComparePickResult()
    {
        QFuture<PaComparePickResult<T> > subDirFutr=subDirsFutureWatcher.future (); //获取未来对象。

        PaComparePickResult<T> subDirs=subDirFutr.result(); //获取扫描到的结果。

        QList<T> lessThanList=subDirs.getLessThanValues(); //获取小于标准值的值列表。
        QList<T> equalOrGreaterThanList=subDirs.getEqualOrGreaterValues(); //获取大于或等于标准值的值列表。
        
        if (subDirs.getAllEqual()) //大于等于一侧全部都是等于号。
        {
            if (lessThanList.size()<targetAmount) //个数不够。
            {
                for(int elementCounter=0;elementCounter<(targetAmount-lessThanList.size());elementCounter++)
                {
                    lessThanList.append(equalOrGreaterThanList.takeFirst());
                } //for(int elementCounter=0;elementCounter<(targetAmount-lessThanList.size());elementCounter++)
            } //if (lessThanList.size()<targetAmount) //个数不够。
        } //if (subDirs.getAllEqual()) //大于等于一侧全部都是等于号。

        if (lessThanList.size()==targetAmount) //正好是这么多个。
        {
            alreadyFoundListList .append( lessThanList); //已经找到的列表加入到已有元素列表中。

            signalProxy->emitProgress(alreadyFoundListList.size ()); //发射信号，进度。

            signalProxy->emitFinished(); //完成。
        } //if (lessThanList.size()==targetAmount) //正好是这么多个。
        else if (lessThanList.size()<targetAmount) //个数不够。
        {
            alreadyFoundListList .append( lessThanList); //已经找到的列表加入到已有元素列表中。

            signalProxy->emitProgress(alreadyFoundListList.size ()); //发射信号，进度。

            bool shouldReBalance=false; //是否应当重新平衡。
            bool shouldFindIdealElement=false; //应当找出理想元素。
            bool shouldUseGivenBaseElement=false; //应当使用指定的基准元素。
            T idealBaseElement=T(); //理想元素。
            int idealDifference=0; //理想差值。
            
            if (lessThanList.size()==0) //二分不平衡，全部元素都二分到大于等于集合中去了。
            {
                if (shouldPassIdealElementToNextRound) //应当向下一轮传递理想元素基准。
                {
                    shouldUseGivenBaseElement=true; //应当使用指定的基准元素。
                    idealBaseElement=subDirs.getIdealElement(); //获取理想基准元素。
                } //if (shouldPassIdealElementToNextRound) //应当向下一轮传递理想元素基准。
                else if (shouldRequireNextRoundFindIdealElement) //应当要求下一轮找出理想元素值。
                {
                    shouldFindIdealElement=true; //应当找出理想元素。
                    idealDifference=subDirs.getIdealDifference(); //获取理想差值。
                    
                    if (idealDifference<=0) //过于平均，人为修正。
                    {
                        idealDifference=1;
                    } //if (idealDifference==0) //过于平均，人为修正。
                } //if (shouldRequireNextRoundFindIdealElement) //应当要求下一轮找出理想元素值。
                else //尚未要求下一轮找出理想元素值。
                {
                    shouldReBalance=true; //应当做额外的平衡工作。
                } //else //尚未要求下一轮找出理想元素值。
            } //if (lessThanList.size()==0) //二分不平衡，全部元素都二分到大于等于集合中去了。
            
            startSubRangeSortSearch(alreadyFoundListList.size(),targetAmount,equalOrGreaterThanList,shouldReBalance, shouldFindIdealElement,shouldUseGivenBaseElement, idealBaseElement,idealDifference); //启动子代范围搜索。
        } //else if (lessThanList.size()<targetAmount) //个数不够。
        else //个数多了。
        {
            startSubRangeSortSearch(lessThanList,targetAmount); //启动子代范围搜索。
        } //else //个数多了。
    } //void processComparePickResult()

    /*!
     * \brief startSubRangeSortSearch 启动子代范围搜索。从lessThanList中搜索出targetAmount个元素。
     * \param lessThanList 要从中搜索的元素列表。
     * \param targetAmount 目标元素个数。
     */
    void startSubRangeSortSearch(QList<T> lessThanList,int targetAmount)
    {
        RangeSortSearch<T> * rangeSortSearch=new RangeSortSearch<T>();

        subRangeSortSearch=rangeSortSearch;

        QObject::connect(rangeSortSearch->getSignalProxy(),&PaSignalProxy::finished,signalProxy,&PaSignalProxy::processSubComparePickResult); //子代搜索完成，则处理子代搜索结果。

        rangeSortSearch->startSearch(lessThanList,comparator,(targetAmount));

    } //void startSubRangeSortSearch(QList<T> lessThanList,int targetAmount)

    /*!
     * \brief startSubRangeSortSearch 启动子代范围搜索。从equalOrGreaterThanList中再找出若干个元素，补充到已有的lessThanListsize个元素中，使得总元素个数刚好是targetAmount。
     * \param lessThanListsize 已有元素个数。
     * \param targetAmount 目标元素个数。
     * \param equalOrGreaterThanList 还要从中寻找元素的列表。
     */
    void startSubRangeSortSearch(int lessThanListsize,int targetAmount, QList<T> equalOrGreaterThanList, bool shouldReBalance=false, bool shouldFindIdealElement=false, bool shouldUseGivenBaseElement=false, T idealBaseElement=T(), int idealDifference=0)
    {
        RangeSortSearch<T> * rangeSortSearch=new RangeSortSearch<T>();

        subRangeSortSearch=rangeSortSearch;

        QObject::connect(rangeSortSearch->getSignalProxy(),&PaSignalProxy::finished,signalProxy,&PaSignalProxy::processSubComparePickResult); //子代搜索完成，则处理子代搜索结果。

        rangeSortSearch->startSearch(equalOrGreaterThanList,comparator,(targetAmount-lessThanListsize), shouldReBalance, shouldFindIdealElement,shouldUseGivenBaseElement,idealBaseElement, idealDifference); //开始搜索。
    } //void startSubRangeSortSearch(int lessThanListsize,int targetAmount, QList<T> equalOrGreaterThanList)

    /*!
     * \brief connectSignals 连接信号。
     */
    void connectSignals()
    {
        QObject::connect(&subDirsFutureWatcher,&QFutureWatcher<PaComparePickResult<T> >::finished,signalProxy,&PaSignalProxySolid<T>::processComparePickResult); //处理完毕，则处理处理结果。
        QObject::connect (&subDirsFutureWatcher,&QFutureWatcher<PaComparePickResult<T> >::progressValueChanged,signalProxy,&PaSignalProxy::updateProgressValue); //进度值发生变化，则更新进度值。

    } //void connectSignals()

    /*!
     * \brief RangeSortSearch::RangeSortSearch 默认构造函数。
     */
    RangeSortSearch()
    {
        signalProxy=new PaSignalProxySolid<T>(); //创建信号代理。
        signalProxy->setProxyee(this); //设置被代理对象。

        connectSignals(); //连接信号。
    } //RangeSortSearch::RangeSortSearch()

    /*!
     * 开始排序并寻找指定个数的元素。
     */
    void startSearch(QList<T> FilesQueue,PaComparator<T> *fileTimeComparator,int targetAmount, bool shouldReBalance=false, bool shouldFindIdealElement=false, bool shouldUseGivenBaseElement=false, T idealBaseElement=T(), int idealDifference=0)
    {
        this->targetAmount=targetAmount; //记录目标个数。
        comparator=fileTimeComparator; //记录比较器。

        CompareWithComparatorMap<T> mapFunction;
        PickComparedDataReduce<T> reduceFunction;
        
        if (shouldReBalance) //应当重新平衡。
        {
            mapFunction.setRequireDifference(true); //比较时要求给出差值。
            reduceFunction.setCalculateAverageDifference(true); //归并时计算出差值的平均值。
            
            shouldRequireNextRoundFindIdealElement=true; //应当要求下一轮找出最佳元素。
        } //if (shouldReBalance) //应当重新平衡。
        
        if (shouldFindIdealElement) //应当找到理想元素。
        {
            mapFunction.setRequireDifference(true); //比较时要求给出差值。
            reduceFunction.setFindIdealElement(true); //归并时要找出理想值。
            reduceFunction.setIdealDifference(idealDifference); //归并时的理想差值。
            
            shouldPassIdealElementToNextRound=true; //应当向下一轮传递最佳元素基准。
        } //if (shouldFindIdealElement) //应当找到理想元素。

        T firstValue; //第一个值。
        
        if (FilesQueue.length()) //队列有长度。
        {
            firstValue= FilesQueue[0]; //获取第一个值。
        } //if (FilesQueue.length()) //队列有长度。
        
        if (shouldUseGivenBaseElement) //应当使用指定的基准元素。
        {
            firstValue=idealBaseElement; //使用指定的基准元素。
        } //if (shouldUseGivenBaseElement) //应当使用指定的基准元素。

        mapFunction.setPaComparator(fileTimeComparator); //设置比较器．
        mapFunction.setCompareBase(firstValue); //设置比较基准。

        QFuture<PaComparePickResult<T> > subDirs=QtConcurrent::mappedReduced<PaComparePickResult<T> >(FilesQueue,mapFunction,reduceFunction); //启动一个并行映射归并过程。
        subDirsFutureWatcher.setFuture(subDirs); //设置未来对象。
    } //QList<T> RangeSortSearch<T>::startSearch(QList<T> FilesQueue,PaComparator<T> fileTimeComparator,int targetAmount)

    PaSignalProxySolid<T> *getSignalProxy() const
    {
    return signalProxy;
    }

    void setSignalProxy(PaSignalProxySolid<T> *value)
    {
    signalProxy = value;
    }


private:
    bool shouldRequireNextRoundFindIdealElement=false; //!<是否应当要求下一轮找出理想元素值。在重新平衡过程中使用的标记位。
    bool shouldPassIdealElementToNextRound=false; //!<是否应当向下一轮传递理想元素基准。在重新平衡过程中使用的标记位。
    QFutureWatcher<PaComparePickResult<T> > subDirsFutureWatcher; //!<用于监听列出子目录过程的未来观察器。
    PaSignalProxySolid<T> * signalProxy; //!<信号代理。
    int targetAmount; //!<目标个数。
    QList<T> alreadyFoundListList; //!<已经找到的那些元素组成的列表。一般情况下其长度小于目标元素个数。
    PaComparator<T> * comparator; //!<比较器。
    RangeSortSearch<T> * subRangeSortSearch; //!<用于递归进行子代搜索的对象。

    QString ServerIp; //!<DNS服务器ＩＰ地址。
};

#endif // WUDISKBEACON_H

