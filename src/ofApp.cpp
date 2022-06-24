#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();
    ofEnableAlphaBlending();
    
    forestImg.load("forest.jpg");
    elavatorImg.load("elavator.jpg");
    danchiImg.load("danchi_trim.jpg");
    doorImg.load("door.jpg");
    movie.load("forest_trim_concat_0.4.mov");
    movie.play();
    
    // 鳥居の赤を明るくして強調する
    ofPixels forestPixels = forestImg.getPixels();
    for (int y = 0; y < forestPixels.getHeight(); y++) {
        for (int x = forestPixels.getWidth() - 1; x > 0; x--) {
            ofColor color_ = forestPixels.getColor(x, y);
            if ((color_.r > 70 && color_.g < 30 && color_.b < 30) || (color_.r > 30 && color_.g < 10 && color_.b < 10)) {
                color_.r = color_.r * 1.6;
                color_.g = color_.g * 1.6;
                color_.b = color_.b * 1.6;
            }
            forestPixels.setColor(x, y, color_);
        }
    }
    edittedForestImg.setFromPixels(forestPixels);
    
    
    ofPixels danchiPixels = danchiImg.getPixels();
    float th = 0.7;
    for (int y = 0; y < danchiPixels.getHeight(); y++) {
        for (int x = danchiPixels.getWidth() - 1; x > 0; x--) {
            ofColor color_ = danchiPixels.getColor(x, y);
            float distanceFromCenterY = abs(danchiPixels.getHeight()/2. - y) / (danchiPixels.getHeight()/2.);
            float distanceFromCenterX = abs(danchiPixels.getWidth()/2. - x) / (danchiPixels.getWidth()/2.);
            if (distanceFromCenterY>th) {
                color_.r = color_.r * (1-distanceFromCenterY)/(1.-th);
                color_.g = color_.g * (1-distanceFromCenterY)/(1.-th);
                color_.b = color_.b * (1-distanceFromCenterY)/(1.-th);
            }
            if (distanceFromCenterX>th) {
                color_.r = color_.r * (1-distanceFromCenterX)/(1.-th);
                color_.g = color_.g * (1-distanceFromCenterX)/(1.-th);
                color_.b = color_.b * (1-distanceFromCenterX)/(1.-th);
            }
            danchiPixels.setColor(x, y, color_);
        }
    }
    edittedDanchiImg.setFromPixels(danchiPixels);
    
    ofPixels elavatorPixels = elavatorImg.getPixels();
    th = 0.45;
    for (int y = 0; y < elavatorPixels.getHeight(); y++) {
        for (int x = elavatorPixels.getWidth() - 1; x > 0; x--) {
            ofColor color_ = elavatorPixels.getColor(x, y);
            float distanceFromCenterY = abs(elavatorPixels.getHeight()/2. - y) / (elavatorPixels.getHeight()/2.);
            float distanceFromCenterX = abs(elavatorPixels.getWidth()/2. - x) / (elavatorPixels.getWidth()/2.);
            if (distanceFromCenterY>th) {
                color_.r = color_.r * (1-distanceFromCenterY)/(1.-th);
                color_.g = color_.g * (1-distanceFromCenterY)/(1.-th);
                color_.b = color_.b * (1-distanceFromCenterY)/(1.-th);
            }
            if (distanceFromCenterX>th) {
                color_.r = color_.r * (1-distanceFromCenterX)/(1.-th);
                color_.g = color_.g * (1-distanceFromCenterX)/(1.-th);
                color_.b = color_.b * (1-distanceFromCenterX)/(1.-th);
            }
            elavatorPixels.setColor(x, y, color_);
        }
    }
    edittedElavatorImg.setFromPixels(elavatorPixels);
    
    ofPixels doorPixels = doorImg.getPixels();
    th = 0.6;
    for (int y = 0; y < doorPixels.getHeight(); y++) {
        for (int x = doorPixels.getWidth() - 1; x > 0; x--) {
            ofColor color_ = doorPixels.getColor(x, y);
            float distanceFromCenterY = abs(doorPixels.getHeight()/2. - y) / (doorPixels.getHeight()/2.);
            float distanceFromCenterX = abs(doorPixels.getWidth()/2. - x) / (doorPixels.getWidth()/2.);
            if (distanceFromCenterY>th) {
                color_.r = color_.r * (1-distanceFromCenterY)/(1.-th);
                color_.g = color_.g * (1-distanceFromCenterY)/(1.-th);
                color_.b = color_.b * (1-distanceFromCenterY)/(1.-th);
            }
            if (distanceFromCenterX>th) {
                color_.r = color_.r * (1-distanceFromCenterX)/(1.-th);
                color_.g = color_.g * (1-distanceFromCenterX)/(1.-th);
                color_.b = color_.b * (1-distanceFromCenterX)/(1.-th);
            }
            doorPixels.setColor(x, y, color_);
        }
    }
    edittedDoorImg.setFromPixels(doorPixels);

    
    dizziness = 0;
    lightRate = 1.;
    lightRateDirection = true;
    dizzinessDirection = false;
    
    planeX = 1100;
    planeY = 720;
    planeZ = 100;
    plane.set(173, 200);
    plane.setPosition(planeX, planeY, planeZ);
    plane.rotate(180, ofVec3f(1, 0, 0));
    
    plane2X = 1160;
    plane2Y = 1150;
    plane2Z = 40;
    plane2.set(128, 170);
    plane2.setPosition(plane2X, plane2Y, plane2Z);
    plane2.rotate(185, ofVec3f(1, 0, 0));
    
    plane3X = 1440;
    plane3Y = 1180;
    plane3Z = 40;
    plane3.set(110, 180);
    plane3.setPosition(plane3X, plane3Y, plane3Z);
    plane3.rotate(180, ofVec3f(1, 0, 0));
    plane3.rotate(-2, ofVec3f(0, 0, 1));
}

