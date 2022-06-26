//
//  raindrop.cpp
//  sunsetForest
//
//  Created by keita miyano on 2022/06/26.
//

#include "raindrop.hpp"

raindrop::raindrop() {
    this->x = ofRandom(0,ofGetWidth());
    this->y = ofRandom(0,ofGetHeight());
    this->z = ofRandom(-500,500);
    this->speed = 100;
    this->length = 100;
}

void raindrop::update() {
    this->y = this->y + this->speed;
    if (this->y > ofGetHeight()) {
        this->y = 0;
        this->x = ofRandom(0,ofGetWidth());
        this->z = ofRandom(-500,500);
    }
}

void raindrop::draw() {
    int color_ = ofRandom(0, 255);
    ofSetColor(color_,color_,color_,ofRandom(80, 100));
    polyline.clear();
    polyline.addVertex(this->x, this->y, this->z);
    polyline.addVertex(this->x, this->y+this->length, this->z);
    ofSetLineWidth(ofRandom(0, 3));
    polyline.draw();
    ofSetLineWidth(1);
}
