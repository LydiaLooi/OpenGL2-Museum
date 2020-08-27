//=====================================================================
// Models.h
// Methods for the models that are made with glut objects only and aren't textured
// Includes:
// - Chest
// - Mimic
// - Sword + rocks
//
// Author:
// Lydia Looi
//=====================================================================


#if !defined(H_MODELS)
#define H_MODELS

#include <math.h>
#include <GL/freeglut.h>
#define M_PI 3.14159265358979323846


float radian(float theta) {
    return theta * (M_PI / 180);
}


float degree(float theta) {
    return theta * (180 / M_PI);
}


void chestBase() {
    float white[4] = { 1., 1., 1., 1. };
    float black[4] = { 0 };

    glColor4f(1.0, 0.77, 0.33, 1.0); // gold
    // hinges
    glPushMatrix();
    glTranslatef(-5, 2, -5);
    glScalef(3, 2, 1);
    glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 2, -5);
    glScalef(3, 2, 1);
    glutSolidCube(0.5);
    glPopMatrix();

    // Corner pieces

    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);

    glPushMatrix();
    glTranslatef(-8.25, 0, 4.25);
    glScalef(2.5, 4.1, 2.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.25, 0, 4.25);
    glScalef(2.5, 4.1, 2.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.25, 0, -4.25);
    glScalef(2.5, 4.1, 2.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.25, 0, -4.25);
    glScalef(2.5, 4.1, 2.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_SPECULAR, black);


    glColor4f(0.39, 0.15, 0.19, 1.0); // dark purpley colour
    // 4 Base walls

    glPushMatrix();
    glTranslatef(8.0, 0, 0);
    glScalef(2.0, 4.0, 10.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.0, 0, 0);
    glScalef(2.0, 4.0, 10.0);
    glutSolidCube(1.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0, 0, -4);
    glScalef(18.0, 4.0, 2.0);
    glutSolidCube(1.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0, 0, 4);
    glScalef(18.0, 4.0, 2.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // bottom
    glPushMatrix();
    glTranslatef(0.0, -1, 0);
    glScalef(18.0, 2.0, 10.0);
    glutSolidCube(1.0);
    glPopMatrix();

}


