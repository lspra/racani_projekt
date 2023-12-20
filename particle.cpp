#include "particle.hpp"
float sigm3(float x) {
    return 1/(1 + exp(-x))/(1 + exp(-x))/(1 + exp(-x));
}

Particle::Particle()
{
    float r = ((float) rand() / (RAND_MAX)) * 0.4;
    float fi = 2.*3.14* ((float) rand() / (RAND_MAX));
    pos = {r * cosf(fi), 0, r * sinf(fi)};
    speed = {0, 0.008, 0};
    lifespan = 200 / sigm3(r/0.5) * ((float) rand() / (RAND_MAX) / 2 + 0.5);
    age = 0;
    if(r/0.475 > 0.7) {
        speed.x = -0.001 * pos.x;
        speed.z = -0.001 * pos.z;
        color = {1, 0, 0, 0.45};
    }
    else if(r/0.4 > 0.33) {
        speed.x = -0.0005 * pos.x;
        speed.z = -0.0005 * pos.z;
        color = {1, 0.5, 0, 0.45};
    }
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
    if(age * 3 > 2 * lifespan)
        color = {1, 0, 0, 0.45};
    else if(age * 3 > lifespan && color.g == 1)
        color = {1, 0.5, 0, 0.45};
}

void Particle::draw(Ociste o) {
    glPointSize(1.f);
    vert3d normala = {o.x - pos.x, o.y - pos.y, o.z - pos.z};
    glPushMatrix();
    GLfloat angle = acos(normala.z / sqrt(normala.x * normala.x  + normala.y * normala.y  + normala.z * normala.z)) * 180 / 2 / 3.14159;
    glRotatef(angle, -normala.y, normala.x, 0);
    glColor4f(color.r, color.g, color.b, color.a);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glBegin(GL_QUADS);
    //glTexCoord2d(1, 1);
    glVertex3f(pos.x-0.008f, pos.y-0.008f, pos.z+0.0f);
    //glTexCoord2d(1, 0);
    glVertex3f(pos.x+0.008f, pos.y-0.008f, pos.z+0.0f);
    //glTexCoord2d(0, 0);
    glVertex3f(pos.x+0.008f, pos.y+0.008f, pos.z+0.0f);
    //glTexCoord2d(0, 1);
    glVertex3f(pos.x-0.008f, pos.y+0.008f, pos.z+0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glPopMatrix();
}