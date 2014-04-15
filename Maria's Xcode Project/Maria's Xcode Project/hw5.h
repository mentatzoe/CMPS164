//
//  hw5.h
//  Maria's Xcode Project
//
//  Created by Maria Lopez Latorre on 15/04/14.
//  Copyright (c) 2014 CMPS 164 Game Engines. All rights reserved.
//

#ifndef Maria_s_Xcode_Project_hw5_h
#define Maria_s_Xcode_Project_hw5_h

const int texture_width = 256;
const int texture_height = 256;
GLubyte texture_image[256][256][3];

void generate_texture()
{
    for(int i=0; i<texture_width; i++)
        for(int j=0; j<texture_width; j++)
        {
            texture_image[i][j][0] = 255;
            texture_image[i][j][1] = 255*(i & 0x04);
            texture_image[i][j][2] = 255*(j & 0x04);
        }
}

#endif
