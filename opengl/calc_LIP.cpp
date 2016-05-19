#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>

double z = 0.8;		// 初期位置高さ
double x =  0.15;	// 初期位置横
double f = 0.0;		//蹴り力
const double m = 10.00;	//重量kg
const double dt = 0.01;	//インターバル
const double g = 9.8; 	//重力加速m/s^2

double v_x = -0.46;	//初速度及びx方向の速度



void display(void)		//ディスプレイの表示
{
	double roll_x;
	double roll_y;
	double deg;
	double rad = 0;
	double arg = 0.0;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(100, 0);
	glVertex2d(-100, 0);
	glEnd();

	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glVertex2d(30*x, 30*z);
	glVertex2d(0, 0);
	glEnd();
	glTranslatef(30*x, 30*z, 0);
	glRotatef(arg, 0.0, 0.0, 1.0);

	while(1){
		deg = deg + 1;
		rad = deg * M_PI/180;

		roll_x = sin(rad);
		roll_y = cos(rad);

		glRectf(1*roll_x, 1*roll_y, 0.0, 0.0);
		if(deg == 360)break;
	}
	glPopMatrix();

	glutSwapBuffers();
}

void simu(void)			//教科書p104~112までの内容
{
	double E = 0.0;		//軌道エネルギー
	double v = 0.0;		//瞬間の速度
	double x_a = 0.0;	//瞬間の位置

	double a_z = 0.0;	//ｚ方向の加速度
	double v_z = 0.0;	//ｚ方向の速度

	const double F = -m * g;	//重力

	double a_x = 0.0;	//ｘ方向の加速度

	double s;			//倒立振子の回転角
	s = atan(x / z) * 180/M_PI;
	printf("s:%lf \n",s);

	if( -60 < s && s < 60 ){
		s = s * M_PI/180;

		f = m * g /cos(s);		//蹴り力の設定 (4.2)

		a_z = (f*cos(s)+F) / m;		//ｚ方向の運動 (4.3)
		v_z += a_z * dt;
		z += v_z *dt;

		a_x = f*sin(s) / m;		//ｘ方向の運動
		v_x += a_x * dt;
		x += v_x *dt;
	}

	glutPostRedisplay();

	E = (v_x*v_x)/2-(g*x*x)/(2*z);		//軌道エネルギーの計算 (4.11)

	printf("---Orbital energy---/%lf/------\n", E);

	/*軌道エネルギーを比較してポテンシャルの山を越えるか
	over-越えた場合　　under-越えない
	p112の内容を計算する。*/

	if(E > 0){
		printf("---potential <<< over >>>\n");
		v = 2*E;
		v = sqrt(v);
		printf("---v----/%lf/----------\n", v);
	}
	else if(E <= 0){
		printf("---potential <<< under >>>\n");
		x_a = -(2*z*E)/g;
		x_a = sqrt(x_a);
		printf("---x_a-----/%lf/------------\n", x_a);
	}
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
	glViewport( 0, 0, 300, 300 );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y){
	switch (key) {
		case '\x1b':
			exit(0);
			break;
	}
}


void mouse(int button, int state, int x, int y){
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if ( state == GLUT_DOWN)
				glutIdleFunc(simu);
			break;

		case GLUT_RIGHT_BUTTON:
			if ( state == GLUT_DOWN){
				glutIdleFunc(NULL);
				exit(0);
			}break;
		default:
			break;
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (300, 300);
	glutInitWindowPosition (1000, 100);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}

