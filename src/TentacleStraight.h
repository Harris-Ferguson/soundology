#pragma once
#include "BaseShape.h"
#include "ofMain.h"

class TentacleStraight : public BaseShape {
public:
    TentacleStraight() {
        generateTentacle();
    }

private:
    void generateTentacle() {
        // Create a polyline for the tentacle path
        ofPolyline line;
        line.addVertex(ofVec3f(0, 0, 0)); // Start point
        line.addVertex(ofVec3f(0, -200, 0)); // End point

        // Tube parameters
        int tubeSegments = 2;
        float tubeRadius = 2;
        int radialSegments = 8;

        // Generate the tube geometry along the polyline
        generateTubeMesh(line, tubeRadius, tubeSegments, radialSegments);
    }

    void generateTubeMesh(const ofPolyline& line, float radius, int tubeSegments, int radialSegments) {
        mesh.clear();
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);

        int lineResolution = line.size();
        for (int i = 0; i < lineResolution - 1; ++i) {
            ofVec3f currentPoint = line[i];
            ofVec3f nextPoint = line[i + 1];
            ofVec3f direction = (nextPoint - currentPoint).normalized();
            ofVec3f normal = direction.getCrossed(ofVec3f(0, 1, 0)).normalize();
            ofVec3f binormal = direction.getCrossed(normal).normalize();

            for (int j = 0; j <= radialSegments; ++j) {
                float theta = ofMap(j, 0, radialSegments, 0, TWO_PI);
                ofVec3f radialOffset = radius * (cos(theta) * normal + sin(theta) * binormal);
                ofVec3f vertex = currentPoint + radialOffset;

                mesh.addVertex(vertex);
                mesh.addNormal(radialOffset.normalized());
            }
        }

        // Connect the vertices into triangles
        for (int i = 0; i < lineResolution - 1; ++i) {
            for (int j = 0; j < radialSegments; ++j) {
                int nextSegment = (j + 1) % radialSegments;
                int currentIndex = i * (radialSegments + 1) + j;
                int nextIndex = (i + 1) * (radialSegments + 1) + j;
                int nextSegmentIndex = i * (radialSegments + 1) + nextSegment;
                int nextIndexSegment = (i + 1) * (radialSegments + 1) + nextSegment;

                mesh.addIndex(currentIndex);
                mesh.addIndex(nextIndex);
                mesh.addIndex(nextIndexSegment);

                mesh.addIndex(currentIndex);
                mesh.addIndex(nextIndexSegment);
                mesh.addIndex(nextSegmentIndex);
            }
        }
    }
};
