#include "ofApp.h"

//Metody klasy celestial_body
Celestial_body::Celestial_body(double radius, double weight, ofVec3f positions, ofVec3f velocities):
    mPositionsVector(positions), mVelocityVector(velocities),  mWeight(weight) , mRadius(radius)
{
    assert(radius > 0);
    mObject.setRadius(mRadius);
    mObject.setResolution(500);
}

void Celestial_body::setTexture(std::string const &texture_location)
{
    ofDisableArbTex();
    ofLoadImage(mTexture, texture_location);
}

void Celestial_body::setCentralPointForLap(const Celestial_body &main_object)
{
    mMainObjectPositionsVector = main_object.getPositions();
    mMainObjectWeight = main_object.getMass();
}

void Celestial_body::update()
{
    mForceVector = getGravityForce();
    mVelocityVector += mForceVector * dt;
    mPositionsVector += mVelocityVector * dt;
    mPreviusPositionsVector.push_back(mPositionsVector);
}

ofVec3f Celestial_body::getGravityForce()
{
    ofVec3f distance = mPositionsVector - mMainObjectPositionsVector;
    ofVec3f normalizedDistance = distance.normalize();
    return -1 * Gravitational_constant * normalizedDistance * mWeight * mMainObjectWeight / distance.length() / distance.length();
}

void Celestial_body::drawObject()
{
    mObject.setPosition(mPositionsVector);
    mTexture.bind();
    if (mTexture.isAllocated())
    {
        mObject.draw();
    }
    mTexture.unbind();
}

void Celestial_body::drawOrbit()
{
    for (size_t i = 0; i < mPreviusPositionsVector.size(); i++)
    {
        if (i == mPreviusPositionsVector.size() - 1)
            break;

        if (mPreviusPositionsVector[i].y == 0) //after one circle erase the orbits
        {
            mPreviusPositionsVector.clear();
            break;
        }

        ofDrawLine(mPreviusPositionsVector[i].x, mPreviusPositionsVector[i].y , mPreviusPositionsVector[i + 1].x, mPreviusPositionsVector[i + 1].y);

    }
}

//Metody klasy ofApp
void ofApp::setup()
{
    ofSetBackgroundColor(0,0,0);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofDisableArbTex();
    ofLoadImage(mUniverseTexture, "space.jpg");

    mUniverseSphere.setRadius(15000);
    mUniverseSphere.setResolution(500);

    mySound.load("music.mp3");
    mySound.play();

    mCamera.setNearClip(100);
    mCamera.setDistance(7000);
    mCamera.setFarClip(200000);

    NEPTUNE.setTexture("neptune.jpg");
    NEPTUNE.setCentralPointForLap(SUN);
    URANUS.setTexture("uranus.jpg");
    URANUS.setCentralPointForLap(SUN);
    SATURN.setTexture("saturn.jpg");
    SATURN.setCentralPointForLap(SUN);
    JUPITER.setTexture("jupiter.jpg");
    JUPITER.setCentralPointForLap(SUN);
    MARS.setTexture("mars.jpg");
    MARS.setCentralPointForLap(SUN);
    EARTH.setTexture("earth.jpg");
    EARTH.setCentralPointForLap(SUN);
    VENUS.setTexture("venus.jpg");
    VENUS.setCentralPointForLap(SUN);
    MERCURY.setTexture("mercury.jpg");
    MERCURY.setCentralPointForLap(SUN);
    SUN.setTexture("sun.jpg");
}

void ofApp::update()
{
    NEPTUNE.update();
    URANUS.update();
    SATURN.update();
    JUPITER.update();
    MARS.update();
    EARTH.update();
    VENUS.update();
    MERCURY.update();
}

void ofApp::draw()
{
    mCamera.begin();
    NEPTUNE.drawOrbit();
    NEPTUNE.drawObject();
    URANUS.drawOrbit();
    URANUS.drawObject();
    SATURN.drawOrbit();
    SATURN.drawObject();
    JUPITER.drawOrbit();
    JUPITER.drawObject();
    MARS.drawOrbit();
    MARS.drawObject();
    EARTH.drawOrbit();
    EARTH.drawObject();
    VENUS.drawOrbit();
    VENUS.drawObject();
    MERCURY.drawObject();
    MERCURY.drawOrbit();
    SUN.drawObject();
    mUniverseSphere.setPosition(0,0,0);
    mUniverseTexture.bind();
    mUniverseSphere.draw();
    mUniverseTexture.unbind();
    mCamera.end();
}


