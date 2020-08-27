//  ========================================================================
//  COSC363: Computer Graphics (2020);  University of Canterbury.
//
//  FILE NAME: Train.cpp
//  See Lab03.pdf for details
//  ========================================================================

#include <math.h>
#include <GL/freeglut.h>
#include "loadTGA.h"
#include "Models.h"

// =========================================================================
#define GL_CLAMP_TO_EDGE 0x812F // From PDF on skybox
#define GRAVITY 9.81

GLuint txId[8]; // Textures

// =================================== LIGHTING VARIABLES =========================================

// LIGHT0 POSITION above chest
float gx0 = 0;
float gy0 = 20;
float gz0 = -130;
float lgt_pos0[] = { gx0, gy0, gz0, 1.0f };


// LIGHT1 is the spotlight 

// LIGHT2 POSITION for the sword
float gx2 = -30;
float gy2 = 30;
float gz2 = -75;
float lgt_pos2[] = { gx2, gy2, gz2, 1.0f };


// LIGHT3 POSITION for outside the building
float gx3 = 0;
float gy3 = 30;
float gz3 = 50;
float lgt_pos3[] = { gx3, gy3, gz3, 1.0f };

// =================================== CAMERA VARIABLES =========================================
double angleCamera = 0;
double look_x = 0.0;
double look_y = 8;
double look_z = -55.0;
double eye_x;
double eye_y = 8;
double eye_z = 90;
double movementAmount = 1.0;
double angleTurnAmount = 0.05;

// ===================================== OTHER VARIABLES =========================================
float spotStringLength = 10;

// ====================================== NOT MODELS =================================================

void loadTexture()
{
    glGenTextures(8, txId); 	// Create 8 texture ids

    glBindTexture(GL_TEXTURE_2D, txId[0]);  //Use this texture
    loadTGA("front.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[1]);  //Use this texture
    loadTGA("back.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[2]);  //Use this texture
    loadTGA("left.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[3]);  //Use this texture
    loadTGA("right.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[4]);  //Use this texture
    loadTGA("bottom.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[5]);  //Use this texture
    loadTGA("top.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[6]);  //Use this texture
    loadTGA("brick.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[7]);		//Use this texture
    loadTGA("sign.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}


void reshape(int width, int height) {
    float aspectCurr = (float)width / (float)height;
    float aspectReqd = 1.0;
    if (aspectCurr > aspectReqd) {
        glViewport(0, 0, height * aspectReqd, height);
    }
    else {
        glViewport(0, 0, width, width / aspectReqd);
    }
}


void normal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
    float nx, ny, nz;
    nx = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
    ny = z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2);
    nz = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);

    glNormal3f(-nx, -ny, -nz);
}


float parabola(float x, float k, float a, float b) {
    // y = k (x + a)^2 + b
    return k * (x + a) * (x + a) + b;
}


float easeOutCubic(float x) {
    return 1.0 - ((1.0 - x) * (1.0 - x) * (1.0 - x));
}


float easeInOutSine(float x) {
    return -(cos(M_PI * x) - 1) / 2;
}


float simplePendulumAngle(float maxAngleDegree, float length, float time) {
    return maxAngleDegree * cos(time * ((2 * M_PI) / (((2 * M_PI * sqrt(length / GRAVITY))))));
}


// ====================================== MODELS =================================================
void floorQuad() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[4]);  // The texture you want to use for the back wall

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex3f(-600, -1, -600);
    glTexCoord2f(0.0, 0.0); glVertex3f(-600, -1, 600);
    glTexCoord2f(1.0, 0.0); glVertex3f(600, -1, 600);
    glTexCoord2f(1.0, 1.0); glVertex3f(600, -1, -600);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}


void skyQuad() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[5]);  // The texture you want to use for the back wall

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-600, 599, -600);
    glTexCoord2f(0.0, 1.0); glVertex3f(-600, 599, 600);
    glTexCoord2f(1.0, 1.0); glVertex3f(600, 599, 600);
    glTexCoord2f(1.0, 0.0); glVertex3f(600, 599, -600);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}


void skybox()
{
    ////////////////////// FLOOR ///////////////////////
    floorQuad();

    ////////////////////// CEILING ///////////////////////
    skyQuad();

    glEnable(GL_TEXTURE_2D);
    ////////////////////// FRONT WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, txId[0]);  
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex3f(-600, 599, -600);
    glTexCoord2f(0.0, 0.0); glVertex3f(-600, -1, -600);
    glTexCoord2f(1.0, 0.0); glVertex3f(600, -1, -600);
    glTexCoord2f(1.0, 1.0); glVertex3f(600, 599, -600);
    glEnd();

    ////////////////////// BACK WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, txId[1]);  
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0); glVertex3f(-600, 599, 600);
    glTexCoord2f(1.0, 0.0); glVertex3f(-600, -1, 600);
    glTexCoord2f(0.0, 0.0); glVertex3f(600, -1, 600);
    glTexCoord2f(0.0, 1.0); glVertex3f(600, 599, 600);
    glEnd();

    ////////////////////// RIGHT WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, txId[3]);  
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0); glVertex3f(-600, 599, -600);
    glTexCoord2f(1.0, 0.0); glVertex3f(-600, -1, -600);
    glTexCoord2f(0.0, 0.0); glVertex3f(-600, -1, 600);
    glTexCoord2f(0.0, 1.0); glVertex3f(-600, 599, 600);
    glEnd();

    ////////////////////// LEFT WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, txId[2]); 
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex3f(600, 599, -600);
    glTexCoord2f(0.0, 0.0); glVertex3f(600, -1, -600);
    glTexCoord2f(1.0, 0.0); glVertex3f(600, -1, 600);
    glTexCoord2f(1.0, 1.0); glVertex3f(600, 599, 600);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


