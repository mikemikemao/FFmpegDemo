//
// Created by ByteFlow on 2019/7/9.
//

#include "TriangleSample.h"


TriangleSample::TriangleSample()
{

}

TriangleSample::~TriangleSample()
{
}


void TriangleSample::LoadImage(NativeImage *pImage)
{
	//null implement

}

void TriangleSample::Init()
{
	if(m_ProgramObj != 0)
		return;
	char vShaderStr[] =
			"#version 300 es                          \n"//版本
			"layout(location = 0) in vec4 vPosition;  \n"//使用in关键字，在顶点着色器中声明所有的输入顶点属性(Input Vertex Attribute)
			"void main()                              \n"
			"{                                        \n"
			"   gl_Position = vPosition;              \n"
			"}                                        \n";

	char fShaderStr[] =
			"#version 300 es                              \n"
			"precision mediump float;                     \n"
			"out vec4 fragColor;                          \n"
			"void main()                                  \n"
			"{                                            \n"
			"   fragColor = vec4 ( 0.0, 1.0, 0.0, 1.0 );  \n"
			"}                                            \n";

	m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr, m_VertexShader, m_FragmentShader);

}

void TriangleSample::Draw(int screenW, int screenH)
{
	LOGCATE("TriangleSample::Draw");
	GLfloat vVertices[] = {
			0.0f,  0.3f, 0.0f,
			-0.5f, -0.6f, 0.0f,
			0.5f, -0.2f, 0.0f,
	};

	if(m_ProgramObj == 0)
		return;

	glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Use the program object
	glUseProgram (m_ProgramObj);
	//OpenGL还不知道它该如何解释内存中的顶点数据，以及它该如何将顶点数据链接到顶点着色器的属性上
	//链接顶点属性
	// Load the vertex data
	//顶点着色器允许我们指定任何以顶点属性为形式的输入。这使其具有很强的灵活性的同时，它还的确意味着我们必须手动指定输入数据的哪一个部分对应顶点着色器的哪一个顶点属性
	// 。所以，我们必须在渲染前指定OpenGL该如何解释顶点数据。
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
	glEnableVertexAttribArray (0);

	glDrawArrays (GL_TRIANGLES, 0, 3);
	glUseProgram (GL_NONE);

}

void TriangleSample::Destroy()
{
	if (m_ProgramObj)
	{
		glDeleteProgram(m_ProgramObj);
		m_ProgramObj = GL_NONE;
	}

}
