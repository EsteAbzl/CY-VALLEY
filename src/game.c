#include "game.h"


void res_BuffObj(BuffObj* pBuffObj){
  pBuffObj->pv_Buff = 0;
  pBuffObj->atk_Buff = 0;
  pBuffObj->heal = 0;
  pBuffObj->estEquipe = 0;
}

void res_Obj(Obj* pObj){
  pObj->id_Obj = 0;
  pObj->nb_Max = 0;
  pObj->nb = 0;
  pObj->placeinv = 0;

  //for(int n; n<30 , n++){
  //  sprintf(pObj->nom, "");
  //  }

  res_BuffObj(&(pObj->buffObj));
}