void chestLid(float angleOpened) {

    glPushMatrix();
    glTranslatef(0, 4, 0);
    glTranslatef(0, 0, -5.5);
    glRotatef(-angleOpened, 1, 0, 0);
    glTranslatef(0, 0, 5.5);

    float white[4] = { 1., 1., 1., 1. };
    float black[4] = { 0 };

    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);


    glColor4f(1.0, 0.77, 0.33, 1.0); // gold
    // left front slanted edge piece

    glPushMatrix();
    glTranslatef(-9, 4.75 - 0.35355339059, 4.75 - 0.35355339059); // cos(45 degree) /2 = 0.35355339059
    glRotatef(45, 1, 0, 0);
    glScalef(2, 1, sqrt(24.5)); // 3.5^2 + 3.5^2 = 24.5
    glutSolidCube(1.0);
    glPopMatrix();

    // right front slanted edge piece

    glPushMatrix();
    glTranslatef(9, 4.75 - 0.35355339059, 4.75 - 0.35355339059); // cos(45 degree) /2 = 0.35355339059
    glRotatef(45, 1, 0, 0);
    glScalef(2, 1, sqrt(24.5)); // 3.5^2 + 3.5^2 = 24.5
    glutSolidCube(1.0);
    glPopMatrix();


    // left back slanted edge piece

    glPushMatrix();
    glTranslatef(-9, 4.75 - 0.35355339059, -4.75 + 0.35355339059); // cos(45 degree) /2 = 0.35355339059
    glRotatef(-45, 1, 0, 0);
    glScalef(2, 1, sqrt(24.5)); // 3.5^2 + 3.5^2 = 24.5
    glutSolidCube(1.0);
    glPopMatrix();

    // right back slanted edge piece

    glPushMatrix();
    glTranslatef(9, 4.75 - 0.35355339059, -4.75 + 0.35355339059); // cos(45 degree) /2 = 0.35355339059
    glRotatef(-45, 1, 0, 0);
    glScalef(2, 1, sqrt(24.5)); // 3.5^2 + 3.5^2 = 24.5
    glutSolidCube(1.0);
    glPopMatrix();


    // left top piece edge
    glPushMatrix();
    glTranslatef(-9, 6, 0);
    glScalef(2, 1, 6);
    glutSolidCube(1.0);
    glPopMatrix();

    // right top piece edge
    glPushMatrix();
    glTranslatef(9, 6, 0);
    glScalef(2, 1, 6);
    glutSolidCube(1.0);
    glPopMatrix();


    // left front piece vertical
    glPushMatrix();
    glTranslatef(-9, 1.5, 6);
    glScalef(2, 3, 1);
    glutSolidCube(1.0);
    glPopMatrix();

    // right front piece vertical
    glPushMatrix();
    glTranslatef(9, 1.5, 6);
    glScalef(2, 3, 1);
    glutSolidCube(1.0);
    glPopMatrix();

    // left back piece vertical
    glPushMatrix();
    glTranslatef(-9, 1.5, -6);
    glScalef(2, 3, 1);
    glutSolidCube(1.0);
    glPopMatrix();

    // right back piece vertical
    glPushMatrix();
    glTranslatef(9, 1.5, -6);
    glScalef(2, 3, 1);
    glutSolidCube(1.0);
    glPopMatrix();


    // front piece bottom
    glPushMatrix();
    glTranslatef(0, 0.49, 6);
    glScalef(20, 1, 1);
    glutSolidCube(1.0);
    glPopMatrix();

    // back piece bottom
    glPushMatrix();
    glTranslatef(0, 0.49, -6);
    glScalef(20, 1, 1);
    glutSolidCube(1.0);
    glPopMatrix();

    // right side piece bottom
    glPushMatrix();
    glTranslatef(9.5, 0.49, 0.5);
    glScalef(1, 1, 12);
    glutSolidCube(1.0);
    glPopMatrix();

    // left side piece bottom
    glPushMatrix();
    glTranslatef(-9.5, 0.49, 0.5);
    glScalef(1, 1, 12);
    glutSolidCube(1.0);
    glPopMatrix();

    // front lock
    glPushMatrix();
    glTranslatef(0, 0, 6.25);
    glScalef(2, 2, 1);
    glutSolidCube(1.0);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_SPECULAR, black);


    glColor4f(0.39, 0.15, 0.19, 1.0); // dark purpley colour

    // right (facing chest) side
    glPushMatrix();
    glTranslatef(8.5, 2.5, 0);
    glScalef(2, 5.0, 8);
    glutSolidCube(1.0);
    glPopMatrix();

    // left (facing chest) side
    glPushMatrix();
    glTranslatef(-8.5, 2.5, 0);
    glScalef(2, 5.0, 8);
    glutSolidCube(1.0);
    glPopMatrix();




    // front slanted
    glPushMatrix();
    glTranslatef(0.0, 3.79289321881, 3.79289321881); // 4.5 - cos(45) = 3.79289321881 
    glRotatef(45, 1, 0, 0);
    glScalef(19, 2.0, sqrt(18)); // sqrt(3^2 + 3^2)
    glutSolidCube(1.0);
    glPopMatrix();



    // back slanted
    glPushMatrix();
    glTranslatef(0.0, 3.79289321881, -3.79289321881); // 4.5 - cos(45) = 3.79289321881
    glRotatef(-45, 1, 0, 0);
    glScalef(19, 2.0, sqrt(18)); // sqrt(3^2 + 3^2)
    glutSolidCube(1.0);
    glPopMatrix();


    //top
    glPushMatrix();
    glTranslatef(0.0, 5.0, 0);
    glScalef(19, 2.0, 6);
    glutSolidCube(1.0);
    glPopMatrix();


    // front
    glPushMatrix();
    glTranslatef(0.0, 1.5, 5);
    glScalef(19, 3.0, 2.0);
    glutSolidCube(1.0);
    glPopMatrix();

    //back
    glPushMatrix();
    glTranslatef(0.0, 1.5, -5);
    glScalef(19, 3.0, 2.0);
    glutSolidCube(1.0);
    glPopMatrix();


    glPopMatrix();

}


void chest(float angleOpened) {
    chestLid(angleOpened);
    glPushMatrix();
    glTranslatef(0, 2, 0);
    chestBase();
    glPopMatrix();
}


void teethPoint() {
    glPushMatrix();
    glutSolidOctahedron();
    glPopMatrix();
}


