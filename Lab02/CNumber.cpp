#include "CNumber.h"

#include <iostream>

CNumber::CNumber() {
    piDigits = 0;
    iLength = DEFAULT_LENGTH;
    bNegative = false;
    vAllocate(DEFAULT_LENGTH);
    piDigits[0] = 0;
}

CNumber::CNumber(const int val) {
    piDigits = NULL;
    iLength = 0;
    bNegative = false;
    vAssignFromInt(val);
}

CNumber::CNumber(const CNumber &rOther) {
    piDigits = 0;
    iLength = 0;
    bNegative = false;
    vCopyFrom(rOther);
}


CNumber::~CNumber() {
    if (piDigits != NULL)
        delete [] piDigits;
    piDigits = NULL;
}

/* The naive =operator,  creates a shallow copy,
 * meaning the new created object will also point to original construtor piDigits array
 * after destruction of one obj everything seems fine, but the second one wants to delete the same array
 * causing a crash
 */

CNumber &CNumber::operator=(const CNumber &rOther) {
    if (this != &rOther)
        vCopyFrom(rOther);
    return *this;
}

CNumber &CNumber::operator=(const int val) {
    vAssignFromInt(val);
    return *this;
}

std::string CNumber::sToStr() const {
    std::string s = "";
    if (bNegative)
        s += '-';

    for (int i = iLength - 1; i >= 0; i--) {
        s += char(piDigits[i] + '0');
    }
    return s;
}


CNumber CNumber::operator+(const CNumber &rOther) const {
    if (bNegative == rOther.bNegative) {
        CNumber r = vAddAbs(*this, rOther);
        r.bNegative = bNegative;
        r.vNormalizeZero();
        return r;
    }

    int cmp = vCompareMagnitude(*this, rOther);
    if (cmp == 0) return CNumber(0);

    if (cmp > 0) {
        CNumber r = vSubAbs(*this, rOther);
        r.bNegative = bNegative;
        r.vNormalizeZero();
        return r;
    } else {
        CNumber r = vSubAbs(rOther, *this);
        r.bNegative = rOther.bNegative;
        r.vNormalizeZero();
        return r;
    }
}

CNumber CNumber::operator-(const CNumber &rOther) const {
    CNumber negB = rOther;

    bool zero = true;
    for (int i = 0; i < negB.iLength; ++i)
        if (negB.piDigits[i] != 0) {
            zero = false;
            break;
        }
    if (!zero) negB.bNegative = !negB.bNegative;

    CNumber r = (*this) + negB;
    r.vNormalizeZero();
    return r;
}

CNumber CNumber::operator*(const CNumber &rOther) const {
    bool zeroL = (iLength == 1 && piDigits[0] == 0);
    bool zeroR = (rOther.iLength == 1 && rOther.piDigits[0] == 0);
    if (zeroL || zeroR) return CNumber(0);

    CNumber aAbs(*this);
    aAbs.bNegative = false;
    aAbs.vNormalizeZero();

    const int base = DEC_BASE;
    const int n = aAbs.iLength;
    const int m = rOther.iLength;

    int newLen = n + m;
    int *temp = new int[newLen];
    for (int k = 0; k < newLen; ++k) temp[k] = 0;

    for (int i = 0; i < n; ++i) {
        int carry = 0;
        for (int j = 0; j < m; ++j) {
            const int idx = i + j;
            long long sum = static_cast<long long>(temp[idx])
                            + static_cast<long long>(aAbs.piDigits[i]) * rOther.piDigits[j]
                            + carry;
            temp[idx] = static_cast<int>(sum % base);
            carry = static_cast<int>(sum / base);
        }

        temp[i + m] += carry;
    }

    int carry = 0;
    for (int k = 0; k < newLen; ++k) {
        int val = temp[k] + carry;
        if (val >= base) {
            temp[k] = val % base;
            carry = val / base;
        } else {
            temp[k] = val;
            carry = 0;
        }
    }
    if (carry > 0) {
        int *grown = new int[newLen + 1];
        for (int k = 0; k < newLen; ++k) grown[k] = temp[k];
        grown[newLen] = carry;
        if (temp != NULL)
            delete [] temp;
        temp = grown;
        newLen = newLen + 1;
    }


    CNumber prod(0);
    prod.vAllocate(newLen);
    for (int k = 0; k < newLen; ++k) prod.piDigits[k] = temp[k];
    prod.vTrimLeadingZeros();

    bool prodIsZero = (newLen == 1 && prod.piDigits[0] == 0);
    prod.bNegative = (!prodIsZero) && (bNegative != rOther.bNegative);
    prod.vNormalizeZero();

    if (temp != NULL)
        delete [] temp;
    return prod;
}

