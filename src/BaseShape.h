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
        ofMatrix4x4 transformMatrix;
        transformMatrix.scale(scale);
        transformMatrix.rotate(ofRadToDeg(rotation.x), 1, 0, 0);
        transformMatrix.rotate(ofRadToDeg(rotation.y), 0, 1, 0);
        transformMatrix.rotate(ofRadToDeg(rotation.z), 0, 0, 1);
        transformMatrix.translate(position*2);
        ofPushMatrix();
        ofMultMatrix(transformMatrix);

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

    void applyScale(const ofVec3f& scaleVec) {
        scale = scaleVec;
    }

    void applyRotation(const ofVec3f& rotationVec) {
        rotation = rotationVec;
    }

    void applyTranslation(const ofVec3f& translationVec) {
        position = translationVec;
    }
};
