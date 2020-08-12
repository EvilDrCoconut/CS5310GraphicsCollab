#include "SDLGraphicsProgram.h"
#include "Camera.h"
#include <iostream>

#define OBJECTS 10

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h):screenWidth(w),screenHeight(h){
	// Initialization flag
	bool success = true;
	// String to hold any errors that occur.
	std::stringstream errorStream;
	// The window we'll be rendering to
	gWindow = NULL;
	// Render flag

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO)< 0){
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else{
		//Use OpenGL 3.3 core
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
		// We want to request a double buffer for smooth updating.
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		//Create window
		gWindow = SDL_CreateWindow( "Lab",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                screenWidth,
                                screenHeight,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

		// Check if Window did not create.
		if( gWindow == NULL ){
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		//Create an OpenGL Graphics Context
		gContext = SDL_GL_CreateContext( gWindow );
		if( gContext == NULL){
			errorStream << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		// Initialize GLAD Library
		if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
			errorStream << "Failed to iniitalize GLAD\n";
			success = false;
		}

		//Initialize OpenGL
		if(!initGL()){
			errorStream << "Unable to initialize OpenGL!\n";
			success = false;
		}
  	}

    // If initialization did not work, then print out a list of errors in the constructor.
    if(!success){
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors=errorStream.str();
        SDL_Log("%s\n",errors.c_str());
    }else{
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }

	// SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN); // Uncomment to enable extra debug support!
	getOpenGLVersionInfo();

    // Setup our objects
	std::string houseFile = "./../objects/house/house_obj.obj";
	std::string chapelFile = "./../objects/chapel/chapel_obj.obj";
    std::string windmillFile = "./../objects/windmill/windmill.obj";
    std::string cyborgFile = "./../objects/cyborg/cyborg.obj";
    std::string planetFile = "./../objects/planet/planet.obj";
    // std::string backpackFile = "./../objects/backpack/backpack.obj";
    house = new Object(houseFile);
    chapel = new Object(chapelFile);
    windmill = new Object(windmillFile);
    cyborg = new Object(cyborgFile);
    // backpack = new Object(backpackFile);
	// Setup our room
    for(int i= 0; i < OBJECTS-2; ++i){ 
        Object* temp = new Object();
        temp->LoadTexture("brick.ppm");
        objects.push_back(temp);
    }
    // One more object for the floor
    Object* temp = new Object;
    temp->LoadTexture("brick.ppm");
    objects.push_back(temp);

    Object* temp2 = new Object;
    temp->LoadTexture("brick.ppm");
    objects.push_back(temp2);
    
}


// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    // Reclaim all of our objects
    delete house;
    delete chapel;
    delete windmill;
    delete cyborg;
    // delete backpack;
	for(int i= 0; i < OBJECTS; ++i){
        delete objects[i];
    }

    //Destroy window
	SDL_DestroyWindow( gWindow );
	// Point gWindow to NULL to ensure it points to nothing.
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}


// Initialize OpenGL
// Setup any of our shaders here.
bool SDLGraphicsProgram::initGL(){
	//Success flag
	bool success = true;

    // Setup our OpenGL State machine
    // TODO: Read this
    // The below command is new!
    // What we are doing, is telling opengl to create a depth(or Z-buffer) 
    // for us that is stored every frame.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D); 
	return success;
}

float x =0.0f;
float y =0.0f;
float z =0.0f;

// Update OpenGL
void SDLGraphicsProgram::update(float x, float y, float z){
    static float rot = 0;
    rot+=0.01;
    if(rot>360){rot=0;}

    house->getTransform().loadIdentity();
    house->getTransform().translate(0.0f,5.0f,-8.0f);
    house->getTransform().rotate(rot,0.0f,1.0f,0.0f);
    house->getTransform().scale(1.0f,1.0f,1.0f);
    house->update(screenWidth,screenHeight);

    chapel->getTransform().loadIdentity();
    chapel->getTransform().translate(-5.0f+x,1.0f,-8.0f);
    chapel->getTransform().rotate(rot,0.0f,1.0f,0.0f);
    chapel->getTransform().scale(0.5f,0.5f,0.5f);
    chapel->update(screenWidth,screenHeight);

    windmill->getTransform().loadIdentity();
    windmill->getTransform().translate(-5.0f,1.0f,-8.0f+z);
    windmill->getTransform().rotate(rot,0.0f,1.0f,0.0f);
    windmill->getTransform().scale(0.5f,0.5f,0.5f);
    windmill->update(screenWidth,screenHeight);

    cyborg->getTransform().loadIdentity();
    cyborg->getTransform().translate(5.0f,1.0f,-8.0f+z);
    cyborg->getTransform().rotate(rot,0.0f,1.0f,0.0f);
    cyborg->getTransform().scale(0.5f,0.5f,0.5f);
    cyborg->update(screenWidth,screenHeight);

    // backpack->getTransform().loadIdentity();
    // backpack->getTransform().translate(3.0f,1.0f,-8.0f+z);
    // backpack->getTransform().rotate(rot,0.0f,1.0f,0.0f);
    // backpack->getTransform().scale(0.5f,0.5f,0.5f);
    // backpack->update(screenWidth,screenHeight);

	objects[0]->getTransform().loadIdentity();
    objects[0]->getTransform().translate(-4.0f,3.0f,4.0f);
    objects[0]->getTransform().scale(4.0f,4.0f,4.0f);
    objects[0]->update(screenWidth,screenHeight);
    
    objects[1]->getTransform().loadIdentity();
    objects[1]->getTransform().translate(4.0f,3.0f,4.0f);
    objects[1]->getTransform().scale(4.0f,4.0f,4.0f);
    objects[1]->update(screenWidth,screenHeight);

    objects[2]->getTransform().loadIdentity();
    objects[2]->getTransform().translate(-4.0,3.0f,-12.0f);
    objects[2]->getTransform().scale(4.0f,4.0f,4.0f);
    objects[2]->update(screenWidth,screenHeight);

    objects[3]->getTransform().loadIdentity();
    objects[3]->getTransform().translate(4.0,3.0f,-12.0f);
    objects[3]->getTransform().scale(4.0f,4.0f,4.0f);
    objects[3]->update(screenWidth,screenHeight);

    objects[4]->getTransform().loadIdentity();
    objects[4]->getTransform().translate(8.0f,3.0f,0.0f);
    objects[4]->getTransform().rotate(glm::radians(90.0f),0.0f,1.0f,0.0f);
    objects[4]->getTransform().scale(4.0f,4.0f,4.0f);
    objects[4]->update(screenWidth,screenHeight);
    
    objects[5]->getTransform().loadIdentity();
    objects[5]->getTransform().translate(8.0f,3.0f,-8.0f);
    objects[5]->getTransform().rotate(glm::radians(90.0f),0.0f,1.0f,0.0f);
    objects[5]->getTransform().scale(4.0f,4.0f,4.0f);
    objects[5]->update(screenWidth,screenHeight);
    
    objects[6]->getTransform().loadIdentity();
    objects[6]->getTransform().translate(-8.0f,3.0f,0.0f);
    objects[6]->getTransform().rotate(glm::radians(90.0f),0.0f,1.0f,0.0f);
    objects[6]->getTransform().scale(4.0f,4.0f,4.0f);
    objects[6]->update(screenWidth,screenHeight);

    objects[7]->getTransform().loadIdentity();
    objects[7]->getTransform().translate(-8.0f,3.0f,-8.0f);
    objects[7]->getTransform().rotate(glm::radians(90.0f),0.0f,1.0f,0.0f);
    objects[7]->getTransform().scale(4.0f,4.0f,4.0f);
    objects[7]->update(screenWidth,screenHeight);
     
    objects[8]->getTransform().loadIdentity();
    objects[8]->getTransform().translate(0.0f,-1.0f,-4.0f);
    objects[8]->getTransform().scale(8.0f,8.0f,8.0f);
    objects[8]->getTransform().rotate(glm::radians(90.0f),1.0f,0.0f,0.0f);
    objects[8]->update(screenWidth,screenHeight); 

    objects[9]->getTransform().loadIdentity();
    objects[9]->getTransform().translate(0.0f,7.0f,-4.0f);
    objects[9]->getTransform().scale(8.0f,8.0f,8.0f);
    objects[9]->getTransform().rotate(glm::radians(90.0f),1.0f,0.0f,0.0f);
    objects[9]->update(screenWidth,screenHeight); 
}



// Render
// The render function gets called once per loop
void SDLGraphicsProgram::render(){
    // Initialize clear color
    // This is the background of the screen.
    glViewport(0, 0, screenWidth, screenHeight);
    glClearColor( 0.2f, 0.2f, 0.2f, 1.f );
    // TODO: Read this
    // Clear color buffer and Depth Buffer
    // Remember that the 'depth buffer' is our
    // z-buffer that figures out how far away items are every frame
    // and we have to do this every frame!
  	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    (*house).render(1); // Equivalent to house->render();
    (*chapel).render(1);
    (*windmill).render(1);
    (*cyborg).render(1);
    // (*backpack).render(1);
	for(int i= 0; i < OBJECTS; ++i){
        objects[i]->render(2); 
    }
   
    SDL_Delay(50); 
}


//Loops forever!
void SDLGraphicsProgram::loop(){
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();

    // Set a default speed for the camera
    float cameraSpeed = 0.05f;

    int flagX =0; int flagY =0; int flagZ =0;

    // While application is running
    while(!quit){
     	 //Handle events on queue
		while(SDL_PollEvent( &e ) != 0){
        	// User posts an event to quit
	        // An example is hitting the "x" in the corner of the window.
    	    if(e.type == SDL_QUIT){
        		quit = true;
	        }
            // Handle keyboad input for the camera class
            if(e.type==SDL_MOUSEMOTION){
                // Handle mouse movements
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
                Camera::instance().mouseLook(mouseX, mouseY);
            }
            switch(e.type){
                // Handle keyboard presses
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case SDLK_LEFT:
                            Camera::instance().moveLeft(cameraSpeed);
                            break;
                        case SDLK_RIGHT:
                            Camera::instance().moveRight(cameraSpeed);
                            break;
                        case SDLK_UP:
                            Camera::instance().moveForward(cameraSpeed);
                            break;
                        case SDLK_DOWN:
                            Camera::instance().moveBackward(cameraSpeed);
                            break;
                        case SDLK_w:
                            Camera::instance().moveUp(cameraSpeed);
                            break;
                        case SDLK_s:
                            Camera::instance().moveDown(cameraSpeed);
                            break;
                    }
                break;
            }
      	} // End SDL_PollEvent loop.

		// Update our scene
		update(x, y, z);
        
        if (flagX == 0){
            if (x + 0.05 >= 10){
                flagX =1;
                x =10;
            }
            else {
                 x = x +0.05;
            }
        } else {
            if(x - 0.05 <= 0){
                flagX = 0;
                x =0;
            }
            else {
                x = x -0.05;
            }
        }

        if (flagY == 0){
            if (y + 0.05 >= 6){
                flagY =1;
                y =6;
            }
            else {
                 y = y +0.05;
            }
        } else {
            if(y - 0.05 <= 0){
                flagY = 0;
                y =0;
            }
            else {
                y = y -0.05;
            }
        }

        if (flagZ == 0){
            if (z + 0.05 >= 8){
                flagZ =1;
                z =8;
            }
            else {
                 z = z +0.05;
            }
        } else {
            if(z - 0.05 <= 0){
                flagZ = 0;
                z =0;
            }
            else {
                z = z -0.05;
            }
        }

		// Render using OpenGL
	    render(); 	// TODO: potentially move this depending on your logic
					// for how you handle drawing a triangle or rectangle.
      	//Update screen of our specified window
      	SDL_GL_SwapWindow(getSDLWindow());
    }

    //Disable text input
    SDL_StopTextInput();
}

// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::getSDLWindow(){
  return gWindow;
}

// Helper Function to get OpenGL Version Information
void SDLGraphicsProgram::getOpenGLVersionInfo(){
	SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
	SDL_Log("Vendor: %s",(const char*)glGetString(GL_VENDOR));
	SDL_Log("Renderer: %s",(const char*)glGetString(GL_RENDERER));
	SDL_Log("Version: %s",(const char*)glGetString(GL_VERSION));
	SDL_Log("Shading language: %s",(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}
