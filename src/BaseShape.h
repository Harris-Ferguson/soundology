#pragma once
#include "ofMain.h"

class BaseShape {
public:
    ofMesh mesh;
    ofMaterial material;
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

        material.begin();
        mesh.draw();
        material.end();

        ofPopMatrix();
    }

    void setMaterialColor(ofColor color) {
        material.setDiffuseColor(color);
        material.setAmbientColor(color * 0.5);  // Set ambient color to half the diffuse color
        material.setSpecularColor(ofColor(255, 255, 255)); // Set a default white specular highlight
        material.setShininess(128); // Set shininess for the material
    }
};
