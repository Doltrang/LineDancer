//
//  Composition.hpp
//  LiveDraw
//
//  Created by lab101 on 06/09/16.
//
//

#ifndef Composition_hpp
#define Composition_hpp

#include <stdio.h>
#include "cinder/Signals.h"
#include "cinder/gl/Shader.h"

//#define magick;
//
//
//#ifdef magick
#include <Magick++.h>
//#endif


typedef std::vector<ci::vec3> pointVec;

class Composition{
   
    std::string                 mCompositionId;
    std::string                 mOutputFolder;
    int                         mImageLayerId;
    int                         mStepId;

    ci::gl::FboRef              mActiveFbo;
    ci::gl::TextureRef          mLastDrawingTexture;
    
    float                       mWindowScale;
    
    float lastDrawDistance      = 0;
    float minDistance           = 0;
        
    
    std::vector<std::string> mGifInputFiles;
    std::vector<pointVec> strokes;
    
    void writeGifStep(std::string fileName);
    void clearFbo();
    void writeDataFile();
    void framesToGif(std::vector<std::string>& paths, std::string gifPath);
    void clearPath();

     ci::gl::GlslProgRef     mOnionShader;


public:
    
    
    ci::signals::Signal<void(pointVec)>   onNewPoints;

    ci::signals::Signal<void(pointVec)> onNewRectangle;
    ci::signals::Signal<void(pointVec)> onNewLine;
    ci::signals::Signal<void(pointVec)> onNewCircle;
    ci::vec2    mSize;
    
    ci::vec3 getNormalisedPositionAtIndex(ci::Path2d& points, ci::Path2d depths,int index);
    ci::vec3 getNormalisedPositionAtIndex(int index);
    
    ci::Path2d mPath;
    ci::Path2d mDepths;
    
    void setup(ci::ivec2 size);
    void newComposition();
    void clearScene(bool clearOnionLayer=false);

    void setNewSize(ci::ivec2 size,float windowScale);
    void setFbo(ci::gl::FboRef& fbo, ci::ivec2 size,float windowScale);
    
    void drawInFbo(std::vector<ci::vec3>& points,ci::ColorA color);
    void calculatePath(ci::Path2d& path,ci::Path2d& depths, bool emmitTrueOrFalse,ci::ColorA color);
    void draw();
    
    
    void newLine(ci::vec3 pressurePoint);
    void lineTo(ci::vec3 pressurePoint,ci::ColorA color);
    void endLine();
    
    void drawRectangle(ci::vec3 point1,ci::vec3 point2, bool recieved, ci::Color color);
    void drawCircle(ci::vec3 point1,ci::vec3 point2, bool recieved, ci::Color color);
    void drawLine(ci::vec3 point1,ci::vec3 point2, bool recieved, ci::Color color);
    void drawFadeOut();
    void emitShape(ci::vec3 point1, ci::vec3 point2);
    
    void saveLineSegmentForGif();
    void saveLayer();
    void writeScreenshot();


    
    ci::gl::TextureRef getTexture();
    void finished();
    void drawFadeout();
    
    bool isInsideComp(ci::vec3 point);
    
};

#endif /* Composition_hpp */
