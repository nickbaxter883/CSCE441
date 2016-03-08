#ifndef LOAD_H
#define LOAD_H
#include "global.h"
#include "light.h"
#include <iostream>
#include <fstream>
#include "SOIL.h"
#include <vector>
#include <string>
using namespace std;

GLuint texture[2];
GLfloat diffuseBase  [] = {0.9, 0.9, 0.0, 1.0};
GLfloat specularBase [] = {0.9, 0.9, 0.9, 1.0};

GLfloat diffuseRoof  [] = {0.5, 0.0, 1.0, 1.0};

GLfloat diffuseBoat  [] = {0.2, 0.9, 0.2, 1.0};
GLfloat specularBoat [] = {0.3, 0.0, 0.3, 1.0};

void LoadGLTextures()
{
	//load an image file directly as a new OpenGL texture
	texture[0] = SOIL_load_OGL_texture ("objects/wood.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	texture[1] = SOIL_load_OGL_texture ("objects/marble.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	texture[2] = SOIL_load_OGL_texture ("objects/mountain.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	texture[3] = SOIL_load_OGL_texture ("objects/water.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

void load_object(string file) 
{ 
    GLchar type; 
    GLfloat x, y, z, u, v; 
    GLuint idx; 
    vector<Point> vertex_list; 
	vector<Point> texture_points;
	vector<Point> normal_points;
	vector<Point> face;
 
    ifstream fs; 
    fs.open(file.c_str()); 
	//cout << "opening " << file << endl;
 
    if (fs.is_open()) { 
        while (fs >> type) { 
            if (type == 'v') {
                fs >> x >> y >> z; 
				//cout << "point: " << x << " " << y << " " << z << endl;
                vertex_list.push_back(Point(x, y, z));      
			}
			else if (type == 'f') {
				//cout << "face: ";
				face.clear();
				glBegin(GL_POLYGON);
				int i = 0;
				while (fs >> idx) { 
					//cout << idx << " ";
					Point newPoint = vertex_list[idx-1];
					face.push_back(newPoint);
					if (texture_points.size()) {
						Point t = texture_points[i];
						glTexCoord2f(t.x, t.y);
					}
					if (normal_points.size()) {
						Point n = normal_points[i];
						glNormal3f(n.x, n.y, n.z);
					}
					glVertex3f (newPoint.x, newPoint.y, newPoint.z);
                    if (fs.peek() == '\n') break; 
					i++;
                } 
				//cout << endl;
				if (!normal_points.size()) {
					Point v1 = face[0] - face[1];
					Point v2 = face[2] - face[1];
					//cout << "v1: " << v1.x << " " << v1.y << " " << v1.z << endl;
					//cout << "v2: " << v2.x << " " << v2.y << " " << v2.z << endl;
					Point normal = v2.crossProd(v1).norm();
					//cout << "\tnormal: " << normal.x << " " << normal.y << " " << normal.z << endl;
					glNormal3f (normal.x, normal.y, normal.z);
				}
				texture_points.clear();
				normal_points.clear();
				glEnd();
			}
			else if (type == 't') {
				fs >> u >> v;
				texture_points.push_back(Point(u, v, 0));
			}
			else if (type == 'n') {
				fs >> x >> y >> z;
				normal_points.push_back(Point(x, y, z).norm());
			}
        } 
    } 
    else { 
        cout << "Could not open file!\n"; 
        exit(0); 
    } 
 
    fs.close(); 
} 

void drawScene()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//eye, center, up
	gluLookAt(eye.x, eye.y, eye.z, eye.x + view.x, eye.y + view.y, eye.z + view.z, up.x, up.y, up.z);

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		load_object("objects/mountain.obj");
		glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		load_object("objects/water.obj");
		glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	glPushMatrix();
		glRotatef (5*sin(2*PI*animation/iterations), 1, 0, 0);

		glPushMatrix();
			glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseBase);
			glMaterialfv (GL_FRONT, GL_SPECULAR, specularBase);
			glMaterialf (GL_FRONT, GL_SHININESS, 100);
			load_object("objects/base.obj");
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glPushMatrix();
			glTranslatef (2, 2, 12);
			glRotatef (180, 0, 0, 1);
			load_object("objects/beam.obj");
		glPopMatrix();

		glPushMatrix();
			glTranslatef (-2, 2, 12);
			glRotatef (-90, 0, 0, 1);
			load_object("objects/beam.obj");
		glPopMatrix();

		glPushMatrix();
			glTranslatef (-2, -2, 12);
			load_object("objects/beam.obj");
		glPopMatrix();

		glPushMatrix();
			glTranslatef (2, -2, 12);
			glRotatef (90, 0, 0, 1);
			load_object("objects/beam.obj");
		glPopMatrix();

		glPushMatrix();
			glTranslatef (12, -2, 1);
			glRotatef (90, 0, 0, 1);
			load_object("objects/beam.obj");
		glPopMatrix();

		glPushMatrix();
			glTranslatef (12, 2, 1);
			glRotatef (180, 0, 0, 1);
			load_object("objects/beam.obj");
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);

		glPushMatrix();
			glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseRoof);
			glTranslatef (0, 0, 15);
			load_object("objects/roof.obj");
		glPopMatrix();

		glPushMatrix();
			glColor3f(1.0, 0.0, 0.0);
			glTranslatef (4, 0, 0);
			glBindTexture(GL_TEXTURE_2D, texture[0]);
			load_object("objects/dock.obj");
			glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();

	glPopMatrix();

	glPushMatrix();
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuseBoat);
		glMaterialfv (GL_FRONT, GL_SPECULAR, specularBoat);
		glMaterialf (GL_FRONT, GL_SHININESS, 64);
		glRotatef (360.0*animation/iterations, 0, 0, 1);
		glTranslatef (15, 0, 1+2*sin(4.0*PI*animation/iterations));
		load_object("objects/boat.obj");
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
}

#endif

