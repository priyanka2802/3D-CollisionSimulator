#include <GL/glut.h> 
#include<bits/stdc++.h>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include "RGBpixmap.cpp"
using namespace std;
int c=0;
RGBpixmap pix[16];
int ask;
int n;

void velocity1(unsigned char , int , int );

#define cons 1.8
//gravity = 9.8 units/sec^2
float g = 9.8;
//velocity in units/sec
float v1 = 3;
float v2 = 3*cons;
//Masses are proportional to radius
float r1 = 0.5;
float r2 = 0.5;
float x = 2*(1.0 - r2);
//Coefficient of restitution
float e = 0.9; //for boundary
float e1 = 1; //for objects

int flag1 = 0, flag2 = 0;
int framen;
int h = 0;
void init(){
	glClearColor(0,0,0,0);
	glMatrixMode(GLUT_SINGLE|GLUT_RGB);
	glLoadIdentity();
	//glOrtho(-90,100,-15,100,0,1);

}

void display4(){

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1,1,-1,1,-1,1);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL,1.0);

	glPixelZoom(1,1);
	glRasterPos3f(-1,-1,0);
	pix[0].draw();

	//glutSwapBuffers();
	//glFlush();

}

void collision(){

	v2 = v2/cons;
	float m1 = r1*r1*r1;
	float m2 = r2*r2*r2;
	if(flag1==1)v1=-v1;
	if(flag2==0)v2=-v2;
	float tmp1 = ((e1*m2*(v2-v1))+(m1*v1)+(m2*v2))/(m1+m2);
	float tmp2 = ((e1*m1*(v1-v2))+(m1*v1)+(m2*v2))/(m1+m2);

	if(flag1==0 && tmp1<0){
		flag1 = 1;
		v1 = -tmp1;
		//cout << v1;
	}
	if(flag1==1 && tmp1>0){
		flag1 = 0;
		v1 = tmp1;
		//cout << v1;
	}
	if(flag1==0 && tmp1>0){
		v1 = tmp1;
		//cout << v1;
	}
	if(flag1==1 && tmp1<0){
		v1 = -tmp1;
		//cout << v1;
	}

	if(flag2==0 && tmp2>0){
		flag2 = 1;
		v2 = cons*tmp2;
		//cout << v2;
	}
	if(flag2==1 && tmp2<0){
		flag2 = 0;
		v2 = -cons*tmp2;
		//cout << v2;
	}
	if(flag2==0 && tmp2<0){
		//flag2 = 1;
		v2 = -cons*tmp2;
		//cout << v2;
	}
	if(flag2==1 && tmp2>0){
		//flag2 = 0;
		v2 = cons*tmp2;
		//cout << v2;
	}
}

void initLighting(){

	GLfloat qaAmbientLight[]    = {0.2, 0.2, 0.2, 1.0};
	GLfloat qaLightPosition[]    = {0.5, 0, -3.5, 0.5};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
}

