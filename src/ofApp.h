#pragma once

#include "ofMain.h"
#include "raindrop.hpp"
#include "ofxOsc.h"

#define HOST "localhost"
#define TIDALPORT 6060
#define SCPORT 57110

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
        void exit();
        ofImage danchiImg;
        ofImage elavatorImg;
        ofImage edittedElavatorImg;
        ofImage edittedDanchiImg;
        ofImage doorImg;
        ofImage edittedDoorImg;
        ofImage forestImg;
        ofImage edittedForestImg;
        ofImage seaLevelImg;
        ofImage edittedSeaLevelImg;
        ofVideoPlayer movie;
        ofPlanePrimitive plane;
        ofPlanePrimitive plane2;
        ofPlanePrimitive plane3;
        ofPlanePrimitive seaLevel;
        bool elavatorOff;
        bool danchiOff;
        bool doorOff;
        float elavatorTimer;
        float danchiTimer;
        float doorTimer;
        float planeX;
        float planeY;
        float planeZ;
        float plane2X;
        float plane2Y;
        float plane2Z;
        float plane3X;
        float plane3Y;
        float plane3Z;
        int seaLevelX;
        float seaLevelY;
        int maxSeaLevelY;
        int seaLevelZ;
        bool seaLevelDirection;
        float dizziness;
        float maxDizziness;
        bool dizzinessDirection;
        float lightRate;
        bool lightRateDirection;
        float entranceRate;
        bool entranceRateDirection;
        float entranceSoundTimer;
        float entranceSoundLifeTime;
        vector<raindrop*> raindrops;
        int maxRaindropCount;
        int raindropCount;
        bool raindropCountDirection;
        float forestView;
        bool forestDirection;
        // OSC
        ofxOscSender tidalSender;
        ofxOscSender scSender;
};
