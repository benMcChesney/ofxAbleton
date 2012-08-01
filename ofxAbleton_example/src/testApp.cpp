#include "testApp.h"




//--------------------------------------------------------------
void testApp::setup(){

    
	ofBackground(40, 100, 40);

    //LiveOSC listens on port 9000 and sends data back on 9001
	// open an outgoing connection to HOST:PORT
	sender.setup(HOST, SEND_PORT );
    receiver.setup( RECEIVE_PORT ) ; 
}

//--------------------------------------------------------------
void testApp::update(){

    // check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
        string msg_string;
        msg_string = m.getAddress();
        msg_string += ": ";
        for(int i = 0; i < m.getNumArgs(); i++)
        {
            // get the argument type
            msg_string += m.getArgTypeName(i);
            msg_string += ":";
            // display the argument - make sure we get the right type
            if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                msg_string += ofToString(m.getArgAsInt32(i));
            }
            else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                msg_string += ofToString(m.getArgAsFloat(i));
            }
            else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                msg_string += m.getArgAsString(i);
            }
            else{
                msg_string += "unknown";
            }
        }
        
        lastReceivedString = msg_string ; 
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
	// display instructions
	ofDrawBitmapString( "sending osc messages to" + string(HOST) + ofToString( SEND_PORT ) , 10, 20 );
    ofDrawBitmapString( "listening osc messages on " + string(HOST) + ofToString( RECEIVE_PORT ), 10, 35 );
	ofDrawBitmapString( "Last SENT " + lastSentString , 10, 50 );
	ofDrawBitmapString( "last RECEIVED" + lastReceivedString , 10, 65 );
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    
    switch ( key ) 
    {
        case 'a':
        case 'A':
            sendMessage( "/live/play" ) ; 
            break ; 
        
        case 'z':
        case 'Z':
            sendMessage( "/live/stop" ) ; 
            break ; 
    }
    
	if(key == 'a' || key == 'A'){
		
        /*
		m.addIntArg(1);
		m.addFloatArg(3.5f);
		m.addStringArg("hello");
		m.addFloatArg(ofGetElapsedTimef()); */  
			}
    
    //	/live/stop  
}

void testApp::sendMessage ( string message ) 
{
    ofxOscMessage m;
    m.setAddress( message );
    lastSentString = message ; 
    sender.sendMessage(m);
}
//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    /*
	ofxOscMessage m;
	m.setAddress("/mouse/position");
	m.addIntArg(x);
	m.addIntArg(y);
	sender.sendMessage(m); */
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