void drawText(const char *text,int length,float x,float y){
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[36];
	glGetDoublev(GL_PROJECTION_MATRIX,matrix);
	glLoadIdentity(); 	
	glOrtho(0,800,0,600,-5,-5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos3f(x,y,0);
	for(int i=0;i<length;i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);	
}

void drawText1(const char *text,int length,float x,float y){
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[36];
	glGetDoublev(GL_PROJECTION_MATRIX,matrix);
	glLoadIdentity(); 	
	glOrtho(0,800,0,600,-5,-5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos3f(x,y,0);
	for(int i=0;i<length;i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);	
}
float ii = 3.75-r1-1;
int flag = 0;

float t = 0;
float dt = 0.05/3;
float jj = 2.5;
float i = -6.75+r1;
float r21 = cons*r2;
//float r21 = r2;
float j = 6.25+x;
void reshape(GLsizei width, GLsizei height){ 

	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();            
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int animating = 0;  
void updateFrame(){
	if(h==1){
		if(ii>=3.75-r1){
			flag = 1;
			v1 = e*v1;
		}
		if(ii<-6.75+r1){
			flag = 0;
			v1 = e*v1;
		}
			
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(1.5f, 0.0f, -7.0f);
		 
			glBegin(GL_QUADS);
		      		glColor3f(1.0f, 0.5f, 0.0f); 
				glVertex3f( 2.0f, 2.0f, -1.0f);
				glVertex3f(-5.0f, 2.0f, -1.0f);
				glVertex3f(-5.0f, 2.0f,  1.0f);
				glVertex3f( 2.0f, 2.0f,  1.0f);
			 
				glColor3f(1.0f, 0.5f, 0.0f); 
				glVertex3f( 2.0f, -2.0f,  1.0f);
				glVertex3f(-5.0f, -2.0f,  1.0f);
				glVertex3f(-5.0f, -2.0f, -1.0f);
				glVertex3f( 5.0f, -2.0f, -1.0f);

				glColor3f(1.0f, 0.5f, 0.0f); 
				glVertex3f(-5.0f,  2.0f,  1.0f);
				glVertex3f(-5.0f,  2.0f, -1.0f);
				glVertex3f(-5.0f, -2.0f, -1.0f);
				glVertex3f(-5.0f, -2.0f,  1.0f);
			 
			      
				glColor3f(1.0f, 0.5f, 0.0f); 
				glVertex3f(2.0f,  2.0f, -1.0f);
				glVertex3f(2.0f,  2.0f,  1.0f);
				glVertex3f(2.0f, -2.0f,  1.0f);
				glVertex3f(2.0f, -2.0f, -1.0f);
			glEnd(); 
			GLfloat qaGreen[] = {0.0, 1.0, 0.0, 1.0}; 
			initLighting();
			
		if(flag==0){
			glTranslatef(ii,0.0,-5.0);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
			glutSolidSphere(0.5,25,25);
			
			std::string text,text2,text3;
			text="Velocity: "+std::to_string(v1);
			drawText(text.data(),text.size(),-0.7,0.5);

			
				text2="Pause: press space or click mouse";
				drawText(text2.data(),text2.size(),-1,-0.95);
				text3="Exit: press X";
				drawText(text3.data(),text3.size(),0.65,-0.95);
			glutSwapBuffers();
			ii = ii+(v1*0.05)/3;
			glFlush();
		}
		else{
			glTranslatef(ii,0.0,-5.0);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
			glutSolidSphere(0.5,25,25);
			
			std::string text,text2,text3;
			text="Velocity: "+std::to_string(v1);
			drawText(text.data(),text.size(),-0.7,0.5);

			
				text2="Pause: press space or click mouse";
				drawText(text2.data(),text2.size(),-1,-0.95);
				text3="Exit: press X";
				drawText(text3.data(),text3.size(),0.65,-0.95);
			glutSwapBuffers();
			ii = ii-(v1*0.05)/3;
			glFlush();
		}
	}
	else if(h==0){
		if(jj>2.5){
			flag = 0;
			jj = 2.5;
			g = e*g;
		}
		if(jj<=-2.5){
			flag = 1;
			jj = -2.5;
			g = e*g;
		}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(1.5f, 0.0f, -7.0f);
		 
			glBegin(GL_QUADS);
		      		glColor3f(1.0f, 0.5f, 0.0f); 
				glVertex3f( 2.0f, 2.0f, -1.0f);
				glVertex3f(-5.0f, 2.0f, -1.0f);
				glVertex3f(-5.0f, 2.0f,  1.0f);
				glVertex3f( 2.0f, 2.0f,  1.0f);
			 
				glColor3f(1.0f, 0.5f, 0.0f); 
				glVertex3f( 2.0f, -2.0f,  1.0f);
				glVertex3f(-5.0f, -2.0f,  1.0f);
				glVertex3f(-5.0f, -2.0f, -1.0f);
				glVertex3f( 5.0f, -2.0f, -1.0f);

				glColor3f(1.0f, 0.5f, 0.0f); 
				glVertex3f(-5.0f,  2.0f,  1.0f);
				glVertex3f(-5.0f,  2.0f, -1.0f);
				glVertex3f(-5.0f, -2.0f, -1.0f);
				glVertex3f(-5.0f, -2.0f,  1.0f);
			 
			      
				glColor3f(1.0f, 0.5f, 0.0f); 
				glVertex3f(2.0f,  2.0f, -1.0f);
				glVertex3f(2.0f,  2.0f,  1.0f);
				glVertex3f(2.0f, -2.0f,  1.0f);
				glVertex3f(2.0f, -2.0f, -1.0f);
			glEnd(); 
			GLfloat qaGreen[] = {0.0, 1.0, 0.0, 1.0}; 
			initLighting();	
		if(flag==0){
			glTranslatef(0.0,jj,-5.0);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
			glutSolidSphere(0.5,25,25);
			std::string text,text2,text3;
			text="Velocity: "+std::to_string(g*t);
			drawText(text.data(),text.size(),-0.7,0.5);

			
				text2="Pause: press space or click mouse";
				drawText(text2.data(),text2.size(),-1,-0.95);
				text3="Exit: press X";
				drawText(text3.data(),text3.size(),0.65,-0.95);
			glutSwapBuffers();
			jj = jj-((g*(t))*dt);
			t = t+dt;
			glFlush();
		}
		else{
			glTranslatef(0.0,jj,-5.0);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
			glutSolidSphere(0.5,25,25);
			std::string text,text2,text3;
			text="Velocity: "+std::to_string(g*t);
			drawText(text.data(),text.size(),-0.7,0.5);
			
				text2="Pause: press space or click mouse";
				drawText(text2.data(),text2.size(),-1,-0.95);
				text3="Exit: press X";
				drawText(text3.data(),text3.size(),0.65,-0.95);
			glutSwapBuffers();
			jj = jj+(g*(t))*dt;
			t = t-dt;
			if(t<=0){
				flag = 0;
			}
			glFlush();
		}
	}
	else{
		
		//while(1){
			if(i>3.75-r1){
				i = 3.75-r1;
				flag1 = 1;
				v1 = e*v1;
			}
			if(i<-6.75+r1){
				i = -6.75+r1;
				flag1 = 0;
				v1 = e*v1;
			}
			if(j>6.25+x){
				j = 6.25+x;
				flag2 = 0;
				v2 = e*v2;
			}
			if(j<-9.25-x){
				j = -9.25-x;
				flag2 = 1;
				v2 = e*v2;
			}
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(1.5f, 0.0f, -7.0f);
			 
				glBegin(GL_QUADS);
			      		glColor3f(1.0f, 0.5f, 0.0f); 
					glVertex3f( 2.0f, 2.0f, -1.0f);
					glVertex3f(-5.0f, 2.0f, -1.0f);
					glVertex3f(-5.0f, 2.0f,  1.0f);
					glVertex3f( 2.0f, 2.0f,  1.0f);
				 
					glColor3f(1.0f, 0.5f, 0.0f); 
					glVertex3f( 2.0f, -2.0f,  1.0f);
					glVertex3f(-5.0f, -2.0f,  1.0f);
					glVertex3f(-5.0f, -2.0f, -1.0f);
					glVertex3f( 5.0f, -2.0f, -1.0f);

					glColor3f(1.0f, 0.5f, 0.0f); 
					glVertex3f(-5.0f,  2.0f,  1.0f);
					glVertex3f(-5.0f,  2.0f, -1.0f);
					glVertex3f(-5.0f, -2.0f, -1.0f);
					glVertex3f(-5.0f, -2.0f,  1.0f);
				 
				      
					glColor3f(1.0f, 0.5f, 0.0f); 
					glVertex3f(2.0f,  2.0f, -1.0f);
					glVertex3f(2.0f,  2.0f,  1.0f);
					glVertex3f(2.0f, -2.0f,  1.0f);
					glVertex3f(2.0f, -2.0f, -1.0f);
				glEnd(); 
				GLfloat qaGreen[] = {0.0, 1.0, 0.0, 1.0};
			
			
			if((i*(15.5+2*x)-j*(10.5-2*r1) >= -(20*(r1+cons*r2))/(r1+r2))){
							//cout<< "HIIIII";
							collision();
							if(flag1==1){
								i = i-(5*v1*0.05)/3;
								//i = i + (i*(15.5+2*x)-j*(10.5-2*r1))/20;
							}
							else{
								i = i+(5*v1*0.05)/3;
								//i = i - (i*(15.5+2*x)-j*(10.5-2*r1))/20;	
							}
							if(flag2==1){
								j = j+(5*v2*0.05)/3;
								//j = j - (i*(15.5+2*x)-j*(10.5-2*r1))/20;
							}
							else{
								j = j-(5*v2*0.05)/3;
								//j = j + (i*(15.5+2*x)-j*(10.5-2*r1))/20;
							}
							//flag = 1;
							//continue;
				//break;
			} 

			
			if(flag1==0){
				initLighting();
				glTranslatef(i,0.0,-5.0);
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
				glutSolidSphere(r1,25,25);
				glTranslatef(-i,0.0,-5.0);
				if(flag2==0){
					
				
					initLighting();
					glTranslatef(j,0.0,-5.0);
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
					glutSolidSphere(r21,25,25);
					//glTranslatef(-j,0.0,-5.0);
					i = i+(v1*0.05)/3;
					j = j-(v2*0.05)/3;

				}
				else{
					
				
					initLighting();
					glTranslatef(j,0.0,-5.0);
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
					glutSolidSphere(r21,25,25);
					//glTranslatef(-j,0.0,-5.0);
					i = i+(v1*0.05)/3;
					j = j+(v2*0.05)/3;

				}
				
				std::string text, text1,text2,text3;
				text="Velocity1: "+std::to_string(v1);
				drawText(text.data(),text.size(),-0.7,0.5);
				float vel = v2/cons;
				text1="Velocity2: "+std::to_string(vel);
				drawText(text1.data(),text1.size(),0.1,0.5);
				
				text2="Pause: press space or click mouse";
				drawText(text2.data(),text2.size(),-1,-0.95);
				text3="Exit: press X";
				drawText(text3.data(),text3.size(),0.65,-0.95);
				glutSwapBuffers();
				glFlush();
			}
			else{
				initLighting();
				glTranslatef(i,0.0,-5.0);
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
				glutSolidSphere(r1,25,25);
				glTranslatef(-i,0.0,-5.0);
				if(flag2==0){
					
				
					initLighting();
					glTranslatef(j,0.0,-5.0);
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
					glutSolidSphere(r21,25,25);
					//glTranslatef(-j,0.0,-5.0);
					
					i = i-(v1*0.05)/3;	
					j = j-(v2*0.05)/3;

				}
				else{
					
				
					initLighting();
					glTranslatef(j,0.0,-5.0);
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
					glutSolidSphere(r21,25,25);
					//glTranslatef(-j,0.0,-5.0);
					
					i = i-(v1*0.05)/3;	
					j = j+(v2*0.05)/3;

				}
				
				std::string text, text1, text2,text3;
				text="Velocity1: "+std::to_string(v1);
				drawText(text.data(),text.size(),-0.7,0.5);
				float vel = v2/cons;
				text1="Velocity2: "+std::to_string(vel);
				drawText(text1.data(),text1.size(),0.1,0.5);
				
				text2="Pause: press space or click mouse";
				drawText(text2.data(),text2.size(),-1,-0.95);
				text3="Exit: press X";
				drawText(text3.data(),text3.size(),0.65,-0.95);
				glutSwapBuffers();
				glFlush();
			}
			//flag=0;
		//}

	}
	framen++;
}

void timerFunction(int timerID) {
    if (animating) {
		
        updateFrame();
        glutTimerFunc(10, timerFunction, 0);
        glutPostRedisplay();
    }
}

void startAnimation() {

   if ( ! animating ) {
       animating = 1;
       glutTimerFunc(10, timerFunction, 0);
   }
}

void pauseAnimation(){
    animating = 0;
}

void pKey(unsigned char ch, int x, int y) {
    if ( ch == ' ' ) {
		if ( animating )
		   pauseAnimation();
		else
		   startAnimation();
	}
    if(ch=='X'){
		exit(0);
	} 
}



void mouseFun(int button, int state, int x, int y){

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if ( animating )
		   pauseAnimation();
		else
		   startAnimation();
	}

}

void direction(){ 
	
	cout << "Simulation started!" << endl;
	x = 2*(1.0 - r2);
	ii = 3.75-r1-1;
	i = -6.75+r1;
 	r21 = cons*r2;
	j = 6.25+x;
//If H is pressed
	if(h == 1){
		//cout << ii<< endl;
		glutMouseFunc(mouseFun);
		glutKeyboardFunc(pKey);
		startAnimation();
	}
//If V is pressed
	if(h == 0){
		glutMouseFunc(mouseFun);
		glutKeyboardFunc(pKey);
		startAnimation();
	}
	if(h == 3){
		glutMouseFunc(mouseFun);
		glutKeyboardFunc(pKey);
		startAnimation();
	}
	
 
}

void cRes1(unsigned char key, int x, int y){

	int s = 48;
	if(key>=48 && key <=57){

		e = key - s;
		e = e/10+0.1;
		cout << "e: "<<e << endl;
		direction();
	}

}

void cRes2(unsigned char key, int x, int y){

	int s = 48;
	if(key>=48 && key <=57){
		
		e1 = key - s;
		e1 = e1/10+0.1;
		cout << "e1: "<<e1 << endl;
		glutKeyboardFunc(velocity1);
	}

}


void radius1(unsigned char key, int x, int y){

	int s = 48;
	if(key>=49 && key <=52){
		
		r1 = key - s;
		r1 = r1/2;
		cout << "r1: "<<r1 << endl;
		glutKeyboardFunc(cRes1);
	}

}

void radius2(unsigned char key, int x, int y){

	int s = 48;
	if(key>=49 && key <=52){
		
		r2 = key - s;
		r2 = r2/2;
		cout << "r2: "<<r2 << endl;
		glutKeyboardFunc(cRes2);
	}

}

void velocity1(unsigned char key, int x, int y){

	int s = 48;
	if(key>=49 && key <=57){
		
		v1 = key - s;
		cout << "v1: "<<v1 << endl;
		glutKeyboardFunc(radius1);
	}

}

void velocity2(unsigned char key, int x, int y){

	int s = 48;
	if(key>=49 && key <=57){
		
		v2 = key - s;
		cout << "v2: "<<v2 << endl;
		v2 = v2*cons;
		glutKeyboardFunc(radius2);
	}

}

void motion(int button, int state, int x, int y){
	//cout << x;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && n==2 && ask == 0){
		h = 3;
		cout << "Horizontal\n";
		direction();
	}

	else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && n==2 && ask == 1){
		h = 3;
		cout << "Horizontal\n";
		glutKeyboardFunc(velocity2);
	}

	else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 310){
		h = 0;
		cout << "Vertical\n";
		if(ask==0){
			direction();
		}
		else{
			glutKeyboardFunc(velocity1);

		}
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x <310){
		h = 1;
		cout << "Horizontal\n";
		if(ask==0){
			direction();
		}
		else{
			glutKeyboardFunc(velocity1);
		}
	}

}

