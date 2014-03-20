#Traffic Lights

##Overview
This application pulls in rtsp traffic feeds and translates the traffic movements into low resolution, architectural LED display. 

###Requirements
To run this application, you'll need:
- [openFrameworks](http://www.openframeworks.cc/)
- ofxGui (comes with oF 0.8) 
- [ofxCv](https://github.com/kylemcdonald/ofxCv)



###QTKit Changes
You'll also need to modify the openFrameworks QTKit files (not sure about windows or Linux).  The modified files are included in this repo in the QTKit_alt folder. Copy these files and place them in libs>video folder.
The modification allows the video window to resize when the rtsp feed resizes. This is a bug with how QTKit in openFrameworks deals with video resizing, refer to this pull request: https://github.com/openframeworks/openFrameworks/pull/2572


####To Do:
- allow re-sizing of cell polygons
- automate pixel-index capture with each cell
- automate cell averaging with each cell
- fix issue with "second setPoints() function
- comment everything
- add ofxSerial or ofxArduino to send LED values
- write serial->i2c code for sending values to custom LED driver
- improve GUI
