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
    rgba color = {1, 1, 0, 0.45};
    Particle();
    ~Particle();
    void draw(Ociste o);
    void process();
};

