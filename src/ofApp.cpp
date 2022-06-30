#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofDisableArbTex();
    ofEnableAlphaBlending();
    
    // OSCのセッティング
    tidalSender.setup(HOST, TIDALPORT);
    scSender.setup(HOST, SCPORT);
    
    // SuperColliderで再生予定の音の準備
    ofxOscMessage m;
    // 雨
    m.setAddress("/s_new");
    m.addStringArg("rain");
    m.addIntArg(1000);
    m.addIntArg(1);
    m.addIntArg(0);
    m.addStringArg("amp");
    m.addFloatArg(0.f);
    scSender.sendMessage(m, false);
    m.clear();
    // 森の喧騒
    m.setAddress("/s_new");
    m.addStringArg("sunsetForest");
    m.addIntArg(1001);
    m.addIntArg(1);
    m.addIntArg(0);
    m.addStringArg("amp");
    m.addFloatArg(0.f);
    m.addStringArg("groundNoise");
    m.addFloatArg(0.f);
    scSender.sendMessage(m, false);
    m.clear();
    // 入り口の出現音
    m.setAddress("/s_new");
    m.addStringArg("sine");
    m.addIntArg(1002);
    m.addIntArg(1);
    m.addIntArg(0);
    m.addStringArg("amp");
    m.addFloatArg(0.f);
    m.addStringArg("freq");
    m.addFloatArg(142.65225);
    m.addStringArg("parFreq");
    m.addFloatArg(1.5);
    m.addStringArg("pan2Freq");
    m.addFloatArg(11);
//    m.addStringArg("pan");
//    m.addFloatArg(0.7);
    m.addStringArg("vibratoDepth");
    m.addFloatArg(0.3);
    m.addStringArg("vibratoFreq");
    m.addFloatArg(3);
    m.addStringArg("reverb");
    m.addFloatArg(0.6);
    scSender.sendMessage(m, false);
    m.clear();
    
    // 画像・動画の読み込み
    forestImg.load("forest.jpg");
    seaLevelImg.load("forest640.jpg");
    elavatorImg.load("elavator.jpg");
    danchiImg.load("danchi_trim.jpg");
    doorImg.load("door.jpg");
    movie.load("forest_trim_concat_0.4.mov");
    movie.play();
    // 森
    forestView = 0.f;
    // 雨粒
    maxRaindropCount = 400;
    raindropCount = 0;
    raindrops.resize(maxRaindropCount);
    for (int i=0; i<raindrops.size(); i++) {
        raindrops[i] = new raindrop(&seaLevelY);
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

    forestDirection = false;
    
    dizziness = 0.;
    maxDizziness = 100.;
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
    entranceSoundTimer = ofGetElapsedTimef();
    entranceSoundLifeTime = 20.f; //寿命
    
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
    seaLevelY = (float)ofGetHeight();
    seaLevelZ = ofGetWidth()/2;
    seaLevel.set(ofGetWidth(), ofGetWidth());
    seaLevel.setPosition(seaLevelX, seaLevelY, seaLevelZ);
    seaLevel.rotate(-90, ofVec3f(1, 0, 0));
    seaLevelDirection = false;
    maxSeaLevelY = 830;
}

