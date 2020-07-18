//
// Adapted by Ryan Beaumont on 8/04/20.
// This is an adaption of the code for reading and drawing off files given in the lab
//

#if !defined(H_LMF)
#define H_LMF

#include <iostream>
#include <fstream>
#include <climits>
#include <math.h>
#include <GL/freeglut.h>
using namespace std;

float *x, *y, *z;					//vertex coordinates
int *nv, *t1, *t2, *t3, *t4;		//number of vertices and vertex indices of each face
int nvert, nface;					//total number of vertices and faces
float angleX = 10.0,  angleY = -20;	//Rotation angles about x, y axes
float xmin, xmax, ymin, ymax;

void normal(int indx)
{
    float x1 = x[t1[indx]], x2 = x[t2[indx]], x3 = x[t3[indx]];
    float y1 = y[t1[indx]], y2 = y[t2[indx]], y3 = y[t3[indx]];
    float z1 = z[t1[indx]], z2 = z[t2[indx]], z3 = z[t3[indx]];
    float nx, ny, nz;
    nx = y1*(z2-z3) + y2*(z3-z1) + y3*(z1-z2);
    ny = z1*(x2-x3) + z2*(x3-x1) + z3*(x1-x2);
    nz = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
    glNormal3f(nx, ny, nz);
}

void loadMeshFile(const char* fname)
{
    ifstream fp_in;
    int ne;

    fp_in.open(fname, ios::in);
    if(!fp_in.is_open())
    {
        cout << "Error opening mesh file" << endl;
        exit(1);
    }

    fp_in.ignore(INT_MAX, '\n');				//ignore first line
    fp_in >> nvert >> nface >> ne;			    // read number of vertices, polygons, edges (not used)

    x = new float[nvert];                        //create arrays
    y = new float[nvert];
    z = new float[nvert];

    nv = new int[nface];
    t1 = new int[nface];
    t2 = new int[nface];
    t3 = new int[nface];
    t4 = new int[nface];

    for(int i=0; i < nvert; i++)                         //read vertex list
        fp_in >> x[i] >> y[i] >> z[i];

    for(int i=0; i < nface; i++)                         //read polygon list
    {
        fp_in >> nv[i] >> t1[i] >> t2[i] >> t3[i];
        if (nv[i] == 4)
            fp_in >> t4[i];
        else
            t4[i] = -1;
    }

    fp_in.close();
}

void drawObjectFromFile (const char* fname){
    loadMeshFile(fname);
    for(int indx = 0; indx < nface; indx++)		//draw each face
    {
        normal(indx);
        if (nv[indx] == 3)	glBegin(GL_TRIANGLES);
        else				glBegin(GL_QUADS);
        glVertex3d(x[t1[indx]], y[t1[indx]], z[t1[indx]]);
        glVertex3d(x[t2[indx]], y[t2[indx]], z[t2[indx]]);
        glVertex3d(x[t3[indx]], y[t3[indx]], z[t3[indx]]);
        if(nv[indx]==4)
            glVertex3d(x[t4[indx]], y[t4[indx]], z[t4[indx]]);
        glEnd();
    }
}

#endif