void groundQuads()
{
	float white[4] = {1., 1., 1., 1.};
	float black[4] = {0};
    int sizeW = 160;
    int sizeL = 300;

	glColor4f(0.3, 0.3, 0.3, 1.0);  //The floor is dark grey in colour
	glNormal3f(0.0, 1.0, 0.0);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT2);

	glBegin(GL_QUADS);
	for(int i = -sizeW; i < sizeW; i++)
	{
		for(int j = -sizeL;  j < sizeL; j++)
		{
			glVertex3f(i, 0, j);
			glVertex3f(i, 0, j+1);
			glVertex3f(i+1, 0, j+1);
			glVertex3f(i+1, 0, j);
		}
	}
	glEnd();

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT2);
}


void spotlight() {
    float grey[4] = { 0.2, 0.2, 0.2, 1.0 };
    float white[4] = { 1.0, 1.0, 1.0, 1.0 };
    ///// Actual spotlight
    glEnable(GL_LIGHT1);
    float spotpos[] = { 0, 0, 0 };
    float spotdir[] = {0, -10, 0};
    glLightfv(GL_LIGHT1, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);

    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 100);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdir);

    /// string ///
    glPushMatrix();
    glTranslatef(0, -spotStringLength, 0);

    glPushMatrix();
    glTranslatef(0, (spotStringLength * 0.5) - 1, 0);
    glScalef(0.2, spotStringLength, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix(); // spotlight light actual light
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdir);
    glLightfv(GL_LIGHT1, GL_POSITION, spotpos);
    glPopMatrix();

    ////// Spotlight model ///////
    glPushMatrix();

    glTranslatef(0, -1, 0);
    glRotatef(90, 1, 0, 0);

    GLUquadric* q;
    q = gluNewQuadric();
    gluCylinder(q, 0.5, 1, 3, 50, 50);
    gluQuadricDrawStyle(q, GLU_FILL);

    //// small disk
    gluDisk(q, 0.0, 0.5, 20, 5);

    //// Light disk
    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0, 0, 3);
    gluDisk(q, 0.0, 1, 20, 5);
    glPopMatrix();
    glPopMatrix();


    glPopMatrix();
    glEnable(GL_LIGHTING);
}


