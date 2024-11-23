#ifndef PAMAPREDUCEFUNCTIONS_H
#define PAMAPREDUCEFUNCTIONS_H

#include "PaPreCompile.h" //QList

#include "PaCompareResult.h" //CompareResult
#include "PaComparator.h" //PaComparator

template<typename T>
class PaMapReduceFunctions
{
    static PaComparator<T> * paComparator; //!<比较器。


public:
    /*!
     * 对单个元素进行比较，并返回比较结果。
     */
    CompareResult<T> compareWithComparatorMap(const T dir2Scan)
    {
        CompareResult<T> result;

        result.setValue(dir2Scan); //设置结果中具体的值。

        CompareResultRelation compareResultRelation= paComparator->paCompare(dir2Scan,compareBase); //进行比较。

        result.setCompareResultRelation(compareResultRelation);

        return result;
    }


    /*!
     * \brief pickComparedDataReduce 将比较结果归并到总的结果列表中。
     * \param result 最后归并出来的结果。
     * \param partListedSubDirs 要归并的中间结果对象。
     */
    T pickComparedDataReduce(QList<QList<T> > &result, CompareResult<T> const & partListedSubDirs)
    {
        T pseudoResult;
        CompareResultRelation compareResultRelation=partListedSubDirs.getCompareResultRelation();

        T value=partListedSubDirs.getValue();

        if (compareResultRelation==LessThan)
        {
            result.appendLessThanValue(value);
        } //if (compareResultRelation==LessThan)
        else
        {
            result.appendEqualOrGreaterThanValue(value);
        } //else

        return pseudoResult;
    } //static void pickComparedDataReduce(QList<QList<T>> &result,const CompareResult<T> & partListedSubDirs)

    T compareBase; //!<比较的基准元素。

    PaComparator<T> * getPaComparator() const
    {
        return paComparator;
    }

    void setPaComparator(PaComparator<T> *value)
    {
        paComparator = value;
    }

    T getCompareBase() const
    {
    return compareBase;
    }

    void setCompareBase(const T &value)
    {
    compareBase = value;
    }

}; //class PaMapReduceFunctions


#endif // MAPREDUCEFUNCTIONS_H


