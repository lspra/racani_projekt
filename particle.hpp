#include <GL/glut.h>
#include <stdio.h>
#include <math.h>


typedef struct _Ociste {
    GLfloat	x;
    GLfloat	y;
    GLfloat	z;
} Ociste;

typedef struct
{
    GLfloat x, y, z;
} vert3d;

typedef struct
{
    GLfloat r, g, b, a;
} rgba;

class Particle
{
private:
public:
    vert3d pos, speed;
    int lifespan, age;
    rgba color = {1, 1, 0, 0.3};
    Particle();
    ~Particle();
    void draw(Ociste o);
    void process();
};

float sigm3(float x) {
    return 1/(1 + exp(-x))/(1 + exp(-x))/(1 + exp(-x));
}

Particle::Particle()
{
    float r = ((float) rand() / (RAND_MAX)) * 0.9;
    float fi = 2.*3.14* ((float) rand() / (RAND_MAX));
    pos = {r * cosf(fi), 0, r * sinf(fi)};
    speed = {0, 0.008, 0};
    lifespan = 400 / sigm3(r) * ((float) rand() / (RAND_MAX) / 2 + 0.5);
    age = 0;
    if(r > 0.7)
        color = {1, 0, 0, 0.3};
    else if(r > 0.33)
        color = {1, 0.5, 0, 0.3};
}

Particle::~Particle()
{
}

void Particle::process() {
    pos.x += speed.x + 0.01 * (2*(float) rand() / (RAND_MAX) - 1);
    pos.y += speed.y;
    pos.z += speed.z + 0.01 * (2*(float) rand() / (RAND_MAX) - 1);
    age += 20;
    if(age > 0.65 * lifespan) {
        speed.x = - 0.01 * pos.x;
        speed.z = - 0.01 * pos.z;
        speed.y *= 1.001;
    }
    if(age > 0.9 * lifespan)
        color = {0.5, 0.6, 0.5, 0.3};
    else if(age * 3 > 2 * lifespan)
        color = {1, 0, 0, 0.3};
    else if(age * 3 > lifespan && color.g == 1)
        color = {1, 0.5, 0, 0.3};
}

void Particle::draw(Ociste o) {
    glPointSize(1.f);
    vert3d normala = {o.x - pos.x, o.y - pos.y, o.z - pos.z};
    glPushMatrix();
    GLfloat angle = acos(normala.z / sqrt(normala.x * normala.x  + normala.y * normala.y  + normala.z * normala.z)) * 180 / 2 / 3.14159;
    glRotatef(angle, -normala.y, normala.x, 0);
    glColor4f(color.r, color.g, color.b, color.a);
    glBegin(GL_QUADS);
    glVertex3f(pos.x-0.008f, pos.y-0.008f, pos.z+0.0f);
    glVertex3f(pos.x+0.008f, pos.y-0.008f, pos.z+0.0f);
    glVertex3f(pos.x+0.008f, pos.y+0.008f, pos.z+0.0f);
    glVertex3f(pos.x-0.008f, pos.y+0.008f, pos.z+0.0f);
    glEnd();
    glPopMatrix();
}
