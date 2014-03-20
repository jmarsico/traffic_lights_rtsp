//
//  sampleCell.cpp
//  traffic_lights_rtsp
//
//  Created by Jakob Marsico on 3/18/14.
//
//

#include "sampleCell.h"

sampleCell::sampleCell(){}

void sampleCell::init(int _ID){
    bSettingPoints = false;
    bRegisteredEvents = false;
    bIsSet = false;
    increment = 0;
    ofLogVerbose() << "cell initialized";
    ID = _ID;
    total = 0;
}


//--------------------------------------------------------------
void sampleCell::addPoint(){

    if(bSettingPoints == true)
    {
        ofLogVerbose() << "cell: " << ID << " increment is: " << increment;
        
        if(increment == 0)
        {
            p0.x = tempPoint.x;
            p0.y = tempPoint.y;
            shape.addVertex(p0);
        
            ofLogVerbose() << "cell: " << ID << " point 0 is: " << p0.x << " " << p0.y;
            
        }
        if(increment == 1)
        {
            p1.x = tempPoint.x;
            p1.y = tempPoint.y;
            shape.addVertex(p1);
            
            ofLogVerbose() << "cell: " << ID << " point 1 is: " << p1.x << " " << p1.y;
        }
        if(increment == 2)
        {
            p2.x = tempPoint.x;
            p2.y = tempPoint.y;
            shape.addVertex(p2);
            
            ofLogVerbose() << "cell: " << ID << " point 2 is: " << p2.x << " " << p2.y;
        }
        if(increment == 3)
        {
            p3.x = tempPoint.x;
            p3.y = tempPoint.y;
            shape.addVertex(p3);
            shape.close();
            bSettingPoints = false;
            bIsSet = true;
            
            ofLogVerbose() << "cell: " << ID << " point 3 is: " << p3.x << " " << p3.y;
            ofLogVerbose() << "bIsSet is true";
            ofUnregisterMouseEvents(this);
        }
        increment ++;
        ofLogVerbose() << "cell: " << ID << " increment is: " << increment;
    }


}

//--------------------------------------------------------------
void sampleCell::setPoints(ofPoint oldP0, ofPoint oldP1){
    bSettingPoints = true;
    secondSet = true;
    if(!bRegisteredEvents) {
        ofRegisterMouseEvents(this); // this will enable our circle class to listen to the mouse events.
        bRegisteredEvents = true;
    }
   
    p0 = oldP0;
    p1 = oldP1;
    shape.addVertex(p0);
    shape.addVertex(p1);
    int increment = 2;
    ofLogVerbose() << "setPoints " << ID << " started with two points";
    ofLogVerbose() << "cell: " << ID << " point 0 is: " << p0.x << " " << p0.y;
    ofLogVerbose() << "cell: " << ID << " point 1 is: " << p1.x << " " << p1.y;
    ofLogVerbose() << "cell: " << ID << " increment is: " << increment;

}

//--------------------------------------------------------------
void sampleCell::setPointsFirst(){
   
    bSettingPoints = true;
    secondSet = false;
    if(!bRegisteredEvents) {
        ofRegisterMouseEvents(this); // this will enable our circle class to listen to the mouse events.
        bRegisteredEvents = true;
    }
    ofLogVerbose() << "i am here!";
    int increment = 0;
    ofLogVerbose() << "setPoints " << ID << " started empty";
}

//--------------------------------------------------------------
void sampleCell::draw(int alphaCoeff){
    alpha = alphaCoeff * 15;
    
    if(bIsSet){
        ofSetColor(255,0,0, alpha);
        ofBeginShape();
            ofVertex(p0);
            ofVertex(p1);
            ofVertex(p2);
            ofVertex(p3);
        ofEndShape();
        
    }
    
    ofSetColor(0, 255, 0);
    shape.draw();
    ofDrawBitmapString(ofToString(average), shape.getCentroid2D().x, shape.getCentroid2D().y);
    
    
}

//--------------------------------------------------------------
void sampleCell::reset(){
    shape.clear();
    ofLogVerbose() << "ID: " << ID << " is RESET";
    increment = 0;
    bIsSet = false;
    setPointsFirst();
}


//--------------------------------------------------------------
void sampleCell::getPixLocations(const ofPixels &_pix, ofPoint _startPoint){
    pix = _pix;
    int startX = _startPoint.x;
    int startY = _startPoint.y;
    
    for(int x = 0; x < pix.getWidth(); x++)
    {
        for(int y = 0; y < pix.getHeight(); y++)
        {
            if(shape.inside(x + startX, y + startY))
            {
                int index = pix.getPixelIndex(x, y);
                pixIn.push_back(index);
            }
        }
    }
    
    ofLogVerbose() << "num of pix in: " << ID <<  " pixIn: " << pixIn.size();
}

//--------------------------------------------------------------
int sampleCell::getCellAvg(const ofPixels &_pix){
    pix = _pix;
    
    for(int i = 0; i < pixIn.size(); i++)
    {
        //ofLogVerbose() << "cell: " << ID << ", Value of pixel " << pixIn[i] << ": " << (int)pix[pixIn[i]];
        
        total = total + (int)pix[pixIn[i]];
    }
    
    average = total / pixIn.size();
    total = 0;
    ofLogVerbose() << "average of cell " << ID << ": " << average;
    return average;
}

//--------------------------------------------------------------
bool sampleCell::isPointsSet(){
    return bIsSet;
}

//--------------------------------------------------------------
bool sampleCell::isSettingPoints(){
    return bSettingPoints;
}

//--------------------------------------------------------------
void sampleCell::mouseMoved(ofMouseEventArgs & args){}
void sampleCell::mouseDragged(ofMouseEventArgs & args){}
void sampleCell::mousePressed(ofMouseEventArgs & args){
    tempPoint.x = args.x;
    tempPoint.y = args.y;
    ofLogVerbose() << "JUST CLICKED cell: " << ID << " increment is: " << increment;
    addPoint();
}
void sampleCell::mouseReleased(ofMouseEventArgs & args){}

