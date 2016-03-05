varying vec3 fragment_color;
varying vec3 fragment_normal;

//
// this shader just assigned the fragment wiith the interpolated color 
//
void main()
{
    gl_FragColor = vec4(fragment_color, 1.0);
}
