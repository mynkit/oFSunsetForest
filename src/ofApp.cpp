#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofDisableArbTex();
    ofEnableAlphaBlending();
    
    forestImg.load("forest.jpg");
    seaLevelImg.load("forest640.jpg");
    elavatorImg.load("elavator.jpg");
    danchiImg.load("danchi_trim.jpg");
    doorImg.load("door.jpg");
    movie.load("forest_trim_concat_0.4.mov");
    movie.play();
    // 雨粒
    maxRaindropCount = 300;
    raindropCount = 0;
    raindrops.resize(maxRaindropCount);
    for (int i=0; i<raindrops.size(); i++) {
        raindrops[i] = new raindrop();
    }
    
    
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
    float th = 0.65;
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
    entranceRate = 0.;
    lightRateDirection = true;
    dizzinessDirection = false;
    entranceRateDirection = false;
    
    elavatorOff = false;
    danchiOff = false;
    doorOff = false;
    elavatorTimer = ofGetElapsedTimef();
    danchiTimer = ofGetElapsedTimef();
    doorTimer = ofGetElapsedTimef();
    
    planeX = 1100;
    planeY = 720;
    planeZ = 100;
    plane.set(173, 200);
    plane.setPosition(planeX, planeY, planeZ);
    plane.rotate(180, ofVec3f(1, 0, 0));
    
    plane2X = 1161;
    plane2Y = 1150;
    plane2Z = 40;
    plane2.set(128, 170);
    plane2.setPosition(plane2X, plane2Y, plane2Z);
    plane2.rotate(185, ofVec3f(1, 0, 0));
    
    plane3X = 1442;
    plane3Y = 1180;
    plane3Z = 40;
    plane3.set(110, 180);
    plane3.setPosition(plane3X, plane3Y, plane3Z);
    plane3.rotate(180, ofVec3f(1, 0, 0));
    plane3.rotate(-2, ofVec3f(0, 0, 1));
    
    seaLevelX = ofGetWidth()/2;
    seaLevelY = ofGetHeight();
    seaLevelZ = ofGetWidth()/2;
    seaLevel.set(ofGetWidth(), ofGetWidth());
    seaLevel.setPosition(seaLevelX, seaLevelY, seaLevelZ);
    seaLevel.rotate(-90, ofVec3f(1, 0, 0));
}

//--------------------------------------------------------------
void ofApp::update(){
    movie.update();
    for (int i=0; i<raindrops.size(); i++) {
        raindrops[i]->update();
    }
    if (raindropCountDirection) {
        if(raindropCount<maxRaindropCount){
            raindropCount+=1;
        }
    }else{
        if(raindropCount>0){
            raindropCount-=1;
        }
    }
    if (lightRateDirection) {
        if(lightRate<1){
            lightRate+=0.005;
        }
    }else{
        if(lightRate>0){
            lightRate-=0.005;
        }
    }
    if (entranceRateDirection) {
        if(entranceRate<1){
            entranceRate+=0.005;
        }
    }else{
        if(entranceRate>0){
            entranceRate-=0.005;
        }
    }
    if (dizzinessDirection) {
        if(dizziness<100){
            dizziness+=1;
        }
        // 目眩し始めたら入り口たちは点滅する
        bool rnd = ofRandom(100)<1;
        if(rnd) {
            elavatorOff=true;
            elavatorTimer=ofGetElapsedTimef() + ofRandom(0.f,0.08f);
            danchiOff=true;
            danchiTimer=ofGetElapsedTimef() + ofRandom(0.f,0.08f);
            doorOff=true;
            doorTimer=ofGetElapsedTimef() + ofRandom(0.f,0.08f);
        }
    }else{
        if(dizziness>0){
            dizziness-=1;
        }
    }
    // タイマーが終了したら入り口消えるの解除
    if(elavatorOff){
        if(elavatorTimer<ofGetElapsedTimef()){
            elavatorOff=false;
        }
    }
    if(danchiOff){
        if(danchiTimer<ofGetElapsedTimef()){
            danchiOff=false;
        }
    }
    if(doorOff){
        if(doorTimer<ofGetElapsedTimef()){
            doorOff=false;
        }
    }
    
    ofPixels seaLevelPixels = seaLevelImg.getPixels();
    int filterLevel = 20;
    float waveSpeed = 0.01;
    for (int y = 0; y < seaLevelPixels.getHeight(); y++) {
        int noise_x = ofMap(ofNoise(y * waveSpeed + ofGetFrameNum() * waveSpeed), 0, 1, -filterLevel, filterLevel);
        noise_x = noise_x * ofMap(y, 0, seaLevelPixels.getHeight(), 1, 0.1);
        if (noise_x > 0) {
            for (int x = seaLevelPixels.getWidth() - 1; x > noise_x; x--) {
                seaLevelPixels.setColor(x, y, seaLevelPixels.getColor(x - noise_x, y));
            }
        }
        else if(noise_x < 0) {
            for (int x = 0; x < seaLevelPixels.getWidth() + noise_x; x++) {
                seaLevelPixels.setColor(x, y, seaLevelPixels.getColor(x - noise_x, y));
            }
        }
    }
    edittedSeaLevelImg.setFromPixels(seaLevelPixels);
 
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

    if(!danchiOff){
        ofSetColor(255, 255, 255, 255*pow(entranceRate*(1-lightRate), 3));
        edittedDanchiImg.bind();
        plane.draw();
        edittedDanchiImg.unbind();
    }
    if(!elavatorOff){
        ofSetColor(255, 255, 255, 240*pow(entranceRate*(1-lightRate), 3));
        edittedElavatorImg.bind();
        plane2.draw();
        edittedElavatorImg.unbind();
    }
    if(!doorOff){
        ofSetColor(255, 255, 255, 140*pow(entranceRate*(1-lightRate), 3));
        edittedDoorImg.bind();
        plane3.draw();
        edittedDoorImg.unbind();
    }
    
    ofSetColor(255, 255, 255, 100);
    edittedSeaLevelImg.bind();
    seaLevel.draw();
    edittedSeaLevelImg.unbind();
    
    for (int i=0; i<raindropCount; i++) {
        raindrops[i]->draw();
    }
    
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
    case 'e':
        if(entranceRateDirection) {
            entranceRateDirection=false;
        }else{
            entranceRateDirection=true;
        }
        break;
    case 'r':
        if(raindropCountDirection) {
            raindropCountDirection=false;
        }else{
            raindropCountDirection=true;
        }
        break;
    case OF_KEY_UP:
        seaLevelY -= 10;
        seaLevel.setPosition(seaLevelX, seaLevelY, seaLevelZ);
        break;
    case OF_KEY_DOWN:
        seaLevelY += 10;
        seaLevel.setPosition(seaLevelX, seaLevelY, seaLevelZ);
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
