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
    ofPoint p0, p1, p2, p3, tempPoint;
    vector <int> pixIn;
    int redVal;
    ofPolyline shape;
    int ID;
    
    sampleCell();
    
    void init(int _ID);
    
    void setPoints(ofPoint oldP0, ofPoint oldP1);
    void setPointsFirst();
    void draw(int alphaCoeff);
    void reset();
    bool isPointsSet();
    bool isSettingPoints();
    
    int getCellAvg(const ofPixels &_pix);
    int total;
    ofPixels pix;
    
    void getPixLocations(const ofPixels &_pix, ofPoint _startPoint);
    
    void mouseMoved(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    void mousePressed(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);
  
    
    
protected:
    bool bSettingPoints;
    bool bRegisteredEvents;
    bool bIsSet;
    int increment;
    int average;
    int alpha;
    void addPoint();
    bool secondSet;
};



#endif /* defined(__traffic_lights_rtsp__sampleCell__) */
