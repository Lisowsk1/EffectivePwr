#ifndef CTABLE_H
#define CTABLE_H
#include <string>




class CTable {

public:
    CTable();

    CTable(std::string &sName, int iTableLen);

    CTable(std::string sName, int tableLen);

    CTable(const CTable &pcOther);

    ~CTable();

    CTable *pcClone();

    CTable *pcClone() const;

    void vSetName(const std::string &name);

    bool bSetNewSize(int tableLen);

private:
    static const std::string DEFAULT_NAME; //cannot be initialized in class
    static const int DEFAULT_LENGTH = 10;

    std::string sName;
    int iTableLen;
    int *piTable;

};


#endif //GRIND1_CTABLE_H
