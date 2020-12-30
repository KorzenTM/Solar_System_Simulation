#pragma once

#include "ofMain.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

class Celestial_body
{
private:
    ofVec3f mPositionsVector;
    ofVec3f mMainObjectPositionsVector;
    ofVec3f mVelocityVector;
    ofVec3f mForceVector;
    std::vector<ofVec3f> mPreviusPositionsVector;
    double mWeight;
    double mMainObjectWeight; //if necessary
    int mRadius;
    ofColor mColor;
    ofTexture mTexture;
    ofSpherePrimitive mObject;
    //stałe
    const double dt = 0.1;
    const double Gravitational_constant = 6.67E-11;
public:
    Celestial_body(double radius,double weight, ofVec3f positions, ofVec3f velocities);
    void setTexture(std::string const &texture_location);
    void drawOrbit();
    void drawObject();
    void setCentralPointForLap(const Celestial_body &main_object);
    void update();
    ofVec3f getGravityForce();
    ofVec3f getPositions() const {return mPositionsVector;}
    double getMass() const {return mWeight;}
    ~Celestial_body() {}
};

class ofApp : public ofBaseApp{
private:
    ofEasyCam mCamera;
    ofSpherePrimitive mUniverseSphere; // :)
    ofSoundPlayer mySound;
    ofTexture mUniverseTexture;
public:
    void setup();
    void update();
    void draw();
    //Ustawienie planet (zmudne :()
    Celestial_body SUN{200.0f, 1000000.0f, ofVec3f(0, 0, 0), ofVec3f(0, 0, 0)};
    Celestial_body MERCURY{26, 1200, ofVec3f(800,0,  0), ofVec3f(0, 4, 0)};
    Celestial_body VENUS{35, 1200, ofVec3f(1500, 0, 0), ofVec3f(0, 8, 0)};
    Celestial_body EARTH{37, 2000, ofVec3f(2500,0, 0), ofVec3f(0, 12, 0)};
    Celestial_body MARS{30, 1400, ofVec3f(3000, 0, 0), ofVec3f(0, 16, 0)};
    Celestial_body JUPITER{130, 2100, ofVec3f(3800, 0, 0), ofVec3f(0, 20, 0)};
    Celestial_body SATURN{120, 2000, ofVec3f(4500, 0, 0), ofVec3f(0, 24, 0)};
    Celestial_body URANUS{90, 2400 ,ofVec3f(5300, 0, 0), ofVec3f(0, 28, 0)};
    Celestial_body NEPTUNE{85, 1500, ofVec3f(6000, 0, 0), ofVec3f(0, 32, 0)};
};


