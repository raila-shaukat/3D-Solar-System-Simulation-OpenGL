#include <GL/glut.h>
#include <cmath>
#include <string>

#define PI 3.14159265358979323846



// Variables for rotation and orbit speeds
float sunRotation = 0.0f;
float mercuryOrbit = 0.0f, mercuryRotation = 0.0f;
float venusOrbit = 0.0f, venusRotation = 0.0f;
float earthOrbit = 0.0f, earthRotation = 0.0f;
float marsOrbit = 0.0f, marsRotation = 0.0f;
float jupiterOrbit = 0.0f, jupiterRotation = 0.0f;
float saturnOrbit = 0.0f, saturnRotation = 0.0f;
float uranusOrbit = 0.0f, uranusRotation = 0.0f;
float neptuneOrbit = 0.0f, neptuneRotation = 0.0f;



// Variables for camera position
float cameraY = 20.0f; // Default Y position of the camera



// Function to draw a sphere
void drawSphere(float radius)
{
    glutSolidSphere(radius, 50, 50);
}



// Function to draw an orbit as a circle
void drawOrbit(float radius)
{
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 1.0, 1.0); // White color for the orbit
    for (int i = 0; i < 360; ++i) {
        float angle = i * PI / 180.0f;
        glVertex3f(radius * cos(angle), 0.0f, radius * sin(angle));
    }
    glEnd();
}



// Function to display planet names
void drawText(const char* text, float x, float y, float z)
{
    glColor3f(1.0, 1.0, 1.0); // Set text color to white
    glRasterPos3f(x, y, z);
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}




void init()
{
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glEnable(GL_LIGHTING);   // Enable lighting
    glEnable(GL_LIGHT0);     // Enable light source 0
    glEnable(GL_COLOR_MATERIAL); // Enable color tracking for materials
    glClearColor(0.0, 0.0, 0.0, 1.0); // Background color
}



// Display callback
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, cameraY, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);



    // Sun
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glRotatef(sunRotation, 0.0, 1.0, 0.0);
    drawSphere(3.0f);
    glPopMatrix();



    // Planets and Orbits
    struct Planet
    {
        const char* name;
        float* orbitAngle;
        float orbitRadius;
        float orbitSpeed;
        float selfRotation;
        float radius;
        float color[3];
    };



    Planet planets[] = {
        {"Mercury", &mercuryOrbit, 6.0f, 0.1f, 0.3f, 0.5f, {0.7f, 0.7f, 0.7f}},
        {"Venus", &venusOrbit, 8.0f, 0.07f, 0.2f, 0.8f, {1.0f, 0.5f, 0.0f}},
        {"Earth", &earthOrbit, 10.0f, 0.05f, 0.15f, 1.0f, {0.0f, 0.0f, 1.0f}},
        {"Mars", &marsOrbit, 12.0f, 0.04f, 0.1f, 0.9f, {1.0f, 0.0f, 0.0f}},
        {"Jupiter", &jupiterOrbit, 15.0f, 0.02f, 0.08f, 2.0f, {1.0f, 0.8f, 0.6f}},
        {"Saturn", &saturnOrbit, 18.0f, 0.015f, 0.05f, 1.8f, {0.9f, 0.7f, 0.4f}},
        {"Uranus", &uranusOrbit, 21.0f, 0.01f, 0.03f, 1.5f, {0.4f, 0.7f, 1.0f}},
        {"Neptune", &neptuneOrbit, 24.0f, 0.008f, 0.02f, 1.4f, {0.0f, 0.0f, 0.8f}}
    };



    for (Planet& planet : planets)
        {
        drawOrbit(planet.orbitRadius); // Draw orbit
        glPushMatrix();
        glRotatef(*(planet.orbitAngle), 0.0, 1.0, 0.0); // Orbit rotation
        glTranslatef(planet.orbitRadius, 0.0, 0.0);    // Orbit radius
        glColor3fv(planet.color);
        glRotatef(planet.selfRotation, 0.0, 1.0, 0.0); // Self-rotation
        drawSphere(planet.radius);
        drawText(planet.name, 0.0f, planet.radius + 0.5f, 0.0f); // Draw name
        glPopMatrix();

        // Update orbit angle for the next frame
        *(planet.orbitAngle) += planet.orbitSpeed;
        if (*(planet.orbitAngle) > 360.0f) {
            *(planet.orbitAngle) -= 360.0f;
        }
    }

    glutSwapBuffers();
}



// Idle callback for animation
void idle()
{
    sunRotation += 0.1f; // Slower rotation of the sun
    if (sunRotation > 360.0f) sunRotation -= 360.0f;

    glutPostRedisplay();
}




// Keyboard callback for moving the camera
void keyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        cameraY += 1.0f; // Move the camera up
        break;
    case GLUT_KEY_DOWN:
        cameraY -= 1.0f; // Move the camera down
        break;
    default:
        break;
    }
    glutPostRedisplay();
}



// Reshape callback
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Solar System with White Labels");




    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutSpecialFunc(keyboard); // Register special key callback
    glutMainLoop();



    return 0;


}
