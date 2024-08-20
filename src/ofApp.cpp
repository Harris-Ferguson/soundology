#include "ofApp.h"

#define AUDIO_SCALING 50

ofMesh createCylinderMesh(float radiusTop, float radiusBottom, float height, int radialSegments, int heightSegments) {
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    float halfHeight = height / 2.0f;
    float angleStep = TWO_PI / radialSegments;

    // Create vertices and normals
    for (int y = 0; y <= heightSegments; ++y) {
        float v = float(y) / heightSegments;
        float currentHeight = height * v - halfHeight;
        float radius = ofLerp(radiusBottom, radiusTop, v);  // Linearly interpolate between bottom and top radius

        for (int i = 0; i <= radialSegments; ++i) {
            float angle = i * angleStep;
            float x = radius * cos(angle);
            float z = radius * sin(angle);

            mesh.addVertex(ofVec3f(x, currentHeight, z));
            mesh.addNormal(ofVec3f(x, 0, z).normalize());
            mesh.addTexCoord(ofVec2f(float(i) / radialSegments, v));
        }
    }

    // Create faces
    for (int y = 0; y < heightSegments; ++y) {
        for (int i = 0; i < radialSegments; ++i) {
            int current = y * (radialSegments + 1) + i;
            int next = current + radialSegments + 1;

            mesh.addIndex(current);
            mesh.addIndex(next);
            mesh.addIndex(current + 1);

            mesh.addIndex(next);
            mesh.addIndex(next + 1);
            mesh.addIndex(current + 1);
        }
    }

    return mesh;
}


ofMesh createTorusMesh(float majorRadius, float minorRadius, int majorSegments, int minorSegments) {
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    for (int i = 0; i < majorSegments; ++i) {
        float theta = ofMap(i, 0, majorSegments, 0, TWO_PI);
        ofVec3f majorCenter(cos(theta) * majorRadius, sin(theta) * majorRadius, 0);

        for (int j = 0; j < minorSegments; ++j) {
            float phi = ofMap(j, 0, minorSegments, 0, TWO_PI);
            ofVec3f minorPoint = majorCenter + ofVec3f(cos(theta) * (majorRadius + minorRadius * cos(phi)), sin(theta) * (majorRadius + minorRadius * cos(phi)), minorRadius * sin(phi));
            ofVec3f normal = (minorPoint - majorCenter).normalize();

            mesh.addVertex(minorPoint);
            mesh.addNormal(normal);
            mesh.addTexCoord(ofVec2f(float(i) / majorSegments, float(j) / minorSegments));
        }
    }

    for (int i = 0; i < majorSegments; ++i) {
        for (int j = 0; j < minorSegments; ++j) {
            int current = i * minorSegments + j;
            int next = ((i + 1) % majorSegments) * minorSegments + j;
            int currentNext = current + 1;
            int nextNext = next + 1;

            mesh.addIndex(current);
            mesh.addIndex(nextNext % (majorSegments * minorSegments));
            mesh.addIndex(next);

            mesh.addIndex(current);
            mesh.addIndex(currentNext % (majorSegments * minorSegments));
            mesh.addIndex(nextNext % (majorSegments * minorSegments));
        }
    }

    return mesh;
}



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

void ofApp::generateGeometries() {
    // Rocks
    addGeom(make_shared<BaseShape>(createTetrahedronMesh(10)), ofVec3f(0, 0, 0), ofVec3f(40, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<BaseShape>(createTetrahedronMesh(20)), ofVec3f(0, 0, 0), ofVec3f(20, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<BaseShape>(createTetrahedronMesh(20)), ofVec3f(0, 0, 0), ofVec3f(0, -40, 0), ofVec3f(1, 1, 1));

    // Legs
    addGeom(make_shared<Leg>(4, 3), ofVec3f(1, 1, 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(4, 6), ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(5, 3), ofVec3f(0, 0, PI / 2), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(6, 4), ofVec3f(0, -(PI / 2), 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(7, 3), ofVec3f(0, PI / 2, PI / 2), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(8, 5), ofVec3f(0, 1, 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(9, 2), ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(10, 6), ofVec3f(0, 0, PI / 2), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(11, 3), ofVec3f(1, -(PI / 2), 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));

	// Antennas
	addGeom(make_shared<Antenna>(4), ofVec3f(0, -(PI/2), 0), ofVec3f(0,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<Antenna>(5), ofVec3f(0, 0, 0), ofVec3f(0,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<Antenna>(6), ofVec3f(0, PI/2, 0), ofVec3f(0,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<Antenna>(7), ofVec3f( PI/2, -PI/2, 0), ofVec3f(0,0,0), ofVec3f(1,1,1));

	// Doughnuts
	addGeom(make_shared<BaseShape>(createTorusMesh(20, 7, 4, 10)), ofVec3f(0,0,0), ofVec3f(0,20,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTorusMesh(20, 7, 4, 10)), ofVec3f(0,0,0), ofVec3f(40,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTorusMesh(20, 7, 10, 10)), ofVec3f(0,0,0), ofVec3f(20,10,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTorusMesh(20, 5, 4, 3)), ofVec3f(0,0,0), ofVec3f(40,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTorusMesh(20, 5, 4, 5)), ofVec3f(0,0,0), ofVec3f(40,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTorusMesh(20, 2, 4, 10)), ofVec3f(0,0,0), ofVec3f(40,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTorusMesh(20, 4, 4, 10)), ofVec3f(0,0,0), ofVec3f(40,0,0), ofVec3f(1,1,1));

	// Mineral Horns
	addGeom(make_shared<Minerals>(createCylinderMesh(3, 10, 20, 3, 1)), ofVec3f(1,0,0), ofVec3f(0,20,0), ofVec3f(1,1,1));
	addGeom(make_shared<Minerals>(createCylinderMesh(3, 10, 20, 3, 1)), ofVec3f(1,1,-PI/2), ofVec3f(20,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<Minerals>(createCylinderMesh(3, 10, 20, 3, 1)), ofVec3f(1,0,PI/2), ofVec3f(40,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<Minerals>(createCylinderMesh(3, 10, 20, 3, 1)), ofVec3f(0,1,0), ofVec3f(50,0,0), ofVec3f(1,1,1));

	// Spikes 
	addGeom(make_shared<BaseShape>(createCylinderMesh(0, 6, 60, 5, 10)), ofVec3f(-PI/2, 0, 0), ofVec3f(0,0,-30), ofVec3f(1.5, 0.7, 1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(0, 6, 60, 5, 10)), ofVec3f(-PI/2, 0, 0), ofVec3f(0,0,-30), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(0, 6, 60, 5, 10)), ofVec3f(-PI/2, 0, 0), ofVec3f(20,20,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(0, 6, 70, 4, 10)), ofVec3f(0, 0, 0), ofVec3f(0,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(0, 6, 80, 4, 10)), ofVec3f(0, -PI/2, 0), ofVec3f(0,0,0), ofVec3f(1,1,1));
}


void ofApp::addGeom(shared_ptr<BaseShape> geom, const ofVec3f& rotation, const ofVec3f& translation, const ofVec3f& scale) {
    geom->applyScale(scale);
    geom->applyRotation(rotation);
    geom->applyTranslation(translation);
    shapes.push_back(geom);
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);

	// Enable lighting
    ofEnableLighting();
    pointLight.enable();

	ofEnableDepthTest();

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

	generateGeometries();
	for (auto& shape : shapes) {
        shape->setMaterialColor(ofColor::blue);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();

	for (auto& shape : shapes) {
        shape->draw();
    }

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
