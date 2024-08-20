#include "ofApp.h"

#define AUDIO_SCALING 50

ofMesh createCircleMesh(float radius, int resolution) {
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    mesh.addVertex(ofVec3f(0, 0, 0));  // Center vertex
    mesh.addColor(ofColor::white);

    for (int i = 0; i <= resolution; i++) {
        float angle = ofMap(i, 0, resolution, 0, TWO_PI);
        ofVec3f vertex = ofVec3f(cos(angle) * radius, sin(angle) * radius, 0);
        mesh.addVertex(vertex);
        mesh.addColor(ofColor::white);
    }

    return mesh;
}


ofMesh createTetrahedronMesh(float size) {
    ofMesh mesh;

    // Define vertices
    ofVec3f v0(1, 1, 1);
    ofVec3f v1(-1, -1, 1);
    ofVec3f v2(-1, 1, -1);
    ofVec3f v3(1, -1, -1);

    // Scale vertices
    v0 *= size;
    v1 *= size;
    v2 *= size;
    v3 *= size;

    // Add vertices
    mesh.addVertex(v0);
    mesh.addVertex(v1);
    mesh.addVertex(v2);
    mesh.addVertex(v3);

    // Define faces (each face is a triangle)
    mesh.addIndex(0); mesh.addIndex(1); mesh.addIndex(2);
    mesh.addIndex(0); mesh.addIndex(2); mesh.addIndex(3);
    mesh.addIndex(0); mesh.addIndex(3); mesh.addIndex(1);
    mesh.addIndex(1); mesh.addIndex(3); mesh.addIndex(2);

    return mesh;
}

ofMesh createOctahedronMesh(float size) {
    ofMesh mesh;

    // Define vertices
    ofVec3f v0(0, 0, 1);
    ofVec3f v1(1, 0, 0);
    ofVec3f v2(0, 1, 0);
    ofVec3f v3(-1, 0, 0);
    ofVec3f v4(0, -1, 0);
    ofVec3f v5(0, 0, -1);

    // Scale vertices
    v0 *= size;
    v1 *= size;
    v2 *= size;
    v3 *= size;
    v4 *= size;
    v5 *= size;

    // Add vertices
    mesh.addVertex(v0);
    mesh.addVertex(v1);
    mesh.addVertex(v2);
    mesh.addVertex(v3);
    mesh.addVertex(v4);
    mesh.addVertex(v5);

    // Define faces (each face is a triangle)
    mesh.addIndex(0); mesh.addIndex(1); mesh.addIndex(2);
    mesh.addIndex(0); mesh.addIndex(2); mesh.addIndex(3);
    mesh.addIndex(0); mesh.addIndex(3); mesh.addIndex(4);
    mesh.addIndex(0); mesh.addIndex(4); mesh.addIndex(1);
    mesh.addIndex(5); mesh.addIndex(1); mesh.addIndex(2);
    mesh.addIndex(5); mesh.addIndex(2); mesh.addIndex(3);
    mesh.addIndex(5); mesh.addIndex(3); mesh.addIndex(4);
    mesh.addIndex(5); mesh.addIndex(4); mesh.addIndex(1);

    return mesh;
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);

	// Enable lighting
    ofEnableLighting();
    pointLight.enable();

	ofEnableDepthTest();

	ofMesh boxMesh = ofMesh::box(2, 2, 2, 1, 1, 1);
	pettle = new Pettle();
	tentacle = new Tentacle(2);
	antenna = new Antenna(8);
	minerals = new Minerals(boxMesh);
	leg = new Leg(3, 4);

	pettle->position.set(0, 0, 0);
    minerals->position.set(0, 0, 0);
    tentacle->position.set(0, 0, 0);
    antenna->position.set(0, 0, 0);
	leg->position.set(0, 0, 0);

	pettle->setMaterialColor(ofColor::pink);
	minerals->setMaterialColor(ofColor::red);
	tentacle->setMaterialColor(ofColor::purple);
	antenna->setMaterialColor(ofColor::blue);
	leg->setMaterialColor(ofColor::lightBlue);

	// Set up the camera
    cam.setNearClip(0.1);
    cam.setFarClip(10000);
    cam.setPosition(0, 0, 600); // Start camera at a reasonable distance
    cam.lookAt(ofVec3f(0, 0, 0)); // Look at the origin

    // Set up the light
    pointLight.setPointLight(); 
    pointLight.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 300);
    pointLight.setDiffuseColor(ofColor(255, 255, 255)); 
    pointLight.setSpecularColor(ofColor(255, 255, 255)); 
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();

	pettle->draw();
    minerals->draw();
    tentacle->draw();
    antenna->draw();
	leg->draw();

    cam.end();
}


void ofApp::audioIn(ofSoundBuffer & input){

	
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
