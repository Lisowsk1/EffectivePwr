

#ifndef TABLE_ALLOC_H
#define TABLE_ALLOC_H

#include <stddef.h>

void v_alloc_table_fill_34(int iSize);

bool b_alloc_table_2_dim(int **&ppiTable, int iSizeX, int iSizeY);

bool b_alloc_table_2_dimR(int ***ppiTable, int iSizeX, int iSizeY);

bool b_dealloc_table_2_dim(int **&ppiTable, int iSizeX, int iSizeY);

bool b_dealloc_table_2_dim(int ***ppiTable, int iSizeX, int iSizeY);

bool b_make_1d_filled(int **ppTable, size_t n, int value);
bool b_free_2d(int **piTable, int iSizeX, int iSizeY);


#endif