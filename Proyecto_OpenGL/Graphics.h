#ifndef _GRR
#define _GRR
#include <windows.h>
#include <windowsx.h>
#include <gl\GLU.h>
#include <gl\GL.h>
#include "glext.h"
#include "SkyDome.h"
#include "GeoPlane.h"
float poscx, poscy, poscz, dircx, dircy, dircz, LuzX, LuzY, LuzZ, EscaladoX, EscaladoY, EscaladoZ;
SkyDome *Mars, *Earth, *Jupiter, *SpaceWindow,*navebola,*panel,*meteoro,*ovni,*vidrio;
int Rotacion = 0;
int Rotacion2 = 0;
int RotacionPlaneta = 0;
int movX = 0, movY = 0, movZ;
class Camara {
public:
	Camara()
	{
	}

	void CamaraUpdate()
	{
		gluLookAt(poscx, poscy, poscz,
			dircx, dircy, dircz,
			0, 1, 0);
	}
};

class Graph : public Camara
{
public:
	
	float angulo, gira;

	Graph(HWND hWnd)
	{
		//experimenten cambiandole de valores a la camara
		poscx = 0;
		LuzX = 0;
		poscy = 1;
		LuzY = 100;
		poscz = 25;
		LuzZ = 0;
		dircx = 0;
		dircy = 0;
		dircz = 0;
		angulo = 0; 
		gira = 0;
		EscaladoX = 1;
		EscaladoY = 1;
		EscaladoZ = 1;

		glShadeModel(GL_SMOOTH);
		//habilitamos el control de profundidad en el render
		glEnable(GL_DEPTH_TEST);
		//habilitamos la iluminacion
		glEnable(GL_LIGHTING);

		// habilitamos la luz 0 o primer luz
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		//habilitamos la forma de reflejar la luz
		glEnable(GL_COLOR_MATERIAL);

		//Habilitamos las texturas
		//Mars = new SkyDome(hWnd, 32, 32, 50, L"FIRE2.jpg");
		Mars = new SkyDome(hWnd, 32, 32, 50, L"EnergySphere.png");
		Earth = new SkyDome(hWnd, 32, 32, 25, L"EarthTexture.jpg");
		SpaceWindow = new SkyDome(hWnd, 6, 6, 100, L"WindowTexture.jpg");
		Jupiter = new SkyDome(hWnd, 32, 32, 100, L"JupiterTexture.jpg");
		navebola = new SkyDome(hWnd, 32, 32, 5, L"nave-bola.jpg");
		panel = new SkyDome(hWnd, 4, 3, 10, L"panel.jpg");
		meteoro = new SkyDome(hWnd, 8, 10, 10, L"meteoro.jpg");
		ovni = new SkyDome(hWnd, 32, 32, 10, L"ovni.jpg");
		vidrio = new SkyDome(hWnd, 32, 32, 10, L"vidrio.jpg");
		
	}

	
	void DrawSpaceship(float spacex, float spacey, float spacez) {

		//Dibuja base Principal
		GLfloat LightSpcu[] = { 0, 0, 10, 1.0 };
		GLfloat LightPosSpcu[] = { spacex, spacey, spacez, 0.0 };
		glLightfv(GL_LIGHT1, GL_DIFFUSE, LightSpcu);
		glLightfv(GL_LIGHT1, GL_POSITION, LightPosSpcu);
		//Bases de la nave
		glPushMatrix();
		glTranslatef(spacex, spacey, spacez);
			glPushMatrix();
				//Dibuja esfera oscura
				glPushMatrix();
					glColor3f(1, 1, 1);
					glTranslatef(0, 70, 0);
					//glScalef(1.0f, 1.5f, 1.0f);
					glRotatef(180, 1.0f, 0.0f, 0.0f);
					Mars->Draw();
				glPopMatrix();

				glPushMatrix();
					glColor3f(1, 1, 1);
					glTranslatef(0, 140, 0);
					glScalef(1.0f, 0.5f, 1.0f);
					glRotatef(180, 1.0f, 0.0f, 0.0f);
					SpaceWindow->Draw();
				glPopMatrix();

				glPushMatrix();
					glColor3f(1, 1, 1);
					glTranslatef(100, 140, 0);
					glScalef(.5f, 0.25f, .5f);
					glRotatef(180, 1.0f, 0.0f, 0.0f);
					SpaceWindow->Draw();
				glPopMatrix();

				glPushMatrix();
					glColor3f(1, 1, 1);
					glTranslatef(-100, 145, 0);
					glScalef(.5f, 0.25f, .5f);
					glRotatef(180, 1.0f, 0.0f, 0.0f);
					SpaceWindow->Draw();
				glPopMatrix();

				glPushMatrix();
					glColor3f(1, 1, 1);
					glTranslatef(50, 160, 100);
					glScalef(.5f, 0.25f, .5f);
					glRotatef(180, 1.0f, 0.0f, 0.0f);
					SpaceWindow->Draw();
				glPopMatrix();
			glPopMatrix();

			//Alerones de la nave
			glPushMatrix();
				glPushMatrix();
					glColor3f(0, 0.5, 1);
					glRotatef(Rotacion2, 0, 1, 0);
					glTranslatef(0.0f, 80.0f, -80.0f);
					glRotatef(90, 0.0f, 1.0f, 0.0f);
					glScalef(1.0f, 4.0f, 0.0f);
					glutSolidCube(20);
				glPopMatrix();

				glPushMatrix();
					glColor3f(0, 0.5, 1);
					glRotatef(Rotacion2, 0, 1, 0);
					glTranslatef(0.0f, 80.0f, 80.0f);
					glRotatef(90, 0.0f, 1.0f, 0.0f);
					glScalef(1.0f, 4.0f, 0.0f);
					glutSolidCube(20);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		

	}

