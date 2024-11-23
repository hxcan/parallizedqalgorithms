#ifndef COMPAREWITHCOMPARATORMAP_H
#define COMPAREWITHCOMPARATORMAP_H

#include "PaPreCompile.h" //QList

#include "PaCompareResult.h" //CompareResult
#include "PaComparator.h" //PaComparator

template<typename T>
class CompareWithComparatorMap
{
private:
    bool requireDifference=false; //!<比较时要求给出差值。
    PaComparator<T> * paComparator; //!<比较器。


public:
    typedef CompareResult<T> result_type;

    /*!
     * 对单个元素进行比较，并返回比较结果。
     */
    CompareResult<T> operator()(const T dir2Scan)
    {
        CompareResult<T> result;

        result.setValue(dir2Scan); //设置结果中具体的值。

        CompareResultRelation compareResultRelation= paComparator->paCompare(dir2Scan,compareBase); //进行比较。
        
        result.setCompareResultRelation(compareResultRelation);
        
        if (requireDifference) //要计算差值。
        {
            int difference=paComparator->getDifference(dir2Scan,compareBase); //获取差值。

            result.setDifference(difference); //记录差值。
        } //if (requireDifference) //要计算差值。


        return result;
    }


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

    bool getRequireDifference() const
    {
        return requireDifference;
    }
    
    void setRequireDifference(bool value)
    {
        requireDifference = value;
    }
    
}; //class PaMapReduceFunctions


#endif // MAPREDUCEFUNCTIONS_H