//--------------------------------------------------------------
void ofApp::update(){
    movie.update();
    for (int i=0; i<raindrops.size(); i++) {
        raindrops[i]->update();
    }
    if(forestDirection){
        if(forestView<1){
            forestView+=0.002;
        }
    }else{
        if(forestView>0){
            forestView-=0.002;
        }
    }
    if (raindropCountDirection) {
        if(raindropCount<maxRaindropCount){
            if (ofRandom(1)<0.375){
                raindropCount+=1;
            }
        }
    }else{
        if(raindropCount>0){
            if (ofRandom(1)<0.375){
                raindropCount-=1;
            }
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
        if(dizziness<maxDizziness){
            dizziness+=0.1;
        }
    }else{
        if(dizziness>0){
            dizziness-=0.1;
        }
    }
    if(seaLevelDirection){
        if(seaLevelY>maxSeaLevelY){
            seaLevelY-=0.25;
        }
    }else{
        if(seaLevelY<ofGetHeight()){
            seaLevelY+=0.25;
        }
    }
    seaLevel.setPosition(seaLevelX, seaLevelY, seaLevelZ);
    if(seaLevelY<=(maxSeaLevelY+ofGetHeight())/2){
        // 入り口が水面の下に入ったら入り口たちは点滅する
        if(ofRandom(100)<1) {
            elavatorOff=true;
            elavatorTimer=ofGetElapsedTimef() + ofRandom(0.f,0.08f);
        }
        if(ofRandom(100)<1) {
            doorOff=true;
            doorTimer=ofGetElapsedTimef() + ofRandom(0.f,0.08f);
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
    
    // 水面をゆらゆらさせる
    ofPixels seaLevelPixels = seaLevelImg.getPixels();
    int filterLevel = 13;
    float waveSpeed = 0.2;
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
    
    // TidalCyclesにOSCメッセージを送る
    ofxOscMessage m;
    // 森の生き物
    m.setAddress("/ctrl");
    m.addStringArg("forest");
    m.addFloatArg(forestView);
    tidalSender.sendMessage(m, false);
    m.clear();
    // 雨量
    m.setAddress("/ctrl");
    m.addStringArg("rainfall");
    m.addFloatArg(ofMap((float)raindropCount, 0.f, (float)maxRaindropCount, 0.f, 1.f, true));
    tidalSender.sendMessage(m, false);
    m.clear();
    // 水位
    m.setAddress("/ctrl");
    m.addStringArg("pond");
    m.addFloatArg(ofMap(seaLevelY, ofGetHeight(), maxSeaLevelY, 0.f, 1.f, true));
    tidalSender.sendMessage(m, false);
    m.clear();
    // 地響き
    m.setAddress("/ctrl");
    m.addStringArg("groundNoise");
    m.addFloatArg(ofMap((float)dizziness, 0.f, (float)maxDizziness, 0.f, 2.5f, true));
    tidalSender.sendMessage(m, false);
    m.clear();
    // SuperColliderにOSCメッセージ送る
    // 地響き
    m.setAddress("/n_set");
    m.addIntArg(1001);
    m.addStringArg("groundNoise");
    m.addFloatArg(ofMap((float)dizziness, 0.f, (float)maxDizziness, 0.f, 0.9f, true));
    scSender.sendMessage(m, false);
    m.clear();
    // 入り口
    m.setAddress("/n_set");
    m.addIntArg(1002);
    m.addStringArg("amp");
    float entranceVol = pow(entranceRate*(1-lightRate), 3)*pow(forestView, 10)*0.05;
    entranceVol = entranceVol * pow((entranceSoundTimer - ofGetElapsedTimef()) / entranceSoundLifeTime, 0.25);
    m.addFloatArg(entranceVol);
    scSender.sendMessage(m, false);
    m.clear();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(185, 183, 184);
    
    ofSetColor(185+(255-185)*lightRate, 183+(255-183)*lightRate, 184+(255-184)*lightRate, (255-lightRate*50)*forestView);
    forestImg.draw(0, 0, 1782, 1336.5);

    ofSetColor(185+(255-185)*lightRate, 183+(255-183)*lightRate, 184+(255-184)*lightRate, (255-lightRate*255)*forestView);
    edittedForestImg.draw(0, 0, 1782, 1336.5);

    ofSetColor(185+(255-185)*lightRate, 183+(255-183)*lightRate, 184+(255-184)*lightRate, dizziness-lightRate*20);
    
    movie.draw(0, 0, 1782, 1336.5);

    if(!danchiOff){
        ofSetColor(255, 255, 255, 255*pow(entranceRate*(1-lightRate), 3)*pow(forestView, 10));
        edittedDanchiImg.bind();
        plane.draw();
        edittedDanchiImg.unbind();
    }
    if(!elavatorOff){
        ofSetColor(255, 255, 255, 240*pow(entranceRate*(1-lightRate), 3)*pow(forestView, 10));
        edittedElavatorImg.bind();
        plane2.draw();
        edittedElavatorImg.unbind();
    }
    if(!doorOff){
        ofSetColor(255, 255, 255, 140*pow(entranceRate*(1-lightRate), 3)*pow(forestView, 10));
        edittedDoorImg.bind();
        plane3.draw();
        edittedDoorImg.unbind();
    }
    ofSetColor(255, 255, 255, 100*((float)(ofGetHeight()-seaLevelY)/(ofGetHeight()-maxSeaLevelY)));
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
            entranceSoundTimer = ofGetElapsedTimef() + entranceSoundLifeTime;
        }
        break;
    case 'f':
        if(forestDirection) {
            forestDirection=false;
            // SuperColliderで再生予定の音の準備
            ofxOscMessage m;
            // 雨
            m.setAddress("/n_set");
            m.addIntArg(1001);
            m.addStringArg("amp");
            m.addFloatArg(0.f);
            scSender.sendMessage(m, false);
            m.clear();
        }else{
            forestDirection=true;
            // SuperColliderで再生予定の音の準備
            ofxOscMessage m;
            // 雨
            m.setAddress("/n_set");
            m.addIntArg(1001);
            m.addStringArg("amp");
            m.addFloatArg(1.f);
            scSender.sendMessage(m, false);
            m.clear();
        }
        break;
    case 'r':
        if(raindropCountDirection) {
            raindropCountDirection=false;
            // SuperColliderで再生予定の音の準備
            ofxOscMessage m;
            // 雨
            m.setAddress("/n_set");
            m.addIntArg(1000);
            m.addStringArg("amp");
            m.addFloatArg(0.f);
            scSender.sendMessage(m, false);
            m.clear();
        }else{
            raindropCountDirection=true;
            // SuperColliderで再生予定の音の準備
            ofxOscMessage m;
            // 雨
            m.setAddress("/n_set");
            m.addIntArg(1000);
            m.addStringArg("amp");
            m.addFloatArg(1.f);
            scSender.sendMessage(m, false);
            m.clear();
        }
        break;
    case 's':
        if(seaLevelDirection){
            seaLevelDirection=false;
        }else{
            seaLevelDirection=true;
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

//--------------------------------------------------------------
void ofApp::exit(){
    // SuperColliderにOSCメッセージを送って停止させる
    ofxOscMessage m;
    // 雨
    m.setAddress("/n_free");
    m.addIntArg(1000);
    scSender.sendMessage(m, false);
    m.clear();
    // 森の喧騒
    m.setAddress("/n_free");
    m.addIntArg(1001);
    scSender.sendMessage(m, false);
    m.clear();
    // 入り口
    m.setAddress("/n_free");
    m.addIntArg(1002);
    scSender.sendMessage(m, false);
    m.clear();
    // TidalCycles側のstateもリセットする
    // 雨量
    m.setAddress("/ctrl");
    m.addStringArg("rainfall");
    m.addFloatArg(0.f);
    tidalSender.sendMessage(m, false);
    m.clear();
    // 森の生き物
    m.setAddress("/ctrl");
    m.addStringArg("forest");
    m.addFloatArg(0.f);
    tidalSender.sendMessage(m, false);
    m.clear();
    // 地鳴り
    m.setAddress("/ctrl");
    m.addStringArg("groundNoise");
    m.addFloatArg(0.f);
    tidalSender.sendMessage(m, false);
    m.clear();
    // 雨量
    m.setAddress("/ctrl");
    m.addStringArg("rainfall");
    m.addFloatArg(0.f);
    tidalSender.sendMessage(m, false);
    m.clear();
    // 水位
    m.setAddress("/ctrl");
    m.addStringArg("pond");
    m.addFloatArg(0.f);
    tidalSender.sendMessage(m, false);
    m.clear();
}