	void DrawHT1Z1(float posbolax, float posbolay, float posbolaz, GLUquadricObj*quadratic) {
		glPushMatrix();
		glTranslatef(posbolax, posbolay, posbolaz);
			glPushMatrix();
				//(1, 1, 1);
				glTranslatef(0.0, 10.0, 0.0);
				navebola->Draw();
			glPopMatrix();

			glPushMatrix();
				//(1, 1, 1);
				glTranslatef(0.0, 10.0, 7.0);
				panel->Draw();
			glPopMatrix();

			glPushMatrix();
				//(1, 1, 1);
				glTranslatef(0.0, 10.0, -7.0);
				panel->Draw();
			glPopMatrix();

			glPushMatrix();
				glColor3f(.30, .30, .30);
				glTranslatef(0.0, 10, -7.0);
				glRotatef(90, 0, 0, 1);
				gluCylinder(quadratic, 1, 1, 14.0f, 32, 32);
			glPopMatrix();
		glPopMatrix();
	}

	void DrawOvni(float posovnix, float posovniy, float posovniz) {

		glPushMatrix();
		glTranslatef(posovnix, posovniy, posovniz);
		glRotatef(Rotacion,0, 1, 0);
			glPushMatrix();
			glTranslatef(0.0, 10.0, 0.0);
			glRotatef(-90, 0, 0, 1);
			glScalef(.5, 2, 2);
			glRotatef(-90, 1, 0, 0);
			ovni->Draw();
			glPopMatrix();
	
			//glTranslatef(posmetx, posmety, posmetz);
			glPushMatrix();
			glColor3f(0, 0, 1);
			glTranslatef(0.0, 13.0, 0.0);
			glScalef(.7, .7, .7);
			vidrio->Draw();
			glPopMatrix();
		glPopMatrix();
	}

	void DrawMeteoro(float posmetx, float posmety, float posmetz) {
		glPushMatrix();
		glTranslatef(posmetx, posmety, posmetz);
			glPushMatrix();
			//(1, 1, 1);
			glTranslatef(0.0, 10.0, 0.0);
			meteoro->Draw();
			glPopMatrix();
		glPopMatrix();
	}

