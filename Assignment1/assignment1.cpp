/*
 *COSC363 Assignment 1
 *Author: Ryan Beaumont
 *Student ID: 31591316
*/

#include <GL/freeglut.h>
#include <cmath>
#include "loadTGA.h"
#include "loadMeshFile.h"
#define GL_CLAMP_TO_EDGE 0x812F

//Global Variables-------------------------------------------------------------
//Camera Variables
float camY = 3;
float camX = 0;
float camZ = 0;
float angle = -90;
int MOVE_FORWARD = 1;
int MOVE_BACKWARD = -1;
float MOVEMENT_SPEED = 0.5;


//Colours
float white[3] = {1, 1, 1};
float grey[4] = {0.2, 0.2, 0.2, 1.0};
float black[3] = {0,0,0};

//Door Variables
float doorX = 0.5;

//Spotlight Variables
float startingX = 0;
float spotlightX = startingX;
float spotlightZ = -70;
float spotlightAngle = 0;
float lightPosition = spotlightX;
bool spotlightAnim = false;
bool spotlightDirection = false;

//Man Variables
float manZ = -65;
float manX = -10;
float manAngle = 0;
float manArmLegAngle = 0;
bool manAnim = false;
bool manArmLegDirection = true;
bool manTurnAround = false;
bool manRunningBackwards = false;
float manTurning = 0;
float manSpeed = 2;


//plane variables
float rotorAngle = 0;
float planeYRotation = 0;
float planeX = 0;
float planeZ = -65;
bool planeDirection = true;
float planeNegative = 1;
bool planeBackflip = false;
float backflipAngle = 0;
float planeSpeed = 1;
float planeRadius = 10;

//Car Variables
bool carStart = false;
float carAngle = 0;
float carZ = 0;

//Cannonball Variables
float cannonAngle = 30;
float cannonLength = 67.991;
float cannonBallY = cannonLength * sin(cannonAngle/180 * M_PI) + 30;
float cannonBallX = cannonLength * cos(cannonAngle/180 * M_PI) - 20;
float netVelocity = 10;
float velocityx = netVelocity * cos(cannonAngle/180 * M_PI); //X Velocity
float velocityy = netVelocity * sin(cannonAngle/180 * M_PI); //Y Velocity
float g = 9.81; //gravity
bool cannonballFired = false;

//Textures
GLuint skyboxTextures[6];
GLuint textures[3];


