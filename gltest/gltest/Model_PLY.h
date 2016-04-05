//
//  Model_PLY.h
//  gltest
//
//  Created by Chenbo Li on 3/5/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#ifndef Model_PLY_h
#define Model_PLY_h
/* Demonstrates how to load PLY files
 * Needs some refactoring.
 *
 * http://talkera.org/opengl/
 * Model needs to be triangulated
 * Use blender
 *
 * Just the class for loading PLY files.
 *
 */
#define M_PI       3.14159265358979323846

#include <cmath>
#ifdef _WIN32
    #include <windows.h>
    #include <GL/glew.h>
#elif defined __APPLE__
    #include <OpenGL/gl3.h>
#endif

#include <stdio.h>
#include <string.h>

#include <string>
#include <stdlib.h>


class Model_PLY
{
public:
    int Load(const char *filename);
    void Draw();
    float* calculateDomeTexture( float coord1, float coord2, float coord3 );
    Model_PLY();
    
    float* Faces_Triangles;
    float* Faces_Quads;
    float* Vertex_Buffer;
    float* Normals;
	float* Textures;
    
    int TotalConnectedTriangles;
    int TotalConnectedQuads;
    int TotalConnectedPoints;
    int TotalFaces;
    
    
};


inline float* Model_PLY::calculateDomeTexture(float coord1, float coord2, float coord3)
{
	float* uv = new float[2];
	uv[0] = 0.5 - atan2(coord3, coord1) / (2* M_PI);
	uv[1] = acos(coord2) / M_PI;
	return uv;
}

Model_PLY::Model_PLY()
{
    
}

