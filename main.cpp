#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define dimension 30


class dipole_state
{
public:
  double arg = (2*M_PI)*(1.0/4.0);
  double length = 1.0;
  double potential = 1.0;
  double enable = 1.0;
};

class field
{
  public:
  double arg = (2.0*M_PI)*(1.0/4.0);
  double strength = 1.5;
  double strength_final = 1.5;
};

void display_cell(dipole_state[][dimension]);

main()
{
FILE *RecFile;
RecFile = fopen("Rec.txt", "w");
fprintf(RecFile, "number of trial,B,potential\n");


  int i, j;
  double k;
  double torialNo =20000;
  double allPotential = 0.0;
  field magneticField;
  dipole_state magnetic[dimension][dimension];
  dipole_state rand_magnetic;

  //無効セルの設定
  //端のセルを無効化
  for (i = 0; i < dimension-1; i++)
  {
    magnetic[i][0].enable = 0.0;
  }
  for (i = 0; i < dimension-1; i++)
  {
    magnetic[i][6].enable = 0.0;
  }
  for (j = 0; j < dimension-1; j++)
  {
    magnetic[0][j].enable = 0.0;
  }
  for (j = 0; j < dimension-1; j++)
  {
    magnetic[6][j].enable = 0.0;
  }


  //角度の初期化
  for (i = 1; i <= dimension-2; i++)
  {
    for (j = 1; j <= dimension-2; j++)
    {
    //ランダムな角度で初期化
    //magnetic[i][j].arg =((double)rand() / ((double)RAND_MAX + 1)) *(2*M_PI);
    //決まった角度で初期化
    magnetic[i][j].arg = (2*M_PI)*(3.0/4.0);
    }
  }


  //ポテンシャルの初期化
  for (i = 1; i <= dimension-2; i++)
  {
    for (j = 1; j <= dimension-2; j++)
    {
      magnetic[i][j].potential =
          -1.0 * (cos(magnetic[i + 1][j].arg - magnetic[i][j].arg)*magnetic[i + 1][j].enable
           + cos(magnetic[i - 1][j].arg - magnetic[i][j].arg)*magnetic[i -1][j].enable
           + cos(magnetic[i][j + 1].arg - magnetic[i][j].arg)*magnetic[i][j+1].enable
           + cos(magnetic[i][j - 1].arg - magnetic[i][j].arg))*magnetic[i][j-1].enable;
      magnetic[i][j].potential = magnetic[i][j].potential-magneticField.strength*cos(magneticField.arg - magnetic[i][j].arg);
    }
  }

    display_cell(magnetic);
    //sleep(11111111);


  display_cell(magnetic);

  //メインのループ
  for (k = 0; k < torialNo; k++)
  {
    printf("processing:%f %\n", (k / torialNo) * 100.0);
    for (i = 1; i <= dimension-2; i++)
    {
      for (j = 1; j <= dimension-2; j++)
      {
        //ランダムに配置
          rand_magnetic.arg = ((double)rand() / ((double)RAND_MAX + 1)) *(2*M_PI);
          rand_magnetic.potential =
              -1.0 * (cos(magnetic[i + 1][j].arg - rand_magnetic.arg)*magnetic[i + 1][j].enable
                + cos(magnetic[i - 1][j].arg - rand_magnetic.arg)*magnetic[i - 1][j].enable
                + cos(magnetic[i][j + 1].arg - rand_magnetic.arg)*magnetic[i][j+1].enable
                + cos(magnetic[i][j - 1].arg - rand_magnetic.arg)*magnetic[i][j-1].enable);
          rand_magnetic.potential = rand_magnetic.potential-magneticField.strength*cos(magneticField.arg - rand_magnetic.arg);

          if (rand_magnetic.potential < magnetic[i][j].potential)
          {
            magnetic[i][j].arg = rand_magnetic.arg;
            magnetic[i][j].potential = rand_magnetic.potential;
          }
          allPotential=allPotential+magnetic[i][j].potential;
      }
    }
    fprintf(RecFile, "%f,%f,%f\n",k,magneticField.strength,allPotential);
    allPotential =0.0;
    magneticField.strength=magneticField.strength-(magneticField.strength_final*2/torialNo);
  }
  display_cell(magnetic);
  fclose(RecFile);
  return 0;
}

void display_cell(dipole_state magnetic[][dimension])
{
  printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
  int i, j;
  //表示
  for (i = 1; i <= 5; i++)
  {
    for (j = 1; j <= 5; j++)
    {
      printf("|U=%3.2f:arg=%3.2f[deg]|", magnetic[i][j].potential, magnetic[i][j].arg*(360.0/(2*M_PI)));
      //printf("|arg=%3.2f[deg]|",magnetic[i][j].arg*(360.0/(2*M_PI)));
      //printf("|U=%3.2f|", magnetic[i][j].potential);


      //printf("|arg:%3.2f\t|", magnetic[i][j].potential, magnetic[i][j].arg);
    }
    printf("\n");
  }
}
