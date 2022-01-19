#ifndef _GeoPla
#define _GeomPla
#define _USE_MATH_DEFINES
#include <math.h>
#include "Image.h"


struct VertexPlane {
	float vertx1;
	float verty1; 
	float vertz1;
	float vertx2; 
	float verty2;
	float vertz2;
	float vertx3;
	float verty3;
	float vertz3;
	float vertx4;
	float verty4;
	float vertz4;
};

float Avertx1, Averty1, Avertz1, Avertx2, Averty2, Avertz2, Avertx3, Averty3, Avertz3, Avertx4, Averty4, Avertz4;

class SkyPlane : public Imagenes {
public:
	unsigned int textureplane;

	SkyPlane(HWND hWnd, float vertx1, float verty1, float vertz1, float vertx2, float verty2, float vertz2, float vertx3, float verty3, float vertz3, 
		float vertx4, float verty4, float vertz4, WCHAR nombre[]) {
		
		Carga(nombre);
			if (Dir_Imagen()) {
				glGenTextures(1, &textureplane);
				glBindTexture(GL_TEXTURE_2D, textureplane);
				/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);*/
				gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, Ancho(), Alto(), GL_RGB, GL_UNSIGNED_BYTE, Dir_Imagen());
				//disponemos la textura del gdi.
				Descarga();
			}

			Avertx1 = vertx1;
			Averty1 = verty1;
			Avertz1 = vertz1;

			Avertx2 = vertx2;
			Averty2 = verty2;
			Avertz2 = vertz2;

			Avertx3 = vertx3;
			Averty3 = verty3;
			Avertz3 = vertz3;

			Avertx4 = vertx4;
			Averty4 = verty4;
			Avertz4 = vertz4;

		}

	~SkyPlane() {
		glDeleteTextures(1, &textureplane);

	}

	void Draw()
	{
		
		//habilitamos el culling para reducir tiempo de procesamiento de las texturas
		//las texturas se analizan pixel a pixel para determinar que se imprimen o no
		//por lo que aunque no la veamos nos costo, por eso la eliminamos.
		//glEnable(GL_CULL_FACE);
		//hay dos tipos de cull el frontal(GL_FRONT) y el trasero (GL_BACK)
		//glCullFace(GL_FRONT);
		//habilitamos la textura, podriamos mezclar colores y cambiar la tonalidad de la textura
		//con glColorxf
		glEnable(GL_TEXTURE_2D);
		//usamos modulate para que la textura sea afectada por el valor de la normal en cuanto a luz
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, textureplane);
		//habilitamos la posibilidad de guardar arreglos de procesamiento inmediato
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
		//Asignamos la malla del plano
		glBegin(GL_POLYGON);

		glTexCoord2f(1.0, 1.0); glVertex3f(Avertx1, Averty1, Avertz1); 
		glTexCoord2f(0.0, 1.0); glVertex3f(Avertx2, Averty2, Avertz2);
		glTexCoord2f(0.0, 0.0); glVertex3f(Avertx3, Averty3, Avertz3);
		glTexCoord2f(1.0, 0.0); glVertex3f(Avertx4, Averty4, Avertz4);

	/*	glTexCoord2f(1.0, 1.0); glVertex2f(Avertx1, Averty1);
		glTexCoord2f(0.0, 1.0); glVertex2f(Avertx2, Averty2);
		glTexCoord2f(1.0, 0.0); glVertex2f(Avertx3, Averty3);
		glTexCoord2f(0.0, 0.0); glVertex2f(Avertx4, Averty4);*/

		glEnd();

		//desocupamos la asignacion para que podamos utilizarlo con un nuevo elemento
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		 //glDisable(GL_CULL_FACE);
		
		glDisable(GL_TEXTURE_2D); 
	}

};
#endif