//
//  OscParamTextField.h
//  ofxAbletonLive
//
//  Created by Ben McChesney on 8/17/12.
//
//

#ifndef ofxAbletonLive_OscParamTextField_h
#define ofxAbletonLive_OscParamTextField_h

#include "ofMain.h"
#include "TextField.h"
#include "SimpleRadioButton.h"

class OscParamTextField : public TextField
{
    public :
        OscParamTextField( ) { }
    
    
        virtual void init ( float _x , float _y , float _width , float _height , string fontPath , int fontSize , string _defaultText , ofColor _color = ofColor::white , ofColor _activeColor = ofColor::red , float antiAlias = 4.0f )
        {
            
            activeColor = _activeColor ;
            antiAliasFactor = antiAlias ;
            textBlock.init( fontPath , fontSize , antiAliasFactor ) ;
            defaultText = _defaultText ;
            setText( defaultText ) ;
            //textBlock.setText( defaultText ) ;
            x = _x ;
            y = _y ;
            color = _color ;
            
            bActive = false ;
            activeText = "";
            
            bounds = ofRectangle( _x , _y , _width , _height ) ;
            addPoint( x , y ) ;
            addPoint ( x + _width , y ) ;
            addPoint ( x + _width , y + _height ) ;
            addPoint ( x , y + _height ) ;
            
            radioButtons ;
            
            SimpleRadioButton * activeObj = new SimpleRadioButton( ) ;
            SimpleRadioButton * floatObj = new SimpleRadioButton( ) ;
            SimpleRadioButton * intObj = new SimpleRadioButton( ) ;
            
            float buttonSize = 50 ;
            float spacing = 35 ;
            ofRectangle activeObjRect = ofRectangle( _x + _width + spacing , _y , buttonSize , buttonSize ) ;
            activeObj->setup( 4 , ofVec2f( activeObjRect.x , activeObjRect.y ) ) ;
            activeObj->addPoint( 0 , 0 ) ;
            activeObj->addPoint( 0 + activeObjRect.width , 0  ) ;
            activeObj->addPoint( 0 + activeObjRect.width , 0 + activeObjRect.height  ) ;
            activeObj->addPoint( 0 , 0 + activeObjRect.height ) ;
            activeObj->init( ofColor( 15 ) , "ACTIVE" ) ;
            
            ofRectangle floatObjRect = ofRectangle( _x + _width + spacing * 2 + buttonSize , _y , buttonSize , buttonSize ) ;
            floatObj->setup( 4 , ofVec2f( floatObjRect.x , floatObjRect.y ) ) ;
            floatObj->addPoint( 0 , 0 ) ;
            floatObj->addPoint( 0 + activeObjRect.width , 0  ) ;
            floatObj->addPoint( 0 + activeObjRect.width , 0 + activeObjRect.height  ) ;
            floatObj->addPoint( 0 , 0 + activeObjRect.height ) ;
            floatObj->init( ofColor( 15 ) , "FLOAT" ) ;
            
            ofRectangle intObjRect = ofRectangle( _x + _width + spacing * 3 + buttonSize * 2 , _y , buttonSize , buttonSize ) ;
            intObj->setup( 4 , ofVec2f( intObjRect.x , intObjRect.y ) ) ;
            intObj->addPoint( 0 , 0 ) ;
            intObj->addPoint( 0 + intObjRect.width , 0  ) ;
            intObj->addPoint( 0 + intObjRect.width , 0 + intObjRect.height  ) ;
            intObj->addPoint( 0 , 0 + activeObjRect.height ) ;
            intObj->init( ofColor( 15 ) , "INT" ) ;
            
            intObj->bActive = false ;
            floatObj->bActive = false ;
            activeObj->bActive = false ;
            
            radioButtons.push_back( activeObj ) ;
            radioButtons.push_back( floatObj ) ;
            radioButtons.push_back( intObj ) ;
        }

        virtual void draw ( )
        {
            //baseDraw( ) ;
            
            if ( bActive == true )
            {
                ofSetColor( activeColor , getOFAlpha() * .2 ) ;
                ofRect( bounds ) ;
            }
            
            ofNoFill( ) ;
            ofSetColor ( color , getOFAlpha() ) ;
            ofRect( bounds ) ;
            ofFill( ) ;
            
            ofPushMatrix( ) ;
            ofTranslate( x , y ) ;
            //ofScale ( .5 , .5 ) ;
            textBlock.draw( 0 , 0 ) ;
            
            ofSetColor( 255 , 255 , 255 ) ; 
           
            ofPopMatrix( ) ;
            
            ofSetColor( 255 , 255 , 255 ) ;
            for ( int i = 0 ; i < radioButtons.size() ; i++ )
            {
                radioButtons[ i ]->draw( ) ;
            }
            
            //activeObj->draw( ) ;
            //floatObj->draw( ) ;
            //intObj->draw( ) ;
            cout << "DRAW ME !" << endl ; 
        }
    
        bool input ( float x , float y )
        {
            //If one is already selected
            int hitIndex = -2 ;
            //bool ofxPolygonHitTest::pointInPoly ( vector<ofVec2f> pts , float x , float y )
            for ( int i = 0 ; i < radioButtons.size() ; i++ )
            {
                if ( ofxPolygonHitTest::Instance()->pointInPoly( radioButtons[i]->pts , x , y ) == true )
                {
                    hitIndex = i ; 
                    break ; 
                }
            }
                
            if ( hitIndex >= 0 )
            {
                for ( int p = 0 ; p < radioButtons.size() ; p++ )
                {
                    radioButtons[ p ]->bActive = false ;
                }
                radioButtons[ hitIndex ]->bActive = true ;
            }
            
            if ( ofxPolygonHitTest::Instance()->pointInPoly( pts , x , y ) == true )
            {
                bActive = true ; 
            }
            
            /*
            if ( activeObj.bActive == true || floatObj.bActive == true || intObj.bActive == true )
            {
                
            }*/
        }
    
        vector<SimpleRadioButton*> radioButtons ;

};

#endif
