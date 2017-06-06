#include "Kinematics.h"
#include "Link.h"

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

static double step = 1.f;

static GLdouble angle[6];

static GLdouble centerX = 0.0f;
static GLdouble centerY = 0.0f;
static GLdouble centerZ = 0.0f;

/*
 * 直方体を描く
 */
static void myBox(double x, double y, double z)
{
  GLdouble vertex[][3] = {
    { -x, -y, -z },
    {  x, -y, -z },
    {  x,  y, -z },
    { -x,  y, -z },
    { -x, -y,  z },
    {  x, -y,  z },
    {  x,  y,  z },
    { -x,  y,  z }
  };

  const static int face[][4] = {
    { 0, 1, 2, 3 },
    { 1, 5, 6, 2 },
    { 5, 4, 7, 6 },
    { 4, 0, 3, 7 },
    { 4, 5, 1, 0 },
    { 3, 2, 6, 7 }
  };

  const static GLdouble normal[][3] = {
    { 0.0, 0.0,-1.0 },
    { 1.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0 },
    {-1.0, 0.0, 0.0 },
    { 0.0,-1.0, 0.0 },
    { 0.0, 1.0, 0.0 }
  };

  const static GLfloat red[] = { 0.3, 0.6, 0.8, 1.0 };

  int i, j;

  /* 材質を設定する */
  glMaterialfv(GL_FRONT, GL_DIFFUSE, red);

  glBegin(GL_QUADS);
  for (j = 0; j < 6; ++j) {
    glNormal3dv(normal[j]);
    for (i = 4; --i >= 0;) {
      glVertex3dv(vertex[face[j][i]]);
    }
  }
  glEnd();
}

/*
 * 円柱を描く
 */
static void myCylinder(double radius, double height, int sides)
{
  const static GLfloat yellow[] = { 0.5, 0.5, 0.5, 1.0 };
  double step = 6.28318530717958647692 / (double)sides;
  int i = 0;

  /* 材質を設定する */
  glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);

  /* 上面 */
  glNormal3d(0.0, 1.0, 0.0);
  glBegin(GL_TRIANGLE_FAN);
  while (i < sides) {
    double t = step * (double)i++;
    glVertex3d(radius * sin(t), height, radius * cos(t));
  }
  glEnd();

  /* 底面 */
  glNormal3d(0.0, -1.0, 0.0);
  glBegin(GL_TRIANGLE_FAN);
  while (--i >= 0) {
    double t = step * (double)i;
    glVertex3d(radius * sin(t), -height, radius * cos(t));
  }
  glEnd();

  /* 側面 */
  glBegin(GL_QUAD_STRIP);
  while (i <= sides) {
    double t = step * (double)i++;
    double x = sin(t);
    double z = cos(t);

    glNormal3d(x, 0.0, z);
    glVertex3f(radius * x, height, radius * z);
    glVertex3f(radius * x, -height, radius * z);
  }
  glEnd();
}

/*
 * 地面を描く
 */
static void myGround(double height)
{
  const static GLfloat ground[][4] = {
    { 0.6, 0.6, 0.6, 1.0 },
    { 0.3, 0.3, 0.3, 1.0 }
  };

  int i, j;

  glBegin(GL_QUADS);
  glNormal3d(0.0, 1.0, 0.0);
  for (j = -5; j < 5; ++j) {
    for (i = -5; i < 5; ++i) {
      glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i + j) & 1]);
      glVertex3d((GLdouble)i, height, (GLdouble)j);
      glVertex3d((GLdouble)i, height, (GLdouble)(j + 1));
      glVertex3d((GLdouble)(i + 1), height, (GLdouble)(j + 1));
      glVertex3d((GLdouble)(i + 1), height, (GLdouble)j);
    }
  }
  glEnd();
}

/*
 * 画面表示
 */
