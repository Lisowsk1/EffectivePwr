#include <iostream>

#include "table_alloc.h"

using namespace std;

//ALLOCATING USING REFERENCE TO THE DOUBLE POINTER
bool b_alloc_table_2_dim(int **&piTable, int iSizeX, int iSizeY) {
    if (iSizeX <= 0 || iSizeY <= 0)
        return false;


    piTable = new int *[iSizeX]; //allocating space
    for (int i = 0; i < iSizeX; i++) {
        piTable[i] = new int[iSizeY];
    }


    /*Test loop filling array with 0 and printing
    for (int i = 0; i < iSizeX; i++) {
        for (int j = 0; j < iSizeY; j++) {
            piTable[i][j] = 0;
        }
    }

    for (int i = 0; i < iSizeX; i++) {
        for (int j = 0; j < iSizeY; j++) {
            cout << piTable[i][j] << " ";
        }
        cout << endl;
    }


    */

    return true;
}


//ALLOCATING WITHOUT USING REFERENCE, USING TRIPLE POINTER AND DEREFERENCING

bool b_alloc_table_2_dim(int ***piTable, int iSizeX, int iSizeY) {
    if (iSizeX <= 0 || iSizeY <= 0)
        return false;


    *piTable = new int *[iSizeX]; //allocating space
    for (int i = 0; i < iSizeX; i++) {
        (*piTable)[i] = new int[iSizeY];
    }


    /* Test loop filling array with 0 and printing
    for (int i = 0; i < iSizeX; i++) {
        for (int j = 0; j < iSizeY; j++) {
            (*piTable)[i][j] = 0;
        }
    }

    for (int i = 0; i < iSizeX; i++) {
        for (int j = 0; j < iSizeY; j++) {
            cout << (*piTable)[i][j] << " ";
        }
        cout << endl;
    }

*/

    return true;
}


//DEALLOCATING USING REFERENCE TO THE DOUBLE POINTER
bool b_dealloc_table_2_dim(int **&piTable, int iSizeX, int iSizeY) {
    //iSizeY is not used, can be removed, but its in specification
    if (piTable == NULL || iSizeX <= 0 || iSizeY <= 0)
        return false;
    for (int i = 0; i < iSizeX; i++) {
        delete[] piTable[i];
    }
    delete[] piTable;
    piTable = NULL;
    return true;
}

//DEALLOCATING WITHOUT USING REFERENCE, USING TRIPLE POINTER AND DEREFERENCING
bool b_dealloc_table_2_dim(int ***piTable, int iSizeX, int iSizeY) {
    //iSizeY is not used, can be removed, but its in specification
    if (piTable == NULL || *piTable == NULL || iSizeX <= 0 || iSizeY <= 0)
        return false;

    for (int i = 0; i < iSizeX; i++) {
        delete[] (*piTable)[i];
    }
    delete[] *piTable;
    *piTable = NULL;
    return true;
}


int main() {
    int **pi_table = NULL;
    int iSizeX = 2;
    int iSizeY = 2;

    //With reference
    //b_alloc_table_2_dim(pi_table, iSizeX, iSizeY);
    //b_dealloc_table_2_dim(pi_table,iSizeX,iSizeY);

    //Without reference
    b_alloc_table_2_dim(&pi_table, iSizeX, iSizeY);
    b_dealloc_table_2_dim(&pi_table, iSizeX, iSizeY);

    return 0;
}