CNumber CNumber::operator/(const CNumber &rOther) const {
    // x/0 and 0/x
    if (rOther.iLength == 1 && rOther.piDigits[0] == 0)
        return CNumber(0);
    if (iLength == 1 && piDigits[0] == 0)
        return CNumber(0);

    CNumber aAbs(*this);
    aAbs.bNegative = false;
    aAbs.vNormalizeZero();
    CNumber bAbs(rOther);
    bAbs.bNegative = false;
    bAbs.vNormalizeZero();

    int cmp = vCompareMagnitude(aAbs, bAbs);
    // x/x=1
    if (cmp == 0) {
        CNumber one(1);
        one.bNegative = (bNegative != rOther.bNegative);
        one.vNormalizeZero();
        return one;
    }
    // <1
    if (cmp < 0) {
        return CNumber(0);
    }

    aAbs.vTrimLeadingZeros();
    int msA = aAbs.iLength - 1;
    CNumber rem(0);

    int nQuotientDigits = msA + 1;
    int *qArray = new int[nQuotientDigits];
    for (int i = 0; i < nQuotientDigits; i++) qArray[i] = 0;
    int qPos = 0;

    for (int i = msA; i >= 0; i--) {
        int newLen = rem.iLength + 1;
        int *grown = new int[newLen];
        grown[0] = aAbs.piDigits[i];
        for (int j = 0; j < rem.iLength; j++)
            grown[j + 1] = rem.piDigits[j];
        rem.vDeallocate();
        rem.piDigits = grown;
        rem.iLength = newLen;
        rem.vTrimLeadingZeros();


        int best = 0;
        for (int d = 0; d < DEC_BASE; d++) {
            CNumber dNum(d);
            CNumber prod = bAbs * dNum;
            int cmp = vCompareMagnitude(prod, rem);
            if (cmp <= 0) {
                best = d;
            }
        }

        qArray[qPos] = best;
        qPos++;

        if (best != 0) {
            CNumber bestNum(best);
            CNumber sub = bAbs * bestNum;
            rem = vSubAbs(rem, sub);
            rem.vTrimLeadingZeros();
        }
    }

    CNumber quot(0);
    quot.vAllocate(qPos);
    for (int t = 0; t < qPos; ++t) {
        quot.piDigits[t] = qArray[qPos - 1 - t];
    }
    quot.vTrimLeadingZeros();

    bool quotIsZero = (quot.iLength == 1 && quot.piDigits[0] == 0);
    quot.bNegative = (!quotIsZero) && (bNegative != rOther.bNegative);
    quot.vNormalizeZero();

    if (qArray != NULL)
        delete [] qArray;

    return quot;
}


void CNumber::vAllocate(int newSize) {
    if (newSize < 1)
        newSize = DEFAULT_LENGTH;

    vDeallocate();

    piDigits = new int[newSize];
    iLength = newSize;
    for (int i = 0; i < iLength; ++i)
        piDigits[i] = 0;
}

void CNumber::vDeallocate() {
    if (piDigits != NULL)
        delete [] piDigits;
    piDigits = 0;
    iLength = 0;
}