static void display(void)
{
  const static GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };     /* 球の色 */
  const static GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 }; /* 光源の位置 */

  /* 画面クリア */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* モデルビュー変換行列の初期化 */
  glLoadIdentity();

  /* 光源の位置を設定 */
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

  /* 視点の移動（シーンの方を奥に移す）*/
  glTranslated(0.0, 0.0, -10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt( -20.0f, 10.0f, -20.0f,
	            centerX, centerY, centerZ,
	            0.5f, 0.5f, 0.5f);

  /* シーンの描画 */
  myGround(-2.0);                           /* 地面　　　 */

	// 土台
  glTranslated(0.0, -1.8, 0.0);
	glRotated(angle[0], 0.0, 1.0, 0.0);
  myCylinder(0.8, 0.2, 16);                 /* 土台　　　 */

	// 一番目の腕
  glTranslated(0.0, 1.0, 0.0);
  myBox(0.2, 1.2, 0.2);
	// 関節
  glTranslated(0.0, 1.0, 0.0); glRotated(90.0, 1.0, 0.0, 0.0);
  glRotated(angle[1], 0.0, 1.0, 0.0);
  myCylinder(0.3, 0.4, 16);

	// 2番目の腕
  glTranslated(0.0, 0.0, -1.0);
  myBox(0.2, 0.2, 1.2);
	// 関節
  glTranslated(0.0, 0.0, -1.0);
  glRotated(angle[2], 0.0, 1.0, 0.0);
	glRotated(angle[3], 0.0, 0.0, 1.0);
  myCylinder(0.3, 0.4, 16);

	// 3番目の腕
  glTranslated(0.0, 0.0, -1.0);
  myBox(0.2, 0.2, 1.2);
	// 関節
  glTranslated(0.0, 0.0, -1.0);
  glRotated(angle[4], 0.0, 1.0, 0.0);
  myCylinder(0.3, 0.4, 16);

	// 4番目の腕
  //glTranslated(0.0, 0.0, -1.0);
  //myBox(0.2, 0.2, 1.2);
	// 関節
  //glTranslated(0.0, 0.0, -1.0);
  //glRotated(angle[4], 0.0, 1.0, 0.0);
  //myCylinder(0.3, 0.4, 16);

	// 5番目の腕
  glTranslated(0.0, 0.0, -0.4);
  myBox(0.2, 0.2, 0.6);

	// ハンド
  glTranslated(0.0, 0.0, -0.9);
	glRotated(angle[5], 0.0, 0.0, 1.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
  glutSolidCube(0.7);

  glFlush();
}

static void resize(int w, int h)
{
  /* ウィンドウ全体をビューポートにする */
  glViewport(0, 0, w, h);

  /* 透視変換行列の指定 */
  glMatrixMode(GL_PROJECTION);

  /* 透視変換行列の初期化 */
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

  /* モデルビュー変換行列の指定 */
  glMatrixMode(GL_MODELVIEW);
}

static void keyboard(unsigned char key, int x, int y)
{
  /* ESC か q をタイプしたら終了 */
  if (key == '\033' || key == 'q') {
    exit(0);
  }else if(key == 'f'){
		angle[0] += step;
	}else if(key == 'j'){
		angle[0] -= step;
	}else if(key == 'd'){
		angle[1] += step;
	}else if(key == 'k'){
		angle[1] -= step;
	}else if(key == 's'){
		angle[2] += step;
	}else if(key == 'l'){
		angle[2] -= step;
	}else if(key == 'r'){
		angle[3] += step;
	}else if(key == 'u'){
		angle[3] -= step;
	}
}

void idle(void)
{
	glutPostRedisplay();
}

static void init(void)
{
  /* 初期設定 */
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

int main(int argc, char *argv[])
{
	Link ulink[JOINT_NUM];
	Kinematics ik_node(ulink);
	SetJointInfo(ulink);

	for(int i=0;i<6;i++)
		angle[i] = 0.0f;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
  init();
  glutMainLoop();
  return 0;
}
