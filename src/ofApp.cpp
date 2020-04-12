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

    // --------------------------------------
    // Microphone setup
    // --------------------------------------
    soundStream.printDeviceList();
    // たぶんここらへんでバッファサイズ指定してる
    int bufferSize = 256;
    buffer.assign(bufferSize, 0.0);

    // 入力デバイスの設定をするよ
    ofSoundStreamSettings settings;
    // TODO: GUIから入力デバイスを選択できるようにする
    // auto devices = soundStream.getDeviceList();
    auto devices = soundStream.getMatchingDevices("default");
    if (!devices.empty()) {
        settings.setInDevice(devices[0]);
    }
    settings.setInListener(this);
    settings.sampleRate = 44100; // 44.1[kHz]
    settings.numOutputChannels = 0;
    settings.numInputChannels = 1;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
}


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    drawLabelCenter("Sound Only");
    drawWhiteNoise();

    ofPushStyle();
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2 - 256, 400, 0);

        // ofSetColor(255);
        // ofDrawBitmapString("Buffer", 4, 18);
        //
        // ofSetLineWidth(1);
        // ofDrawRectangle(0, 0, 512, 200);

        ofSetColor(245, 58, 135);
        ofSetLineWidth(3);
            ofBeginShape();
            for (unsigned int i = 0; i < buffer.size(); i++) {
                ofVertex(i*2, 100 - buffer[i] * 180.0f);
            }
            ofEndShape();
        ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 's') { soundStream.start(); }
    else if (key == 'e') { soundStream.stop(); }
}

void ofApp::drawLabelCenter(string content) {
    float contentW = northstar.stringWidth(content),
          contentH = northstar.stringHeight(content);
    float x = ofGetWidth()  / 2.0 - contentW / 2.0,
          y = ofGetHeight() / 2.0 - contentH / 2.0;

    ofPushStyle();
        ofSetColor(labelColor);
        northstar.drawString(content, x, y);
    ofPopStyle();
}

void ofApp::drawWhiteNoise() {
    // 8x8のノイズブロックを画面全体に描画する
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
    float currentVolume = 0.0;
    float numCounted = 0;

    for (size_t i = 0; i < inputBuffer.getNumFrames(); i++) {
        buffer[i] = inputBuffer[i] * 0.5;
        currentVolume += pow(buffer[i], 2);
        numCounted++;
    }

    currentVolume /= (float)numCounted;
    rmsBuffer.push_back(currentVolume);
}
