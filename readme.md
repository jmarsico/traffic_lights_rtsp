#Traffic Lights

###Requirements
To run this application, you'll need:
- ofxAddon ofxGui (comes with oF 0.8) 
- [ofxCv](https://github.com/kylemcdonald/ofxCv).  



###QTKit Changes
You'll also need to modify the openFrameworks QTKit files (not sure about windows or Linux).  The modified files are included in this repo in the QTKit_alt folder. Copy these files and place them in libs>video folder.
The modification allows the video window to resize when the rtsp feed resizes. This is a bug with how QTKit in openFrameworks deals with video resizing, refer to this pull request: https://github.com/openframeworks/openFrameworks/pull/2572