void sweepObject(float* vx, float* vy, float* vz, float* wx, float* wy, float* wz, const int N, int nSides) {
    float r_theta = radian(360.0 / nSides);

    for (int j = 0; j < nSides; j++) {
        for (int i = 0; i < N; i++) {
            wx[i] = vx[i] * cos(r_theta) + vz[i] * sin(r_theta);
            wy[i] = vy[i];
            wz[i] = -vx[i] * sin(r_theta) + vz[i] * cos(r_theta);

        }
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < N; i++) {
            if (i > 0) {
                normal(vx[i - 1], vy[i - 1], vz[i - 1],
                    vx[i], vy[i], vz[i],
                    wx[i - 1], wy[i - 1], wz[i - 1]);
            }
            glVertex3f(vx[i], vy[i], vz[i]);

            if (i > 0) {
                normal(wx[i - 1], wy[i - 1], wz[i - 1],
                    vx[i], vy[i], vz[i],
                    wx[i], wy[i], wz[i]);
            }
            glVertex3f(wx[i], wy[i], wz[i]);
        }
        glEnd();

        for (int i = 0; i < N; i++) {
            vx[i] = wx[i];
            vy[i] = wy[i];
            vz[i] = wz[i];
        }
    }
}


void diamond() {

    float white[4] = { 1., 1., 1., 1. };
    float black[4] = { 0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);

    glColor3f(0.35, 0.78, 0.96);
    const int N = 4;  // Total number of vertices on the base curve of the pillar
    float vx_init[N] = { 0, 2, 1, 0 };
    float vy_init[N] = { 0, 2, 3, 3 };
    float vz_init[N] = { 0 };
    float vx[N], vy[N], vz[N];
    float wx[N], wy[N], wz[N];

    for (int i = 0; i < N; i++)		// Initialize data
    {
        vx[i] = vx_init[i];
        vy[i] = vy_init[i];
        vz[i] = vz_init[i];
    }
    sweepObject(vx, vy, vz, wx, wy, wz, N, 6); // not textured
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
}


void pillar(int sides, float height) {
    height = height - 8.5;
    const int N = 44;  // Total number of vertices on the base curve of the pillar
    float vx_init[N] = { 0.000,5.000,4.990,4.960,4.908,4.833,4.732,4.600,4.428,4.200,3.872,3.000,3.000,2.000,2.000,2.010,2.042,2.100,2.200,2.500,2.800,2.900,2.958,2.990,3.000,2.990,2.958,2.900,2.800,2.500,2.500,3.154,3.400,3.571,3.700,3.799,3.875,3.931,3.970,3.992,4.000,5.000,5.000,0.000 };
    float vy_init[N] = { 0,0,0.2,0.4,0.6,0.8,1,1.2,1.4,1.6,1.8,2,3,3,3 + height,3.1 + height,3.2 + height,3.3 + height,3.4 + height,3.5 + height,3.6 + height,3.7 + height,3.8 + height,3.9 + height,4 + height,4.1 + height,4.2 + height,4.3 + height,4.4 + height,3.9 + height,5 + height,5.15 + height,5.3 + height,5.45 + height,5.6 + height,5.75 + height,5.9 + height,6.05 + height,6.2 + height,6.35 + height,6.5 + height,6.5 + height,8.5 + height,8.5 + height };
    float vz_init[N] = { 0 };
    float vx[N], vy[N], vz[N];
    float wx[N], wy[N], wz[N];

    for (int i = 0; i < N; i++)		// Initialize data
    {
        vx[i] = vx_init[i];
        vy[i] = vy_init[i];
        vz[i] = vz_init[i];
    }

    sweepObject(vx, vy, vz, wx, wy, wz, N, sides);
}


void wallDecal() {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.7);
    glBindTexture(GL_TEXTURE_2D, txId[6]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
    glTexCoord2f(1.0, 0.0); glVertex3f(65, 0, 0);
    glTexCoord2f(1.0, 1.0); glVertex3f(65, 72.6, 0);
    glTexCoord2f(0.0, 1.0); glVertex3f(0, 72.6, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);
}


