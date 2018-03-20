#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(239);
	ofSetWindowTitle("Insta");

	ofEnableDepthTest();
	ofSetLineWidth(3);
	ofSetCircleResolution(60);

	this->cam.setPosition(ofPoint(0, -620, 100));
	this->cam.setTarget(ofPoint(0, 0, 0));
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	int y;
	int y_span = 72;

	// Draw Line
	for (y = -ofGetHeight() - (ofGetFrameNum() * 5) % y_span; y < ofGetHeight(); y += y_span) {

		ofFill();
		ofSetColor(39);
		ofDrawRectangle(ofPoint(-50, y), 100, 20);
		ofDrawRectangle(ofPoint(-50, y), 5, y_span);
		ofDrawRectangle(ofPoint(45, y), 5, y_span);

		ofSetColor(239);
		ofDrawRectangle(ofPoint(-45, y + 20), 90, y_span - 20);
	}

	// Draw Building
	this->draw_building(50, y_span);
	this->draw_building(-50, y_span);

	// Draw Sun
	ofTranslate(ofPoint(0, ofGetHeight(), 0));
	ofRotateX(90);
	ofFill();
	ofSetColor(139, 0, 0);
	ofDrawCircle(ofPoint(), 500);

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::draw_building(float x, int y_span) {

	int param = ofRandom(393939);

	std::vector<ofPoint> vertices;
	int y = -ofGetHeight() - (ofGetFrameNum() * 5) % y_span;
	vertices.push_back(ofPoint(x, y, 0));
	for (; y < ofGetHeight(); y += y_span) {

		float z = ofMap(ofNoise((y + param) * 0.3 + (ofGetFrameNum() * 5) * 0.3), 0, 1, 30, 250);
		vertices.push_back(ofPoint(x, y, z));
		vertices.push_back(ofPoint(x, y + y_span, z));
	}
	vertices.push_back(ofPoint(x, y, 0));

	ofFill();
	ofSetColor(239);
	ofBeginShape();
	ofVertices(vertices);
	ofEndShape(true);

	ofNoFill();
	ofSetColor(39);
	ofBeginShape();
	ofVertices(vertices);
	ofEndShape(true);
}

//========================================================================
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}

