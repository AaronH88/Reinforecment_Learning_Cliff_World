
static int cliffWorldMap[4][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1}
};

struct boardPos {

  double stateValue;
  int xPos;
  int yPos;
  double action_Q_Value[4];
};
