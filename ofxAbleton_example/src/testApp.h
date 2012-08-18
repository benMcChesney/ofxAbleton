#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "TextField.h"
#include "OscParamTextField.h"

#define HOST "localhost"
#define SEND_PORT 9000
#define RECEIVE_PORT 9001 
//--------------------------------------------------------
class testApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofTrueTypeFont font;
    
		ofxOscSender sender;
        string lastSentString ; 
    
        ofxOscReceiver receiver ; 
        string lastReceivedString ; 
    
        void sendMessage ( string message ) ;
    
        TextField messageText ;
        OscParamTextField arg1TF ;
        OscParamTextField arg2TF ;
        OscParamTextField arg3TF ;
    
        bool bAbletonPlaying ;
    
        ofPoint mouseDragWindow ;
        ofPoint mouseDragValue ;
        ofPoint mouseDragMax ;
        ofPoint mouseDragMin ;
    
        bool bAttachMouse ;
    
    void disableAllTextFields( ) ; 
        
    
    

};

