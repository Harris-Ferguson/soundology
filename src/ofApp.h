#pragma once

#include "ofMain.h"
#include "Pettle.h"
#include "Minerals.h"
#include "Tentacle.h"
#include "Antenna.h"
#include "Leg.h"
#include "TentacleStraight.h"
#include <memory>
#include <vector>

class ofApp : public ofBaseApp{
	
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
				
		void audioIn(ofSoundBuffer & input);

		void generateGeometries();
		void generateTestGeometries();
		void addGeom(shared_ptr<BaseShape> geom, const ofVec3f& rotation, const ofVec3f& translation, const ofVec3f& scale);

		int getRandomShapeIndex();

		// Container for all precomputed shapes
    	std::vector<std::shared_ptr<BaseShape>> precomputedGeometries;

		// shape we are currently rendering
		shared_ptr<BaseShape> shapeToRender;

		ofLight pointLight;
		ofEasyCam cam;

		ofPlanePrimitive waterPlane; 
    	ofTexture waterTexture;  
		ofShader waterShader;
		ofFbo reflectionFbo;

	private:
		float rotationAngle;
		float rotationSpeed;
};
