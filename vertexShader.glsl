attribute vec4 vPosition;
attribute vec4 vNormal;

uniform mat4 mModelView;
uniform mat4 mProjection;
//uniform mat4 mNormals;

void main(){
  //gl_Position = mProjection * mView * mModel * (vPosition + 0.1*vNormal);
  gl_Position = mProjection * mModelView * vPosition;
}
