//
//  sampleCell.h
//  traffic_lights_rtsp
//
//  Created by Jakob Marsico on 3/18/14.
//
//

#ifndef __traffic_lights_rtsp__sampleCell__
#define __traffic_lights_rtsp__sampleCell__

#include <iostream>
#include "ofMain.h"

class sampleCell{
public:
    vector <ofPoint> p;
    //p0, p1, p2, p3, tempPoint;
    ofPoint tempPoint;
    vector <int> pixIn;
    int redVal;
    ofPolyline shape;
    int ID;
    
    sampleCell();
    
    void init(int _ID);
    
    void setPoints(ofPoint oldP0, ofPoint oldP1, const ofPixels &_pix, ofPoint _startPoint);
    void setPointsFirst(const ofPixels &_pix, ofPoint _startPoint);
    void draw(int alphaCoeff);
    void reset();
    bool isPointsSet();
    bool isSettingPoints();
    void addPoint();
    
    int getCellAvg(const ofPixels &_pix);
    int total;
    ofPixels pix;
    int startX;
    int startY;
    bool bSettingPoints;
    
    void getPixLocations();
    
    void mouseMoved(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    void mousePressed(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);
  
    
    
protected:
    
    bool bRegisteredEvents;
    bool bIsSet;
    int increment;
    int average;
    int alpha;
    bool secondSet;
};



#endif /* defined(__traffic_lights_rtsp__sampleCell__) */
