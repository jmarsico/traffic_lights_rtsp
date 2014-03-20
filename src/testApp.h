#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofEvents.h"
#include "sampleCell.h"


class testApp : public ofBaseApp{

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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);


    //ofVideoGrabber grabber;
    //ofImage greyImage;
    vector <int> brights;
    
    ofQTKitPlayer rtsp;
    ofImage thresholded;
    ofPixels rtspPix;
    ofPixels threshPix;
    ofxCv::RunningBackground background;
    
    ofxPanel gui;
    ofxIntSlider backgroundThresh;
    ofxIntSlider learningTime;
    ofxButton reset;
    ofxButton bGetPix;
    ofxToggle bGetValues;
    int boxSize;
    
    
    bool bIsSetting;
   // bool bGetPix;
    
    static const int numLEDs = 10;
    
    //states
    sampleCell cells[numLEDs];

};
