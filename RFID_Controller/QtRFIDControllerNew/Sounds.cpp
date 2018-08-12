#include "Sounds.h"

bool Sounds::playActivate()
{
    if (system("play /home/denisparadiuk/Music/Activated.mp3")){
        return true;
    } else {
        return false;
    }
}

bool Sounds::playNewCard(){

    if (system("play /home/denisparadiuk/Music/NewCard.mp3")){
        return true;
    } else {
        return false;
    }
}

bool Sounds::playNotFound(){

    if (system("play /home/denisparadiuk/Music/NotFound.mp3")){
        return true;
    } else {
        return false;
    }
}

bool Sounds::playOpen(){

    if (system("play /home/denisparadiuk/Music/DoorOpen.mp3")){
        return true;
    } else {
        return false;
    }
}
