#pragma once
#include "ofMain.h"

class BaseShape {
public:
    ofMesh mesh;
    ofVec3f position;
    ofVec3f rotation;
    ofVec3f scale;

    BaseShape() {
        scale.set(1.0f, 1.0f, 1.0f);
    }

    BaseShape(const ofMesh& mesh) : mesh(mesh) {
        scale.set(1.0f, 1.0f, 1.0f);
    }

    virtual void update() {}

    virtual void draw() {
        ofPushMatrix();
        ofTranslate(position);
        ofRotateXDeg(rotation.x);
        ofRotateYDeg(rotation.y);
        ofRotateZDeg(rotation.z);
        ofScale(scale.x, scale.y, scale.z);
        mesh.draw();
        ofPopMatrix();
    }
};
