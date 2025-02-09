precision mediump float;
uniform float u_time;
        
// A simple cosine-based color palette.
vec3 palette(float t) {
    vec3 a = vec3(0.5);
    vec3 b = vec3(0.5);
    vec3 c = vec3(1.0);
    vec3 d = vec3(0.0, 0.33, 0.67);
    return a + b * cos(6.28318 * (c * t + d));
}
        
void main() {
    vec2 resolution = vec2(1920, 1080);
    // Map pixel coordinates to normalized space.
    vec2 uv = (gl_FragCoord.xy - 0.5 * resolution.xy) / resolution.y;
          
    // Apply a slow rotation.
    float angle = u_time * 0.1;
    float s = sin(angle);
    float c = cos(angle);
    uv = vec2(uv.x * c - uv.y * s, uv.x * s + uv.y * c);
          
    // Fractal constant modulated by time.
    vec2 c_const = vec2(sin(u_time * 0.5), cos(u_time * 0.3));
    vec2 z = uv * 1.5;
          
    // Compute (smoothed) iteration count.
    float iteration = 0.0;
    const float maxIteration = 1000.0;
    float mu = 0.0;
    for (float i = 0.0; i < maxIteration; i++) {
    z = vec2(z.x*z.x - z.y*z.y, 2.0*z.x*z.y) + c_const;
    if (dot(z, z) > 4.0) {
        iteration = i;
        float log_zn = log(dot(z, z)) / 2.0;
        float nu = log(log_zn / log(2.0)) / log(2.0);
        mu = i + 1.0 - nu;
        break;
    }
    iteration = i;
    mu = i;
    }
          
    // Normalize the iteration count and adjust for contrast.
    float normIter = mu / maxIteration;
    normIter = pow(normIter, 0.3);
    vec3 color = palette(normIter + u_time * 0.1);
          
    // Brighten dark colors slightly.
    float brightness = (color.r + color.g + color.b) / 3.0;
    if (brightness < 0.2) {
    color += vec3(0.2);
    }
          
    gl_FragColor = vec4(color, 1.0);
}
