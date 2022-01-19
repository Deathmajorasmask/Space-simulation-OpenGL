#ifndef _Sky
#define _Sky
#include "Geometry.h"
#include "Image.h"

class SkyDome :public Primitivos, public Imagenes
{
public:
	//En honor a nuestros ancestros llamaremos "Maya" a la malla
	//e suna estructura que contiene a los indices y vertices de la figura
	Maya cuadro;
	//variables locales de la clase para contener los stacks y los slices de la esfera
	int st, sl;
	//el nombre numerico de la textura en cuestion, por lo pronto una
	unsigned int esferaTextura;

	//El constructor llama al metodo Esfera de la clase geometrias que generara los vertices
	//normales y uvs de la misma, nos regresa la estructura Maya.
	SkyDome(HWND hWnd, int stacks, int slices, float radio, WCHAR nombre[])
	{
		this->hWnd = hWnd;
		cuadro = Esfera(stacks, slices, radio, 0, 1);
		st = stacks;
		sl = slices;
		//cargamos la textura de la figura
		Carga(nombre);
		//en caso del puntero de la imagen sea nulo se brica esta opcion
		if (Dir_Imagen())
		{
			glGenTextures(1, &esferaTextura);
			glBindTexture(GL_TEXTURE_2D, esferaTextura);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, Ancho(), Alto(), GL_RGB, GL_UNSIGNED_BYTE, Dir_Imagen());
			//disponemos la textura del gdi.
			Descarga();
		}
	}

	~SkyDome()
	{
		//nos aseguramos de disponer de los recursos previamente reservados
		delete cuadro.maya;
		delete cuadro.indices;
		glDeleteTextures(1, &esferaTextura);
	}

	void Draw()
	{
		int ind = 0;
		int indice;

		//habilitamos el culling para reducir tiempo de procesamiento de las texturas
		//las texturas se analizan pixel a pixel para determinar que se imprimen o no
		//por lo que aunque no la veamos nos costo, por eso la eliminamos.
		glEnable(GL_CULL_FACE);
		//hay dos tipos de cull el frontal y el trasero (back)
		glCullFace(GL_FRONT);
		//habilitamos la textura, podriamos mezclar colores y cambiar la tonalidad de la textura
		//con glColorxf
		glEnable(GL_TEXTURE_2D);
		//usamos modulate para que la textura sea afectada por el valor de la normal en cuanto
		//a luz
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, esferaTextura);
		//habilitamos la posibilidad de guardar arreglos de procesamiento inmediato
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		//asignamos punteros de vertices, normales y texturas al buffer de conexiones que sigue
		glVertexPointer(3, GL_FLOAT, sizeof(Vertices), &cuadro.maya[0].Posx);
		glNormalPointer(GL_FLOAT, sizeof(Vertices), &cuadro.maya[0].Normx);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertices), &cuadro.maya[0].u);

		//conectamos todos los vertices previamente cargados a traves de sus punteros para procesarse
		glDrawElements(GL_TRIANGLES, (sl - 1)*(st - 1) * 6, GL_UNSIGNED_INT, cuadro.indices);
		//desocupamos la asignacion para que podamos utilizarlo con un nuevo elemento
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_CULL_FACE);
		glDisable(GL_TEXTURE_2D);

	}
};
#endif