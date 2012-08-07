#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "ofMain.h"

class TextField
{
    public:
        TextField() {}
        virtual ~TextField() {}

        float x , y ;
        ofColor color ;

        bool bActive ;      //If the text field is currently listening or being forwarded input events
        string text ;
        string fontPath ;
        int fontSize ;
    
        ofTrueTypeFont font ;
    
        void init ( float _x , float _y , string _fontPath , int _fontSize , ofColor _color = ofColor::white )
        {
            x = _x ;
            y = _y ;
            color = _color ;

            bActive = true ;
            text = "DEFAULT TEXT" ;
            fontPath = _fontPath ;
            fontSize = _fontSize ; 
            font.loadFont( fontPath , fontSize ) ;
        }
    

        void appendText ( string _addition )
        {
            if ( !bActive )
                return ;

            
            if ( text == "" )
            {
                text = _addition ;
            }
            else
            {
                //TODO : max character limit ?
                text += _addition ;
            }
        }

        void backspace ( )
        {
            if ( !bActive )
                return ;

            if ( text.size() > 1 )
            {
                string str = text.substr( 0 , text.size() - 1 ) ;
                text = str ;
            }
            else
            {
                text = "" ;
            }
        }

        void update ( )
        {

        }
        
        void draw ( )
        {
            ofSetColor ( color ) ;
            font.drawString( text , x , y ) ;
        }

    private:
};

#endif // TEXTFIELD_H
