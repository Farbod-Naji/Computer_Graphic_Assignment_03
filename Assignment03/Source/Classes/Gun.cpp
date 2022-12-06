#include "Gun.h"
#include <gl/glut.h>

void Gun::drawCylinder() {
    glPushMatrix();
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        gluDisk(gluNewQuadric(), 0.0, 1.0, 20, 10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 1.0f);
        gluDisk(gluNewQuadric(), 0.0, 1.0, 20, 10);
    glPopMatrix();

    glPushMatrix();
        gluCylinder(gluNewQuadric(), 1.0, 1.0, 1.0, 20, 10);
    glPopMatrix();
}

bool Gun::update(float dt)
{
    gunTurningAngle += gunTurningSpeed;
    if (gunTurned) {
        gunTurned = false;
        return true;
    }
    return false;
}

void Gun::render()
{
    glPushMatrix();
        glTranslatef(barrelPos.x, barrelPos.y, barrelPos.z);
        glutSolidSphere(1.0f, 50, 50);
    glPopMatrix();

    glPushMatrix();    
        glTranslatef(gunPos.x, gunPos.y, gunPos.z);
        glRotatef(gunRotation.x, -1.0, 0.0, 0.0);
        glRotatef(gunRotation.y, 0.0, 1.0, 0.0);
        Gun::drawGun();
    glPopMatrix();
}

void Gun::drawGun()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, robotBody_mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, robotBody_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, robotBody_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, robotBody_mat_shininess);

    glPushMatrix();
        //rotating the gun
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        
        glRotatef(gunTurningAngle, 0.0f, 1.0f, 0.0f);
        


        // gun base
        glPushMatrix();
            glScalef(1.0f, 0.5f, 1.0f);
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            drawCylinder();
            //drawBullet();
        glPopMatrix();


        glPushMatrix();

            glPushMatrix();
                glTranslatef(0.0f, 0.0f, -1.0f * (3/5.0f));
                glScalef(gunWidth, gunLength, gunDepth);
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                drawCylinder();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0.0f, 0.0f, 1.0f * (3 / 5.0f));
                glScalef(gunWidth, gunLength, gunDepth);
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                drawCylinder();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(1.0f * (3 / 5.0f), 0.0f, 0.0f);
                glScalef(gunWidth, gunLength, gunDepth);
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                drawCylinder();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(-1.0f / 2, 0.0f, 0.0f);
                glScalef(gunWidth, gunLength, gunDepth);
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                drawCylinder();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}
