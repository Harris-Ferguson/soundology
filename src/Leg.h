#pragma once
#include "BaseShape.h"

class Leg : public BaseShape {
public:
    Leg(int num, float radius) {
        ofMesh tentacleGeom;
        
        for (int j = 0; j < 2; j++) {
            ofPolyline randomPoints;

            // Create points along the leg
            for (int i = 0; i < num; i++) {
                randomPoints.addVertex(-30 * i, -40 * sin(i * 2), 0);
            }

            // Generate the tube mesh from the polyline
            ofMesh geometry = generateTubeMesh(randomPoints, radius, 7);

            // Apply rotation
            float rotationAngle = sin(j);
            ofMatrix4x4 rotationMatrix;
            rotationMatrix.makeRotationMatrix(rotationAngle, rotationAngle + 1, rotationAngle + 0.5, 1.0);
            
            // Transform the vertices of the tube mesh
            for (int i = 0; i < geometry.getNumVertices(); i++) {
                ofVec3f vertex = geometry.getVertex(i);
                vertex = vertex * rotationMatrix;
                geometry.setVertex(i, vertex);

                ofVec3f normal = geometry.getNormal(i);
                normal = normal * rotationMatrix.getRotate(); // Rotate the normal
                geometry.setNormal(i, normal);
            }

            // Merge the geometry into the final mesh
            tentacleGeom.append(geometry);
        }

        // Set the generated geometry as the mesh of the BaseShape
        mesh = tentacleGeom;
    }

private:
    ofMesh generateTubeMesh(const ofPolyline& line, float radius, int segments) {
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);

        for (int i = 0; i < line.size(); i++) {
            ofVec3f thisPoint = line[i];
            ofVec3f nextPoint = line[(i + 1) % line.size()];  // next point in the polyline

            ofVec3f direction = (nextPoint - thisPoint).normalized();
            ofVec3f normal = direction.getCrossed(ofVec3f(0, 0, 1)).normalize();  // create a perpendicular vector
            ofVec3f binormal = direction.getCrossed(normal).normalize();  // another perpendicular vector

            for (int j = 0; j < segments; j++) {
                float theta = ofMap(j, 0, segments, 0, TWO_PI);
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

        return mesh;
    }
};
