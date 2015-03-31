// SL 2012-02-08

uniform sampler2D u_Image;

varying vec2      v_TexCoord;

uniform vec2      u_ImageSize;
uniform vec4      u_UVWH;

void main()
{
  vec2 uv         = ((v_TexCoord  * u_UVWH.zw) + u_UVWH.xy) / u_ImageSize.xy;
  gl_FragColor    = texture2D( u_Image, uv );
}

