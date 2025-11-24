#include "core/gl/VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Update(const void* data, GLsizeiptr size)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	Unbind();
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}