void wallDecal2() {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.7);
    glBindTexture(GL_TEXTURE_2D, txId[6]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
    glTexCoord2f(1.0, 0.0); glVertex3f(65, 0, 0);
    glTexCoord2f(1.0, 0.25); glVertex3f(65, 18, 0);
    glTexCoord2f(0.0, 0.25); glVertex3f(0, 18, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);
}


void sign() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[7]);
    glPushMatrix();
    glScalef(0.3, -0.3, -0.3);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex3f(-17, 9, 0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-17, -9, 0);
    glTexCoord2f(1.0, 0.0); glVertex3f(17, -9, 0);
    glTexCoord2f(1.0, 1.0); glVertex3f(17, 9, 0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void building() {
    glEnable(GL_LIGHT0);
    glColor4f(0.7, 0.7, 0.7, 1.0);

    // sign
    glPushMatrix();
    glTranslatef(0, 24.5, -8.8);
    sign();
    glPopMatrix();

    // Inside pillars
    glPushMatrix();
    glTranslatef(-34, 0, -150);
    pillar(50, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(34, 0, -150);
    pillar(50, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-34, 0, -100);
    pillar(50, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(34, 0, -100);
    pillar(50, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-34, 0, -50);
    pillar(50, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(34, 0, -50);
    pillar(50, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-34, 0, -16);
    pillar(50, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(34, 0, -16);
    pillar(50, 30);
    glPopMatrix();

    // Front pillars
    
    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT3);

    glPushMatrix();
    glTranslatef(-15, 30, 0);
    glRotatef(45, 0, 1, 0);
    glScalef(1, -1, 1);
    pillar(50, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, 30, 0);
    glRotatef(45, 0, 1, 0);
    glScalef(-1, -1, 1);
    pillar(50, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(40, 30, 0);
    glRotatef(45, 0, 1, 0);
    glScalef(-1, -1, 1);
    pillar(50, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-40, 30, 0);
    glRotatef(45, 0, 1, 0);
    glScalef(-1, -1, 1);
    pillar(50, 30);
    glPopMatrix();
    

    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT0);


    // Front walls
    glPushMatrix();
    glTranslatef(-25, 15, -9.95);

    glScalef(31, 30, 1);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(25, 15, -9.95);
    glScalef(31, 30, 1);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 25, -9.95);
    glScalef(20, 10, 1);
    glutSolidCube(1.0);
    glPopMatrix();

    glDisable(GL_LIGHT3);    

    // side walls
    glPushMatrix();
    glTranslatef(-40, 15, -85);
    glScalef(1, 30, 151);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-40.51, 15, -85);

    glBegin(GL_QUADS);
    glVertex3f(0, -15, -75.5);
    glVertex3f(0, -15, 75.5);
    glVertex3f(0, 15, 75.5);
    glVertex3f(0, 15, -75.5);
    glEnd();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(40, 15, -85);
    glScalef(1, 30, 151);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(40.51, 15, -85);

    glBegin(GL_QUADS);
    glVertex3f(0, -15, -75.5);
    glVertex3f(0, -15, 75.5);
    glVertex3f(0, 15, 75.5);
    glVertex3f(0, 15, -75.5);
    glEnd();

    glPopMatrix();

    // Back wall
    glPushMatrix();
    glTranslatef(0, 15, -160);
    glScalef(80, 30, 1);
    glutSolidCube(1.0);
    glPopMatrix();

    // Ceiling
    glEnable(GL_LIGHT3);
    glPushMatrix();
    glTranslatef(0, 32, -80);
    glScalef(90, 4, 170);
    glutSolidCube(1.0);
    glPopMatrix();
    glDisable(GL_LIGHT0);

    glPushMatrix();
    glTranslatef(0, 34, -80);
    glScalef(95, 3, 175);
    glutSolidCube(1.0);
    glPopMatrix();
    glDisable(GL_LIGHT3);

    glEnable(GL_LIGHT0);
    glPushMatrix();
    glTranslatef(0, 30, -85);
    glScalef(80, 1, 150);
    glutSolidCube(1.0);
    glPopMatrix();
    glDisable(GL_LIGHT0);

    // Ground
    glPushMatrix();
    glTranslatef(0, -0.1, -85);
    glScalef(0.25, 1, 0.25);
    groundQuads();
    glPopMatrix();

    // Decals
    // Right front
    glPushMatrix();
    glTranslatef(10, -1.5, -9.4);
    glScalef(0.45, 0.5, 1);
    wallDecal();
    glPopMatrix();

    // Left front
    glPushMatrix();
    glTranslatef(-40, -1.5, -9.4);
    glScalef(0.45, 0.5, 1);
    wallDecal();
    glPopMatrix();
   
    // Top front
    glPushMatrix();
    glTranslatef(-10, 20, -9.4);
    glScalef(0.35, 0.5, 1);
    wallDecal2();
    glPopMatrix();
}

// ====================================== PARTICLES  ========================================================

float sparklez = 1; 

const int SPARKLEZN = 15;
float sparklezX[SPARKLEZN] = { 0 };
float sparklezY[SPARKLEZN] = { 0 };
float sparklezZ[SPARKLEZN] = { 0 };
float sparklezT[SPARKLEZN] = { 0 };
float sparklezC[SPARKLEZN] = { 0 };


void initSparklez() {
    for (int i = 0; i < SPARKLEZN; i++) {
        sparklezX[i] = rand() % 5;
        sparklezY[i] = rand() % 30;
        sparklezZ[i] = rand() % 10;
        sparklezT[i] = (rand() % 10) / 10.0;
        sparklezC[i] = 0.05;
    }
}

void particles() {
    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT3);

    for (int i = 0; i < SPARKLEZN; i++) {
        glColor4f(1.0, 1.0, 1.0, sparklezT[i]);
        glPushMatrix();
        glTranslatef(sparklezX[i], sparklezY[i], sparklezZ[i]);
        glScalef(0.15, 0.25, 0.15);
        glutSolidOctahedron();
        glPopMatrix();
    }

    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT3);

    // Disable blending
    glDisable(GL_BLEND);
}


