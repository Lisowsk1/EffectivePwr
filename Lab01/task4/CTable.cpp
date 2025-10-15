//
// Created by Lisu on 15.10.2025.
//

#include "CTable.h"
#include <iostream>
#include <string>

const std::string CTable::DEFAULT_NAME("default");


CTable::CTable() : piTable(0), //initializer list
                   iTableLen(0) { //constructor body
    vSetName(DEFAULT_NAME);
    bSetNewSize(DEFAULT_LENGTH);
    std::cout<<"nonp: "<<sName<<std::endl;
    piTable = new int[DEFAULT_LENGTH];
}

CTable::CTable(std::string& name, int iTableLen) : sName(name),
piTable(0),
iTableLen(iTableLen > 0 ? iTableLen : DEFAULT_LENGTH){
std::cout<<"parameter: "<<sName<<std::endl;
    piTable = new int[iTableLen];
}

CTable::CTable(const CTable &pcOther) : sName(pcOther.sName+"_copy"),
piTable(0),
iTableLen(pcOther.iTableLen) {
    std::cout<<"copy: "<<sName<<std::endl;
    piTable = new int[iTableLen];
    std::copy(pcOther.piTable, pcOther.piTable+iTableLen, piTable);
}

CTable::~CTable(){
    delete[] piTable;
    std::cout<<"deleting: "<<sName<<std::endl;
}

CTable* CTable::pcClone() {
    return new CTable(*this);
}

void CTable::vSetName(const std::string& name) {
    this->sName = name;
}

bool CTable::bSetNewSize(int iTableLen) {
    this->iTableLen = iTableLen;
}


void v_mod_tab(CTable* pcTab, int iNewSize) {
    if (pcTab) pcTab->bSetNewSize(iNewSize);
}

void v_mod_tab(CTable cTab, int iNewSize) {
    cTab.bSetNewSize(iNewSize);
}