void CNumber::vAssignFromInt(int val) {
    if (val == 0) {
        vAllocate(1);
        piDigits[0] = 0;
        bNegative = false;
        return;
    }
    if (val < 0) {
        bNegative = true;
        val = -val; //val = abs(val) from here
    }


    int len = 0;
    for (int t = val; t > 0; t /= DEC_BASE) {
        len++;
    }

    vAllocate(len);
    int t = val;
    for (int i = 0; i < len; i++) {
        piDigits[i] = t % DEC_BASE;
        t /= DEC_BASE;
    }

    vTrimLeadingZeros();
}

void CNumber::vCopyFrom(const CNumber &rOther) {
    bNegative = rOther.bNegative;

    int srcLen = (rOther.iLength > 0) ? rOther.iLength : DEFAULT_LENGTH;

    delete [] piDigits;
    piDigits = 0;
    piDigits = new int[srcLen];
    iLength = srcLen;

    if (rOther.piDigits != 0) {
        for (int i = 0; i < srcLen; ++i)
            piDigits[i] = (i < rOther.iLength) ? rOther.piDigits[i] : 0;
    } else {
        for (int i = 0; i < srcLen; ++i) piDigits[i] = 0;
    }

    vNormalizeZero();
}

int CNumber::vCompareMagnitude(const CNumber &A, const CNumber &B) {
    //ms = most significant
    int msA = (A.iLength > 0) ? A.iLength - 1 : 0;
    while (msA > 0 && A.piDigits[msA] == 0) --msA;

    int msB = (B.iLength > 0) ? B.iLength - 1 : 0;
    while (msB > 0 && B.piDigits[msB] == 0) --msB;

    if (msA != msB) return (msA < msB) ? -1 : 1;

    for (int i = msA; i >= 0; --i) {
        if (A.piDigits[i] < B.piDigits[i]) return -1;
        if (A.piDigits[i] > B.piDigits[i]) return 1;
    }
    return 0;
}

CNumber CNumber::vSubAbs(const CNumber &A, const CNumber &B) {
    CNumber result;
    result.vAllocate(A.iLength);

    int borrow = 0;
    for (int i = 0; i < A.iLength; i++) {
        int da = A.piDigits[i] - borrow;
        int db = (i < B.iLength) ? B.piDigits[i] : 0;

        if (da < db) {
            da += DEC_BASE;
            borrow = 1;
        } else borrow = 0;

        result.piDigits[i] = da - db;
    }
    result.bNegative = false;
    result.vTrimLeadingZeros();
    return result;
}

CNumber CNumber::vAddAbs(const CNumber &A, const CNumber &B) {
    int resultLen = std::max(A.iLength, B.iLength) + 1;
    CNumber result;
    result.vAllocate(resultLen);

    int carry = 0;
    for (int i = 0; i < resultLen; ++i) {
        int da = (i < A.iLength) ? A.piDigits[i] : 0;
        int db = (i < B.iLength) ? B.piDigits[i] : 0;

        int s = da + db + carry;
        result.piDigits[i] = s % DEC_BASE;
        carry = s / DEC_BASE;
    }
    result.bNegative = false;
    result.vTrimLeadingZeros();
    return result;
}


void CNumber::vNormalizeZero() {
    bool allZero = true;
    for (int i = 0; i < iLength; ++i)
        if (piDigits[i] != 0) {
            allZero = false;
            break;
        }
    if (allZero) bNegative = false;
}

void CNumber::vTrimLeadingZeros() {
    int ms = iLength - 1;
    while (ms > 0 && piDigits[ms] == 0)
        ms--;

    int newLen = ms + 1;
    if (newLen < 1) newLen = 1;


    if (newLen != iLength) {
        int *pNew = new int[newLen];
        for (int i = 0; i < newLen; ++i)
            pNew[i] = piDigits[i];

        if (piDigits != NULL)
            delete [] piDigits;
        piDigits = pNew;
        iLength = newLen;
    }

    vNormalizeZero();
}