// ====================================== ANIMATION-RELATED ================================================= 


// -------------------------- CHEST-RELATED ------------------------------ //
int normalChestOpened = 0; // 0 nope, 1 opening, 2 opened
float normalChestOpenedAngle = 0; // 146 degrees the lid hits the ground
float maxOpenAngle = 146;
float openTimer = 0;
// Diamond 
float diamondRotate = 0;
float diamondHeight = 5;
float diamondMaxHeight = 6;
float diamondMinHeight = 4;
float diamondHeightChange = 0.1;

// -------------------------- MIMIC-RELATED ------------------------------ //
int mimicActivated = 0; // 0 nope, 1 opening, 2 idle CLOSING, 3 idle OPENIUNG
float mimicTimer = 0;
float mimicOpenAngle = 0;
float mimicMaxOpenAngle = 45.0;
float mimicMinIdleAngle = 15.0;


// -------------------------- SWORD-RELATED ------------------------------ //
int swordActivated = 0; // 0 nope, 1 wobble , 2 pull out, 3 idle
float swordTimer = 0;
float swordHeight = 0;
float swordAngle = -5; // side to side angle
float swordRotation = 0; // actual rotation
float swordMaxIdleHeight = 12;
float swordMinIdleHeight = 8;
float swordHeightChange = 0.1;
float swordMinAngle = -7;
float swordMaxAngle = -3;
float swordAngleChange = 1;

// -------------------------- LAMP-RELATED ------------------------------ //
float lampTimer = 0;
float lampAngle = 0;
float lampMaxAngle = 10;

// ------------------------- PARTICLE ANIMATION ------------------------- //
void animateParticles() {
    if (sparklez == 1) {
        for (int i = 0; i < SPARKLEZN; i++) {
            // if the sparkle reaches y = 0 or completely transparent randomise it again
            if (sparklezY[i] <= 0 || sparklezT[i] <= 0) {
                sparklezX[i] = rand() % 5;
                sparklezY[i] = rand() % 30;
                sparklezZ[i] = rand() % 10;
                sparklezT[i] = 0;
                sparklezC[i] = 0.05;
            }

            if (sparklezT[i] >= 1) {
                sparklezC[i] = -sparklezC[i];
            }
            sparklezY[i] -= 0.1;
            sparklezT[i] += sparklezC[i];
        }
    }
}

