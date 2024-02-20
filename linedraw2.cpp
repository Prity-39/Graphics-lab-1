#include <GL/glut.h>
#include <bits/stdc++.h>

#define LINE_COUNT 360
#define WIDTH 512
#define HEIGHT 512
#define RADIUS 200

void drawLine(int x0, int y0, int x1, int y1);
void drawLine0(int x0, int y0, int x1, int y1, int zone);
void drawPixel(int x, int y, int zone);

static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH / 2, WIDTH / 2 - 1, -HEIGHT / 2, HEIGHT / 2 - 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int points[LINE_COUNT][4];


void generateLines()
{
    for (int i = 0; i < LINE_COUNT; i++)
    {
        points[i][0] = 0;
        points[i][1] = 0;
        points[i][2] = RADIUS * cos(i);
        points[i][3] = RADIUS * sin(i);
    }
}
void drawLine(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0, dy = y1 - y0;

    if (abs(dx) >= abs(dy)){ 
        if (dx >= 0 && dy >= 0) drawLine0(x0, y0, x1, y1, 0);
        else if (dx < 0 && dy >= 0) drawLine0(-x0, y0, -x1, y1, 3);
        else if (dx < 0 && dy < 0) drawLine0(-x0, -y0, -x1, -y1, 4);
        else drawLine0(x0, -y0, x1, -y1, 7);
    }
    else{ 
        if (dx >= 0 && dy >= 0) drawLine0(y0, x0, y1, x1, 1);
        else if (dx < 0 && dy >= 0) drawLine0(y0, -x0, y1, -x1, 2);
        else if (dx < 0 && dy < 0) drawLine0(-y0, -x0, -y1, -x1, 5);
        else drawLine0(-y0, x0, -y1, x1, 6);
    }
}

void drawLine0 (int x0, int y0, int x1, int y1, int zone)
{
    int dx = x1 - x0, dy = y1 - y0;
    int delE = 2 * dy, delNE = 2 * (dy - dx);
    int d = 2 * dy - dx;
    int x = x0, y = y0;
    while (x < x1)
    {
        drawPixel (x, y, zone);
        if (d < 0){ //delE
            d += delE;
            x++;
        }
        else{ //delNE
            d += delNE;
            x++; y++;
        }
        drawPixel (x, y, zone);
    }
}
void drawPixel (int x, int y, int zone)
{
    switch (zone)
    {
    case 0:
        glColor3f(0.5f, 0.0f, 1.0f);
        glVertex2i(x, y);
        break;
    case 1:
        glColor3d(0, 0, 255);
        
        glVertex2i(y, x);
        break;
    case 2:
        glColor3d(0, 102, 102);
        glVertex2i(-y, x);
        break;
    case 3:
        glColor3d(0, 102, 0);
        glVertex2i(-x, y);
        break;
    case 4:
        glColor3d(255, 255, 0);
        glVertex2i(-x, -y);
        break;
    case 5:
        glColor3d(1.0f, 0.5f, 0.0f);
        glVertex2i(-y, -x);
        break;
    case 6:
        glColor3d(204, 0, 0);
        glVertex2i(y, -x);
        break;
    case 7:
        glColor3d(0, 102, 102);
        glVertex2i(x, -y);
        break;
    }
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2i(-WIDTH / 2, 0);
    glVertex2i(WIDTH / 2, 0);
    glVertex2i(0, -HEIGHT / 2);
    glVertex2i(0, HEIGHT / 2);
    glEnd();

    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = 0; i < LINE_COUNT; i++)
        drawLine(points[i][0], points[i][1], points[i][2], points[i][3]);
    
    glEnd();

    glutSwapBuffers();
}
 
static void idle(void)
{
    glutPostRedisplay();
}
 
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    generateLines();
    glutCreateWindow("Experiment 02");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
}

