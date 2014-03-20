#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    ofEnableAlphaBlending();
    ofSetLogLevel(OF_LOG_VERBOSE);

    
    gui.setup();
    gui.add(backgroundThresh.setup("bgThresh", 21, 0, 255));
    gui.add(learningTime.setup("learnTime", 50, 30, 2000));
    gui.add(reset.setup("reset background"));
    gui.setPosition(10, ofGetHeight() - 200);
    
    boxSize = 10;
    
    
    
    for(int i = 0; i < numLEDs; i++)
    {
        brights.push_back(0);
    }
    
    
    ofLog() << "size of brights array: " << brights.size();
    
    
    rtsp.loadMovie("rtsp://170.93.143.139:1935/rtplive/1d01d54801280075004d823633235daa", OF_QTKIT_DECODE_PIXELS_AND_TEXTURE, true);

    rtsp.play();
    ofLog() << "size: " << rtsp.getWidth() << " " << rtsp.getHeight();
    
    
    for(int i = 0; i < numLEDs; i++)
    {
        cells[i].init(i);
    }
    
    bIsSetting = true;
    bGetPix = false;
    
    background.setLearningTime(50);
    background.setThresholdValue(200);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    background.setLearningTime(learningTime);
    background.setThresholdValue(backgroundThresh);
    
    if(reset)
    {
        background.reset();
    }
    
    if(!cells[0].isPointsSet() && !cells[0].isSettingPoints()){
        cells[0].setPointsFirst();
    }
    
    if(cells[0].isPointsSet())
    {
        for(int i = 1; i < numLEDs; i++)
        {
            if(cells[i-1].isPointsSet() && !cells[i].isSettingPoints())
            {
                cells[i].setPointsFirst();
            }
        }
    }
        
    rtsp.update();
    if(rtsp.isFrameNew()){
        
        rtspPix = rtsp.getPixelsRef();
        background.update(rtspPix, thresholded);
        thresholded.update();
        
        
    }
    
    if(bGetPix){
        for(int i = 0; i < numLEDs; i++)
        {
            ofPoint start;
            start.set(0,0);
            cells[i].getPixLocations(rtspPix, start);
        }
        bGetPix = false;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    //ofBackground(0);
    gui.draw();
    ofSetColor(255);
   
    ofPushMatrix();
        rtsp.draw(0,0);
        stringstream rtspReport;
        rtspReport
        << "width: " << rtsp.getWidth() << endl
        << "height: " << rtsp.getHeight() << endl
        << "speed: " << rtsp.getSpeed() << endl
        << "numPix" << rtspPix.size() << endl
        << "framerate: " << ofGetFrameRate() << endl;
    
        ofDrawBitmapString(rtspReport.str(), 0, 300);

    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(rtsp.getWidth()+10, 0);
    thresholded.draw(0,0);
    ofPopMatrix();
    
    //draw boxes
    ofPushMatrix();
        ofTranslate(boxSize, ofGetHeight()/2 - boxSize);
        for(int i = 0; i < numLEDs; i++)
        {
            ofPushMatrix();
                ofTranslate(boxSize*i, ofGetHeight()/2 - boxSize);
                ofSetColor(brights[i]);
                ofRect(0,0,boxSize, boxSize);
                ofDrawBitmapString(ofToString(i), 0,0);
            ofPopMatrix();
            
        }
    ofPopMatrix();
    
    //draw the cells
    for(int i = 0; i < numLEDs; i++)
    {
        cells[i].draw(i);
    }
        
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == ' '){
        for(int i = 0; i < numLEDs; i++)
        {
            cells[i].reset();
        }
    }
    
    if(key == 'k'){
        bGetPix = true;
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
