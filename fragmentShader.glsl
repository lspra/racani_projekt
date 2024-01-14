#version 450 core
out vec4 FragColor;
in vec4 pos;
uniform float time;

float circle(vec2 p, vec2 center) {
    return (abs(p.x) - center.x)*(abs(p.x) - center.x) + (p.y - center.y)*(p.y - center.y);
}

float shape(vec2 p) {
    float c = circle(p, vec2(0.6, 0.6));
    float sin1 = 0.014 * sin(127 * p.x + 4*time);
    float sin2 = 0.007 * sin(211 * p.x + 100 + 3*time);
    float sin3 = 0.003 * sin(331 * p.x + 15 + 7*time);
    float sin4 = 0.004 * sin(383 * p.x + 70 + 5*time);
    return c + sin1 - sin2 + sin3 -sin4 - 0.36f;
}

float spark_shape(vec2 p) {
    vec2 trans_p;   
    trans_p.x = p.x + 0.01 * abs(sin(127 * p.x + time)) + 0.008 * abs(sin(211 * p.x + 100 + 2*time));
    trans_p.y = p.y + 0.01 * abs(sin(131 * p.x + time)) + 0.008 * abs(sin(199 * p.x + 100 + 2*time));
    trans_p.x *= 2;
    float cx = 0.1f + 0.5f * pos.z;
    float cy = 0.1f * pos.z + 0.4 - cx;
    if(p.x < 0.0f)
        cx += 0.07f;
    return circle(trans_p, vec2(cx, cy)) - 0.0007f;
}

vec4 addSpark(vec2 p) {
    if(abs(p.x) > 0.0f && p.y > 0.0f) {
        if(spark_shape(p) < -0.0006f)
            return vec4(1.0f, 1, 0.0f, 1.0f);
        if(spark_shape(p) < -0.0004f)
            return vec4(1.0f, 0.6, 0.0f, 1.0f);
        if(spark_shape(p) < -0.0002f)
            return vec4(1.0f, 0.3, 0.0f, 1.0f);
        if(spark_shape(p) < 0.0f)
            return vec4(1.0f, 0, 0.0f, 1.0f);
    }
    return vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

void main()
{
    FragColor = vec4(0.0, 0.0f, 0.0f, 1.0f);
    if(pos.y > 0.0f && abs(pos.x) < 0.6f && pos.y < 0.6f) {
        float shape_v = shape(pos.xy);
        if(shape_v > 0.25f)
            FragColor = vec4(1.0f, 1- length(pos.xy)*2 + shape_v / 1.5, 0.3f, 1.0f);
        else if(shape_v > 0.2f)
            FragColor = vec4(1.0f, 1- length(pos.xy)*3 + shape_v / 1.75, 0.15f, 1.0f);
        else if(shape_v > 0.15f)
            FragColor = vec4(1.0f, 1- length(pos.xy)*3 + shape_v / 2, 0.0f, 1.0f);
        else if(shape_v > 0.1f)
            FragColor = vec4(1.0f, 1- length(pos.xy)*3.5 + shape_v / 2.5, 0.0f, 1.0f);
        else if(shape_v > 0.07f)
            FragColor = vec4(1.0f, 1- length(pos.xy)*5 + shape_v / 3, 0.0f, 1.0f);
        else if(sin(time) > 0.0)
            FragColor = addSpark(pos.xy - vec2(sin(2*time) * 0.03f, -cos(time) * 0.05)) * sin(time);
    }
} 