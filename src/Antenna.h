#pragma once
#include "BaseShape.h"

class Antenna : public BaseShape {
public:
    Antenna(int num) {
        ofPolyline line;
        for (int i = 0; i < num; i++) {
            line.addVertex(20 * i, 15 * sin(i * num), 0);
        }

        generateTubeMesh(line, 5, 6);  // 5 is the radius, 6 is the number of segments around the tube
    }

    void generateTubeMesh(const ofPolyline& line, float radius, int segments) {
        mesh.clear();

        for (int i = 0; i < line.size(); i++) {
            ofVec3f thisPoint = line[i];
            ofVec3f nextPoint = line[(i + 1) % line.size()];  // next point in the polyline

            ofVec3f direction = (nextPoint - thisPoint).normalized();
            ofVec3f normal = direction.getCrossed(ofVec3f(0, 0, 1)).normalize();  // create a perpendicular vector
            ofVec3f binormal = direction.getCrossed(normal).normalize();  // another perpendicular vector

            for (int j = 0; j < segments; j++) {
                float theta = TWO_PI * j / segments;
                ofVec3f offset = radius * (cos(theta) * normal + sin(theta) * binormal);
                mesh.addVertex(thisPoint + offset);  // add the vertex to the mesh
                mesh.addNormal(offset.normalized());  // add the normal for shading
                mesh.addTexCoord(ofVec2f(j / (float)segments, i / (float)line.size()));  // optional: add texture coordinates
            }
        }

        // Create the faces of the tube
        for (int i = 0; i < line.size() - 1; i++) {
            for (int j = 0; j < segments; j++) {
                int nextSegment = (j + 1) % segments;
                int currentIndex = i * segments + j;
                int nextIndex = (i + 1) * segments + j;
                int nextSegmentIndex = i * segments + nextSegment;
                int nextIndexSegment = (i + 1) * segments + nextSegment;

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
