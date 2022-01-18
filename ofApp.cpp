#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();

	int len = 300;
	int width = 1;
	for (int y = -1500; y <= 150; y += width) {

		int start_param = ofMap(ofNoise(y * 0.0008, ofGetFrameNum() * 0.005), 0, 1, 0, 720);
		int end_param = start_param + 70;

		for (int param = start_param; param <= end_param; param++) {

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(this->make_point(len, param), width *  0.5 + y));
			vertices.push_back(glm::vec3(this->make_point(len, param), width * -0.5 + y));

			this->face.addVertices(vertices);

			float value = 0;
			if (y < -500) {

				value = ofMap(y, -500, -1500, 0, 255);
			}

			this->face.addColor(ofColor(value));
			this->face.addColor(ofColor(value));

			if (param > start_param) {

				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 4);
				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 4);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->face.draw();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}