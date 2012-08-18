//
//  SimpleRadioButton.h
//  ofxAbletonLive
//
//  Created by Ben McChesney on 8/17/12.
//
//

#ifndef ofxAbletonLive_SimpleRadioButton_h
#define ofxAbletonLive_SimpleRadioButton_h

#include "ofMain.h"
#include "BasePolyObject.h"

class SimpleRadioButton : public BasePolyObject {

    
public:
    SimpleRadioButton( ) { }
    
    
    bool bActive ;
    ofColor color ;
    string label ;

    void init ( ofColor _color , string _label )
    {
        color = _color ;
        label = _label ;
    }

    

    void draw ( )
    {
        //baseDraw( ) ;
        ofSetColor( color ) ;
        
        if ( !bActive )
            ofNoFill( ) ;
        else
            ofFill( ) ; 
        
        
        ofPushMatrix( ) ;
        
        ofBeginShape( ) ;
        for ( int p = 0 ; p < pts.size() ; p++ )
        {
            ofVertex( pts[p].x , pts[p].y ) ;
        }
        ofVertex( pts[0].x , pts[0].y ) ;
        ofEndShape( ) ; 
            //ofRect( pts[0].x , pts[0].y , pts[1].x , pts[2].y ) ;
            
        ofPopMatrix( ) ;
        ofFill( ) ;
        ofDrawBitmapString ( label , pivot.x , pivot.y - 15 ) ;
        
    }

};

#endif
