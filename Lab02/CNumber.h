#ifndef CNumber_H
#define CNumber_H

#include <string>

#define DEFAULT_LENGTH 1
#define DEC_BASE     10

class CNumber {
public:
    CNumber();

    CNumber(int val);

    CNumber(const CNumber &pcOther);

    ~CNumber();

    CNumber &operator=(const CNumber &pcOther);

    CNumber &operator=(int val);

    CNumber operator+(const CNumber &pcOther) const;

    CNumber operator-(const CNumber &pcOther) const;

    CNumber operator*(const CNumber &rOther) const;

    CNumber operator/(const CNumber &rOther) const;

    std::string sToStr() const;

private:
    int *piDigits;
    int iLength;
    bool bNegative;


    void vAllocate(int newSize);

    void vDeallocate();

    static int vCompareMagnitude(const CNumber &A, const CNumber &B);

    void vTrimLeadingZeros();

    void vAssignFromInt(int val);

    void vCopyFrom(const CNumber &rOther);

    void vNormalizeZero();

    static CNumber vAddAbs(const CNumber &A, const CNumber &B);

    static CNumber vSubAbs(const CNumber &A, const CNumber &B);
};

#endif
