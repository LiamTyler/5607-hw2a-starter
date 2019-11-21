#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <iostream>
#include <sstream>

#include "ShaderStuff.hpp"

static void error_callback(int error, const char* description) {
	std::cerr << "GLFW Error: " << description << std::endl;
}

GLuint InitShaders()
{
    // Define the names of the shader files
    std::stringstream vshader, fshader;
    vshader << SRC_DIR << "/vshader2b.glsl";
    fshader << SRC_DIR << "/fshader2b.glsl";
    
    // Load the shaders and use the resulting shader program
    GLuint program = InitShader( vshader.str().c_str(), fshader.str().c_str() );
    
    return program;
}

int main( int argc, char** argv )
{
    glfwSetErrorCallback( error_callback );
	if ( !glfwInit() )
    {
        std::cout << "Could not initialize GLFW" << std::endl;
		return false;
    }

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    int SW = 1280;
    int SH = 720;
	GLFWwindow* window = glfwCreateWindow( SW, SH, "Title of window", NULL, NULL );
	if ( !window )
    {
        std::cout << "Could not create the GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	// set opengl context to be current window, and load glaad
	glfwMakeContextCurrent( window );
	if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
    {
		std::cout << "Failed to gladLoadGLLoader" << std::endl;
		glfwTerminate();
		return false;
	}
    GLuint program = InitShaders();
	std::cout << "Vendor: " << glGetString( GL_VENDOR ) << std::endl;
	std::cout << "Renderer: " << glGetString( GL_RENDERER ) << std::endl;
	std::cout << "Version: " << glGetString( GL_VERSION ) << std::endl;

	glfwSwapInterval(1); // vsync

    glm::vec3 vertices[] =
    {
        glm::vec3( -.5, -.5, 0 ), glm::vec3( 0, 0, 1 ), // vertex 0 normal 0
        glm::vec3(  .5, -.5, 0 ), glm::vec3( 0, 0, 1 ), // vertex 1 normal 1
        glm::vec3(   0,  .5, 0 ), glm::vec3( 0, 0, 1 ), // vertex 2 normal 2
    };

    GLuint vbo;
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );
    // query the shader for the location
    glEnableVertexAttribArray( 0 ); // position is location 0 in the vertex shader
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof( glm::vec3 ), 0 );
    glEnableVertexAttribArray( 1 ); // normal is location 1 in the vertex shader
    glVertexAttribPointer(
        1, // location
        3, // num elements
        GL_FLOAT, // type of single element
        GL_FALSE, // should opengl normalize this data
        2 * sizeof( glm::vec3 ), // stride in bytes to reach start of next normal
        (void*) sizeof( glm::vec3 ) // offset in bytes of the first normal in the buffer
    );

    glEnable( GL_DEPTH_TEST );


	while ( !glfwWindowShouldClose( window ) )
    {
        // handle input
        glfwPollEvents();
        if ( glfwGetKey( window, GLFW_KEY_ESCAPE) == GLFW_PRESS )
        {
			glfwSetWindowShouldClose( window, GLFW_TRUE );
        }

        float time = glfwGetTime();

        // render scene
        glClearColor( .2, .2, .2, 1 );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glm::mat4 V = glm::lookAt( glm::vec3( 1, 0, 5 ), glm::vec3( 1, 0, -5 ), glm::vec3( 0, 1, 0 ) );
        glm::mat4 P = glm::perspective( glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f );

        auto VP = P * V;
        glUniformMatrix4fv( glGetUniformLocation( program, "VP" ), 1, GL_FALSE, &VP[0][0] );

        glm::mat4 model(1);
        model = glm::rotate( model, time, glm::vec3( 0, 1, 0 ) );
        model = glm::scale( model, glm::vec3( 2 ) );
        glUniformMatrix4fv( glGetUniformLocation( program, "M" ), 1, GL_FALSE, &model[0][0] );

        glm::vec3 color = glm::vec3( 1, 0, 0 );
        glUniform3fv( glGetUniformLocation( program, "Kd" ), 1, &color[0] );

        glBindVertexArray( vao );
        glDrawArrays( GL_TRIANGLES, 0, 3 );

        glfwSwapBuffers( window );
	}

	// Clean up
	glfwDestroyWindow( window );
	glfwTerminate();

    return 0;
}