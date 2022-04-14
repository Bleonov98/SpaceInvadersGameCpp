#pragma once
#include "stdfix.h"

#define ROWS 48
#define COLS 150

typedef struct wd {
    int size_rows;
    int size_cols;
    unsigned char vBuf[ROWS][COLS]{' '};
} WD;