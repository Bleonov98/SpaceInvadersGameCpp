#pragma once
#include "GameObject.h"

typedef struct vct {
    int vecSize;
    vector<GameObject*> allKnownObjects;
} VCT;