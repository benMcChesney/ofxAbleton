#include "testApp.h"




//--------------------------------------------------------------
void testApp::setup(){

    

//	ofBackground(40, 100, 40);
    ofBackgroundGradient( ofColor( 15 , 15 , 15 ), ofColor( 65 , 65 , 65 ) ) ; 

    //LiveOSC listens on port 9000 and sends data back on 9001
	// open an outgoing connection to HOST:PORT
	sender.setup(HOST, SEND_PORT );
    receiver.setup( RECEIVE_PORT ) ;
    
    messageText.init( 10 , 400 , "type/Batang.ttf" , 16 ) ;
    
    bAbletonPlaying = false ; 
    mouseDragMax = 200 ;
    mouseDragMin = 40 ;
    mouseDragValue = mouseDragMin ;
    
    bAttachMouse = true ;
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
        
        cout << msg_string << endl ; 
        
        lastReceivedString = msg_string ;
    }
    
    messageText.update ( ) ;
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
	// display instructions
	ofDrawBitmapString( "sending osc messages to" + string(HOST) + ofToString( SEND_PORT ) , 10, 20 );
    ofDrawBitmapString( "listening osc messages on " + string(HOST) + ofToString( RECEIVE_PORT ), 10, 35 );
	ofDrawBitmapString( "Last SENT " + lastSentString , 10, 50 );
	ofDrawBitmapString( "last RECEIVED" + lastReceivedString , 10, 65 );
    
    ofSetColor( 255 , 255 , 125 ) ;
    ofLine ( 0 , mouseDragWindow.y , ofGetWidth() , mouseDragWindow.y ) ;
    ofSetColor( 125 , 255 , 255 ) ;
    ofLine ( mouseDragWindow.x , 0 , mouseDragWindow.x , ofGetHeight() ) ;
    
    ofSetColor( 255 , 255 ,255 ) ;
    messageText.draw ( ) ; 
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    //13 is enter
   
    
    switch ( key )
    {
           // if(key == 13)key = '\n';
            
                        
        case 'a':
        case 'A':
            //sendMessage( "/live/play" ) ;
            break ; 
        
        case 'z':
        case 'Z':
            //sendMessage( "/live/stop" ) ;
            break ;
            
        case 13:
            //SEND THE MESSAGE
            sendMessage( messageText.text ) ;
            return ; 
            break ;
            
        case 'm':
        case 'M':
            bAttachMouse = !bAttachMouse ;
            break ; 
    }
    
    //cout << "key pressed!" << key << endl ;
    if(key == 8 || key == 127 )
    {
        /*
         if( pos != 0 ){pos--;
         msgTx = msgTx.substr(0,pos);
         }else msgTx = "";*/
        messageText.backspace() ;
    }
    else{
        if ( key != 32 )
            messageText.text.append(1, (char) key);
        else
        {
            bAbletonPlaying = !bAbletonPlaying ;
            string playbackCommand = "/live/play" ;
            if ( bAbletonPlaying == false )
                playbackCommand = "/live/stop" ;
            
            sendMessage( playbackCommand ) ;
        }
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
    if ( bAttachMouse == true )
    {
        
       m.addFloatArg( mouseDragValue.x );
       lastSentString += " " + ofToString( mouseDragValue ) ;
    }
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

    mouseDragWindow = ofPoint ( x , y ) ;
    mouseDragValue.x = ofMap ( x , 0 , ofGetWidth() , mouseDragMin.x , mouseDragMax.x , true ) ;
    mouseDragValue.y = ofMap ( y , 0 , ofGetHeight() , mouseDragMin.y , mouseDragMax.y , true ) ;
    
    if ( bAttachMouse )
    {
         sendMessage( "/live/tempo" ) ;
    }
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