void noOfParticles(int button, int state, int x, int y){

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 220){
		n = 2;
		cout << "2 Particles\n";
		glutMouseFunc(motion);
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x <220){
		n = 1;
		cout << "1 Particle\n";
		glutMouseFunc(motion);
	}

}



void input1(int button, int state, int x, int y){

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 335){
		ask=0;
		cout << "Default\n";
		glutMouseFunc(noOfParticles);
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x <335){
		ask=1;
		cout << "Manual\n";
		glutMouseFunc(noOfParticles);
	}

}
void space(unsigned char key, int x, int y){

	if(key==32){
			
			glColor3f(1,1,1);
		
			std::string text;
			text="Collision Simulation";
			drawText1(text.data(),text.size(),-0.3,0.90);
			text="Click on method of input: 1.Manual          2.Default";
			drawText(text.data(),text.size(),-0.95,0.70);
			text="Number of particles: 1          2";
			drawText(text.data(),text.size(),-0.95,0.55);
			text="Direction of motion: 1.Horizontal          2.Vertical";
			drawText(text.data(),text.size(),-0.95,0.40);
			text="For manual inputs, enter the inputs in given order for each particle:";
			drawText(text.data(),text.size(),-0.95,0.20);
			text="Velocity of the particle[1,9]";
			drawText(text.data(),text.size(),-0.95,0.05);
			text="Diameter of the particle[1,4]";
			drawText(text.data(),text.size(),-0.95,-0.10);
			text="Cofficient of restitution[0,9](will be converted to the range[0,1])";
			drawText(text.data(),text.size(),-0.95,-0.25);
			text="(For collison between particles and";
			drawText(text.data(),text.size(),-0.95,-0.40);
			text="for collision between particle and the boundary)";
			drawText(text.data(),text.size(),-0.95,-0.55);
			glutSwapBuffers();
			glFlush();
			//glutKeyboardFunc(input); 
			glutMouseFunc(input1);
	}

}


int main(int argc, char** argv){

	glutInit(&argc, argv);            
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize(640, 480);   
	glutCreateWindow("Collision Simulation");
	//glutDisplayFunc(draw);
		pix[0].readBMPFile("images.bmp",true);	//glutReshapeFunc(reshape); 
	//if(c==0){
					       display4();  c++;
	//}
	cout << "Enter space key\n";
	glutKeyboardFunc(space); 
	framen = 0;
	glutReshapeFunc(reshape); 
	glutMainLoop();           
	glutHideWindow();
	return 0;
}
