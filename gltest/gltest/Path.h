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


#elif defined __APPLE__

const char* SHADER_PATH = "../../gltest/Shader/"; // Shader path in OSX debug mode


#endif

#endif /* Path_h */
