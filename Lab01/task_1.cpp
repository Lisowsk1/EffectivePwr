#include <iostream>

#include "table_alloc.h"

using namespace std;


int const FILL_VALUE = 34;


void v_alloc_table_fill_34(int iSize) {

    if (iSize <= 0 || iSize > INT_MAX) {
        cout << "Invalid size!" << endl;
    } else {
        int* p_iArray = new int[iSize];

        for (int i = 0; i < iSize; i++) {
            p_iArray[i] = FILL_VALUE;
        }

        for (int i = 0; i < iSize; i++) {
            cout << p_iArray[i] << endl;
        }

        delete [] p_iArray;
        p_iArray = NULL;
    }
}

int main() {

    int iSize = 3;

    v_alloc_table_fill_34(iSize);
    v_alloc_table_fill_34(-5);
    v_alloc_table_fill_34(9999999999999999999999999999999999999);

    return 0;
}
