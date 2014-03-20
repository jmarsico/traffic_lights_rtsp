#Traffic Lights

###Requirements
To run this application, you'll need the ofxAddon ofxGui.  You'll also need to modify the openFrameworks QTKit files (only works on osx).  The modified files are included in this repo. Simply copy these files and place them in libs>video folder.

###QTKit Changes
The modification allows the video window to resize when the rtsp feed resizes. This is a bug with how QTKit in openFrameworks deals with video resizing, refer to this pull request: https://github.com/openframeworks/openFrameworks/pull/2572