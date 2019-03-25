#include "ofMain.h"
#include "AlgorithmicUrbanComposition.hpp"

AlgorithmicUrbanComposition::LACJsonData d1 {};


//AlgorithmicUrbanComposition::LACJsonData d2 {};
//AlgorithmicUrbanComposition::LACJsonData d3 {};
//AlgorithmicUrbanComposition::LACJsonData d4 {};
//AlgorithmicUrbanComposition::LACJsonData d5 {};
//AlgorithmicUrbanComposition::LACJsonData d6 {};
//AlgorithmicUrbanComposition::LACJsonData d7 {};
//AlgorithmicUrbanComposition::LACJsonData d8 {};
//AlgorithmicUrbanComposition::LACJsonData d9 {};
//AlgorithmicUrbanComposition::LACJsonData d10 {};

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    ofVideoPlayer video;
    
    bool isPlay = false;
    bool isFullScreen = false;
    
    
private:
   int framenumber =0;
};


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    ofSetFullscreen(true);
    ofSetFrameRate(60);
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    //ofSetWindowTitle("LAC AlgorithmicUrbanComposition");
    ofxSubscribeOsc(50000, "/frame_num", [&](ofxOscMessage& m){
        d1.sendOscMessage(m.getArgAsInt(0));
    });
    
    
    d1.load("final.json");
    
    
//    d2.load("1.json");
//    d3.load("2.json");
//    d4.load("3.json");
//    d5.load("4.json");
//    d6.load("5.json");
//    d7.load("6.json");
//    d8.load("7.json");
//    d9.load("8.json");
//    d10.load("9.json");
    
    
    ofBackground(0, 0, 0);
    //    main_output.setName("City Soundscape");
    ofSetFrameRate(60);
    
    const std::string file_path = "final-fullhd.mp4";
    video.load(file_path);
    video.setLoopState(OF_LOOP_NORMAL);
    
    cout << "------- Video property -----" << "\n";
    cout <<  "[WIDTH] " << video.getWidth() << "\n";
    cout <<  "[HEIGHT] " << video.getHeight() << "\n";
    cout << "[FPS] " << video.getTotalNumFrames() << "\n";
    
    
    
//    ofxSubscribeOsc(7777, "/video_toggle", [&](ofxOscMessage& m ){
//        auto val = m.getArgAsBool(0);
//        if ( val ){
            video.play();
//        }else{
//            video.stop();
//        }
//    });
//
//    ofxSubscribeOsc(7777, "/clear",[&](ofxOscMessage& m){
//        video.firstFrame();
//    });
    

}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    if (video.isFrameNew()){
        framenumber++;
         d1.sendOscMessage(framenumber);
        //d2.sendOscMessage(framenumber);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    stringstream ss;
    ss << "ip address : " <<ofToString(AlgorithmicUrbanComposition::HOST) << "\n"
    << "port : " << ofToString(AlgorithmicUrbanComposition::PORT) << "\n";
    
    ofDrawBitmapString(ss.str(), 20, 20);
    ofDrawBitmapString(ofGetFrameRate(), 50, 50);
    video.draw(0, 0, ofGetWidth(), ofGetHeight());
//    ofPushStyle();
//    ofSetColor(255,0,0);
//    ofDrawLine(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight());
//    ofDrawLine(ofGetWidth()/4, 0, ofGetWidth()/4, ofGetHeight());
//    ofDrawLine(ofGetWidth()/4*3, 0, ofGetWidth()/4*3, ofGetHeight());
//    ofDrawLine(0, ofGetHeight()/2, ofGetWidth(), ofGetHeight()/2);
//    ofPopStyle();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}


int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 2);
    settings.setSize(1920,1080);
    settings.decorated = false;
    settings.windowMode = OF_FULLSCREEN;
   settings.multiMonitorFullScreen = false;
    settings.setPosition(ofVec2f(2880,0));
//    settings.decorated = false;
//    auto first_window = ofCreateWindow(settings);
////
//    settings.shareContextWith = first_window;
////    settings.resizable = true;
////    settings.setSize(1920,1080);
////    settings.setPosition(ofVec2f(300,0));
////    settings.decorated = false;
//    auto second_window = ofCreateWindow(settings);
////
////    shared_ptr<ofApp> mainApp(new ofApp);
////    ofRunApp(first_window, mainApp);
////    ofRunApp(second_window, mainApp);
//    ofRunApp(first_window, std::make_shared<ofApp>());
//    ofRunApp(second_window, std::make_shared<ofApp>());
////
//////    shared_ptr<ofApp> mainApp(new ofApp);
//    ofRunMainLoop();
//
//    ofSetupOpenGL(1920,1080,OF_WINDOW);
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
    
}

