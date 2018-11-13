#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include <cmath>
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//gdal library
#include <gdal.h>
#include <gdal_priv.h>
#include <ogrsf_frmts.h>
#include <cpl_conv.h>
//callback prototype for when the window changes
#include "../../filestut/data/model.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//GLAL FUNCTIONS
void transformToUtm(double& x, double& y)
{
    OGRSpatialReference    oUTM, *poLatLong;
    OGRCoordinateTransformation *poTransform;

    oUTM.SetProjCS("UTM 11 / WGS84");
    oUTM.SetWellKnownGeogCS( "WGS84" );
    oUTM.SetUTM( 11 );

    poLatLong = oUTM.CloneGeogCS();
    
    poTransform = OGRCreateCoordinateTransformation( poLatLong, &oUTM );
    if( poTransform == NULL )
    {
        return;
    }
    

    if( !poTransform->Transform( 1, &x, &y) )
    {
      // Error here
    }
};

void ComputeGeoProperties(GDALDataset *poDataset, int width, int height, double& x, double& y,double& xright, double& ybottom, double& xres, double& yres)
{
    double adfGeoTransform[6];
    if( poDataset->GetGeoTransform( adfGeoTransform ) == CE_None )
    {
        printf( "Origin = (%.6f,%.6f)\n",
                adfGeoTransform[0], adfGeoTransform[3] );

        printf( "Pixel Size = (%.6f,%.6f)\n",
                adfGeoTransform[1], adfGeoTransform[5] );
        x = adfGeoTransform[0];
        y = adfGeoTransform[3];
        xright = x + adfGeoTransform[1]*width;
        ybottom = y + adfGeoTransform[5]*height;
    }
    else
    {
      return;
    }

    std::string proj;
    proj = std::string(poDataset->GetProjectionRef());

    OGRSpatialReference sr2;
    const char* test = &proj[0];
    sr2.importFromWkt(&test);
    
    // Get Geography Coordinate System clone
    OGRSpatialReference* geog2 = sr2.CloneGeogCS(); 

    // Now to create coordinate transform function
    OGRCoordinateTransformation* poTransform2 = OGRCreateCoordinateTransformation( &sr2, geog2 );

    // Compute corners
    poTransform2->Transform(1,&x,&y);
    poTransform2->Transform(1,&xright,&ybottom);

    // Transform to utm on both corners
    transformToUtm(x,y);
    transformToUtm(xright,ybottom);
    std::cout << xright << " " << ybottom <<std::endl;
    
    // Lets compute the absolute width and height in utm
    double absoluteW = xright - x;
    double absoluteH = y - ybottom;

    // now lets compute the average resolution (in utm) of the DEM
    xres = absoluteW / width;
    yres = absoluteH / height;
};

glm::vec3 ComputeNormal(glm::vec3 center, int i, int j, int width, int height,std::vector<std::vector<float>>& data, float Max, float xres, float yres );

struct Vertex
{
    glm::vec3 position; // where each dot is located
    glm::vec3 normal; // the normal for this dot
    glm::vec2 uv; // uvs for texture coordinate mapping
};

