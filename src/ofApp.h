#pragma once

#include "ofMain.h"
#include "ofxEasyFft.h"
#include "Pettle.h"
#include "Minerals.h"
#include "Tentacle.h"
#include "Antenna.h"
#include "Leg.h"
#include "TentacleStraight.h"
#include <memory>
#include <vector>
#include <utility>

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
		void plot(vector<float>& buffer, float scale);
		void applyFFTToGeometry(ofMesh& mesh, const vector<float>& fftValues);

		void generateGeometries();
		void generateTestGeometries();
		void addGeom(shared_ptr<BaseShape> geom, const ofVec3f& rotation, const ofVec3f& translation, const ofVec3f& scale);
		void createPregeom(ofMesh& geometry, float size, const ofMesh& pregeom, int type);
		void updatePregeom(ofMesh& geometry, float size, const ofMesh& pregeom, int type);

		int getRandomShapeIndex();

		// Container for all precomputed shapes
    	std::vector<std::shared_ptr<BaseShape>> precomputedGeometries;

		// shape we are currently rendering
		shared_ptr<BaseShape> shapeToRender;
		std::vector<std::pair<int, ofMesh>> submeshes;
		ofMutex submeshMutex;

		ofLight pointLight;
		ofEasyCam cam;

		ofPlanePrimitive waterPlane; 
    	ofTexture waterTexture;  
		ofShader waterShader;
		ofImage waterImage;
		ofFbo reflectionFbo;

		ofImage skyImage;
		ofTexture skyTexture;
		ofPlanePrimitive skyPlane;
		ofShader skyShader;

		// FFT stuff
		int bufferSize;
		ofxEasyFft fft;
		vector<float> drawBins, middleBins, audioBins;

	private:
		float rotationAngle;
		float rotationSpeed;
};
