#ifndef PICKCOMPAREDDATAREDUCE_H
#define PICKCOMPAREDDATAREDUCE_H

#include "PaPreCompile.h" //QList

#include "PaCompareResult.h" //CompareResult
#include "PaComparator.h" //PaComparator
#include "PaComparePickResult.h" //PaComparePickResult

template<typename T>
class PickComparedDataReduce
{
private:
    int existingIdealDifference=-1; //!<已有的理想差值。
    int idealDifference=0; //!<归并时的理想差值。
    bool findIdealElement=false; //!<是否要在归并时要找出理想值。
    bool calculateAverageDifference=false; //!<是否要在归并时计算出差值的平均值。
    static PaComparator<T> * paComparator; //!<比较器。


public:
    typedef void result_type;

    /*!
     * \brief pickComparedDataReduce 将比较结果归并到总的结果列表中。
     * \param result 最后归并出来的结果。
     * \param partListedSubDirs 要归并的中间结果对象。
     */
    void operator()(PaComparePickResult<T> &result, const CompareResult<T>  & partListedSubDirs)
    {
        CompareResultRelation compareResultRelation=partListedSubDirs.getCompareResultRelation();

        T value=partListedSubDirs.getValue();

        if (compareResultRelation==LessThan)
        {
            result.appendLessThanValue(value);
        } //if (compareResultRelation==LessThan)
        else
        {
            result.appendEqualOrGreaterThanValue(value);

            if (compareResultRelation==GreaterThan) //有大于的。
            {
                result.setAllEqual(false); //不是全部都是等于号。
            } //if (compareResultRelation==GreaterThan) //有大于的。
        } //else

        
        if (calculateAverageDifference) //要计算差值的平均值。
        {
            int difference=partListedSubDirs.getDifference(); //获取差值。
            
            result.addDifferenceAndCalculateAvarage(difference); //累加差值并且计算平均值。
        } //if (calculateAverageDifference) //要计算差值的平均值。
        
        if (findIdealElement) //要寻找理想元素基准。
        {
            int difference=partListedSubDirs.getDifference(); //获取差值。

            if (difference>=idealDifference) //大于等于理想差值。
            {
                if (existingIdealDifference==-1) //已有理想差值尚未初始化。
                {
                    existingIdealDifference=difference+1; //初始化为较大的数。
                } //if (existingIdealDifference==-1) //已有理想差值尚未初始化。
                
                if (difference<existingIdealDifference) //小于已有的理想差值。则要替换。
                {
                    existingIdealDifference=difference; //记录新的理想差值。
                    
                    result.setIdealElement(value); //设置理想元素。
                } //if (difference<existingIdealDifference) //小于已有的理想差值。则要替换。
            } //if (difference>=idealDifference) //大于等于理想差值。
        } //if (findIdealElement) //要寻找理想元素基准。
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

    bool getCalculateAverageDifference() const
    {
        return calculateAverageDifference;
    }
    
    void setCalculateAverageDifference(bool value)
    {
        calculateAverageDifference = value;
    }
    
    bool getFindIdealElement() const
    {
        return findIdealElement;
    }
    
    void setFindIdealElement(bool value)
    {
        findIdealElement = value;
    }
    
    int getIdealDifference() const
    {
    return idealDifference;
    }
    
    void setIdealDifference(int value)
    {
    idealDifference = value;
    }
    
}; //class PaMapReduceFunctions


#endif // MAPREDUCEFUNCTIONS_H