// ------------------------- LAMP ANIMATION ------------------------- //
void animateLamp() {
    lampTimer += 0.050; // 50ms
    lampAngle = simplePendulumAngle(lampMaxAngle, spotStringLength / 10.0, lampTimer);
}

// ------------------------- CHEST ANIMATION ------------------------- //
void animateChest() {
    if (normalChestOpened >= 1) {

        // ------------------ DIAMOND ------------------- //
        if (diamondHeight >= diamondMaxHeight || diamondHeight <= diamondMinHeight) {
            diamondHeightChange = -diamondHeightChange;
        }

        diamondHeight += diamondHeightChange;
        diamondRotate += 2;
    }

    if (normalChestOpened == 1) {


        openTimer += 0.5;
        if (openTimer <= 8.5) { // Initial open
            normalChestOpenedAngle = parabola(openTimer, 2, 0, 0);
        }
        else if (openTimer <= 18) { // First bounce
            normalChestOpenedAngle = parabola(openTimer, 2, -sqrt(23) - sqrt(73), 100);
        }
        else { // Second bounce
            normalChestOpenedAngle = parabola(openTimer, 2, -sqrt(8) - sqrt(23) - sqrt(23) - sqrt(73), 130);

            if (normalChestOpenedAngle >= maxOpenAngle) {
                normalChestOpenedAngle = maxOpenAngle;
                normalChestOpened = 2;
            }
        }
        if (normalChestOpenedAngle > maxOpenAngle) { // Just makes sure the angle isnt more than the max angle so doesnt clip through the floor
            normalChestOpenedAngle = maxOpenAngle;
        }
    }
}
// ------------------------- MIMIC ANIMATION ------------------------- //
void animateMimic() {
    if (mimicActivated == 1) {
        mimicOpenAngle = easeOutCubic(mimicTimer) * mimicMaxOpenAngle;
        mimicTimer += 0.1;
        if (mimicOpenAngle >= mimicMaxOpenAngle) {
            mimicActivated = 2;
        }
    }
    else if (mimicActivated == 2) {

        mimicOpenAngle -= 2;


        if (mimicOpenAngle <= mimicMinIdleAngle) {
            mimicTimer = 0;
            mimicActivated = 3;
        }
    }
    else if (mimicActivated == 3) {

        mimicOpenAngle = easeInOutSine(mimicTimer) * mimicMaxOpenAngle + mimicMinIdleAngle;

        mimicTimer += 0.05;

        if (mimicOpenAngle >= mimicMaxOpenAngle) {
            mimicActivated = 2;
        }

    }
}

// ------------------------- SWORD ANIMATION ------------------------- //
void animateSword() {
    if (swordActivated == 1) {
        swordTimer += 0.1;
        if (swordAngle >= swordMaxAngle || swordAngle <= swordMinAngle) {
            swordAngleChange = -swordAngleChange;

        }
        swordAngle += swordAngleChange;


        if (swordTimer >= 1) {
            swordTimer = 0;
            swordActivated = 2;
        }

    }
    else if (swordActivated == 2) {
        swordHeight = easeOutCubic(swordTimer) * swordMaxIdleHeight;
        swordTimer += 0.1;
        swordRotation++;
        if (swordHeight >= swordMaxIdleHeight) {
            swordActivated = 3;
        }
    }
    else if (swordActivated == 3) {
        if (swordHeight >= swordMaxIdleHeight || swordHeight <= swordMinIdleHeight) {
            swordHeightChange = -swordHeightChange;
        }

        swordHeight += swordHeightChange;
        swordRotation += 2;
    }
}



// ------------------------ TIMER-FUNCTION ----------------------------- //
void myTimer(int value) {

    animateParticles();

    animateLamp();

    animateChest();

    animateMimic();

    animateSword();

    glutPostRedisplay();
    glutTimerFunc(50, myTimer, 0); // Note: 50ms
}

