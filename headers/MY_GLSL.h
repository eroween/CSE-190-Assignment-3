#ifndef __MY_GLSL_H__
#define __MY_GLSL_H__
//#include <windows.h>

#if defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <glm.hpp>

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//  Read shaders from the disk into the main memory
int Read_Shader(char *name, char **shader_text)
{
    FILE* fp = fopen(name, "r+");
    if(fp==NULL) return 0;
	//Calculate the file size and allocate the shader_content
	fseek(fp, 0L, SEEK_END);
    int size=ftell(fp)+1;
	if(*shader_text)	delete[] (*shader_text);
	*shader_text = new char[size];
	//Read the shader file
	int count=0;
	fseek(fp, 0, SEEK_SET);
	count = fread(*shader_text, 1, size, fp);
	(*shader_text)[count] = '\0';
	//The end
    fclose(fp);
    return count;
}

bool Read_Shader_Source(char *shader_name, char **vertexShader, char **fragmentShader)
{
	char vert_shader_name[1024];
	sprintf(vert_shader_name, "%s.vert", shader_name);
	if(!Read_Shader(vert_shader_name, vertexShader))
    {
        printf("Cannot read the file %s.\n", vert_shader_name);
        return false;
    }
	char frag_shader_name[1024];
	sprintf(frag_shader_name, "%s.frag", shader_name);
	if(!Read_Shader(frag_shader_name, fragmentShader))
    {
        printf("Cannot read the file %s.\n", frag_shader_name);
        return false;
    }
    return true;
}



//  GLSL setup routine
GLuint Setup_GLSL(char *name)
{
	GLuint programObject;
	GLuint vertexShaderObject;
	GLuint fragmentShaderObject;
    glewInit();
	if(!(programObject=glCreateProgram()))
	{
		printf("Error creating shader program object.\n");
		return 0;
	}
	else printf("Succeeded creating shader program object.\n");
	if(!(vertexShaderObject=glCreateShader(GL_VERTEX_SHADER)))
	{
	  printf("Error creating vertex shader object.\n");
	 return 0;
	}
	else printf("Succeeded creating vertex shader object.\n");
	if(!(fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER)))
	{
		printf("Error creating fragment shader object.\n");
		return 0;
	}
	else printf("Succeeded creating fragment shader object.\n");

	//Step 3: Load the shaders from the disk into the two shader objects
	char* vertexShaderSource=0;
	char* fragmentShaderSource=0;
	Read_Shader_Source(name, &vertexShaderSource, &fragmentShaderSource);
	glShaderSource(vertexShaderObject,1,(const char**)&vertexShaderSource,NULL);
	glShaderSource(fragmentShaderObject,1,(const char**)&fragmentShaderSource,NULL);
	delete[] vertexShaderSource;
	delete[] fragmentShaderSource;

	//Step 4: Compile the vertex shader
	glCompileShader(vertexShaderObject);
	//If there is any error, print out the error log
	GLint result;
	glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &result);
	if(result==GL_FALSE)
	{
		printf(" vertex shader compilation failed!\n");
		GLint logLen;
		glGetShaderiv(vertexShaderObject, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char* log=new char[logLen];
			GLsizei written;
			glGetShaderInfoLog(vertexShaderObject, logLen, &written, log);
			printf("Shader log: \n %s", log);
			delete[] log;
		}
	}

	//Step 5: Compile the fragment shader
	glCompileShader(fragmentShaderObject);
	//If there is any error, print out the error log
	glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &result);
	if(result==GL_FALSE)
	{
		printf(" fragment shader compilation failed!\n");
		GLint logLen;
		glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH, &logLen);
		if(logLen > 0)
		{
			char* log = new char[logLen];
			GLsizei written;
			glGetShaderInfoLog(fragmentShaderObject, logLen, &written, log);
			printf("Shader log: \n %s", log);
			delete[] log;
		}
	}

	//Step 6: Attach the shader objects and link the program object
	glAttachShader(programObject, vertexShaderObject);
	glAttachShader(programObject, fragmentShaderObject);
	glLinkProgram(programObject);

	return(programObject);
}




#endif
