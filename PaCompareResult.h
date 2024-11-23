#ifndef PACOMPARERESULT_H
#define PACOMPARERESULT_H

#include "CompareResultRelation.h" //CompareResultRelation

using namespace ParallelizedAlgorithm;

template<typename T>
class CompareResult
{
private:
    int difference=0; //!<记录差值。
    T value;
    CompareResultRelation compareResultRelation;


public:
    T getValue() const
    {
    return value;
    }

    void setValue(const T &value)
    {
        this->value = value;
    }

    CompareResultRelation getCompareResultRelation() const
    {
    return compareResultRelation;
    }

    void setCompareResultRelation(const CompareResultRelation &value)
    {
    compareResultRelation = value;
    }

    int getDifference() const
    {
        return difference;
    }
    
    void setDifference(int value)
    {
        difference = value;
    }
    
};

#endif // DATATYPE_H

