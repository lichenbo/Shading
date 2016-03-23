//
//  Path.h
//  gltest
//
//  Created by Chenbo Li on 3/5/16.
//  Copyright © 2016 binarythink. All rights reserved.
//

#ifndef Path_h
#define Path_h


#ifdef _WIN32

const char* SHADER_PATH = "Shader/";
const char* MODEL_PATH = "Model/";


#elif defined __APPLE__

const char* SHADER_PATH = "../../gltest/Shader/"; // Shader path in OSX debug mode
const char* MODEL_PATH = "../../gltest/Model/";

#endif

#define GET_SHADER_PATH(path, n, str) \
    memset(path, 0, n); \
    strcat(path, SHADER_PATH); \
    strcat(path, str);

#define GET_MODEL_PATH(path, n, str) \
    memset(path, 0, n); \
    strcat(path, MODEL_PATH); \
    strcat(path, str);

#endif /* Path_h */
