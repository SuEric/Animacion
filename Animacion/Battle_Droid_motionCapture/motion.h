#define NUM_JOINTS 5
#define MAX_CPOINTS 34
#define OVERSAMPLE 10
#define CYCLE_SIZE 100
#define CYCLE_STEP 1.0/CYCLE_SIZE

float fStep = CYCLE_SIZE/2;  
float IncStep = 1.0;
GLfloat Walk_cycle[2][NUM_JOINTS][CYCLE_SIZE];  //arreglo de los angulos calculados
int Step = CYCLE_SIZE/2;  // Posicion en ciclo, inicia en medio 


typedef struct ControlPts {
  int numpoints;
  float xcoords[MAX_CPOINTS];
  float angles[MAX_CPOINTS];
} tControlPts;

tControlPts RotCurve[NUM_JOINTS];

/***********************BEZIER**********************/

void MultMV(float m[3][4], float v[4], float dest[3]){
  int i, j;
  for (i = 0; i < 3; i++) {
    dest[i] = 0;
    for (j = 0; j < 4; j++)
      dest[i] += m[i][j] * v[j];
  }
}

void MultM(float m1[3][4], float m2[4][4], float dest[3][4]){
  int i, j, k;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 4; j++) {
      dest[i][j] = 0;
      for (k = 0; k < 4; k++)
		dest[i][j] += (m1[i][k] * m2[k][j]);
    }
}

void ComputeCurve(int joint){
  float prod[3][4], tm[4], pos[3];
  float t = 0, tinc = (float)CYCLE_STEP/OVERSAMPLE;
  int ctlpoint, i;
  float BBasis[4][4] = {{-1, 3, -3, 1}, {3, -6, 3, 0},
                        {-3, 3,  0, 0}, {1,  0, 0, 0}};
  int lastindex, newindex;

  float pointset[3][4];
  for (i = 0; i < 4; i++)   // las z's son siempre cero, solo en 2-d
    pointset[2][i] = 0; 

  lastindex = -1;
  for(ctlpoint = 0; ctlpoint < RotCurve[joint].numpoints; ctlpoint += 3) {
    t = 0;
    for (i = 0; i < 4; i++)
      pointset[0][i] = RotCurve[joint].xcoords[ctlpoint + i];
    for (i = 0; i < 4; i++)
      pointset[1][i] = RotCurve[joint].angles[ctlpoint + i];

    MultM(pointset, BBasis, prod);

    while (t <= 1) {
      tm[0] = t*t*t;
      tm[1] = t*t;
      tm[2] = t;
      tm[3] = 1;
      MultMV(prod, tm, pos);
      newindex = (int)(pos[0]*(CYCLE_SIZE-1));

      if ((int)(newindex > lastindex))  { 
	Walk_cycle[0][joint][newindex] = pos[1];
	lastindex++;
      } 
      t += tinc;
    }
  }

  for (i = 0; i < CYCLE_SIZE; i++)
      Walk_cycle[1][joint][i] = Walk_cycle[0][joint][(i+(CYCLE_SIZE/2))%CYCLE_SIZE];
}


//Lee archivo de movimientos
int ReadCSetFromFile(char *filename)
{
  FILE *infile = fopen(filename, "r");  
  int numjoints, numpoints, joint, point, mirrorlegs;
  float value;

  if (infile == NULL)
    goto abort;
  
  if (!fscanf(infile, " %d", &numjoints) || numjoints != NUM_JOINTS)
    goto abort;

  if (!fscanf(infile, " %d", &mirrorlegs) || (mirrorlegs != 0 &&
                                              mirrorlegs != 1))
    goto abort;  

  for (joint = 0; joint < NUM_JOINTS; joint++) {
    if (!fscanf(infile, " %d", &numpoints) || numpoints < 4 || numpoints > MAX_CPOINTS)
      goto abort;

    RotCurve[joint].numpoints = numpoints;

    for (point = 0; point < numpoints; point++){
      if (!fscanf(infile, " %f", &value))
	goto abort;
      RotCurve[joint].xcoords[point] = value;
    }
    for (point = 0; point < numpoints; point++) {
      if (!fscanf(infile, " %f", &value))
	goto abort;
      RotCurve[joint].angles[point] = value;
    }
  }

  fclose(infile);
  return 0;

  abort:
    fclose(infile);
    fprintf(stderr, "Something went wrong while reading file %s\n", filename);
    //FlatCSet();
    return -1;
}

void ComputeCSetAndMakeLists(void){
  int joint;
    
  for(joint = 0; joint < NUM_JOINTS; joint++)
    ComputeCurve(joint);
}