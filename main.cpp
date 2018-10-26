#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//callback prototype for when the window changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


int main()
{
	std::cout << "Program started...\n";
	glfwInit();
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//creating window object
	GLFWwindow *window = glfwCreateWindow(800, 600, "GeoSim",NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	glViewport(0,0,800,600);
	
	//Registering callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	while(!glfwWindowShouldClose(window))
	{
		//clear the color buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//input
		processInput(window);
    		//glfw: swap buffers and poll IO events (keys pressed/released)
		glfwSwapBuffers(window);
    		glfwPollEvents();    
	}
	//clear resources that were allocated!
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
