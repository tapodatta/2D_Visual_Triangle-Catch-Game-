// TAPO DATTA(1560),Joy Biswas(1564)

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

float triangleX = 100.0f;
float triangleY = 400.0f;

float triangleSize = 25.0f;


float squareX = 400.0f;
float squareY = 100.0f;

float squareSize = 30.0f;
float squareSpeed = 5.0f;

bool gameRunning = true;

clock_t gameStartTime;
clock_t lastMouseClickTime;

bool firstMouseClick = true;

const double GAME_TIME = 60.0;

const double MOUSE_INTERVAL = 2.0;

void drawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);

    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}


void drawTriangle()
{
    glColor3f(1.0f, 0.5f, 0.0f);

    glBegin(GL_TRIANGLES);

        glVertex2f(
            triangleX,
            triangleY + triangleSize
        );
        glVertex2f(
            triangleX - triangleSize,
            triangleY - triangleSize
        );
        glVertex2f(
            triangleX + triangleSize,
            triangleY - triangleSize
        );

    glEnd();
}

void drawSquare()
{
    glColor3f(0.6f, 0.6f, 0.6f);

    glBegin(GL_QUADS);

        glVertex2f(
            squareX - squareSize,
            squareY - squareSize
        );

        glVertex2f(
            squareX + squareSize,
            squareY - squareSize
        );

        glVertex2f(
            squareX + squareSize,
            squareY + squareSize
        );

        glVertex2f(
            squareX - squareSize,
            squareY + squareSize
        );

    glEnd();
}


bool checkCollision()
{
    float triangleLeft = triangleX - triangleSize;
    float triangleRight = triangleX + triangleSize;

    float triangleBottom = triangleY - triangleSize;
    float triangleTop = triangleY + triangleSize;

    float squareLeft = squareX - squareSize;
    float squareRight = squareX + squareSize;

    float squareBottom = squareY - squareSize;
    float squareTop = squareY + squareSize;

    if (triangleRight >= squareLeft &&
        triangleLeft <= squareRight &&
        triangleTop >= squareBottom &&
        triangleBottom <= squareTop)
    {
        return true;
    }

    return false;
}

double getGameTime()
{
    clock_t currentTime = clock();

    return (double)(currentTime - gameStartTime) / CLOCKS_PER_SEC;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    drawTriangle();
    drawSquare();

    double elapsedTime = getGameTime();

    int remainingTime = (int)(GAME_TIME - elapsedTime);

    if (remainingTime < 0)
        remainingTime = 0;

    glColor3f(1.0f, 1.0f, 1.0f);

    char timerText[50];

    sprintf(
        timerText,
        "Time Left: %d seconds",
        remainingTime
    );

    drawText(10, 475, timerText);

    drawText(
        10,
        450,
        "Square: W A S D | Mouse: Move Triangle"
    );

    if (!gameRunning)
    {
        glColor3f(1.0f, 1.0f, 1.0f);

        if (checkCollision())
        {
            drawText(
                160,
                270,
                "GAME OVER!"
            );

            drawText(
                130,
                240,
                "Triangle Caught!"
            );
        }
        else
        {
            drawText(
                160,
                270,
                "GAME OVER!"
            );

            drawText(
                135,
                240,
                "Time Up!"
            );
        }

        drawText(
            155,
            210,
            "Press R to Restart"
        );
    }


    glutSwapBuffers();
}


