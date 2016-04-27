#pragma once

#include "rt3d.h"
#include "rt3dObjLoader.h"
#include "vector2.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>

using std::vector;

class Label {

public:

	void loadMesh(char* fileName) {
		vector<GLfloat> verts;
		vector<GLfloat> norms;
		vector<GLfloat> tex_coords;
		vector<GLuint> indices;
		rt3d::loadObj(fileName, verts, norms, tex_coords, indices);
		GLuint size = indices.size();
		meshIndexCount = size;

		mesh = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), size, indices.data());
	}
	

	void draw() {

	}

	GLuint textToTexture(const char * str, GLuint textID) {
		GLuint texture = textID;
		TTF_Font * font = textFont;

		SDL_Surface * stringImage = TTF_RenderText_Blended(font, str, { 255, 255, 255 });

		if (stringImage == NULL) {
			std::cout << "String surface not created." << std::endl;
		}

		if (texture == 0) {
			glGenTextures(1, &texture);
		}

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, stringImage->w, stringImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, stringImage->pixels);
		glBindTexture(GL_TEXTURE_2D, NULL);

		SDL_FreeSurface(stringImage);
		return texture;
	}

	char* text;
	Vector2 pos, size;

private:
	TTF_Font* textFont;

	GLuint mesh;
	GLuint meshIndexCount = 0;

};
