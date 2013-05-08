// model.cpp - *.m file format loading and displaying functions

// from:  www.falloutsoftware.com
// by:    Greg Damon (gregd@falloutsoftware.com)
// ---------------------------------------------

#include "glbase.h"

model_t sampleModel;

int mmReadCh (FILE **file)
{
	return fgetc(*file);
}

void mmSkipLine (FILE **file)
{
	fgets(sysBuffer, 128, *file);
}

// mmReadNextParam: reads the next parameter from a *.m file stream,
// skips all unneeded characters
float mmReadNextParam (FILE **file)
{
	int ch = 0;
	float f = 0;
	bool legal = false;

	while (true)
	{
		ch = mmReadCh(file);
		
		if (ch == EOF)		// EOF or error: set err to 1 and break out of the loop
			SysShutdownMSG("mmReadNextParam: unexpected EOF or parsing error\r\ncheck your *.m model file syntax");

		((ch >= 0x30  &&			// skip spaces or any other misc. characters (, . etc)
		  ch <= 0x39) ||
		  ch == 0x2d) ?				// a vertex param. could be negative so look for '-' (0x2d) while parsing
		  legal = true : legal = false;

		if (legal)
		{
			// back up by one character
			if (fseek(*file, (ftell(*file)- 1), SEEK_SET) != 0)
				SysShutdownMSG("mmReadNextParam: fseek failed, sorry; check your *.m model file syntax");

			// read the floating-point parameter and return it
			fscanf(*file, "%f", &f);
			return f;
		}
	}

	// EOF or error
	return 0;
}

// LoadModel(); loads an m file format model into model_t *model
void LoadModel (char *sFilename, model_t *model)
{
	FILE *file = fopen(sFilename, "r");

	if (file)
	{
		// find the "beginmodel" tag
		while (true)
			if (strncmp(fgets(sysBuffer, 128, file), "beginmodel", 10) == 0)
				break;

		// read the number of polygons in this model
		sscanf(sysBuffer, "beginmodel %d", &model->nPolygons);

		// allocate enough memory for this model
		model->pList = (polygon_t *)malloc(model->nPolygons * sizeof(polygon_t));

		// read all polygon vertices
		for (int i=0; i<model->nPolygons * 3; i++) {
			model->pList->v[i].x = mmReadNextParam(&file);
			model->pList->v[i].y = mmReadNextParam(&file);
			model->pList->v[i].z = mmReadNextParam(&file);
		}

		fclose(file);
	}
	else
	{
		sprintf(sysBuffer, "LoadModelM(): Cannot open file \"%s\"", sFilename);
		SysShutdownMSG(sysBuffer);
	}
}

// DrawPolygon(); draws an opengl polygon defined by polygon_t
void DrawPolygon (polygon_t *p)
{
	vector_t vecNormal = { 0.0f, 0.0f, 0.0f };

	glBegin(GL_TRIANGLES);
    // calculate normal vector
	normal(p->v, &vecNormal);
	glNormal3f(p->v[0].x + vecNormal.x, p->v[0].y + vecNormal.y, p->v[0].z + vecNormal.z);
	// draw the polygon
	glVertex3f(p->v[0].x, p->v[0].y, p->v[0].z);
	glVertex3f(p->v[1].x, p->v[1].y, p->v[1].z);
	glVertex3f(p->v[2].x, p->v[2].y, p->v[2].z);
	glEnd();
	/*
	// draw the normal vector
	glBegin(GL_LINES);
	glVertex3f(p->v[0].x, p->v[0].y, p->v[0].z);
	glVertex3f(p->v[0].x + vecNormal.x, p->v[0].y + vecNormal.y, p->v[0].z + vecNormal.z);
	glEnd();
	*/
}

// DrawModel(); draws a model
void DrawModel (model_t *model, vertex_t *translate, float r_anglex, float r_angley, float r_anglez)
{
	glLoadIdentity();
	glTranslatef(translate->x, translate->y, translate->z);
	glRotatef(r_anglex, 1.0f, 0.0f, 0.0f);
	glRotatef(r_angley, 0.0f, 1.0f, 0.0f);
	glRotatef(r_anglez, 0.0f, 0.0f, 1.0f);

	for (int i=0; i<model->nPolygons; i++)
		DrawPolygon(&model->pList[i]);
}

// FreeModel(); frees model memory
void FreeModel (model_t *model)
{
	if (model->pList)
	{
		free(model->pList);
		model->pList = NULL;
	}
}

// misc. gl functions:
void normalize (vector_t *v)
{
    // calculate the length of the vector
    float len = (float)(sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z)));

    // avoid division by 0
    if (len == 0.0f)
        len = 1.0f;

    // reduce to unit size
    v->x /= len;
    v->y /= len;
    v->z /= len;
}

// normal(); - finds a normal vector and normalizes it
void normal (vertex_t v[3], vector_t *normal)
{
    vector_t a, b;

    // calculate the vectors A and B
    // note that v[3] is defined with counterclockwise winding in mind
    // a
    a.x = v[0].x - v[1].x;
    a.y = v[0].y - v[1].y;
    a.z = v[0].z - v[1].z;
    // b
    b.x = v[1].x - v[2].x;
    b.y = v[1].y - v[2].y;
    b.z = v[1].z - v[2].z;

    // calculate the cross product and place the resulting vector
    // into the address specified by vector_t *normal
    normal->x = (a.y * b.z) - (a.z * b.y);
    normal->y = (a.z * b.x) - (a.x * b.z);
    normal->z = (a.x * b.y) - (a.y * b.x);

    // normalize
    normalize(normal);
}
