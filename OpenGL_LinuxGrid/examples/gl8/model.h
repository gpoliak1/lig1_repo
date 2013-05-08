typedef struct vector_s
{
	float x,
		  y,
		  z;
} vector_t;

typedef struct vertex_s
{
	float x,
		  y,
		  z;
} vertex_t;

typedef struct polygon_s
{
	vertex_t v[3];
} polygon_t;

typedef struct model_s
{
	int nPolygons;		// number of polygons
	polygon_t *pList;	// list of polygons
} model_t;

extern model_t sampleModel;

// render a polygon
void DrawPolygon (polygon_t *p);

// model ops:
void LoadModel (char *sFilename, model_t *model);	// loads a *.m model file
void DrawModel (model_t *model, vertex_t *translate, float r_anglex, float r_angley, float r_anglez);
void FreeModel (model_t *model);

// misc. gl functions:
void normalize (vector_t *v);
void normal (vertex_t v[3], vector_t *normal);