	void DrawStanleykubrick(float scaleqx, float scaleqy, float scaleqz, GLUquadricObj *quadratic) {
		
		glPushMatrix();
			glTranslatef(100, 0, 0);
			//glScalef(scaleqx, scaleqy, scaleqz);
			glPushMatrix();
				glTranslatef(100, 0, 0);
				glPushMatrix();
					glColor3f(.64, .32, 0);
					//glTranslatef(100.0, 0, 0.0);
					glRotatef(90, 90, 0, 0);
					gluCylinder(quadratic, 3, 3, 2.0f, 32, 32);
				glPopMatrix();
			
				glPushMatrix();
					glColor3f(.64, .32, 0);
					glTranslatef(0.0, -2, 0.0);
					glRotatef(90, 90, 0, 0);
					gluCylinder(quadratic, 3, 1.5, 2.0f, 32, 32);
				glPopMatrix();
				glPopMatrix();

				glPushMatrix();
					glTranslatef(100, -15, 0.0);
					glRotatef(180, 1, 0, 0);
					glPushMatrix();
						glColor3f(.64, .32, 0);
						//glTranslatef(0.0, 11.5, 0.0);
						glRotatef(90, 90, 0, 0);
						gluCylinder(quadratic, 3, 3, 2.0f, 32, 32);
					glPopMatrix();
					glPushMatrix();
						glColor3f(.64, .32, 0);
						glTranslatef(0.0, -2, 0.0);
						glRotatef(90, 90, 0, 0);
						gluCylinder(quadratic, 3, 1.5, 2.0f, 32, 32);
					glPopMatrix();
				glPopMatrix();

					glPushMatrix();
						glColor3f(.64, .32, 0);
						glTranslatef(100.0, -2, 0.0);
						glRotatef(90, 90, 0, 0);
						gluCylinder(quadratic, 1.5, 1.5, 10.0f, 32, 32);
					glPopMatrix();

					glPushMatrix();
						glColor3f(.64, .32, 0);
						glTranslatef(100.0, -2, 0.0);
						glRotatef(90, 90, 0, 0);
						glutSolidTorus(2, 10, 10, 10);
					glPopMatrix();

					glPushMatrix();
						glColor3f(.64, .32, 0);
						glTranslatef(100.0, -15, 0.0);
						glRotatef(90, 90, 0, 0);
						glutSolidTorus(2, 10, 10, 10);
					glPopMatrix();

					//tubitos
					glPushMatrix();
						glPushMatrix();
							glColor3f(.64, .32, 0);
							glTranslatef(100.0, -2, 3.0);
							//glRotatef(90, 0, 0, 0);
							gluCylinder(quadratic, .5, .5, 7.0f, 32, 32);
						glPopMatrix();

						glPushMatrix();
							glColor3f(.64, .32, 0);
							glTranslatef(103.0, -2, 0.0);
							glRotatef(90, 0, 1, 0);
							gluCylinder(quadratic, .5, .5, 7.0f, 32, 32);
						glPopMatrix();

						glPushMatrix();
							glColor3f(.64, .32, 0);
							glTranslatef(100.0, -2, -3.0);
							glRotatef(180, 0, 1, 0);
							gluCylinder(quadratic, .5, .5, 7.0f, 32, 32);
						glPopMatrix();

						glPushMatrix();
							glColor3f(.64, .32, 0);
							glTranslatef(97.0, -2, 0.0);
							glRotatef(270, 0, 1, 0);
							gluCylinder(quadratic, .5, .5, 7.0f, 32, 32);
						glPopMatrix();
					glPopMatrix();
						glPushMatrix();
							glTranslatef(0, -12, 0);
							glPushMatrix();
							glColor3f(.64, .32, 0);
							glTranslatef(100.0, -2, 3.0);
							//glRotatef(90, 0, 0, 0);
							gluCylinder(quadratic, .5, .5, 7.0f, 32, 32);
						glPopMatrix();

						glPushMatrix();
							glColor3f(.64, .32, 0);
							glTranslatef(103.0, -2, 0.0);
							glRotatef(90, 0, 1, 0);
							gluCylinder(quadratic, .5, .5, 7.0f, 32, 32);
						glPopMatrix();

						glPushMatrix();
							glColor3f(.64, .32, 0);
							glTranslatef(100.0, -2, -3.0);
							glRotatef(180, 0, 1, 0);
							gluCylinder(quadratic, .5, .5, 7.0f, 32, 32);
						glPopMatrix();

						glPushMatrix();
							glColor3f(.64, .32, 0);
							glTranslatef(97.0, -2, 0.0);
							glRotatef(270, 0, 1, 0);
							gluCylinder(quadratic, .5, .5, 7.0f, 32, 32);
						glPopMatrix();
				glPopMatrix();
			glPopMatrix();
	}

	void Render(HDC hDC)	
	{
		//GLfloat mat_ambient_cubo[] = { 0.1, 0.1, 0.1, 1.0f };
		//GLfloat mat_diffuse_cubo[] = { 0.0, 0.0, 0.8, 1.0f };
		//GLfloat mat_specular_cubo[] = { 0.9, 0.9, 0.9, 1.0f };


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//GLfloat LightAmb2[] = { 0, 0, 0, 1 };

		GLfloat LightAmb2[] = { 0.0, 0.0,0.0, 0.0 };
		GLfloat LightPos[] = { LuzX, LuzY, LuzZ, 0.0 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb2);
		glLightfv(GL_LIGHT0, GL_POSITION, LightPos);

		glLoadIdentity();
		CamaraUpdate();
		GLUquadricObj *quadratic = gluNewQuadric();
		glClearColor(0, 0, 0, 0);

		glPushMatrix();
		glColor3f(1, 1, 1);
			glTranslatef(400.0f, 40.0f, 0.0f);
			Earth->Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-300.0f, 100.0f, 50.0f);
		glRotatef(RotacionPlaneta, 0, 1, 0);
		glScalef(EscaladoX, EscaladoY, EscaladoZ);
		Jupiter->Draw();
		glPopMatrix();

		DrawSpaceship(1, 1, 1);

		glColor3f(1, 1, 1);

		DrawHT1Z1(200, 200, 0,quadratic);
		DrawHT1Z1(movX, 300, 0, quadratic);
		DrawHT1Z1(-200, movY, 0, quadratic);
		DrawHT1Z1(movX-40, movY-40, 0, quadratic);

		DrawMeteoro(20, 0, -100);
		DrawMeteoro(-200, 200, -100);
		DrawMeteoro(400, 50, 20);
		DrawMeteoro(-50, 200, -100);
		DrawOvni(400, 90, 0);
		DrawStanleykubrick(EscaladoX, EscaladoY, EscaladoZ, quadratic);

		SwapBuffers(hDC);

	}

};

#endif 