void keyboardFunc(unsigned char key, int x, int y)
{
    if (key == 'r' || key == 'R')
    {
        triangleX = 100.0f;
        triangleY = 400.0f;

        squareX = 400.0f;
        squareY = 100.0f;

        gameStartTime = clock();

        lastMouseClickTime = clock();

        firstMouseClick = true;

        gameRunning = true;

        glutPostRedisplay();

        return;
    }

    if (!gameRunning)
        return;

    if (key == 'w' || key == 'W')
    {
        squareY += squareSpeed;
    }

    else if (key == 's' || key == 'S')
    {
        squareY -= squareSpeed;
    }

    else if (key == 'a' || key == 'A')
    {
        squareX -= squareSpeed;
    }


    else if (key == 'd' || key == 'D')
    {
        squareX += squareSpeed;
    }

    if (squareX - squareSize < 0)
        squareX = squareSize;

    if (squareX + squareSize > WINDOW_WIDTH)
        squareX = WINDOW_WIDTH - squareSize;

    if (squareY - squareSize < 0)
        squareY = squareSize;

    if (squareY + squareSize > WINDOW_HEIGHT)
        squareY = WINDOW_HEIGHT - squareSize;

    if (checkCollision())
    {
        gameRunning = false;
    }


    glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y)
{
    if (button != GLUT_LEFT_BUTTON)
        return;
    if (state != GLUT_UP)
        return;

    if (!gameRunning)
        return;


    clock_t currentTime = clock();


    if (firstMouseClick)
    {
        firstMouseClick = false;

        lastMouseClickTime = currentTime;

        int oglY = WINDOW_HEIGHT - y;

        triangleX = (float)x;
        triangleY = (float)oglY;

        if (triangleX - triangleSize < 0)
            triangleX = triangleSize;

        if (triangleX + triangleSize > WINDOW_WIDTH)
            triangleX = WINDOW_WIDTH - triangleSize;

        if (triangleY - triangleSize < 0)
            triangleY = triangleSize;

        if (triangleY + triangleSize > WINDOW_HEIGHT)
            triangleY = WINDOW_HEIGHT - triangleSize;

        glutPostRedisplay();

        return;
    }


    double timeSinceLastClick =
        (double)(currentTime - lastMouseClickTime)
        / CLOCKS_PER_SEC;

    if (timeSinceLastClick >= MOUSE_INTERVAL)
    {
        lastMouseClickTime = currentTime;

        int oglY = WINDOW_HEIGHT - y;



        triangleX = (float)x;
        triangleY = (float)oglY;

        if (triangleX - triangleSize < 0)
            triangleX = triangleSize;

        if (triangleX + triangleSize > WINDOW_WIDTH)
            triangleX = WINDOW_WIDTH - triangleSize;

        if (triangleY - triangleSize < 0)
            triangleY = triangleSize;

        if (triangleY + triangleSize > WINDOW_HEIGHT)
            triangleY = WINDOW_HEIGHT - triangleSize;


        if (checkCollision())
        {
            gameRunning = false;
        }


        glutPostRedisplay();
    }
}


void timerFunc(int value)
{
    if (gameRunning)
    {
        double elapsedTime = getGameTime();


        if (elapsedTime >= GAME_TIME)
        {
            gameRunning = false;
        }

        if (checkCollision())
        {
            gameRunning = false;
        }
    }


    glutPostRedisplay();

    glutTimerFunc(100, timerFunc, 0);
}


void reshape(int w, int h)
{
    glViewport(
        0,
        0,
        (GLsizei)w,
        (GLsizei)h
    );


    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();


    glOrtho(
        0,
        WINDOW_WIDTH,
        0,
        WINDOW_HEIGHT,
        -1,
        1
    );


    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}

void initialization()
{
    glClearColor(
        0.0f,
        0.0f,
        0.0f,
        1.0f
    );


    gameStartTime = clock();

    lastMouseClickTime = clock();
}


int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(
        GLUT_RGB | GLUT_DOUBLE
    );
    glutInitWindowPosition(
        100,
        50
    );
    glutInitWindowSize(
        WINDOW_WIDTH,
        WINDOW_HEIGHT
    );

    glutCreateWindow(
        "Triangle Catch Game"
    );

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboardFunc);

    glutMouseFunc(mouseFunc);
    initialization();
    glutTimerFunc(
        100,
        timerFunc,
        0
    );
    glutMainLoop();


    return 0;
}
