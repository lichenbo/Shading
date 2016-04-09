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
const char* SHADER_DEFER_PATH = "Shader/DeferredShading/";
const char* SHADER_EXPONENTIAL_PATH= "Shader/ExponentialShadowMap/";
const char* SHADER_IMAGELIGHT_PATH= "Shader/ImageBasedLighting/";
const char* SHADER_VISBUFFER_PATH= "Shader/VisibilityBuffer/";
const char* MODEL_PATH = "Model/";
const char* HDR_PATH = "IBL/";


#elif defined __APPLE__

const char* SHADER_PATH = "../../gltest/Shader/"; // Shader path in OSX debug mode
const char* SHADER_DEFER_PATH = "../../gltest/Shader/DeferredShading/";
const char* SHADER_EXPONENTIAL_PATH = "../../gltest/Shader/ExponentialShadowMap/";
const char* SHADER_IMAGELIGHT_PATH = "../../gltest/Shader/ImageBasedLighting/";
const char* SHADER_VISBUFFER_PATH= "../../gltest/Shader/VisibilityBuffer/";
const char* MODEL_PATH = "../../gltest/Model/";
const char* HDR_PATH = "../../gltest/IBL/";

#endif

#define GET_SHADER_PATH(path, n, str) \
    memset(path, 0, n); \
    strcat(path, SHADER_PATH); \
    strcat(path, str);

#define GET_SHADER_DEFER_PATH(path, n, str) \
    memset(path, 0, n); \
    strcat(path, SHADER_DEFER_PATH); \
    strcat(path, str);
#define GET_SHADER_EXPONENTIAL_PATH(path, n, str) \
    memset(path, 0, n); \
    strcat(path, SHADER_EXPONENTIAL_PATH); \
    strcat(path, str);
#define GET_SHADER_IMAGELIGHT_PATH(path, n, str) \
    memset(path, 0, n); \
    strcat(path, SHADER_IMAGELIGHT_PATH); \
    strcat(path, str);

#define GET_SHADER_VISBUFFER_PATH(path, n, str) \
    memset(path, 0, n); \
    strcat(path, SHADER_VISBUFFER_PATH); \
    strcat(path, str);

#define GET_MODEL_PATH(path, n, str) \
    memset(path, 0, n); \
    strcat(path, MODEL_PATH); \
    strcat(path, str);

#define GET_HDR_PATH(path, n, str) \
	memset(path, 0, n); \
	strcat(path, HDR_PATH); \
	strcat(path, str);

#endif /* Path_h */
