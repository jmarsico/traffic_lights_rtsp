#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    ofEnableAlphaBlending();
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(20);
    
    ////////set up the gui
    gui.setup();
    gui.add(bLoadCells.setup("Load Cells"));
    gui.add(bSaveCells.setup("Save Cells"));
    gui.add(cellReset.setup("Clear Cells"));
    gui.add(bShowBinaryMask.setup("Show Mask", false));
    gui.add(reset.setup("Reset Background"));
    gui.add(backgroundThresh.setup("Background Threshold", 21, 0, 255));
    gui.add(learningTime.setup("LearnvTime", 50, 30, 2000));
    gui.add(bReady.setup("Ready for Cells", false));
    gui.add(bLinkCells.setup("Link Cells", true));
    gui.add(lightAmp.setup("Gain", 1.5, 0.5, 10.0));
    gui.add(avgAmt.setup("Smoothing", 5, 1, 100));
    gui.add(bSendOSC.setup("Send OSC", false));
    gui.add(bSendUDP.setup("Send UDP", false));
    gui.add(frameRate.set("Framerate", 0));
    
    gui.setPosition(700, 0);
    gui.loadFromFile("settings.xml");
    
    
    grabber.initGrabber(320, 280);
    
    ////////initialize the LED value vector
    for(int i = 0; i < numLEDs; i++)
    {
        brightVals.push_back(0);
    }
    ofLog() << "size of brightVals array: " << brightVals.size();
    
    ////////set upt he RTSP feed
    // MD feeds: http://www.chart.state.md.us/TravInfo/trafficcams.php#
    /*rtsp.loadMovie("rtsp://170.93.143.140:1935/rtplive/eb0165ea044c0160004806363d235daa", OF_QTKIT_DECODE_PIXELS_AND_TEXTURE, true);
    rtsp.play();
    ofLog() << "size: " << rtsp.getWidth() << " " << rtsp.getHeight();
    
     
     */
    
    sender.setup(HOST, PORT);
    
    //////////initialize all the cells
    for(int i = 0; i < numLEDs; i++)
    {
        cells[i].init(i);
    }
    
    bIsSetting = true;
    bShowVideo = true;
    
    ////////set up XML for points access
    if(myXML.load("cellPoints.xml")) ofLog() << "XML loaded successfully";
    else ofLog() << "XML did not load, check data/ folder";
    
    //create the socket and set to send to 169.254.0.2:11999
	//udpConnection.Create();
	//udpConnection.Connect("169.254.0.2",11999);
	//udpConnection.SetNonBlocking(true);
}

//--------------------------------------------------------------
void testApp::update(){
    frameRate = ofGetFrameRate();
    
    //set background parameters from GUI
    background.setLearningTime(learningTime);
    background.setThresholdValue(backgroundThresh);
    
    //load cells
    if(bSaveCells) saveCellsToXml();
    if(bLoadCells) loadCellsFromXml();
    
    //reset background
    if(reset) background.reset();
    
    if(cellReset)
    {
        for(int i = 0; i < numLEDs; i ++)
        {
            cells[i].reset();
            cells[i].init(i);
            brightVals[i] = 0;
        }
        bReady = false;
    }

    //use rtsp
    if( !bUseLocalVid )
    {
        grabber.update();
        if(grabber.isFrameNew() && grabber.getWidth() > 200)
        {
            grabPix = grabber.getPixelsRef();
            grabPix.resize(grabber.getWidth() * 2, grabber.getHeight()*2);
            background.update(grabPix, thresholded);
            thresholded.update();
            threshPix = thresholded.getPixelsRef();
        }
        else if (grabber.getWidth() < 200)
        {
            ofSetColor(255);
            ofDrawBitmapString("no data", 10,10);
        }
    }
    
    
    //set up a starting point for cells[] array
    if(!bUseLocalVid)start.set(0,0);
    if(bUseLocalVid)start.set(0,0);

    
    
    //----------------- cells -------------------------
    if(bReady)
    {
        //if the first cell in the array is not set, start setting it also, wait for threshPix to have data
        if(!cells[0].isPointsSet() && !cells[0].isSettingPoints())
        {
            cells[0].setPointsFirst(threshPix, start);
        }
        
        //if the first cell is set, use the second setup function
        if(cells[0].isPointsSet())
        {
            //go through each cell, starting with the second
            for(int i = 1; i < numLEDs; i++)
            {
                //if the previous cell is set.
                //if this cell is not in the process of setting points
                //if this cell is not already set up
                if(cells[i-1].isPointsSet() && !cells[i].isSettingPoints() && !cells[i].isPointsSet())
                {
                    //set the first two points of this new cell to the last two points of previous cell
                    if(bLinkCells)
                    {
                        cells[i].setPoints(cells[i-1].p[2], cells[i-1].p[3], threshPix, start);
                    }
                    else
                    {
                        cells[i].setPointsFirst(threshPix, start);
                    }
                }
            }
        }
    }
    
    int averageAmount = avgAmt;
    //if a cell is set, go ahead and start getting its brightness
    for(int i = 0; i < numLEDs; i++)
    {
        if(cells[i].isPointsSet()){
            cells[i].getCellBrightness(threshPix);
            brightVals[i] = cells[i].getAverageBrightness(averageAmount);
        }
    }
    
    if(bSendUDP) sendLights();
    if(bSendOSC) sendOSC();
}

