//
//  sampleCell.cpp
//  traffic_lights_rtsp
//
//  Created by Jakob Marsico on 3/18/14.
//
//

#include "sampleCell.h"

sampleCell::sampleCell(){}

//--------------------------------------------------------------
void sampleCell::init(int _ID){
    bSettingPoints = false;
    bRegisteredEvents = false;
    bIsSet = false;
    ofLogVerbose() << "cell initialized";
    ID = _ID;
    total = 0;
    
    avgCounter = 0;
    
    numSamples = 5;
    
    for(int i = 0; i < numSamples; i++)
    {
        average.push_back(0);
    }
    

}


//--------------------------------------------------------------
void sampleCell::setPoints(ofPoint oldP0, ofPoint oldP1, const ofPixels &_pix, ofPoint _startPoint)
{
    
    pix = _pix;
    startX = _startPoint.x;
    startY = _startPoint.y;
    bSettingPoints = true;
    if(!bRegisteredEvents) {
        ofRegisterMouseEvents(this); // this will enable our circle class to listen to the mouse events.
        bRegisteredEvents = true;
    }
   
    p.push_back(oldP0);
    p.push_back(oldP1);
    shape.addVertex(p[0]);
    shape.addVertex(p[1]);
    
    ofLog() << "*************************************************";
    ofLogVerbose() << "setPoints " << ID << " started with two points";
    ofLogVerbose() << "cell[" << ID << "] p[0] is: " << p[0].x << " " << p[0].y;
    ofLogVerbose() << "cell[" << ID << "] p[1] is: " << p[1].x << " " << p[1].y;

}

void sampleCell::setPixIn(const ofPixels &_pix){
    pix = _pix;
}

//--------------------------------------------------------------
void sampleCell::setPointsFirst(const ofPixels &_pix, ofPoint _startPoint){
    pix = _pix;
    startX = _startPoint.x;
    startY = _startPoint.y;
    bSettingPoints = true;
    if(!bRegisteredEvents) {
        ofRegisterMouseEvents(this); // this will enable our circle class to listen to the mouse events.
        bRegisteredEvents = true;
    }
    ofLog() << "*************************************************";
    ofLogVerbose() << "setPoints " << ID << " started empty";
    ofLogVerbose() << "cell[" << ID << "] has pix: " << pix.size();
}

//--------------------------------------------------------------
void sampleCell::addPoint(){
    
    if(bSettingPoints == true)
    {
        if(p.size() == 0)
        {
            ofPoint temp;
            temp.x = tempPoint.x;
            temp.y = tempPoint.y;
            p.push_back(temp);
            shape.addVertex(p[0]);
            
            ofLogVerbose() << "cell[" << ID << "] point[0] is: " << p[0].x << " " << p[0].x;
            
        }
        else if(p.size() == 1)
        {
            ofPoint temp;
            temp.x = tempPoint.x;
            temp.y = tempPoint.y;
            p.push_back(temp);
            shape.addVertex(p[1]);
            
            ofLogVerbose() << "cell[" << ID << "] point[1] is: " << p[1].x << " " << p[1].y;
        }
        else if(p.size() == 2)
        {
            ofPoint temp;
            temp.x = tempPoint.x;
            temp.y = tempPoint.y;
            p.push_back(temp);
            shape.addVertex(p[2]);
            
            ofLogVerbose() << "cell[" << ID << "] point[2] is: " << p[2].x << " " << p[2].y;
        }
        else if(p.size() == 3)
        {
            ofPoint temp;
            temp.x = tempPoint.x;
            temp.y = tempPoint.y;
            p.push_back(temp);
            shape.addVertex(p[3]);
            shape.close();
            bSettingPoints = false;
            bIsSet = true;
            
            ofLogVerbose() << "cell[" << ID << "] point[3] is: " << p[3].x << " " << p[3].y;
            ofLogVerbose() << "bIsSet is true";
            ofUnregisterMouseEvents(this);
        }
        if(bIsSet)
        {
            getPixLocations();
            
        }
        
    }
    
    
}


//--------------------------------------------------------------
void sampleCell::draw(int alphaCoeff){
    alpha = alphaCoeff * 15;
    
    if(bIsSet){
        ofSetColor(255,0,0, alpha);
        ofBeginShape();
            ofVertex(p[0]);
            ofVertex(p[1]);
            ofVertex(p[2]);
            ofVertex(p[3]);
        ofEndShape();
        
        
        
    }
    
    ofSetColor(0, 255, 0);
    shape.draw();
    ofDrawBitmapString(ofToString(brightness), shape.getCentroid2D().x, shape.getCentroid2D().y);
    
    
}

/*
//--------------------------------------------------------------
void sampleCell::reset(){
    shape.clear();
    ofLogVerbose() << "ID: " << ID << " is RESET";
    bIsSet = false;
    //setPointsFirst();
}
*/

//--------------------------------------------------------------
void sampleCell::getPixLocations(){
    
    //ofLog() << "number of pixels in PIX: " << pix.size();
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
int sampleCell::getCellBrightness(const ofPixels &_pix){
    pix = _pix;
    
    //if pixIn is not empty
    if(pixIn.size() > 0)
    {
        for(int i = 0; i < pixIn.size(); i++)
        {
            total = total + (int)pix[pixIn[i]];
        }
    
        brightness = total / pixIn.size();
        total = 0;
    }
    //ofLogVerbose() << "brightness of cell " << ID << ": " << brightness;
    return brightness;
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
int sampleCell::getAverageBrightness(int _numSamples){
    
    

    numSamples = _numSamples;


    //remove old reading
    runningTotal = runningTotal - average[avgCounter];
    
    //set that lcoation to newest value
    average[avgCounter] = brightness;
    
    //add the newest reading
    runningTotal += average[avgCounter];
    
    //increment the counter (location in vector)
    avgCounter++;
    


    if(avgCounter >= average.size()-1)
    {
        avgCounter = 0;
    }
    
    if(numSamples != average.size())
    {
        
        average.clear();
        runningTotal = 0;
        
        //runningTotal = 0;
        while(numSamples > average.size())
        {
    
            average.push_back(brightness);
        }
        
        while(average.size() > numSamples)
        {
            average.pop_back();
        }
    }
    
    
    if(runningTotal < 0)
    {
        runningTotal = 0;
    }
    
    
    int avge = (int)(runningTotal / average.size());
    
    if(avge > 255)
    {
        avge = 255;
    }

    ofLogVerbose() << "ID: " << ID <<  ": numSamples: " << average.size() << " runningTotal: " << runningTotal
    << " average: " << avge;
    
    
    return avge;
}

//--------------------------------------------------------------
void sampleCell::mouseMoved(ofMouseEventArgs & args){}
void sampleCell::mouseDragged(ofMouseEventArgs & args){}
void sampleCell::mousePressed(ofMouseEventArgs & args){
    tempPoint.x = args.x;
    tempPoint.y = args.y;
    addPoint();
}
void sampleCell::mouseReleased(ofMouseEventArgs & args){}

