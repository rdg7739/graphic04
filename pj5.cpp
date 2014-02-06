#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "vrtx.h"
#include <sstream>
#include <stdlib.h>
#include <math.h>
#define delta = 0.00004444449
#define foo = 1000000
using std::stringstream;
using std::string;
using namespace std;

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

//GLfloat camX=0, camY=25, camZ=78;
GLfloat camX=0, camY=0, camZ=500;
GLfloat focX = 0.0, focY = 0, focZ = 0, angleX = 0.0, angleY = 0.0, angleZ = 0.0;
double dh = 0.5, ds = 0.5, dv = 0.5;
vector< vector<vrtx> > segList;
vector< int > vrtxsNum;
float segNum, vrtNum;
GLfloat lightpos[4] = { 0.0, 3.0, 2.0, 0.0 };
GLfloat lightamb[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightdif[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lmodel_ambient[]={0.4, 0.4, 0.4, 1.0};
GLfloat local_view[]={0.0};

void findHSV(float r, float g, float b, float *h, float *s, float *v){

float hueHSV, cmaxHSV = 0.0, cminHSV, deltaHSV;
	cmaxHSV = std::max(r, std::max(g,b));
	cminHSV = std::min(r, std::min(g,b));
	deltaHSV = cmaxHSV - cminHSV;
		*s = deltaHSV / cmaxHSV;
		*v = cmaxHSV;
	if( deltaHSV = 0)
		deltaHSV = 1;
	if( r == cmaxHSV)
		hueHSV = (g -b) / deltaHSV;
	else if (g == cmaxHSV)
		hueHSV = 2 + (b-r) / deltaHSV;
	else 
		hueHSV = 4 + (r-g) / deltaHSV;
	if (hueHSV < 0)
		hueHSV += 6.0;
	*h = hueHSV * (1.0/6.0);
//	cout << &h << endl;
	}

void findRGB(float *r, float *g, float *b, float h, float s, float v){

float c1, c2, modH, cmin, i;
c1 = s * v;

h /= 60;
modH = fmod( h, 2.0f);
c2 = c1 * ( 1 - abs(modH -1));

i = floor(h);
cmin = v - c1;


if( i == 0){
*r = c1;
*g = c2;
*b = 0;
}
else if (i == 1){
*r = c2;
*g = c1;
*b = 0;
}

else if (i == 2){
*r = 0;
*g = c1;
*b = c2;
}
else if (i == 3){
*r = 0;
*g = c2;
*b = c1;
}
else if (i == 4){
*r = c2;
*g = 0;
*b = c1;
}
else if (i == 5){
*r = c1;
*g = 0;
*b = c2;
}
*r += cmin;
*g += cmin;
*b += cmin;
//cout << r << g << b << endl;
}
void findRGB(float *r, float *g, float *b, float num){

 float s = 1 * ds;
 float v = 1 * dv;
 float h = num * 0.0004 * 1000000 * dh;
 int i = 0;
 float modH;
 float temp1, temp2, temp3, temp4;
if( s == 0){
	*r = v;
	*g = v;
	*b = v;
	return;
}
h /= 60;
i = floor(h);
temp1 = h - i;
temp2 = v * ( 1 - s);
temp3 = v * ( 1 - s * temp1);
temp4 = v * ( 1 - s * ( 1 - temp1));

if( i == 0){
*r = v;
*g = temp4;
*b = temp2;
}
else if (i == 1){
*r = temp3;
*g = v;
*b = temp2;
}

else if (i == 2){
*r = temp2;
*g = v;
*b = temp3;
}
else if (i == 3){
*r = temp2;
*g = temp3;
*b = temp4;
}
else if (i == 4){
*r = temp4;
*g = temp2;
*b = v;
}
else if (i == 5){
*r = v;
*g = temp2;
*b = temp3;
}
//cout << r << g << b << endl;
}

void init(void){
  glShadeModel (GL_SMOOTH);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();
    glClearColor(0.5, 0.5, 0.5, 1.0); 
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightamb);
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightdif);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
ifstream theFile ("./region_s3.data");
if(!theFile){
	cerr << "Error: Open file error!" << endl;
	exit(1);
}else{
cout << "Loading file: " << "region_s3.data" << endl;
int i, j;
theFile >> segNum;
cout << segNum << endl;
for( i = 0; i < segNum; i++){
	theFile >> vrtNum;
	vrtxsNum.push_back(vrtNum);
	vector<vrtx> vrtxList;
	for( j =0; j < vrtNum; j++){
		float x, y, z, a1, a2, a3;
		theFile >> x >> y >>  z >> a1 >> a2 >> a3;
		vrtx ho;
		ho.setVRTX(x, y, z, a1, a2, a3);
		vrtxList.push_back(ho);
	}
	segList.push_back(vrtxList);
}
}}


