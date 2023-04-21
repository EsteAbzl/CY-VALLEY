#include "map.h"

Map** createMap(int width, int height){
    Map **map = NULL;

    if( !(map = calloc(width, width*sizeof(int*)))){
        printf("ERREUR: pb avec malloc");
    }

    for(int x = 0; x<width; x++){
        if( !(map[x] = calloc(height, height*sizeof(int)))){
            printf("ERREUR: pb avec malloc");
        }
    }

    return map;
}