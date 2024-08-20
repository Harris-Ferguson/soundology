#pragma once
#include "BaseShape.h"

class Minerals : public BaseShape {
public:
    Minerals(ofMesh geom, int max = 4) {
        float dis = 0;
        for (int j = 0; j < max; j++) {
            ofMesh meshClone = geom;
            ofVec3f pos((25 - dis) / 3, dis / 2, 0);
            dis += 25 * (1 - (j + 1) / (float)max);

            // Apply scaling
            ofMatrix4x4 scaleMatrix;
            scaleMatrix.scale(1 - j / (float)max, 1 - j / (float)max, 1 - j / (float)max);

            // Apply rotation around Z axis
            ofMatrix4x4 rotationMatrix;
            rotationMatrix.makeRotationMatrix(1.5 * j / (float)max, 0, 0, 1);

            // Apply translation
            ofMatrix4x4 translationMatrix;
            translationMatrix.translate(pos);

            // Combine the transformations
            ofMatrix4x4 transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;

            // Apply the transformation to all vertices
            for (int i = 0; i < meshClone.getNumVertices(); i++) {
                ofVec3f vertex = meshClone.getVertex(i);
                vertex = vertex * transformMatrix; // Apply the transformation matrix
                meshClone.setVertex(i, vertex);

                ofVec3f normal = meshClone.getNormal(i);
                normal = normal * rotationMatrix; // Only rotate the normals, no scaling or translation
                meshClone.setNormal(i, normal);
            }

            // Append the transformed meshClone to the final mesh
            mesh.append(meshClone);
        }
    }
};