//------------------Textures importation--------------------------------
void importSkyboxTextures(){
    glGenTextures(6, skyboxTextures); 	// Create 6 texture ids

    glBindTexture(GL_TEXTURE_2D, skyboxTextures[0]);
    loadTGA("resources/textures/rt.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, skyboxTextures[1]);  //Use this texture
    loadTGA("resources/textures/bk.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, skyboxTextures[2]);  //Use this texture
    loadTGA("resources/textures/lt.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, skyboxTextures[3]);  //Use this texture
    loadTGA("resources/textures/up.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, skyboxTextures[4]);  //Use this texture
    loadTGA("resources/textures/dn.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, skyboxTextures[5]);  //Use this texture
    loadTGA("resources/textures/ft.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

void loadTexture()
{
    importSkyboxTextures();

    glGenTextures(4, textures);

    glBindTexture(GL_TEXTURE_2D, textures[0]);  //Use this texture
    loadTGA("resources/textures/Floor.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, textures[1]);  //Use this texture
    loadTGA("resources/textures/Walls.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);


    glBindTexture(GL_TEXTURE_2D, textures[2]);  //Use this texture
    loadTGA("resources/textures/Sphere.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, textures[3]);  //Use this texture
    loadTGA("resources/textures/Roof.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

//-----------------------Skybox-------------------------------------------
/*
Draw skybox
*/
void drawSkybox () {
    glDisable(GL_LIGHTING);
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, skyboxTextures[0]);
    glBegin(GL_QUADS);
    //Right
        glNormal3f(-1.0, 0.0, 0.0);
        glTexCoord2f(0.0, 1.0);glVertex3f(400, 400, -400);
        glTexCoord2f(0.0, 0.0);glVertex3f(400, -400, -400);
        glTexCoord2f(1.0, 0.0);glVertex3f(400, -400, 400);
        glTexCoord2f(1.0, 1.0);glVertex3f(400, 400, 400);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, skyboxTextures[1]);
    glBegin(GL_QUADS);
    //Back
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(1.0, 1.0);glVertex3f(400, 400, -400);
        glTexCoord2f(1.0, 0.0);glVertex3f(400, -400, -400);
        glTexCoord2f(0.0, 0.0);glVertex3f(-400, -400, -400);
        glTexCoord2f(0.0, 1.0);glVertex3f(-400, 400, -400);
    glEnd();
    //Left
    glBindTexture(GL_TEXTURE_2D, skyboxTextures[2]);
    glBegin(GL_QUADS);
        glNormal3f(1.0, 0.0, 0.0);
        glTexCoord2f(1.0, 1.0);glVertex3f(-400, 400, -400);
        glTexCoord2f(1.0, 0.0);glVertex3f(-400, -400, -400);
        glTexCoord2f(0.0, 0.0);glVertex3f(-400, -400, 400);
        glTexCoord2f(0.0, 1.0);glVertex3f(-400, 400, 400);
    glEnd();
    //Front
    glBindTexture(GL_TEXTURE_2D, skyboxTextures[5]);
    glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, -1.0);
        glTexCoord2f(1.0, 0.0);glVertex3f(-400, -400, 400);
        glTexCoord2f(1.0, 1.0);glVertex3f(-400, 400, 400);
        glTexCoord2f(0.0, 1.0);glVertex3f(400, 400, 400);
        glTexCoord2f(0.0, 0.0);glVertex3f(400, -400, 400);
    glEnd();
    //Top
    glBindTexture(GL_TEXTURE_2D, skyboxTextures[3]);
    glBegin(GL_QUADS);
        glNormal3f(-0.0, -1.0, 0.0);
        glTexCoord2f(0.0, 1.0);glVertex3f(400, 400, -400);
        glTexCoord2f(1.0, 1.0);glVertex3f(-400, 400, -400);
        glTexCoord2f(1.0, 0.0);glVertex3f(-400, 400, 400);
        glTexCoord2f(0.0, 0.0);glVertex3f(400, 400, 400);
    glEnd();
    //Bottom
    glBindTexture(GL_TEXTURE_2D, skyboxTextures[4]);
    glBegin(GL_QUADS);
        glNormal3f(-0.0, -1.0, 0.0);
        glTexCoord2f(0.0, 0.0);glVertex3f(400, -400, -400);
        glTexCoord2f(1.0, 0.0);glVertex3f(-400, -400, -400);
        glTexCoord2f(1.0, 1.0);glVertex3f(-400, -400, 400);
        glTexCoord2f(0.0, 1.0);glVertex3f(400, -400, 400);
    glEnd();
    glEnable(GL_LIGHTING);
}

//-----------------------------------------------------------------------------
/* drawFloor:
 * Draws the floor for the scene.
 * Draws the Floor as many quads of the same colour so that spotlight can appear on the floor.
 * Textures the Quads
*/
void drawFloor() {
    glNormal3f(0, 1, 0);
    glColor4f(0.7, 0.7, 0.7, 1.0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_QUADS);
    for(int i = -50; i < 50; i++)
    {
        for(int j = -100;  j < 10; j++)
        {
            glNormal3f(0.0, 1.0, 0.0);
            glTexCoord2f(0.0, 0.0);glVertex3f(i, 0, j);
            glTexCoord2f(0.0, 1.0);glVertex3f(i, 0, j+1);
            glTexCoord2f(1.0, 1.0);glVertex3f(i+1, 0, j+1);
            glTexCoord2f(1.0, 0.0);glVertex3f(i+1, 0, j);
        }
    }
    glEnd();
}

//--------------------Building Functions-------------------------------
/*
 * This function draws glu draws and textures primitives that make up the front of the building
 * */
void drawFront(){
    glColor3f(0.568, 0.568, 0.568);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
    //Left Side
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0.0, 3.0);glVertex3f(-25, 10, -30);
        glTexCoord2f(0.0, 0.0);glVertex3f(-25, 0, -30);
        glTexCoord2f(10.0, 0.0);glVertex3f(-2, 0, -30);
        glTexCoord2f(10.0, 3.0);glVertex3f(-2, 10, -30);

        glTexCoord2f(0.0, 3.0);glVertex3f(-25, 10, -30.5);
        glTexCoord2f(0.0, 0.0);glVertex3f(-25, 0, -30.5);
        glTexCoord2f(10.0, 0.0);glVertex3f(-2, 0, -30.5);
        glTexCoord2f(10.0, 3.0);glVertex3f(-2, 10, -30.5);
    //Right Side
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(10.0, 0.0);glVertex3f(25, 0, -30);
        glTexCoord2f(0.0, 0.0);glVertex3f(2, 0, -30);
        glTexCoord2f(0.0, 3.0);glVertex3f(2, 10, -30);
        glTexCoord2f(10.0, 3.0);glVertex3f(25, 10, -30);

        glTexCoord2f(10.0, 0.0);glVertex3f(25, 0, -30.5);
        glTexCoord2f(0.0, 0.0);glVertex3f(2, 0, -30.5);
        glTexCoord2f(0.0, 3.0);glVertex3f(2, 10, -30.5);
        glTexCoord2f(10.0, 3.0);glVertex3f(25, 10, -30.5);
    //Middle
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0.0, 3*0.5);glVertex3f(-2, 10, -30);
        glTexCoord2f(0.0, 0.0);glVertex3f(-2, 5, -30);
        glTexCoord2f(10.0*4/22, 0.0);glVertex3f(2, 5, -30);
        glTexCoord2f(10.0*4/22, 3*0.5);glVertex3f(2, 10, -30);

        glTexCoord2f(0.0, 3.0*0.5);glVertex3f(-2, 10, -30.5);
        glTexCoord2f(0.0, 0.0);glVertex3f(-2, 5, -30.5);
        glTexCoord2f(10.0*4/22, 0.0);glVertex3f(2, 5, -30.5);
        glTexCoord2f(10.0*4/22, 3*0.5);glVertex3f(2, 10, -30.5);
    //DoorFrame
        glColor3f(0, 0, 0);
        glNormal3f(0,0,1);
        glVertex3f(-2, 5, -30.5);
        glVertex3f(-2, 5, -30);
        glVertex3f(-2, 0, -30);
        glVertex3f(-2, 0, -30.5);
        glNormal3f(0,0,1);
        glVertex3f(2, 5, -30.5);
        glVertex3f(2, 5, -30);
        glVertex3f(2, 0, -30);
        glVertex3f(2, 0, -30.5);
        glNormal3f(0,1,0);
        glVertex3f(2, 5, -30.5);
        glVertex3f(2, 5, -30);
        glVertex3f(-2, 5, -30);
        glVertex3f(-2, 5, -30.5);
    glEnd();

}

/*
 * This function draws draws and textures glu primitives that make up the left, right and rear sides of the building
 * */
void drawSides(){
    glColor3f(0.568, 0.568, 0.568);
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    glBegin(GL_QUADS);
    //Left Side
        glNormal3f(1,0,0);
        glTexCoord2f(0.0, 3.0);glVertex3f(-25,10,-30);
        glTexCoord2f(0.0, 0.0);glVertex3f(-25,0,-30);
        glTexCoord2f(20.0, 0.0);glVertex3f(-25,0,-80);
        glTexCoord2f(20.0, 3.0);glVertex3f(-25,10,-80);
   //RightSide
        glNormal3f(-1,0,0);
        glTexCoord2f(0.0, 3.0);glVertex3f(25,10,-30);
        glTexCoord2f(0.0, 0.0);glVertex3f(25,0,-30);
        glTexCoord2f(20.0, 0.0);glVertex3f(25,0,-80);
        glTexCoord2f(20.0, 3.0);glVertex3f(25,10,-80);

    //Rear
        glNormal3f(0,0,0);
        glTexCoord2f(0.0, 3.0);glVertex3f(25, 10, -80);
        glTexCoord2f(0.0, 0.0);glVertex3f(25, 0, -80);
        glTexCoord2f(20.0, 0.0);glVertex3f(-25, 0, -80);
        glTexCoord2f(20.0, 3.0);glVertex3f(-25, 10, -80);
    glEnd();
}

/*
 * This function draws glutSolidCubes that act as doors for the building
 * */
void drawDoor(){
    glColor4f(0.7, 0.7, 0.7, 1.0);
    glPushMatrix();
        glScalef(2,5,0.2);
        glTranslatef(doorX, 0.5, -151.5);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glScalef(2,5,0.2);
        glTranslatef(-doorX, 0.5, -151.5);
        glutSolidCube(1);
    glPopMatrix();
}

/*
 * This function draws and textures glu primitives that make up the roof of the building
 * */
void drawRoof(){
    glColor3f(0.568, 0.568, 0.568);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_TRIANGLES);
        glNormal3f(0,0,1);
        glTexCoord2f(10.0,1.5);glVertex3f(0, 15, -30);
        glTexCoord2f(0.0,0.0);glVertex3f(-25, 10, -30);
        glTexCoord2f(20.0,0.0);glVertex3f(25, 10, -30);

        glTexCoord2f(10.0,1.5);glVertex3f(0, 15, -80);
        glTexCoord2f(0.0,0.0);glVertex3f(-25, 10, -80);
        glTexCoord2f(20.0,0.0);glVertex3f(25, 10, -80);
    glEnd();

    //RoofPanels
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glBegin(GL_QUADS);
        glNormal3f(0,-1,0);
        glTexCoord2f(0.0,0.0);glVertex3f(-25, 10, -30);
        glTexCoord2f(30.0,0.0);glVertex3f(-25, 10, -80);
        glTexCoord2f(30.0,5.0);glVertex3f(0, 15, -80);
        glTexCoord2f(0.0,5.0);glVertex3f(0, 15, -30);

        glTexCoord2f(0.0,0.0);glVertex3f(25, 10, -30);
        glTexCoord2f(30.0,0.0);glVertex3f(25, 10, -80);
        glTexCoord2f(30.0,5.0);glVertex3f(0, 15, -80);
        glTexCoord2f(0.0,5.0);glVertex3f(0, 15, -30);
    glEnd();
}


/*
 * drawBuilding call the function needed to fully render the building
 * */
void drawBuilding(){
    glDisable(GL_LIGHTING);
    drawFront();
    drawDoor();
    drawSides();
    drawRoof();
    glEnable(GL_LIGHTING);
}

/*
 * castShadow render the sphere under a spotlight and its planar shadow.
 * */
void castShadow(){
    float shadowMatrix[16] = {15, 0, 0, 0, -15, 0.1, 50, -1, 0, 0, 15, 0, 0, 0, 0, 15 };
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glMultMatrixf(shadowMatrix);
        glColor4f(0.2,0.2,0.2, 1.0);
        glTranslatef(15, 0, -50);
        glutSolidSphere(0.5,50, 20);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glPushMatrix();
        glTranslatef(15, 2, -50);
        glColor3f(0.5, 0, 0.5);
        glutSolidSphere(0.5,50, 20);
    glPopMatrix();
}

//-----------------------------------------------------------------------------
/*
 * Draws the light that swings back and forth
 * */
void drawMovingSpotLight(){
    glColor3f(0.913, 0.858, 0.627);
    glPushMatrix();
        glTranslatef(spotlightX, 15, spotlightZ);
        glRotatef(spotlightAngle, 0, 0, 1);
        glTranslatef(0, -5, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCylinder(0.01, 5, 50, 10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(spotlightX, 15, spotlightZ);
        glRotatef(spotlightAngle, 0, 0, 1);
        glTranslatef(0, -5, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(0.5, 0.5, 50, 10);
    glPopMatrix();
}

/*
 * Draws the man that runs around in circles
 * */
void drawMan () {
    glPushMatrix();
        glTranslatef(0,3.5,0);
        glutSolidSphere(0.3,20, 10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 3.2-0.75, 0);
        glScalef(0.2, 1.5, 0.8);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 3.0, 0);
        glTranslatef(0, 0.0, 0.6);
        glutSolidSphere(0.2,20, 10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 3.0, 0);
        glTranslatef(0, 0.0, -0.6);
        glutSolidSphere(0.2,20, 10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 2.0, 0);
        glTranslatef(0, 1.0, -0.6);
        glRotatef(-manArmLegAngle, 0, 0, 1);
        glTranslatef(0, -1.0, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCylinder(0.05, 1, 20, 10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 2.0, 0);
        glTranslatef(0, 1.0, 0.6);
        glRotatef(manArmLegAngle, 0, 0, 1);
        glTranslatef(0, -1.0, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCylinder(0.05, 1, 20, 10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 0.45, 0);
        glTranslatef(0, 1.25, 0.2);
        glRotatef(-manArmLegAngle, 0, 0, 1);
        glTranslatef(0, -1.25, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCylinder(0.05, 1.25, 20, 10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 0.45, 0);
        glTranslatef(0, 1.25, -0.2);
        glRotatef(manArmLegAngle, 0, 0, 1);
        glTranslatef(0, -1.25, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCylinder(0.05, 1.25, 20, 10);
    glPopMatrix();
}

/*
 * This function draws the plane that flies around using plane.off and rotor.off
 * */
void drawPlane (){
    glTranslatef(0, 3.1, 0);
    glRotatef(planeNegative*backflipAngle, 0, 0, 1);
    glTranslatef(0, -3.1, 0);
    glRotatef(planeNegative * 90, 0, 1, 0);
    glScalef(0.4, 0.4 ,0.4);
    glPushMatrix();
        glTranslatef(0, 0.6, 0);
        drawObjectFromFile("resources/offFiles/plane.off");
    glPopMatrix();

    glTranslatef(0, 0, 3);
    glRotatef(rotorAngle, 0, 0, 1);
    drawObjectFromFile("resources/offFiles/rotor.off");
}

/*
 * Draws the small car that drives around
 * */
void drawCar(){
    glColor3f(0.709, 0.172, 0.2);
    glPushMatrix();
        glTranslatef(0, 1.5, 0);
        glScalef(1, 0.75, 3);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 2.25, -0.5);
        glScalef(1, 0.75, 1);
        glutSolidCube(1);
    glPopMatrix();
    glColor3f(0, 0, 0);
    glPushMatrix();
        glTranslatef(0.45, 1, -0.75);
        glRotatef(90, 0, 1, 0);
        glutSolidCylinder(0.5, 0.2, 20, 20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.45, 1, 0.75);
        glRotatef(90, 0, 1, 0);
        glutSolidCylinder(0.5, 0.2, 20, 20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-0.65, 1, -0.75);
        glRotatef(90, 0, 1, 0);
        glutSolidCylinder(0.5, 0.2, 20, 20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-0.65, 1, 0.75);
        glRotatef(90, 0, 1, 0);
        glutSolidCylinder(0.5, 0.2, 20, 20);
    glPopMatrix();
}

/*
 * Adjusts the angle of the cannon and all other variables dependant on it
 * */
void adjustCannonAngle(float adjustment){
    cannonAngle+= adjustment;
    cannonBallY = cannonLength * sin(cannonAngle/180 * M_PI) + 30;
    cannonBallX = cannonLength * cos(cannonAngle/180 * M_PI) - 20;
    velocityx = netVelocity * cos(cannonAngle/180 * M_PI);
    velocityy = netVelocity * sin(cannonAngle/180 * M_PI);
}

/*
 * Adjusts the velocity of the cannon and all other variables dependant on it
 * */
void adjustCannonVelocity (float adjustment){
    netVelocity += adjustment;
    velocityx = netVelocity * cos(cannonAngle/180 * M_PI);
    velocityy = netVelocity * sin(cannonAngle/180 * M_PI);
}


/*
 * Draws the cannon from Cannon.off and the cannon stand
 * */
void drawCannon(){
    glTranslatef(15, 0, -40);
    glScalef(0.03, 0.03, 0.03);
    glColor3f(0.639, 0.639, 0.639);
    glRotatef(180, 0, 1, 0);
    glPushMatrix();
        glTranslatef(-20, 30, 0);
        glRotatef(cannonAngle, 0, 0, 1);
        glTranslatef(20, -30, 0);
        drawObjectFromFile("resources/offFiles/Cannon.off");
    glPopMatrix();
    glPushMatrix();
        glTranslatef(cannonBallX, cannonBallY, 0);
        glutSolidSphere(5, 36, 18);
    glPopMatrix();
    glColor3f(0.298, 0.192, 0.184);
    glPushMatrix();
        glTranslatef(-10, 5, 17);
        glScalef(80, 10, 6);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-20, 25, 17);
        glScalef(40, 30, 6);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-10, 5, -17);
        glScalef(80, 10, 6);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-20, 25, -17);
        glScalef(40, 30, 6);
        glutSolidCube(1);
    glPopMatrix();
}

/* Display:
 * Contains function calls for generating the scene.
 * */
void display()
{
    float lpos[4] = {0., 10., -20, 1.0};  //light's position
    float spot_pos1[4] = {startingX, 10.0, spotlightZ, 1.0};
    float spot_dir1[3] = {lightPosition, -10, 0};
    float spot_pos2[4] = {15 , 10, -50, 1.0};
    float spot_dir2[3] = {0, -1, 0};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camX, camY, camZ, camX+cos(M_PI*angle/180), camY, camZ+sin(M_PI*angle/180), 0, 1, 0);

    glLightfv(GL_LIGHT0,GL_POSITION, lpos);
    glLightfv(GL_LIGHT1, GL_POSITION, spot_pos1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 50.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20);
    glLightfv(GL_LIGHT2,GL_POSITION, spot_pos2);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_dir2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 90.0);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 20);
    glPushMatrix();
        drawSkybox();
    glPopMatrix();

    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_SPECULAR, black);
        drawFloor();
        drawBuilding();
        glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glPopMatrix();

    glPushMatrix();
        drawMovingSpotLight();
    glPopMatrix();

    glPushMatrix();
        castShadow();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(manX, 0, manZ);
        glRotatef(manAngle, 0, 1, 0);
        glTranslatef(0, 0, 5);
        if(manTurnAround){
            glRotatef(manTurning, 0, 1, 0);
        }
        drawMan();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(planeX, 5, planeZ);
        if(!planeDirection){
            glTranslatef(0, 0, 2*planeRadius);
        }
        glRotatef(planeYRotation, 0, 1, 0);
        glTranslatef(0, 0, planeRadius);
        drawPlane();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-10, 0, -40 + carZ);
        glRotatef(carAngle, 0, 1, 0);
        glTranslatef(-5, 0, 0);
        glScalef(0.75, 0.75, 0.75);
        drawCar();
    glPopMatrix();
    drawCannon();
    glFlush();
    glutSwapBuffers();
}

//-----------------------------------------------------------------------------

/*
 * Sets all the lighting properties for the scene
 * */
void lightingProperties() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glLightfv(GL_LIGHT1, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);

    glLightfv(GL_LIGHT2, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT2, GL_SPECULAR, white);
}

void initialize()
{
    loadTexture();
    glEnable(GL_TEXTURE_2D);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    lightingProperties();

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90., 1., 1., 1000.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//-------------------Camera Movement Functions----------------------------------
/*
 * Performs calculates needed to move the camera and adjust the viewing direction
 * */
void calculateMove(int direction) {
    float lookX = camX+cos(M_PI*angle/180);
    float lookZ = camZ+sin(M_PI*angle/180);
    float moveX = lookX - camX;
    float moveZ = lookZ - camZ;
    if (abs(moveX)>abs(moveZ)){
        moveZ /= abs(moveX);
        moveX /= abs(moveX);
    } else {
        moveX /= abs(moveZ);
        moveZ /= abs(moveZ);
    }
    camX += moveX * direction * MOVEMENT_SPEED;
    camZ += moveZ * direction * MOVEMENT_SPEED;
    if (camZ>10) camZ=10;
    if (camZ<-100) camZ=-100;
    if (camX>50) camX=50;
    if (camX<-50) camX=-50;
}

//------------Animation functions---------------------------------
/*
 * Animates the arm and leg movement of the man
 * */
void manArmLegMovement(){
    if (manArmLegAngle < 20 && manArmLegDirection) {
        manArmLegAngle += 5;
    } else if (manArmLegAngle > -20 && !manArmLegDirection) {
        manArmLegAngle -= 5;
    } else {
        manArmLegDirection = !manArmLegDirection;
    }
}

/*
 * Animates the movement of the spotlight
 * */
void spotlightMovement () {
    if(spotlightAnim) {
        if (spotlightAngle == -30 || spotlightAngle == 30) {
            spotlightDirection = !spotlightDirection;
        }
        if (spotlightDirection) {
            spotlightAngle++;
        } else {
            spotlightAngle--;
        }
        lightPosition = 15 * tan(M_PI * spotlightAngle / 180);
    }
}

/*
 * Animates the movement of the doors
 * */
void doorMovement(){
    if ((camX >= -3 && camX <= 3) && (camZ <= -20 && camZ >= -40)){
        if(doorX < 3) doorX+=0.05;
    } else {
        if(doorX > 0.55) doorX-=0.05;
    }
    if(manAnim) {
        if (manAngle < 360 && manAngle > -360 && !manTurnAround) {
            manArmLegMovement();
            if (!manRunningBackwards){
                manAngle+=manSpeed;
            } else {
                manAngle-=manSpeed;
            }
        } else if (manTurnAround){
            if (manTurning < 180){
                manTurning+=2;
            } else {
                manTurnAround = false;
                manTurning = 0;
                manRunningBackwards = !manRunningBackwards;
                manAngle = 0;
            }
        } else {
            manTurnAround = true;
        }
    }
}

/*
 * Animates the movement of the plane rotor
 * */
void rotorMovement(){
    if (rotorAngle == 360){
        rotorAngle = 6;
    } else {
        rotorAngle+=6;
    }
}

/*
 * Animates the movement of the plane
 * */
void planeMovement(){
    rotorMovement();
    if(!planeBackflip){
        if (planeDirection){
            planeYRotation+=planeSpeed;
        } else {
            planeYRotation-=planeSpeed;
        }
        if (planeYRotation <= -180 || planeYRotation >= 360) {
            planeDirection = !planeDirection;
            if(!planeDirection) {
                planeYRotation = 180;
                planeNegative = -1;
            } else {
                planeNegative = 1;
                planeYRotation = 0;
            }
        }
    } else {
        if (backflipAngle < 360){
            backflipAngle+=planeSpeed * 3;
        } else{
            backflipAngle = 0;
            planeBackflip = false;
        }
    }
}

/*
 * Animates the movement of the cannonball according to the set gravity, velocity and angle parameters.
 * */
void cannonballMovement(){
    if (cannonballFired) {
        if (cannonBallY > 0 && cannonBallY < 200 / 0.03 && cannonBallX < 200 / 0.03) { // / 0.03 to account for scaling of the model
            velocityy -= g / 100;
            cannonBallX += velocityx;
            cannonBallY += velocityy;
        } else {
            cannonBallY = cannonLength * sin(cannonAngle/180 * M_PI) + 30;
            cannonBallX = cannonLength * cos(cannonAngle/180 * M_PI) - 20;
            velocityy = netVelocity * sin(cannonAngle/180 * M_PI);
            cannonballFired = false;
        }
    }
}

//----------------------------------Timer Functions-------------------------------------------
/*
 * Timer for animates that are called every 50 ms
 * */
void timer50ms(int value) {
    spotlightMovement();
    doorMovement();
    glutPostRedisplay();
    glutTimerFunc(50, timer50ms, 0);
}

/*
 * Timer for animates that are called every 10 ms
 * */
void timer10ms (int value){
    planeMovement();
    cannonballMovement();
    glutPostRedisplay();
    glutTimerFunc(10, timer10ms, 0);
}

/*
 * Timer for the car animation.
 * */
void carTimer(int value){
    if (carStart) {
        if (carAngle == 180 && carZ > -10) {
            carZ-=0.1;
        } else if (carAngle == 360 && carZ < 0) {
            carZ+=0.1;
        } else {
            if (carAngle == 360) {
                carAngle = 0;
                carZ = 0;
            }
            carAngle++;
        }
        glutPostRedisplay();
    }
    glutTimerFunc(25, carTimer, 0);
}


/*Special:
 *
*/
void special(int key, int x, int y){
    if(key==GLUT_KEY_LEFT) angle-=2;
    else if(key==GLUT_KEY_RIGHT) angle+=2;
    else if(key==GLUT_KEY_UP) calculateMove(MOVE_FORWARD);
    else if (key==GLUT_KEY_DOWN) calculateMove(MOVE_BACKWARD);
    else if (key==GLUT_KEY_END) exit(0);
    else if (key==GLUT_KEY_PAGE_DOWN && camY > -20) camY-=0.5;
    else if (key==GLUT_KEY_PAGE_UP && camY < 20) camY+=0.5;
    glutPostRedisplay();
}

/*Keyboard:
*/
void keyboard(unsigned char key, int x, int y){
    if (key == 's') spotlightAnim=!spotlightAnim;
    else if (key == 'a') manAnim=!manAnim;
    else if (key == 'b' && !planeBackflip) planeBackflip = true;
    else if (key == 'c') carStart = !carStart;
    else if (key == 'f') cannonballFired = true;
    else if (key == 'u' && !cannonballFired && cannonAngle < 90) adjustCannonAngle(1);
    else if (key == 'j' && !cannonballFired && cannonAngle > 0) adjustCannonAngle(-1);
    else if (key == 'i' && !cannonballFired && netVelocity < 30) adjustCannonVelocity(1);
    else if (key == 'k' && !cannonballFired && netVelocity > 5) adjustCannonVelocity(-1);
    else if (key == 'o' && !cannonballFired && g < 30) g++;
    else if (key == 'l' && !cannonballFired && g > 0) g--;
    else if (key == 'p' && !cannonballFired) g = 9.81;
}

//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("Ryan Beaumont Assignment 1");
   initialize();

   glutDisplayFunc(display);
   glutFullScreen();
   //Keyboard Related glutFuncs
   glutSpecialFunc(special);
   glutKeyboardFunc(keyboard);
   //Timer Funcs
   glutTimerFunc(50, timer50ms, 0);
   glutTimerFunc(10, timer10ms, 0);
   glutTimerFunc(25, carTimer, 0);
   glutMainLoop();
   return 0;
}
