//
// Created by antonella on 03/09/18.
//

#ifndef EXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <sstream>



class Texture{

    private:

        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;

    public:
        Texture();

        ~Texture();

        bool loadFromFile( std::string path, SDL_Renderer* gRenderer);

        #ifdef _SDL_TTF_H
            //Creates image from font string
                bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
        #endif

        void free();

        void setColor( Uint8 red, Uint8 green, Uint8 blue);

        void setBlendMode( SDL_BlendMode blending);

        void setAlpha( Uint8 alpha);

        void render( int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);

        //Gets image dimensions
        int getWidth();
        int getHeight();

};


#endif //TEXTURE_H
