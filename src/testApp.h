#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofEvents.h"
#include "sampleCell.h"
#include "ofxXmlSettings.h"
#include "ofxNetwork.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345


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
    void sendOSC();
    
    
    static const int numLEDs = 20;
    vector <int> brightVals;
    //int avgBrights[numLEDs][5];
    
    //ofQTKitPlayer rtsp;
    //ofImage rtspPix;
  
    ofxCv::RunningBackground background;
    ofImage thresholded;
    ofPixels threshPix;
    
    ofVideoGrabber grabber;
    ofImage grabPix;
    
    ofPoint start;
    
    bool bIsSetting;
    bool bShowVideo;
   
    
    sampleCell cells[numLEDs];
    
    ofxXmlSettings myXML;
    ofxUDPManager udpConnection;
    
    ofxOscSender sender;
    
    
    
    ofxPanel gui;
    ofxButton bLoadCells;
    ofxButton bSaveCells;
    ofxIntSlider backgroundThresh;
    ofxIntSlider learningTime;
    ofxButton reset;
    ofxButton cellReset;
    ofxToggle bReady;
    ofxToggle bLinkCells;
    ofxToggle bUseLocalVid;
    ofxFloatSlider lightAmp;
    ofxIntSlider avgAmt;
    ofxToggle bShowBinaryMask;
    ofxToggle bSendUDP;
    ofxToggle bSendOSC;
    ofParameter<float> frameRate;

};
