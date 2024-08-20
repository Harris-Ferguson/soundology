#pragma once
#include "BaseShape.h"

class Pettle : public BaseShape {
public:
    Pettle() {
        mesh = ofMesh::sphere(30, 5);
        scale.z = 0.2f;
    }
};