void createMesh(std::vector<std::vector<float>>& input,float xres, float yres,float max,std::vector<int>& indexs, std::vector<Vertex>& vectors)
{
  // Our vertex information along with normals contained inside
  //std::vector<Vertex> vectors = std::vector<Vertex>();

  // Lets do some index rendering because it will save us some memory to some degree
  //std::vector<int> indexs = std::vector<int>();

  // Time to construct a height map based on the xres and yres for each group of four dots
  for(int i = 0; i < input.size()-1; i++)
  {
    for(int j = 0; j < input[i].size()-1; j++)
    {  

        float UL = (float)(input[i][j])/(float)(max); // Upper left
        float LL = (float)(input[i+1][j])/(float)(max); // Lower left
        float UR = (float)(input[i][j+1])/(float)(max); // Upper right
        float LR = (float)(input[i+1][j+1])/(float)(max); // Lower right

        if(UL <= 0)
        {
          UL = 0;
        }
        
        if(UR <= 0)
        {
          UR = 0;
        }

        if(LR <= 0)
        {
          LR = 0;
        }

        if(LL <= 0)
        {
          LL = 0;
        }
        
        glm::vec3 ULV = {i*xres,UL*max,j*yres};
        glm::vec3 LLV = {(i+1)*xres,LL*max,j*yres};
        glm::vec3 URV = {i*xres,UR*max,(j+1)*yres};
        glm::vec3 LRV = {(i+1)*xres,LR*max,(j+1)*yres};

        // compute smoothed normal
        glm::vec3 a = ComputeNormal(ULV,i,j,input.size(),input[i].size(),input,max,xres,yres);
        glm::vec3 b = ComputeNormal(LLV,i+1,j,input.size(),input[i].size(),input,max,xres,yres);
        glm::vec3 c = ComputeNormal(URV,i,j+1,input.size(),input[i].size(),input,max,xres,yres);
        glm::vec3 d = ComputeNormal(LRV,i+1,j+1,input.size(),input[i].size(),input,max,xres,yres);

        // Push back vector information for these group of dots
        vectors.push_back(Vertex{ {i*xres,UL,j*yres}, a, {(float)i/(float)input.size(),(float)j/(float)input[i].size()} } );
        vectors.push_back(Vertex{ {(i+1)*xres,LL,j*yres}, b, {(float)(i+1)/(float)input.size(),(float)j/(float)input[i].size()} } );
        vectors.push_back(Vertex{ {i*xres,UR,(j+1)*yres}, c, {(float)i/(float)input.size(),(float)(j+1)/(float)input[i].size()} } );
        vectors.push_back(Vertex{ {(i+1)*xres,LR,(j+1)*yres}, d, {(float)(i+1)/(float)input.size(),(float)(j+1)/(float)input[i].size()} } );

        // Push back indices for these verticies
        indexs.push_back(vectors.size() - 4);
        indexs.push_back(vectors.size() - 1);
        indexs.push_back(vectors.size() - 2);
        indexs.push_back(vectors.size() - 4);
        indexs.push_back(vectors.size() - 3);
        indexs.push_back(vectors.size() - 1);
        
    }
  }
}
glm::vec3 ComputeNormal(glm::vec3 center, int i, int j, int width, int height,std::vector<std::vector<float>>& data, float Max, float xres, float yres )
{
  // Compute center of all values which is the i and j passed in
    glm::vec3 left;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 down;
    glm::vec3 sum = glm::vec3(0,0,0);
    bool l = false;
    bool r = false;
    bool u = false;
    bool d = false;

    int count = 0;
  // Compute left
    if(i -1 >= 0)
    {
        left = glm::vec3((i-1)*xres,data[i-1][j],j*yres);
        left = center - left;
        l = true;
    }

    // Compute right
    if(i+1 < width)
    {
        right = glm::vec3((i+1)*xres,data[i+1][j],j*yres);
        right = center - right;
        r = true;
    }

    // Compute up
    if(j-1 >= 0)
    {
        up = glm::vec3((i)*xres,data[i][j-1],(j-1)*yres);
        up = center-up;
        u = true;
    }

    // Compute down
    if(j+1 < height)
    {
        down = glm::vec3((i)*xres,data[i][j+1],(j+1)*yres);
        down = center-down;
        d = true;
    }

    // Compute normals
    if(u  && r)
    {
        glm::vec3 v1 = glm::cross(up,right);
        if(v1.y < 0)
        {
            v1 *= -1;
        }
        sum += v1;
        count = count + 1;
    }
    if(u && l)
    {
        glm::vec3 v1 = glm::cross(up,left);
        if(v1.y < 0)
        {
            v1 *= -1;
        }
        sum += v1;
        count = count + 1;
    }
    if(d && r)
    {
        glm::vec3 v1 = glm::cross(down,right);
        if(v1.y < 0)
        {
            v1 *= -1;
        }
        sum += v1;
        count = count + 1;
    }
    if(d && l)
    {
        glm::vec3 v1 = glm::cross(down,left);
        if(v1.y < 0)
        {
            v1 *= -1;
        }
        sum += v1;
        count = count + 1;
    }

    // Compute average normal
    sum /= count;
  
    // Normalize it and return :D!!!! Enjoy your smoothed normal for some smooth shading!
    return glm::normalize(sum);
}
//SETTINGS
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	std::cout << "Program started...\n";
    //Testing matrix transformation
    //std::cout << "Testing matrix transformation\n";
    //glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    //glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    //vec = trans * vec;
    //std::cout << vec.x << vec.y << vec.z << std::endl;
    //std::cout << "End of testing.." << std::endl;
    //end of testing 
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
    
    //configure global opengel state
    glEnable(GL_DEPTH_TEST);
    //setup shader program
    unsigned int programID = loadShader();
    //new shader class
    Shader ourShader("../shaders/shader.vs","../shaders/shader.fs");
    int nrt;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrt); 
    std::cout << "Maximum nr of vertex attributes supported: " << nrt << std::endl; 
    
    if(!modelvert)
    {
        std::cout << "land model not loaded.....\n";
    }
    std::cout << "Size of modelvert: " << sizeof(modelvert) << "\n";

    //LOADING GDAL DATASET
    GDALDataset *poDataset;
    GDALAllRegister();
    poDataset = (GDALDataset*) GDALOpen("../../filestut/data/N055W004/N055W004_AVE_DSM_converted.tif",GA_ReadOnly);
    
    // Lets get the dimensions of the tif
    int gd_width = GDALGetRasterXSize(poDataset); 
    int gd_height = GDALGetRasterYSize(poDataset);
    double x,y,xright,ybottom,xres,yres;


    std::string proj;
    proj = std::string(poDataset->GetProjectionRef());
    std::cout << "Projection: " << proj << "\n";    
    // Lets get the upper right hand corner of the tiff and its resolution
    /*double adfGeoTransform[6];
    if( poDataset->GetGeoTransform( adfGeoTransform ) == CE_None )
    {
        printf( "Origin = (%.6f,%.6f)\n",
            adfGeoTransform[0], adfGeoTransform[3] );

        printf( "Pixel Size = (%.6f,%.6f)\n",
            adfGeoTransform[1], adfGeoTransform[5] );
        double x = adfGeoTransform[0];
        double y = adfGeoTransform[3];
        double xright = x + adfGeoTransform[1]*gd_width;
        double ybottom = y + adfGeoTransform[5]*gd_height;
    }
    else
    {
        std::cout << "Something went wrong!!";
    }*/
    
    //get number of bands
    int numBands = poDataset->GetRasterCount();
    std::cout << "There are: " << numBands <<"\n";
    
    float min,max;
    int bGotMin, bGotMax;
    double adfMinMax[2];

    GDALRasterBand  *poBand;

    poBand = poDataset->GetRasterBand(1);
    
    //Get the Min and Max
    min = adfMinMax[0] = poBand->GetMinimum( &bGotMin );
    max = adfMinMax[1] = poBand->GetMaximum( &bGotMax );
    //Dataset dimensions
    int bandWidth = poBand->GetXSize();
    int bandHeight = poBand->GetYSize();
    // Get first raster band
    std::cout << "First band width: " << bandWidth << "\n";
    std::cout << "Tiff width: " << gd_width << "\n";
    
    float *pafScanline;
    pafScanline = (float *) CPLMalloc(sizeof(float)*bandWidth*bandHeight);
    
    if(!pafScanline){std::cout << "No memory allocated!";}
    //RasterIO will load the data
    auto err = poBand->RasterIO(GF_Read,0,0,bandWidth,bandHeight,pafScanline,bandWidth,bandHeight,GDT_Float32,0,0);
    std::vector<std::vector<float>> out = std::vector<std::vector<float>>(bandWidth,std::vector<float> (bandHeight,0));
    
    // move everything to a vector -- slow memory but okay for what we are doing especially when zeroing out zero values
    for(int i = 0; i < bandWidth; i++)
    {
        for(int j = 0; j < bandHeight; j++)
        {
            if(pafScanline[(i)*bandWidth+j] > 0)
                out[i][j] = pafScanline[(i)*bandWidth+j];
            else
                out[i][j] = 0;
        }
    }
    //For storing vertix informmation
    // Our vertex information along with normals contained inside
    std::vector<Vertex> vertexes = std::vector<Vertex>();

    // Lets do some index rendering because it will save us some memory to some degree
    std::vector<int> indicies = std::vector<int>();
    //computations
    ComputeGeoProperties(poDataset,gd_width,gd_height,x,y,xright,ybottom,xres,yres);
    //Create mesh
    createMesh(out,xres,yres,max,indicies,vertexes);
    
    //Generating buffers VAO, VBO and EBO
    unsigned int VAO_gdal, VBO_gdal, EBO_gdal;
    glGenVertexArrays(1,&VAO_gdal);
    glGenBuffers(1,&VBO_gdal);
    glGenBuffers(1,&EBO_gdal);
    
    glBindVertexArray(VAO_gdal);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO_gdal);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertexes.size(), &vertexes[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_gdal);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indicies.size(), &indicies[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    //unbind array object for gdal data
    glBindVertexArray(0);
    //END OF GDAL SETUP
    //vertex array 
    float vertices[] = { 
        //positions      //color
    		0.5f, 0.5f, 0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,
     		0.5f, -0.5f, 0.0f,0.0f,1.0f,0.0f,1.0f,0.0f,
     		-0.5f,  -0.5f, 0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,
            -0.5f, 0.5f, 0.0f,1.0f,0.0f,1.0f,0.0f,1.0f
	};

    unsigned int indices[] = {
        0,1,3,
        1,2,3
    };
    
    unsigned int VBO, VAO, EBO, VAO2,VBO2;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Bind VAO first, then bind and set vertex buffer(s) and then configure vertex attributes
    glBindVertexArray(VAO);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //color attribute
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE,8*sizeof(float),(void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    //texture attribute
    glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, 8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    //load and create a texture
    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D, texture);//all upcoming GL_TEXTURE_2D operations now have effect on this texture
    
    //set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    //the FileSystem::getPath(...) is part of the github repository so we can find files on any IDE/platform;
    //unsigned char* data = stbi_load(FileSystem::getPath("../textures/container.jpg").c_str(), &width, &height, &nrChannels,0);
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("../textures/container.jpg", &width, &height, &nrChannels,0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    //TEXTURE 2 STUFF!
    unsigned int mytexture2;
    glGenTextures(1,&mytexture2);
    glBindTexture(GL_TEXTURE_2D, mytexture2);
    
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("../textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
    glGenVertexArrays(1,&VAO2);
    glGenBuffers(1,&VBO2);

    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, 192, modelvert, GL_STATIC_DRAW);

    //Setting attrib pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    // uncomment this call to draw in wireframe polygons.
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    ourShader.use();
    ourShader.setInt("texture2",1);
	while(!glfwWindowShouldClose(window))
	{
		//clear the color buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClear(GL_COLOR_BUFFER_BIT);
        //input
		processInput(window);
        
        //bind Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,mytexture2);


        //Rendering
        //glUseProgram(programID);
        ourShader.use();
                
        //SETTING TRANSFORMATION MATRIX
        /*
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        //QUERY LOCATION IN SHADER PROGRAM
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));*/
        
                // create transformations
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");
        unsigned int projLoc  = glGetUniformLocation(ourShader.ID, "projection");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        //ourShader.setMat4("projection", projection);
        glUniformMatrix4fv(projLoc,1,GL_FALSE, glm::value_ptr(projection));

        //glBindVertexArray(VAO2);
        //glDrawArrays(GL_POINTS, 0, 16);
        
        glBindVertexArray(VAO_gdal);
        glDrawElements(
     		GL_TRIANGLES,      // mode
     		indicies.size(),    // count
     		GL_UNSIGNED_INT,   // type
     		(void*)0           // element array buffer offset
 		);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        //glBindVertexArray(0);
    	//glfw: swap buffers and poll IO events (keys pressed/released)
		glfwSwapBuffers(window);
    	glfwPollEvents();    
	}
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    //Deleting landscape points
    glDeleteVertexArrays(1,&VAO2);
    glDeleteBuffers(1,&VBO2);
	
	//Deleting gdal resources
	glDeleteVertexArrays(1, &VAO_gdal);
	glDeleteBuffers(1, &VBO_gdal);
	glDeleteBuffers(1, &EBO_gdal);
	
	//clear resources that were allocated!
    glfwTerminate();
    //delete the data array
    delete[] modelvert;
	return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