// ====================================== CONTROLS =================================================

void special(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT) { // turn right
        angleCamera += angleTurnAmount;
    }
    else if (key == GLUT_KEY_LEFT) { // turn left
        angleCamera -= angleTurnAmount;
    }
    else if (key == GLUT_KEY_DOWN) {
        // Move backwards
        eye_x -= movementAmount * sin(angleCamera);
        eye_z += movementAmount * cos(angleCamera);
    }
    else if (key == GLUT_KEY_UP) {
        // Move forwards
        eye_x += movementAmount * sin(angleCamera);
        eye_z -= movementAmount * cos(angleCamera);
    }
    look_x = eye_x + 100 * sin(angleCamera);
    look_z = eye_z - 100 * cos(angleCamera);
    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y) {
    if (key == 'a') { 
        // Strafe left
        eye_x -= movementAmount * cos(angleCamera);
        eye_z -= movementAmount * sin(angleCamera);
    }
    else if (key == 'd') {
        // Strafe right
        eye_x += movementAmount * cos(angleCamera);
        eye_z += movementAmount * sin(angleCamera);
    }

    // Keys to activate animations
    else if (key == '1') {
        ////// Open normal chest ///////


        // Only activate if the chest is NOT opened/in the process of opening
        if (normalChestOpened == 0) {
            openTimer = 0;
            normalChestOpened = 1; // activate the animation
        }


    }
    else if (key == '2') {
        // activate mimic if not already activated
        if (mimicActivated == 0) {
            mimicActivated = 1;
            mimicTimer = 0;
        }
    }

    else if (key == '3') {
        // activate sword animation
        if (swordActivated == 0) {
            swordActivated = 1;
            swordTimer = 0;
        }
    }
    else if (key == '4') {
        // toggle particles
        if (sparklez == 1) {
            sparklez = 0;
        }
        else {
            sparklez = 1;
        }

    }
    else if (key == '5') {
        if (spotStringLength > 0.5) {
            lampMaxAngle = 0;
            spotStringLength -= 0.2;
            lampTimer = 0;
        }
    }
    else if (key == '6') {
        if (spotStringLength < 20) {
            lampMaxAngle = 0;

            spotStringLength += 0.2;
            lampTimer = 0;

        }
    }
    else if (key == '7') {
        lampMaxAngle = 10;
        lampTimer = 0;

    }


    else if (key == '0') {
        // reset everything
        normalChestOpened = 0;
        normalChestOpenedAngle = 0;
        diamondHeightChange = 0.1;
        mimicActivated = 0;
        mimicOpenAngle = 0;
        swordActivated = 0;
        swordTimer = 0;
        swordHeight = 0;
        swordRotation = 0;
        swordAngle = -5;
        swordHeightChange = 0.1;
        lampTimer = 0;
        lampMaxAngle = 10;
        spotStringLength = 10;


    }


    else if (key == 'w') {
        eye_y++;
        look_y++;
    }
    else if (key == 's') {
        eye_y--;
        look_y--;
    }
    look_x = eye_x + 100 * sin(angleCamera);
    look_z = eye_z - 100 * cos(angleCamera);
    glutPostRedisplay();

}

// ================================= SCENE MODELS ==============================================

void lampModel() {
    glPushMatrix();
    glTranslatef(30, 30.5, -75);
    glRotatef(lampAngle, 1, 0, 0);
    spotlight();
    glPopMatrix();
}

