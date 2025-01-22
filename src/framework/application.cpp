#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->mouse_state = 0;
	this->time = 0.f;
	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(nullptr);

	this->framebuffer.Resize(w, h);
}

Application::~Application()
{
}

void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;
}

// Render one frame
void Application::Render(void)
{
	/*          DIBUJAR 12 LINEAS            */

	// Calculamos la posicion del centro
	int x = framebuffer.width / 2.0;
	int y = framebuffer.height / 2.0;

	// Longitud/Color de las líneas
	int r = 100;
	Color linea = Color::RED;

	// Guardamos las coordenadas que vamos a ir iterando
	int vx = x;
	int vy = y;

	float angulo = M_PI / 6; // pi/6 equivale a 30 grados

	for (int i = 0;i < 12;++i) {
		vx = x + r * cos(i * angulo); // Equivale a la coordenada inicial más el desplazamiento por el coseno del angulo.
		vy = y + r * sin(i * angulo);
		framebuffer.DrawLineDDA(x, y, vx, vy, linea); // Dibujamos 

	}

	framebuffer.Render();
}

// Called after render
void Application::Update(float seconds_elapsed)
{

}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch (event.keysym.sym) {
	case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
	
	case SDLK_1:
		drawMode = 1;
		break;
	
	case SDLK_2:
		drawMode = 2;
		break;
	
	case SDLK_3:
		drawMode = 3;
		break;
	
	case SDLK_4:
		drawMode = 4;
		break;
	
	case SDLK_5:
		drawMode = 5;
		break;
	
	case SDLK_6:
		drawMode = 6;
		break;
	
	case SDLK_f:

		break;
	
	case SDLK_PLUS:
		++borderWidth;
		break;
	
	case SDLK_MINUS:
		if (borderWidth == 0) {
			break;
		}
		else {
			--borderWidth;
		}
		break;
	}
}

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
		prev_mouse_pos = mouse_position;
	}
}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
		// Guardamos las coordenadas anteriores
		int x0 = prev_mouse_pos.x;
		int y0 = prev_mouse_pos.y;

		// Guardamos las coordenadas actuales:
		int x1 = mouse_position.x;
		int y1 = mouse_position.y;

		// Según el modo dibujamos:
		switch (drawMode) {
			case 1: // if drawMode == 1:
				framebuffer.DrawLineDDA(x0, y0, x1, y1, linea);
				break;

			case 2: // if drawMode == 2:
				// Encontramos el centro según la dirección de donde la dibujamos, corresponde al minimo entre las coordenadas actuales y previas de los ejes.
				int rect_x = std::min(x0,x1);
				int rect_y = std::min(y0,y1);
				
				// Calculamos el punto final, haciendo la diferencia
				int rect_w = abs(x1 - x0);
				int rect_h = abs(y1 - y0);
				framebuffer.DrawRect(rect_x, rect_y, rect_w, rect_h, borde, borderWidth, true, linea);
				break;
			
			//case 3:  // if drawMode == 3:

			//break;
		}
	}
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
	
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;

	// ...
}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}