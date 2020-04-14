#pragma once

#include "ofMain.h"
#include "ofVec2f.h"
#include "ofxGui.h"
#include "array"
// #include "vector"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key) {};
		void mouseMoved(int x, int y) {};
		void mouseDragged(int x, int y, int button) {};
		void mousePressed(int x, int y, int button) {};
		void mouseReleased(int x, int y, int button) {};
		void mouseEntered(int x, int y) {};
		void mouseExited(int x, int y) {};
		void windowResized(int w, int h) {};
		void dragEvent(ofDragInfo dragInfo) {};
		void gotMessage(ofMessage msg) {};

        // Own functions
        void drawLabelCenter(string content);
        void drawWhiteNoise();
        void audioIn(ofSoundBuffer & inputBuffer);

        // constants
        int NOISE_BLOCK_W = 8;
        int NOISE_BLOCK_H = 8;

        // variables
        ofTrueTypeFont northstar;
        ofColor labelColor = ofColor(200);
        bool isRenderBlockNoise = true;

        ofSoundStream soundStream;
        int frameCount = 0;
        vector<float> buffer;
        vector<float> rmsBuffer;
};