void swordModel() {
    float shadowColor[4] = { 0.4, 0.38, 0.47, 1.0 };
    float lightColor[4] = { 1.0, 0.96, 0.87, 1.0 };
    float white[4] = { 1.0, 1.0, 1.0, 1.0 };

    /// Lighting / shadow ///
    float shadowMat[16] = { gy2,0,0,0, -gx2,0,-gz2,-1, 0,0,gy2,0, 0,0,0,gy2 };
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT0);

    glDisable(GL_LIGHTING);
    glPushMatrix();
    glMultMatrixf(shadowMat);
    glColor4f(0.3, 0.28, 0.37, 1.0);

    // Sword object for shadow
    glTranslatef(-20, 1, -75);
    glRotatef(75, 0, 1, 0);
    glPushMatrix();
    glRotatef(swordRotation, 0, 1, 0);
    swordInStone(swordAngle, swordHeight, 1);
    glPopMatrix();
    glPopMatrix();
    glEnable(GL_LIGHTING);

    // Sword object with rocks
    glPushMatrix();
    glTranslatef(-20, 1, -75);
    glRotatef(75, 0, 1, 0);

    glPushMatrix();
    glRotatef(swordRotation, 0, 1, 0);
    swordInStone(swordAngle, swordHeight, 0);
    glPopMatrix();

    rocks();
    glPopMatrix();

    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT0);
}

void chestModel() {
    glPushMatrix();
    glTranslatef(-20, 0, -130); // move everything into place
    glPushMatrix();
    glTranslatef(0, diamondHeight, 0);
    glRotated(diamondRotate, 0, 1, 0);
    diamond();
    glPopMatrix();
    glRotatef(45, 0, 1, 0); // rotate it 45 degrees so it's facing inwards
    chest(normalChestOpenedAngle);
    glPopMatrix();
}

void mimicModel() {
    glPushMatrix();
    glTranslatef(20, 0, -130); // move the mimic into place
    glRotatef(-45, 0, 1, 0); // rotate it -45 degrees so it's facing inwards
    mimicChest(mimicOpenAngle);
    glPopMatrix();
}

// ================================= PUT THE SCENE TOGETHER ==============================================

void displayScene() {

    building();
    lampModel();
    swordModel();

    glEnable(GL_LIGHT0);
    chestModel();
    mimicModel();
    glDisable(GL_LIGHT0);

    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    skybox();
    glPopMatrix();

    if (sparklez == 1) {
        glPushMatrix();
        glTranslatef(-22, 1, -79);
        particles();
        glPopMatrix();
    }

}


void display(void) {
    glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos0);   // for chests
    glLightfv(GL_LIGHT2, GL_POSITION, lgt_pos2);   // for sword
    glLightfv(GL_LIGHT3, GL_POSITION, lgt_pos3);  // for building
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (eye_x, eye_y, eye_z, look_x, look_y, look_z, 0.0, 1.0, 0.0); // Camera

    displayScene();

    glutSwapBuffers();
}


void initialize(void)
{
    float grey[4] = { 0.2, 0.2, 0.2, 1.0 };
    float shadowColor[4] = { 0.4, 0.38, 0.47, 1.0 };
    float lightColor[4] = { 1.0, 0.96, 0.87, 1.0 };
    float white[4] = { 1.0, 1.0, 1.0, 1.0 };

    // Enable textures
    loadTexture();

    // Enable lighting
    glEnable(GL_LIGHTING);

    //	Define light's ambient, diffuse, specular properties
    glLightfv(GL_LIGHT0, GL_AMBIENT, shadowColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glLightfv(GL_LIGHT2, GL_AMBIENT, shadowColor);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT2, GL_SPECULAR, white);

    glLightfv(GL_LIGHT3, GL_AMBIENT, shadowColor);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT3, GL_SPECULAR, white);

    // Enable the material colours through the lighting
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearColor(0.0, 0.0, 0.0, 0.0);  //Background colour

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60., 1.0, 10.0, 1000.0);   //Perspective projection

    // initialize sparklez!
    initSparklez();
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH);
   glutInitWindowSize (800, 800); 
   glutInitWindowPosition (50, 50);
   glutCreateWindow ("[llo35] COSC363 Assignment 1");
   initialize ();

   glutReshapeFunc(reshape); // for aspect ratio fixing when resizing window
   glutDisplayFunc(display); 
   glutSpecialFunc(special); // for camera movement
   glutKeyboardFunc(keyboard); // for camera movement and activating animations
   glutTimerFunc(50, myTimer, 0);
   glutMainLoop();
   return 0;
}
