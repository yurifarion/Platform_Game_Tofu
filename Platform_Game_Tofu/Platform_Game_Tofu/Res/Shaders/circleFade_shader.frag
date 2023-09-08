#version 120
#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;
uniform vec2 u_center;

float circle(in vec2 _st, in float _radius){
    vec2 dist = _st-vec2(0.5);
	return smoothstep(_radius-(_radius*0.01),
                         _radius+(_radius*0.01),
                         dot(dist,dist)*4.0);
}

void main(){
	vec2 st = gl_FragCoord.xy/u_resolution.xy;
	st -= u_center; // <-0.5, 0.5>
	st.x *= u_resolution.x/u_resolution.y; // fix aspect ratio

	vec4 color = vec4(0.0,0.0,0.0,circle(st,0 + u_time*8));

	gl_FragColor = vec4( color);
}