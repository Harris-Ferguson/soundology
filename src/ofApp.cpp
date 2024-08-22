#include "ofApp.h"

#define AUDIO_SCALING 50

ofMesh createCylinderMesh(float radiusTop, float radiusBottom, float height, int radialSegments, int heightSegments) {
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    float halfHeight = height / 2.0f;
    float angleStep = TWO_PI / radialSegments;

    for (int y = 0; y <= heightSegments; ++y) {
        float v = float(y) / heightSegments;
        float currentHeight = height * v - halfHeight;
        float radius = ofLerp(radiusBottom, radiusTop, v);

        for (int i = 0; i <= radialSegments; ++i) {
            float angle = i * angleStep;
            glm::vec3 vertex(radius * cos(angle), currentHeight, radius * sin(angle));

            // Add vertex
            mesh.addVertex(vertex);

            // Calculate and add normal
            glm::vec3 normal = glm::normalize(glm::vec3(cos(angle), 0, sin(angle)));
            mesh.addNormal(normal);

            // Texture coordinates
            mesh.addTexCoord(glm::vec2(float(i) / radialSegments, v));
        }
    }

    // Create faces with proper winding order
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

    for (int i = 0; i <= majorSegments; ++i) {
        float theta = ofMap(i, 0, majorSegments, 0, TWO_PI);
        glm::vec3 majorCenter(cos(theta) * majorRadius, sin(theta) * majorRadius, 0);

        for (int j = 0; j <= minorSegments; ++j) {
            float phi = ofMap(j, 0, minorSegments, 0, TWO_PI);
            glm::vec3 minorPoint = majorCenter + glm::vec3(cos(theta) * (majorRadius + minorRadius * cos(phi)), 
                                                           sin(theta) * (majorRadius + minorRadius * cos(phi)), 
                                                           minorRadius * sin(phi));
            glm::vec3 normal = glm::normalize(minorPoint - majorCenter);

            mesh.addVertex(minorPoint);
            mesh.addNormal(normal);
            mesh.addTexCoord(glm::vec2(float(i) / majorSegments, float(j) / minorSegments));
        }
    }

    // Create faces with proper winding order
    for (int i = 0; i < majorSegments; ++i) {
        for (int j = 0; j < minorSegments; ++j) {
            int current = i * (minorSegments + 1) + j;
            int next = (i + 1) * (minorSegments + 1) + j;

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
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    // Define vertices
    glm::vec3 v0 = glm::normalize(glm::vec3(1, 1, 1)) * size;
    glm::vec3 v1 = glm::normalize(glm::vec3(-1, -1, 1)) * size;
    glm::vec3 v2 = glm::normalize(glm::vec3(-1, 1, -1)) * size;
    glm::vec3 v3 = glm::normalize(glm::vec3(1, -1, -1)) * size;

    // Add vertices and corresponding normals
    mesh.addVertex(v0);
    mesh.addVertex(v1);
    mesh.addVertex(v2);
    mesh.addVertex(v3);

    // Define faces (with proper winding order)
    mesh.addIndex(0); mesh.addIndex(1); mesh.addIndex(2);
    mesh.addIndex(0); mesh.addIndex(2); mesh.addIndex(3);
    mesh.addIndex(0); mesh.addIndex(3); mesh.addIndex(1);
    mesh.addIndex(1); mesh.addIndex(3); mesh.addIndex(2);

    // Calculate and add normals
    mesh.addNormal(glm::normalize(glm::cross(v1 - v0, v2 - v0)));
    mesh.addNormal(glm::normalize(glm::cross(v2 - v0, v3 - v0)));
    mesh.addNormal(glm::normalize(glm::cross(v3 - v0, v1 - v0)));
    mesh.addNormal(glm::normalize(glm::cross(v2 - v1, v3 - v1)));

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

ofMesh createTorusKnotMesh(float radius, float tubeRadius, int radialSegments, int tubularSegments, float p = 2, float q = 3) {
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    for (int i = 0; i <= tubularSegments; ++i) {
        float u = i / float(tubularSegments) * TWO_PI * p;
        float cu = cos(u);
        float su = sin(u);
        float quOverP = q / p * u;
        float cs = cos(quOverP);

        for (int j = 0; j <= radialSegments; ++j) {
            float v = j / float(radialSegments) * TWO_PI;
            float cv = cos(v);
            float sv = sin(v);

            float x = (radius + tubeRadius * cv) * cu;
            float y = (radius + tubeRadius * cv) * su;
            float z = tubeRadius * sv;

            ofVec3f vertex(x, y, z);
            mesh.addVertex(vertex);

            // Calculate normals
            ofVec3f normal = vertex.normalized();
            mesh.addNormal(normal);
        }
    }

    for (int i = 0; i < tubularSegments; ++i) {
        for (int j = 0; j < radialSegments; ++j) {
            int a = i * (radialSegments + 1) + j;
            int b = (i + 1) * (radialSegments + 1) + j;
            int c = (i + 1) * (radialSegments + 1) + (j + 1);
            int d = i * (radialSegments + 1) + (j + 1);

            // Add two triangles for each segment
            mesh.addIndex(a);
            mesh.addIndex(b);
            mesh.addIndex(d);

            mesh.addIndex(b);
            mesh.addIndex(c);
            mesh.addIndex(d);
        }
    }

    return mesh;
}

void ofApp::generateTestGeometries() {
    // Legs
    addGeom(make_shared<Leg>(4, 3), ofVec3f(1, 1, 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(4, 6), ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(5, 3), ofVec3f(0, 0, PI / 2), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(6, 4), ofVec3f(0, -(PI / 2), 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(7, 3), ofVec3f(0, PI / 2, PI / 2), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(8, 5), ofVec3f(0, 1, 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(9, 2), ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(10, 6), ofVec3f(0, 0, PI / 2), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
}


void ofApp::generateGeometries() {
    // Rocks
    addGeom(make_shared<BaseShape>(createTetrahedronMesh(80)), ofVec3f(0, 0, 0), ofVec3f(40, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<BaseShape>(createTetrahedronMesh(80)), ofVec3f(0, 0, 0), ofVec3f(20, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<BaseShape>(createTetrahedronMesh(80)), ofVec3f(0, 0, 0), ofVec3f(0, -40, 0), ofVec3f(1, 1, 1));
	addGeom(make_shared<BaseShape>(createTetrahedronMesh(80)), ofVec3f(0, 0, 0), ofVec3f(40, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<BaseShape>(createTetrahedronMesh(120)), ofVec3f(0, 0, 0), ofVec3f(20, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<BaseShape>(createTetrahedronMesh(120)), ofVec3f(0, 0, 0), ofVec3f(0, -40, 0), ofVec3f(1, 1, 1));

    // Legs
    addGeom(make_shared<Leg>(4, 3), ofVec3f(1, 1, 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(4, 6), ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(5, 3), ofVec3f(0, 0, PI / 2), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(6, 4), ofVec3f(0, -(PI / 2), 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(7, 3), ofVec3f(0, PI / 2, PI / 2), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(8, 5), ofVec3f(0, 1, 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(9, 2), ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
    addGeom(make_shared<Leg>(10, 6), ofVec3f(0, 0, PI / 2), ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));

	// Antennas
	addGeom(make_shared<Antenna>(4), ofVec3f(0, -(PI/2), 0), ofVec3f(0,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<Antenna>(5), ofVec3f(0, 0, 0), ofVec3f(0,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<Antenna>(6), ofVec3f(0, PI/2, 0), ofVec3f(0,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<Antenna>(7), ofVec3f( PI/2, -PI/2, 0), ofVec3f(0,0,0), ofVec3f(1,1,1));

	// Doughnuts
	addGeom(make_shared<BaseShape>(createTorusMesh(70, 7, 4, 10)), ofVec3f(0,0,0), ofVec3f(0,20,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTorusMesh(70, 7, 4, 10)), ofVec3f(0,0,0), ofVec3f(40,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTorusMesh(70, 7, 10, 10)), ofVec3f(0,0,0), ofVec3f(20,10,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTorusMesh(70, 5, 4, 3)), ofVec3f(0,0,0), ofVec3f(40,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTorusMesh(70, 5, 4, 5)), ofVec3f(0,0,0), ofVec3f(40,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTorusMesh(70, 2, 4, 10)), ofVec3f(0,0,0), ofVec3f(40,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTorusMesh(70, 4, 4, 10)), ofVec3f(0,0,0), ofVec3f(40,0,0), ofVec3f(1,1,1));

	// Mineral Horns
	addGeom(make_shared<Minerals>(createCylinderMesh(3, 10, 20, 3, 1)), ofVec3f(1,0,0), ofVec3f(0,20,0), ofVec3f(1,1,1));
	addGeom(make_shared<Minerals>(createCylinderMesh(3, 10, 20, 3, 1)), ofVec3f(1,1,-PI/2), ofVec3f(20,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<Minerals>(createCylinderMesh(3, 10, 20, 3, 1)), ofVec3f(1,0,PI/2), ofVec3f(40,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<Minerals>(createCylinderMesh(3, 10, 20, 3, 1)), ofVec3f(0,1,0), ofVec3f(50,0,0), ofVec3f(1,1,1));

	// Mineral Lines
	addGeom(make_shared<Minerals>(createCylinderMesh(3, 3, 300, 3, 1)), ofVec3f(0,0,0), ofVec3f(0,20,0), ofVec3f(1,1,1));
	addGeom(make_shared<Minerals>(createCylinderMesh(3, 3, 300, 3, 1)), ofVec3f(0,0,-PI/2), ofVec3f(20,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<Minerals>(createCylinderMesh(3, 3, 300, 3, 1)), ofVec3f(0,0,PI/2), ofVec3f(30,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<Minerals>(createCylinderMesh(3, 3, 300, 3, 1)), ofVec3f(0,0,0), ofVec3f(40,0,0), ofVec3f(1,1,1));
	
	// Spikes 
	addGeom(make_shared<BaseShape>(createCylinderMesh(0, 6, 120, 5, 10)), ofVec3f(-PI/2, 0, 0), ofVec3f(0,0,-30), ofVec3f(1.5, 0.7, 1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(0, 6, 120, 5, 10)), ofVec3f(-PI/2, 0, 0), ofVec3f(0,0,-30), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(0, 6, 120, 5, 10)), ofVec3f(-PI/2, 0, 0), ofVec3f(20,20,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(0, 6, 140, 4, 10)), ofVec3f(0, 0, 0), ofVec3f(0,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(0, 6, 140, 4, 10)), ofVec3f(0, -PI/2, 0), ofVec3f(0,0,0), ofVec3f(1,1,1));

	// Long Lines
	addGeom(make_shared<TentacleStraight>(), ofVec3f(0,0,0), ofVec3f(0,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<TentacleStraight>(), ofVec3f(0,-PI/2,0), ofVec3f(0,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<TentacleStraight>(), ofVec3f(0,PI/2,0), ofVec3f(0,0,0), ofVec3f(1,1,1));

	// Pretzels 
	addGeom(make_shared<BaseShape>(createTorusKnotMesh(15, 3, 3, 13)), ofVec3f(0, PI/2, 0), ofVec3f(0,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTorusKnotMesh(15, 3, 3, 10)), ofVec3f(0, 0, 0), ofVec3f(0,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTorusKnotMesh(15, 3, 3, 6)), ofVec3f(0, 0, 0), ofVec3f(0,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTorusKnotMesh(15, 3, 3, 13)), ofVec3f(0, 0, 0), ofVec3f(0,0,0), ofVec3f(1,1,1));

	// Cinder Blocks
	addGeom(make_shared<BaseShape>(createCylinderMesh(12, 7, 80, 4, 10)), ofVec3f(0, 0, 0), ofVec3f(0,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(12, 7, 80, 4, 10)), ofVec3f(0, 0, PI/2), ofVec3f(0,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(3, 10, 80, 4, 10)), ofVec3f(0, 0, 0), ofVec3f(0,20,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(12, 6, 80, 4, 10)), ofVec3f(0, 0, 0), ofVec3f(0,20,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(12, 10, 80, 4, 10)), ofVec3f(0, 0, 0), ofVec3f(0,-40,30), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(3, 10, 80, 4, 10)), ofVec3f(0, 0, 0), ofVec3f(0,20,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(12, 6, 80, 4, 10)), ofVec3f(0, 0, 0), ofVec3f(0,20,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(12, 10, 80, 4, 10)), ofVec3f(0, 0, 0), ofVec3f(0,-40,30), ofVec3f(1,1,1));

	// Pettles
	addGeom(make_shared<Pettle>(), ofVec3f(0,0,0), ofVec3f(30,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<Pettle>(), ofVec3f(0,PI/2,0), ofVec3f(30,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<Pettle>(), ofVec3f(0,-PI/2,0), ofVec3f(30,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCircleMesh(20, 30)), ofVec3f(0,0,0), ofVec3f(40,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCircleMesh(20, 30)), ofVec3f(0,0,0), ofVec3f(0,-30,0), ofVec3f(1,1,1));

	// Triangles
	addGeom(make_shared<BaseShape>(createTetrahedronMesh(6)), ofVec3f(0,0,0), ofVec3f(30,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTetrahedronMesh(6)), ofVec3f(-PI/2,0,0), ofVec3f(30,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTetrahedronMesh(6)), ofVec3f(0,PI/2,0), ofVec3f(30,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createTetrahedronMesh(6)), ofVec3f(0,-PI/2,0), ofVec3f(30,0,0), ofVec3f(1,1,1));

	// Squares ?? 
	addGeom(make_shared<BaseShape>(createCylinderMesh(5, 5, 7, 4, 1)), ofVec3f(0,0,0), ofVec3f(30,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(5, 5, 7, 4, 1)), ofVec3f(-PI/2,0,0), ofVec3f(30,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(5, 5, 7, 4, 1)), ofVec3f(0,PI/2,0), ofVec3f(30,0,0), ofVec3f(1,1,1));
	addGeom(make_shared<BaseShape>(createCylinderMesh(5, 5, 7, 4, 1)), ofVec3f(0,-PI/2,0), ofVec3f(30,0,0), ofVec3f(1,1,1));

	// Bubbles
	addGeom(make_shared<BaseShape>(ofMesh::sphere(5, 5)), ofVec3f(0, 0, 0), ofVec3f(30, 0, 0), ofVec3f(1, 1, 1));
	addGeom(make_shared<BaseShape>(ofMesh::sphere(5, 5)), ofVec3f(-PI / 2, 0, 0), ofVec3f(30, 0, 0), ofVec3f(1, 1, 1));
	addGeom(make_shared<BaseShape>(ofMesh::sphere(5, 5)), ofVec3f(0, PI / 2, 0), ofVec3f(30, 0, 0), ofVec3f(1, 1, 1));
	addGeom(make_shared<BaseShape>(ofMesh::sphere(5, 5)), ofVec3f(0, -PI / 2, 0), ofVec3f(30, 0, 0), ofVec3f(1, 1, 1));
}

void ofApp::createPregeom(ofMesh& geometry, float size, const ofMesh& pregeom, int type) {
    std::vector<ofColor> colors = {
        ofColor::fromHex(0x00AA00), 
        ofColor::fromHex(0x55FF55), 
        ofColor::fromHex(0x0000AA),
        ofColor::fromHex(0x00AAAA),
        ofColor::fromHex(0xAA00AA)
    };

    float fileScale = size / 300000.0f;
    float fileScaleOrg = fileScale;

    if (fileScale < 0.4f) {
        fileScale = 0.4f;
    }
    if (fileScale > 1.0f) {
        fileScale = 1.0f;
    }

    vector<float> fftValues = fft.getBins(); // Get the current FFT values
    int fftSize = fftValues.size();

    for (int k = 0; k < fileScale * 4; ++k) {
        // Copy the precomputed mesh
        ofMesh submesh = pregeom;

        ofColor randomColor = colors[static_cast<int>(ofRandom(0, colors.size()))];

        for (int i = 0; i < submesh.getNumVertices(); ++i) {
            ofLogNotice() << "adding color";
            submesh.addColor(randomColor);
        }

        // Create transformation matrix
        ofMatrix4x4 transformMatrix;

        // Apply scaling using FFT values
        int fftIndex = ofMap(k, 0, static_cast<int>(fileScale * 4), 0, fftSize - 1, true);
        fftIndex = ofClamp(fftIndex, 0, fftSize - 1);
        float fftValue = fftSize == 0 ? 1 : fftValues[fftIndex] * AUDIO_SCALING;

        float scaleValue = fileScale * 4 * (1.0 + fftValue * 0.1); // FFT influences the scale
        transformMatrix.scale(scaleValue, scaleValue, scaleValue);

        // Apply rotation using FFT values
        float randoms[3] = {
            sin((-1 + k * 0.3f) * fileScaleOrg * 687.0f + 0.1f) / 2.0f + 0.5f + fftValue * 0.1f,
            sin((2 + k * 0.9f) * fileScaleOrg * 456.0f + 0.2f) / 2.0f + 0.5f + fftValue * 0.1f,
            sin((1 + k) * fileScaleOrg * 546.0f + 0.3f) / 2.0f + 0.5f + fftValue * 0.1f
        };

        transformMatrix.rotate(randoms[0] * 360.0f, 1, 0, 0);
        transformMatrix.rotate(randoms[1] * 360.0f, 0, 1, 0);
        transformMatrix.rotate(randoms[2] * 360.0f, 0, 0, 1);

        // Apply translation using FFT values
        float randoms2[3] = {
            sin((2 + k) * fileScaleOrg * 413.0f + 0.1f) / 2.0f + 0.5f + fftValue * 0.1f,
            sin((2 + k) * fileScaleOrg * 543.0f + 0.2f) / 2.0f + 0.5f + fftValue * 0.1f,
            sin((2 + k) * fileScaleOrg * 123.0f + 0.3f) / 2.0f + 0.5f + fftValue * 0.1f
        };

        transformMatrix.translate(
            (randoms2[1] - 0.5f) * 100.0f * fileScale,
            (randoms2[0] - 0.5f) * 100.0f * fileScale,
            (randoms2[2] - 0.5f) * 100.0f * fileScale
        );
        ofLogNotice() << "matrix mult on vertices";
        for (auto& vertex : submesh.getVertices()) {
            ofVec4f homogenousVertex = ofVec4f(vertex.x, vertex.y, vertex.z, 1.0); 
            homogenousVertex = transformMatrix.postMult(homogenousVertex); 
            vertex.x = homogenousVertex.x;
            vertex.y = homogenousVertex.y;
            vertex.z = homogenousVertex.z;
        }

        submeshes.push_back(std::make_pair(size, submesh));
        geometry.append(submesh);
    }
}

void ofApp::updatePregeom(ofMesh& geometry, float size, const ofMesh& pregeom, int type) {
    float fileScale = size / 300000.0f;
    float fileScaleOrg = fileScale;

    if (fileScale < 0.4f) {
        fileScale = 0.4f;
    }
    if (fileScale > 1.0f) {
        fileScale = 1.0f;
    }

    vector<float> fftValues = fft.getBins(); // Get the current FFT values
    int fftSize = fftValues.size();

    for (int k = 0; k < fileScale * 4; ++k) {
        // Copy the precomputed mesh
        ofMesh submesh = pregeom;

        // Create transformation matrix
        ofMatrix4x4 transformMatrix;

        // Apply scaling using FFT values
        int fftIndex = ofMap(k, 0, static_cast<int>(fileScale * 4), 0, fftSize - 1, true);
        fftIndex = ofClamp(fftIndex, 0, fftSize - 1);
        float fftValue = fftSize == 0 ? 1 : fftValues[fftIndex] * AUDIO_SCALING;

        float scaleValue = fileScale * 4 * (1.0 + fftValue * 0.1); // FFT influences the scale
        transformMatrix.scale(scaleValue, scaleValue, scaleValue);

        // Apply translation using FFT values
        float randoms2[3] = {
            sin((2 + k) * fileScaleOrg * 413.0f + 0.1f) / 2.0f + 0.5f + fftValue * 0.1f,
            sin((2 + k) * fileScaleOrg * 543.0f + 0.2f) / 2.0f + 0.5f + fftValue * 0.1f,
            sin((2 + k) * fileScaleOrg * 123.0f + 0.3f) / 2.0f + 0.5f + fftValue * 0.1f
        };

        transformMatrix.translate(
            (randoms2[1] - 0.5f) * 100.0f * fileScale,
            (randoms2[0] - 0.5f) * 100.0f * fileScale,
            (randoms2[2] - 0.5f) * 100.0f * fileScale
        );
        for (auto& vertex : submesh.getVertices()) {
            ofVec4f homogenousVertex = ofVec4f(vertex.x, vertex.y, vertex.z, 1.0); 
            homogenousVertex = transformMatrix.postMult(homogenousVertex); 
            vertex.x = homogenousVertex.x;
            vertex.y = homogenousVertex.y;
            vertex.z = homogenousVertex.z;
        }

        // Merge the transformed submesh into the main geometry
        geometry.append(submesh);
    }
}



void ofApp::addGeom(shared_ptr<BaseShape> geom, const ofVec3f& rotation, const ofVec3f& translation, const ofVec3f& scale) {
    geom->applyScale(scale);
    geom->applyRotation(rotation);
    geom->applyTranslation(translation);
    precomputedGeometries.push_back(geom);
}

int ofApp::getRandomShapeIndex() {
    if (!precomputedGeometries.empty()) {
        int randomIndex = ofRandom(0, precomputedGeometries.size()); // Generates a random float between 0 and shapes.size()
        return static_cast<int>(randomIndex); // Casts the random float to an integer
    } else {
        return -1; // Return -1 if the shapes vector is empty
    }
}

//--------------------------------------------------------------
void ofApp::setup() {
    ofDisableArbTex();
    ofBackground(0);
	generateGeometries();

    // Complex geometry assembly
    ofMesh complexGeometry;

    createPregeom(complexGeometry, 1054600, precomputedGeometries[getRandomShapeIndex()]->mesh, 2);
	createPregeom(complexGeometry, 3945123, precomputedGeometries[getRandomShapeIndex()]->mesh, 3);
    createPregeom(complexGeometry, 150000, precomputedGeometries[getRandomShapeIndex()]->mesh, 4);
    createPregeom(complexGeometry, 1502, precomputedGeometries[getRandomShapeIndex()]->mesh, 4);

    // Store or use complexGeometry for rendering
    shapeToRender = make_shared<BaseShape>(complexGeometry);

    // Set up lighting and camera
    ofEnableLighting();
    pointLight.enable();
    ofEnableDepthTest();

    cam.setNearClip(0.1);
    cam.setFarClip(10000);
    cam.setPosition(300, 300, 1000);
    cam.lookAt(ofVec3f(0, 0, 0));

    rotationAngle = 0.0f;
    rotationSpeed = 0.001f;

    // Load the water texture
    if(waterImage.load("textures/water/060.jpg")) {
		waterImage.getTexture().setTextureWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
        ofLogNotice() << "Water texture loaded successfully!";
	} else {
        ofLogError() << "Failed to load water texture!";
    }

    // load the sky texture
    if(skyImage.load("textures/sky/117.jpg")) {
		skyImage.getTexture().setTextureWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
        ofLogNotice() << "Sky texture loaded successfully!";
	} else {
        ofLogError() << "Failed to load Sky texture!";
    }

    // Set up the water plane
    waterPlane.set(10000, 10000, 10, 10);  
    waterPlane.setPosition(0, 500, 0);  
    waterPlane.rotateDeg(90, 1, 0, 0);
    waterPlane.mapTexCoords(0, 0, 1, 1);
    // set up the sky plane
    skyPlane.set(ofGetWidth(), ofGetHeight(), 10, 10);
    skyPlane.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 0);
    skyPlane.mapTexCoords(0, 0, 1, 1);

    // Load the water shader
    if (!waterShader.load("shaders/water/water")) {
        ofLogError() << "Shader failed to load!";
    } else {
        ofLogNotice() << "Shader loaded successfully!";
    }

    // i know i know
    if (!skyShader.load("shaders/water/water")) {
        ofLogError() << "Shader failed to load!";
    } else {
        ofLogNotice() << "Shader loaded successfully!";
    }

    // set up the FBO 
    reflectionFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

    ofLogNotice() << "OpenGL Vendor: " << glGetString(GL_VENDOR);
    ofLogNotice() << "OpenGL Renderer: " << glGetString(GL_RENDERER);
    ofLogNotice() << "OpenGL Version: " << glGetString(GL_VERSION);

    // FFT stuff 
    fft.setup(16384);
}

void ofApp::draw() {
    // 1. Render the reflection to the FBO
    reflectionFbo.begin();
    ofClear(0, 0, 0, 255);  // Clear the FBO with a black background

    // Flip the scene vertically for the reflection effect
    cam.begin();

    // Apply the same rotation as in the main scene, but in the opposite direction for the reflection
    shapeToRender->applyRotation(ofVec3f(0, -rotationAngle, 0));  
    shapeToRender->draw();

    cam.end();
    reflectionFbo.end();

    // 2. Render the main scene
    ofDisableDepthTest();
    // sky first
    skyImage.getTexture().bind();
    skyShader.begin();
    skyShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    skyShader.setUniform1i("skyTexture", 0);
    skyPlane.draw();
    skyShader.end();
    skyImage.getTexture().unbind();
    ofEnableDepthTest();

    // next the water plane (this will render below the shapes)
    cam.begin();
    cam.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));  // Normal camera direction

    // Bind the FBO's texture and pass it to the shader for the water reflection
    reflectionFbo.getTexture().bind(1);  // Bind FBO texture to texture unit 1
    waterImage.getTexture().bind(0);     // Bind the water texture to texture unit 0

    waterShader.begin();
    waterShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    waterShader.setUniform1i("waterTexture", 0);
    waterShader.setUniform1i("reflectionTexture", 1);  // Pass FBO texture as reflection texture

    waterPlane.draw();  // Draw the water plane

    waterShader.end();

    waterImage.getTexture().unbind();
    reflectionFbo.getTexture().unbind();

    // Now render the shape above the water plane with the original rotation
    shapeToRender->applyRotation(ofVec3f(0, rotationAngle, 0));  
    shapeToRender->draw();

    cam.end();

    #ifdef DEBUG
        ofPushMatrix();
        ofTranslate(16, 16);
        ofSetColor(255);
        ofDrawBitmapString("Frequency Domain", 0, 0);
        plot(fft.getBins(), 128);
        ofPopMatrix();
        
        string msg = ofToString((int) ofGetFrameRate()) + " fps";
        ofDrawBitmapString(msg, ofGetWidth() - 80, ofGetHeight() - 20);
    #endif DEBUG
}

void ofApp::plot(vector<float>& buffer, float scale) {
	ofNoFill();
	int n = MIN(1024, buffer.size());
	ofDrawRectangle(0, 0, n, scale);
	ofPushMatrix();
	ofTranslate(0, scale);
	ofScale(1, -scale);
	ofBeginShape();
	for (int i = 0; i < n; i++) {
		ofVertex(i, buffer[i]);
	}
	ofEndShape();
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::update(){
    rotationAngle += rotationSpeed;
    ofVec3f rotation(0, rotationAngle, 0);

    ofMesh complexGeometry;

    submeshMutex.lock();
    for (auto &mesh : submeshes) {
        updatePregeom(complexGeometry, mesh.first, mesh.second, 0);
    }
    submeshMutex.unlock();

    shapeToRender = make_shared<BaseShape>(complexGeometry);

    // Apply rotation
    shapeToRender->applyRotation(rotation);

    // Update the FFT data
    fft.update();
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
