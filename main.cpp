#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

class dipole_state
{
public:
  double arg = 3.14/2.11;
  double length = 1.0;
  double potential = 1.0;
  int enable = 1;
};
void display_cell(dipole_state[][7]);

main()
{

  int i, j;
  double k;
  double torialNo = 1000000;
  dipole_state magnetic[7][7];
  dipole_state rand_magnetic;

  //角度の初期化
  for (i = 1; i <= 5; i++)
  {
    for (j = 1; j <= 5; j++)
    {
      // magnetic[i][j].arg = rand() % 360;                            //乱数で初期化，単位は[deg]
      // magnetic[i][j].arg = ((2 * M_PI) / 360) * magnetic[i][j].arg; //[rad]に変換
      magnetic[i][j].arg =((double)rand() / ((double)RAND_MAX + 1)) *(2*M_PI);
    }
  }


  //ポテンシャルの初期化
  for (i = 1; i <= 5; i++)
  {
    for (j = 1; j <= 5; j++)
    {
      magnetic[i][j].potential =
          -1.0 * (cos(magnetic[i + 1][j].arg - magnetic[i][j].arg)
           + cos(magnetic[i - 1][j].arg - magnetic[i][j].arg)
           + cos(magnetic[i][j + 1].arg - magnetic[i][j].arg) 
           + cos(magnetic[i][j - 1].arg - magnetic[i][j].arg));
    }
  }

    display_cell(magnetic);
    //sleep(11111111);


  display_cell(magnetic);
  for (k = 0; k < torialNo; k++)
  {
    printf("processing:%f %\n", (k / torialNo) * 100.0);
    for (i = 1; i <= 5; i++)
    {
      for (j = 1; j <= 5; j++)
      {

          rand_magnetic.arg = rand() % 360;
          rand_magnetic.arg = ((2 * M_PI) / 360) * rand_magnetic.arg; //[rad]に変換
          rand_magnetic.potential =
              -1.0 * (cos(magnetic[i + 1][j].arg - rand_magnetic.arg)
                + cos(magnetic[i - 1][j].arg - rand_magnetic.arg)
                + cos(magnetic[i][j + 1].arg - rand_magnetic.arg) 
                + cos(magnetic[i][j - 1].arg - rand_magnetic.arg));
          if (rand_magnetic.potential < magnetic[i][j].potential)
          {
            magnetic[i][j].arg = rand_magnetic.arg;
            magnetic[i][j].potential = rand_magnetic.potential;
          }
      }
    }
  }

  display_cell(magnetic);
  return 0;
}

void display_cell(dipole_state magnetic[][7])
{
  printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
  int i, j;
  //表示
  for (i = 1; i <= 5; i++)
  {
    for (j = 1; j <= 5; j++)
    {
      //printf("|U=%3.2f:arg=%3.2f[deg]|", magnetic[i][j].potential, magnetic[i][j].arg*(360.0/(2*M_PI)));
      //printf("|arg=%3.2f[deg]|",magnetic[i][j].arg*(360.0/(2*M_PI)));
      printf("|U=%3.2f|", magnetic[i][j].potential);


      //printf("|arg:%3.2f\t|", magnetic[i][j].potential, magnetic[i][j].arg);
    }
    printf("\n");
  }
}
