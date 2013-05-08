#include "glbase.h"

float angle = 0.0f;

vertex_t modelTranslate = { 0.0f, 0.0f, -4.0f };
float modelAnglex = 0.0f, addAnglex = 0.0f;
float modelAngley = 0.0f, addAngley = 0.0f;

// misc. gl functions
void TranslateToVertex (vertex_t *v)
{
	glTranslatef(v->x, v->y, v->z);
}

void RotateAroundVertex (float angle, vertex_t *v)
{
	glRotatef(angle, v->x, v->y, v->z);
}

void GetInput (void)
{
	I_GetMouse();

	// rotate the model only when the left mouse button is pressed
	if (mse.state.rgbButtons[0])
	{
		float prevx = modelAnglex;
		float prevy = modelAngley;

		modelAnglex += mse.state.lY;
		modelAngley += mse.state.lX;

		addAnglex = modelAnglex - prevx;
		addAngley = modelAngley - prevy;
	}
	else
	{
		modelAnglex += addAnglex;
		modelAngley += addAngley;
	}
}

void RenderFrame (void)
{
	GetInput();

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	DrawModel(&sampleModel, &modelTranslate, modelAnglex, modelAngley, 0.0f);
}
