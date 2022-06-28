//
//  raindrop.hpp
//  sunsetForest
//
//  Created by keita miyano on 2022/06/26.
//

#pragma once

#include "ofMain.h"

class raindrop {
    public:
        float x;
        float y;
        float z;
        float speed;
        float length;
        float height;
        raindrop();
        ~raindrop();
        void update(int seaLevelY);
        void draw();
    private:
        ofPolyline polyline;
};
