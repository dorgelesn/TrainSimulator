typedef struct Voie{
  int id;
  Aiguillage aiguillageLeft;
  Aiguillage aiguillageRight;
  int[2] sens;
    //  [0] = vers la gauche
    //  [1] = vers la droite

  int[3] typeTrain
    //  [0] = autorise TGV
    //  [1] = autorise GL
    //  [2] = autorise M
}Voie;