void teethSet() {


    // Top left teeth
    glColor4f(0.7, 0.7, 0.7, 1); // off white


    glPushMatrix();
    glTranslatef(-8.25, 0, 4.5);
    glScalef(1, 3, 1);
    teethPoint();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.25, 0, 4.5);
    glScalef(1, 2, 1);
    teethPoint();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.25, 0, 4.5);
    teethPoint();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.25, 0, 4.5);
    glScalef(1, 0.5, 1);
    teethPoint();
    glPopMatrix();

}


void mimicLid(float angleOpened) {
    chestLid(angleOpened);

    glPushMatrix();
    glTranslatef(0, 4, 0);
    glTranslatef(0, 0, -5.5);
    glRotatef(-angleOpened, 1, 0, 0);
    glTranslatef(0, 0, 5.5);


    glPushMatrix();
    glTranslatef(0, 0, -0.51);

    teethSet();
    glPushMatrix();
    glScalef(-1, 1, 1); //reflect to the bottom
    teethSet();
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();


}


void mimicBase() {
    chestBase();
    glPushMatrix();

    glTranslatef(0, 2, -1);

    glPushMatrix();
    glScalef(1, -1, 1);
    teethSet();
    glPopMatrix();

    glPushMatrix();
    glScalef(-1, -1, 1);
    teethSet();
    glPopMatrix();

    glPopMatrix();
}


void mimicChest(float angleOpened) {


    mimicLid(angleOpened);

    glPushMatrix();
    glTranslatef(0, 2, 0);
    mimicBase();
    glPopMatrix();
}



void rocks() {

    glColor3f(0.11, 0.11, 0.11);

    glPushMatrix();

    glTranslatef(0, -1, 0);

    glPushMatrix();
    glTranslatef(-2, 0, 0);
    glRotatef(30, 1, 0, 0);
    glRotatef(45, 0, 0, 1);
    glutSolidCube(5.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1, 0, 0);
    glRotatef(20, 1, 0, 0);
    glRotatef(35, 0, 0, 1);
    glutSolidCube(3.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 2);
    glRotatef(40, 1, 0, 0);
    glRotatef(25, 0, 0, 1);
    glutSolidCube(3.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0, 3);
    glRotatef(-20, 1, 0, 0);
    glRotatef(-15, 0, 0, 1);
    glutSolidCube(2.0);
    glPopMatrix();

    glPopMatrix();
}


void sword(int isShadow) {

    float white[4] = { 1., 1., 1., 1. };
    float black[4] = { 0 };




    /// hilt ///
    if (isShadow == 0) { // Only set the colour if it's not supposed to be a shadow
        glColor3f(0.87, 0.53, 0.24);
        glMaterialfv(GL_FRONT, GL_SPECULAR, white);
        glMaterialf(GL_FRONT, GL_SHININESS, 50);
    }



    glPushMatrix();
    glTranslatef(0, 11.5, 0);
    glutSolidCube(1.0);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_SPECULAR, black);


    if (isShadow == 0) { // Only set the colour if it's not supposed to be a shadow
        glColor3f(0.08, 0.07, 0.14);
    }
    glPushMatrix();
    glTranslatef(0, 10, 0);
    glScalef(0.6, 2, 0.6);
    glutSolidCube(1.0);
    glPopMatrix();

    if (isShadow == 0) { // Only set the colour if it's not supposed to be a shadow
        glColor3f(0.11, 0.11, 0.11);
    }

    glPushMatrix();
    glTranslatef(0, 8.5, 0);
    glScalef(3, 1, 1);
    glutSolidCube(1.0);
    glPopMatrix();



    /// blade ///

    if (isShadow == 0) { // Only set the colour if it's not supposed to be a shadow
        glColor3f(0.87, 0.53, 0.24);
        glMaterialfv(GL_FRONT, GL_SPECULAR, white);
        glMaterialf(GL_FRONT, GL_SHININESS, 50);
    }



    glPushMatrix();

    glScalef(0.5, 1, 0.25);

    glPushMatrix();
    glTranslatef(0, 1, 0);
    glScalef(1, 1, 1);

    glutSolidOctahedron();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 4.5, 0);
    glScalef(sqrt(2), 7, sqrt(2));
    glRotatef(45, 0, 1, 0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();


    glMaterialfv(GL_FRONT, GL_SPECULAR, black);



}

void swordInStone(float swordAngle, float swordHeight, int isShadow) {
    glPushMatrix();
    glTranslatef(0, swordHeight, 0);
    glTranslatef(0, -3, 0);
    glRotatef(swordAngle, 0, 0, 1);
    sword(isShadow);
    glPopMatrix();

}




#endif