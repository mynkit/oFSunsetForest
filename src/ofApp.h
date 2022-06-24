#pragma once

#include "ofMain.h"

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
        ofImage danchiImg;
        ofImage elavatorImg;
        ofImage edittedElavatorImg;
        ofImage edittedDanchiImg;
        ofImage doorImg;
        ofImage edittedDoorImg;
        ofImage forestImg;
        ofImage edittedForestImg;
        ofVideoPlayer movie;
        ofPlanePrimitive plane;
        ofPlanePrimitive plane2;
        ofPlanePrimitive plane3;
        float planeX;
        float planeY;
        float planeZ;
        float plane2X;
        float plane2Y;
        float plane2Z;
        float plane3X;
        float plane3Y;
        float plane3Z;
        int dizziness;
        bool dizzinessDirection;
        float lightRate;
        bool lightRateDirection;
        ofCamera cam;
};