//--------------------------------------------------------------
void testApp::draw(){
    //ofBackground(0);
    
    if(bShowVideo){
        gui.draw();
        ofSetColor(255);
        
        grabPix.draw(0,0);
        
        if(bShowBinaryMask)
        {
            ofPushMatrix();
                if(!bUseLocalVid) ofTranslate(0, 0);
                else if(bUseLocalVid) ofTranslate(0, 0);
                thresholded.draw(0,0);
            ofPopMatrix();
        }
        
        //draw the cells
        for(int i = 0; i < numLEDs; i++)
        {
            cells[i].draw(i);
        }
    }
    
    
    //draw boxes
    int boxSize = ofGetWidth() / (numLEDs + 1);
    ofPushMatrix();
        ofTranslate(boxSize/2, ofGetHeight()-boxSize - 20);
        for(int i = 0; i < numLEDs; i++)
        {
            ofPushMatrix();
                ofTranslate(boxSize*i, 0);
                ofSetColor(brightVals[i]);
                ofRect(0,0,boxSize, boxSize);
                ofSetColor(255);
                ofDrawBitmapString(ofToString(i), 0,0);
            ofPopMatrix();
        }
    ofPopMatrix();
}



//--------------------------------------------------------------
void testApp::loadCellsFromXml(){
   
    ofLog() << "Starting to Load cells from XML...";
 
    for(int i = 0; i < numLEDs; i++)
    {
        myXML.pushTag("CELL", i);
        cells[i].setPointsFirst(threshPix, start);
        
        for(int j = 0; j < 4; j++)
        {
            
            int x = myXML.getValue("PT:X", 0, j);
            int y = myXML.getValue("PT:Y", 0, j);
            
            //set it to the points of that cell and add to the polyline
            cells[i].tempPoint.x = x;
            cells[i].tempPoint.y = y;
            cells[i].addPoint();
            ofLogVerbose() << "loadFromXML: cell[" << i << "]: point.x = " << x;
            ofLogVerbose() << "loadFromXML: cell[" << i << "]: point.y = " << y;
        }
        
        cells[i].bSettingPoints = false;
        cells[i].bIsSet = true;
        cells[i].getPixLocations();
        myXML.popTag();
    }
}

//--------------------------------------------------------------
void testApp::saveCellsToXml(){
    myXML.clear();

    for(int i = 0; i < numLEDs; i++)
    {
        if(cells[i].isPointsSet())
        {
            //create a new cell child
            myXML.addTag("CELL");
            //set location to that cell child
            myXML.pushTag("CELL", i);
            
            //go through points
            for(int j = 0; j < cells[i].p.size(); j++)
            {
                myXML.addTag("PT");
                myXML.pushTag("PT", j);
                myXML.setValue("X", cells[i].p[j].x);
                myXML.setValue("Y", cells[i].p[j].y);
                myXML.popTag();
            }
            myXML.popTag();
        }
    }
    myXML.save("cellPoints.xml");
}


//////////////////////////// RUN LIGHTS //////////////////////////////////
void testApp::sendLights(){
   
    string message = "";
    for(int i = 0; i < numLEDs; i++)
    {
        brightVals[i] = (int)(brightVals[i]*lightAmp);
        if(brightVals[i] > 255)
        {
            brightVals[i] = 255;
        }
        
        message+= ofToString(i) + "|" + ofToString(brightVals[i]) + "[/p]";
        //ofLog() << "index: " << i << " || value: " << brightVals[i];
    }
    udpConnection.Send(message.c_str(),message.length());
    //ofLog() << "Message Length: " << message.length();
    
    
}


///////////////////////// SEND OSC ///////////////////////////////////
void testApp::sendOSC(){
    ofxOscMessage m;
    m.setAddress("/vals");
    string printer;
    
    for(int i = 0; i < numLEDs; i++)
    {
		m.addIntArg(brightVals[i]);
    
    }
    
    sender.sendMessage(m);
    ofLog() << "message: ";
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == ' ')
    {
        bShowVideo = !bShowVideo;
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