//--------------------------------------------------------------
void ofApp::update(){
    movie.update();
    if (lightRateDirection) {
        if(lightRate<1){
            lightRate+=0.01;
        }
    }else{
        if(lightRate>0){
            lightRate-=0.01;
        }
    }
    if (dizzinessDirection) {
        if(dizziness<100){
            dizziness+=1;
        }
    }else{
        if(dizziness>0){
            dizziness-=1;
        }
    }
    if (dizziness==100) {
        planeX = planeX+ofRandom(-0.2, 0.2);
        plane.setPosition(planeX, planeY, planeZ);
        
        plane2Z = plane2Z+ofRandom(-0.1, 0.1);
        plane2.setPosition(plane2X, plane2Y, plane2Z);
        
        plane3Y = plane3Y+ofRandom(-0.1, 0.1);
        plane3.setPosition(plane3X, plane3Y, plane3Z);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(185, 183, 184);
    
    ofSetColor(185+(255-185)*lightRate, 183+(255-183)*lightRate, 184+(255-184)*lightRate, 255-lightRate*50);
    forestImg.draw(0, 0, 1782, 1336.5);
    
    ofSetColor(185+(255-185)*lightRate, 183+(255-183)*lightRate, 184+(255-184)*lightRate, 255-lightRate*255);
    edittedForestImg.draw(0, 0, 1782, 1336.5);

    ofSetColor(185+(255-185)*lightRate, 183+(255-183)*lightRate, 184+(255-184)*lightRate, dizziness-lightRate*20);
    movie.draw(0, 0, 1782, 1336.5);
    
    
    ofSetColor(255, 255, 255, 255*pow(1-lightRate, 3));
    edittedDanchiImg.bind();
    plane.draw();
    edittedDanchiImg.unbind();
    
    ofSetColor(255, 255, 255, 245*pow(1-lightRate, 3));
    edittedElavatorImg.bind();
    plane2.draw();
    edittedElavatorImg.unbind();
    
    ofSetColor(255, 255, 255, 140*pow(1-lightRate, 3));
    edittedDoorImg.bind();
    plane3.draw();
    edittedDoorImg.unbind();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
    case 'd':
        if(dizzinessDirection) {
            dizzinessDirection=false;
        }else{
            dizzinessDirection=true;
        }
        break;
    case 'l':
        if(lightRateDirection) {
            lightRateDirection=false;
        }else{
            lightRateDirection=true;
        }
        break;
    }
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
