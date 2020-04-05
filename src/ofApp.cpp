#include "ofApp.h"
#include "ofAppRunner.h"
#include "ofGraphics.h"
#include "ofRectangle.h"
#include <atomic>

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(32);

    // --------------------------------------
    // Font setup
    // --------------------------------------
    ofTrueTypeFont::setGlobalDpi(72);
    northstar.load("NorthstarRegular-9lEy.otf", 72);
    northstar.setLineHeight(32);
    northstar.setLetterSpacing(1.0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    drawLabelCenter("Sound Only");
    drawWhiteNoise();
}

void ofApp::drawLabelCenter(string content) {
    float contentW = northstar.stringWidth(content),
          contentH = northstar.stringHeight(content);
    float x = ofGetWidth()  / 2.0 - contentW / 2.0,
          y = ofGetHeight() / 2.0 - contentH / 2.0;

    ofSetColor(labelColor);
    northstar.drawString(content, x, y);
}

void ofApp::drawWhiteNoise() {
    // 8x8のノイズブロックを画面全体に描画する
    // 描画更新は10 frame 毎に更新
    int w = ofGetWidth() / NOISE_BLOCK_W, h = ofGetHeight() / NOISE_BLOCK_H;

    ofEnableAlphaBlending();
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            ofSetColor(ofColor(ofRandom(1.0) * 255, 6));
            ofDrawRectangle(i * NOISE_BLOCK_W, j * NOISE_BLOCK_H, NOISE_BLOCK_W, NOISE_BLOCK_H);
        }
    }
    ofDisableAlphaBlending();
}

void ofApp::audioIn(ofSoundBuffer & inputBuffer) {
}
