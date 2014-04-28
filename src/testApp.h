#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofEvents.h"
#include "sampleCell.h"
#include "ofxXmlSettings.h"
#include "ofxNetwork.h"


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

    void loadCellsFromXml();
    void saveCellsToXml();
    void sendLights();
    
    
    static const int numLEDs = 10;
    vector <int> brightVals;
    //int avgBrights[numLEDs][5];
    
    ofQTKitPlayer rtsp;
    ofPixels rtspPix;
  
    ofxCv::RunningBackground background;
    ofImage thresholded;
    ofPixels threshPix;
    
    ofVideoGrabber grabber;
    ofPixels grabPix;
    
    ofPoint start;
    
    bool bIsSetting;
    bool bShowVideo;
   
    
    sampleCell cells[numLEDs];
    
    ofxXmlSettings myXML;
    ofxUDPManager udpConnection;
    
    
    
    ofxPanel gui;
    ofxButton bLoadCells;
    ofxButton bSaveCells;
    ofxIntSlider backgroundThresh;
    ofxIntSlider learningTime;
    ofxButton reset;
    ofxToggle bReady;
    ofxToggle bLinkCells;
    ofxToggle bUseLocalVid;
    ofxIntSlider boxSize;
    ofxFloatSlider lightAmp;
    ofxIntSlider avgAmt;

};