void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'h':
	dh -= 0.050;
	if(dh < 0)
	dh += 1;
	break;
      case 'H':
        dh += 0.050;
	if(dh > 1)
	dh -= 1;
	break;
      case 's':
	ds -= 0.050;
	if(ds < 0)
	ds += 1;
	break;
      case 'S':
	ds += 0.050;
	if(ds > 1)
	ds -= 1;
	break;
      case 'v':
	dv -= 0.050;
	if(dv < 0)
	dv += 1;
	break;
      case 'V':
	dv += 0.050;
	if(dv > 0)
	dv -= 1;
	break;

      case 27:
         exit(0);
         break;
   }
   glutPostRedisplay();
glFlush();
}




void Reshape(int w, int h)
{

glViewport(0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(30, 200, 0*(GLfloat)h/(GLfloat)w, 200*(GLfloat)h/(GLfloat)w, -200, 200);
gluLookAt(50, 30, 200, 0, 30, 3, 0, 1, 0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

glutPostRedisplay();
glFlush();
}

void Display(void)
{
int i, j;
float x1, y1, z1, a11, a21, a31, r, g, b;	
 glLoadIdentity();
glClear (GL_COLOR_BUFFER_BIT);
	vector<vrtx> vrtxList;
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
for(i = 0; i < segNum; i++){
	vrtxList = segList[i];
	glBegin(GL_LINE_STRIP);
//	cout << vrtxsNum[i] << endl;
	for( j = 0; j < vrtxsNum[i]; j++){
	x1 = vrtxList[j].x;
	y1 = vrtxList[j].y;
	z1 = vrtxList[j].z;
	a11 = vrtxList[j].a1;
	a21 = vrtxList[j].a2;
	a31 = vrtxList[j].a3;
	//cout << a21 ;
	findRGB(&r, &g, &b, a21);
	glColor3f(r, g, b);
	glVertex3f(x1, y1, z1);
	//cout <<"X: "<< x1 << " Y: "<<  y1 <<" Z: "<< z1 <<" A1: "<< a11 <<" A2: "<< a21 <<" A3: "<< a31 << endl;
 	}
	
	glEnd();
}	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glutPostRedisplay();
   glFlush();
}
void paletteInit(){

  glShadeModel (GL_SMOOTH);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);

	
    glLoadIdentity();
    glClearColor(1, 1, 1, 1.0); 
   
}
void drawPalette(){
 glMatrixMode(GL_MODELVIEW);  
 glLoadIdentity();
glClear (GL_COLOR_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

float px, py, i, j,pz;
px  = 20;
py = 20;
float line =20;
j = 0;
for ( i =20; i < 160; i+=0.1){
glBegin(GL_LINE_STRIP);
	glColor3f(1.0-j, 1.0-j, 1.0-j);
	glVertex3f(30+i, 50, pz);
	glVertex3f(30+i, 80, pz);
glEnd();
	j += 1.0/1400.0;
}
glEnable(GL_DEPTH);
glEnable(GL_LIGHT0);
glEnable(GL_LIGHTING);
glutPostRedisplay();
   glFlush();
}


void mouse(int button, int state, int x, int y)
{
unsigned char pixel[3] = {0};
  switch (button){
	case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN){ 
		
		glReadPixels(x, y, 1,1, GL_RGBA, GL_UNSIGNED_BYTE, pixel); 
		//cout << x << " " << y<< endl;
		if(x > 50 && x < 360 &&  y > 300 && y < 360)
			
		cout << "ho : " << (float) pixel[0]<<"  " << (float) pixel[1]<< " " << (float)pixel[2]<<endl; 
 
}	
		break;
	default:
		break;
}
	glutPostRedisplay();
	glFlush();
}

int main(int argc, char **argv){
   glutInit(&argc, argv);
   glutInitWindowSize (800, 800);
   glutInitWindowPosition (100, 100);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutCreateWindow ("DISPLAY");

   init();

   glutDisplayFunc(Display);
   glutReshapeFunc(Reshape);
   glutKeyboardFunc (keyboard);


   glutInitWindowSize(400, 400);
   glutCreateWindow("color palette");
   glutPositionWindow(900, 100);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   paletteInit();
   glutReshapeFunc(Reshape);
   glutDisplayFunc(drawPalette);
   glutMouseFunc(mouse);
   glutKeyboardFunc(keyboard);
 
 glutSwapBuffers();
  glutMainLoop();
	return 0;
}