int Model_PLY::Load(const char* filename)
{
    this->TotalConnectedTriangles = 0;
    this->TotalConnectedQuads = 0;
    this->TotalConnectedPoints = 0;
    
    const char* pch = strstr(filename,".ply");
    
    if (pch != NULL)
    {
        FILE* file = fopen(filename,"r");
        
        fseek(file,0,SEEK_END);
        long fileSize = ftell(file);
        
        try
        {
            Vertex_Buffer = (float*) malloc (ftell(file));
        }
        catch (char* )
        {
            return -1;
        }
        if (Vertex_Buffer == NULL) return -1;
        fseek(file,0,SEEK_SET);
        
        Faces_Triangles = (float*) malloc(fileSize*sizeof(float));
        Normals  = (float*) malloc(fileSize*sizeof(float));
		Textures = (float*)malloc(fileSize*sizeof(float));
        
        if (file)
        {
            int i = 0;
            int temp = 0;
            int quads_index = 0;
            int triangle_index = 0;
            int normal_index = 0;
            int texture_index = 0;
            char buffer[1000];
            
            fgets(buffer,300,file);			// ply
            
            
            // READ HEADER
            // -----------------
            
            // Find number of vertexes
            while (  strncmp( "element vertex", buffer,strlen("element vertex")) != 0  )
            {
                fgets(buffer,300,file);			// format
            }
            strcpy(buffer, buffer+strlen("element vertex"));
            sscanf(buffer,"%i", &this->TotalConnectedPoints);
            
            // Find number of vertexes
            fseek(file,0,SEEK_SET);
            while (  strncmp( "element face", buffer,strlen("element face")) != 0  )
            {
                fgets(buffer,300,file);			// format
            }
            strcpy(buffer, buffer+strlen("element face"));
            sscanf(buffer,"%i", &this->TotalFaces);
            
            // go to end_header
            while (  strncmp( "end_header", buffer,strlen("end_header")) != 0  )
            {
                fgets(buffer,300,file);			// format
            }
            
            // read verteces
            i =0;
            for (int iterator = 0; iterator < this->TotalConnectedPoints; iterator++)
            {
                fgets(buffer,300,file);
                sscanf(buffer,"%f %f %f %f %f %f", &Vertex_Buffer[i], &Vertex_Buffer[i+1], &Vertex_Buffer[i+2], &Vertex_Buffer[i+3], &Vertex_Buffer[i+4], &Vertex_Buffer[i+5]);
                i += 6;
            }
            
            // read faces
            i =0;
            for (int iterator = 0; iterator < this->TotalFaces; iterator++)
            {
                fgets(buffer,300,file);
                if (buffer[0] == '3')
                {
                    int vertex1 = 0, vertex2 = 0, vertex3 = 0;
                    buffer[0] = ' ';
                    sscanf(buffer,"%i%i%i", &vertex1,&vertex2,&vertex3);
                    
                    Faces_Triangles[triangle_index] = Vertex_Buffer[6*vertex1];
                    Faces_Triangles[triangle_index+1] = Vertex_Buffer[6*vertex1+1];
                    Faces_Triangles[triangle_index+2] = Vertex_Buffer[6*vertex1+2];
                    
                    Faces_Triangles[triangle_index+3] = Vertex_Buffer[6*vertex2];
                    Faces_Triangles[triangle_index+4] = Vertex_Buffer[6*vertex2+1];
                    Faces_Triangles[triangle_index+5] = Vertex_Buffer[6*vertex2+2];
                    
                    Faces_Triangles[triangle_index+6] = Vertex_Buffer[6*vertex3];
                    Faces_Triangles[triangle_index+7] = Vertex_Buffer[6*vertex3+1];
                    Faces_Triangles[triangle_index+8] = Vertex_Buffer[6*vertex3+2];
                    
                    float coord1[3] = { Faces_Triangles[triangle_index], Faces_Triangles[triangle_index+1],Faces_Triangles[triangle_index+2]};
                    float coord2[3] = {Faces_Triangles[triangle_index+3],Faces_Triangles[triangle_index+4],Faces_Triangles[triangle_index+5]};
                    float coord3[3] = {Faces_Triangles[triangle_index+6],Faces_Triangles[triangle_index+7],Faces_Triangles[triangle_index+8]};
                    
                    Normals[normal_index] = Vertex_Buffer[6*vertex1 + 3];
                    Normals[normal_index+1] = Vertex_Buffer[6*vertex1 + 4];
                    Normals[normal_index+2] = Vertex_Buffer[6*vertex1 + 5];
                    Normals[normal_index+3] = Vertex_Buffer[6*vertex2 + 3];
                    Normals[normal_index+4] = Vertex_Buffer[6*vertex2 + 4];
                    Normals[normal_index+5] = Vertex_Buffer[6*vertex2 + 5];
                    Normals[normal_index+6] = Vertex_Buffer[6*vertex3 + 3];
                    Normals[normal_index+7] = Vertex_Buffer[6*vertex3 + 4];
                    Normals[normal_index+8] = Vertex_Buffer[6*vertex3 + 5];
                    
                    float* textureCoord1 = calculateDomeTexture(Normals[normal_index], Normals[normal_index+1], Normals[normal_index+2]);
                    float* textureCoord2 = calculateDomeTexture(Normals[normal_index+3], Normals[normal_index+4], Normals[normal_index+5]);
                    float* textureCoord3 = calculateDomeTexture(Normals[normal_index+6], Normals[normal_index+7], Normals[normal_index+8]);
                    Textures[texture_index] = textureCoord1[0];
                    Textures[texture_index+1] = textureCoord1[1];
                    Textures[texture_index+2] = textureCoord2[0];
                    Textures[texture_index+3] = textureCoord2[1];
                    Textures[texture_index+4] = textureCoord3[0];
                    Textures[texture_index+5] = textureCoord3[1];

                    texture_index+= 6;
                    normal_index += 9;
                    
                    triangle_index += 9;
                    TotalConnectedTriangles += 3;
                }
                i += 3;
            }
            fclose(file);
        }
        
        else { printf("File can't be openedn"); }
    } else {
        printf("File does not have a .PLY extension. ");    
    }
    printf("File %s loaded.\n", filename);
    return 0;
}


#endif /* Model_PLY_h */
