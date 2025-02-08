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

	// Instanciamos camara.s
	camara.fov = 45.0f;
	camara.near_plane = 0.1f;
	camara.far_plane = 100.0f;

	showSingleEntity = true;  // Start in single entity mode
	currentProperty = NONE;

	// Load and initialize entities (same as before)
	Mesh* cube = new Mesh();
	cube->LoadOBJ("res/meshes/cube.obj");

	Entity* e1 = new Entity(cube);
	e1->model_matrix.translate(0, 0, -5);

	entities.push_back(e1);

}

// Render one frame
void Application::Render(void)
{



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

		break;
	
	case SDLK_2:

		break;
	
	
	case SDLK_n:

		break;
	
	case SDLK_PLUS:

		break;
	
	case SDLK_MINUS:

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