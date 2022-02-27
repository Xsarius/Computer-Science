// Politechnika Warszawska
// Wydział Mechaniczny Energetyki i Lotnictwa
// Power Engineering
// Computer Science 1
// Homework 1 
// Kuba Jałoszyński 
// Album number: 304457 
// To compile with <> version or newer
// Made on Microsoft Visual Studio 2019, Microsoft Visual Studio Code
//
// ! If compiled with earlier IDE's, 
// can occur problem(s) that stdbool.h library is not included, etc. !

///////////////////
// Directories. //
/////////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#pragma warning(disable : 4996)

////////////////////////////////////////////////////////////////////////////////
/// Size (type) of figure that should envelop and contain generated points. ///
//////////////////////////////////////////////////////////////////////////////

#define FVN 5                        // F-igure V-ertex N-umber, 
                                    // will be coresponding to 
                                   // number of rows in Figure[][] array.
#define DN 2                      // D-imentions N-umber,
                                 // will be coresponding to,
                                // number of columns in Figure[][] array.
                               // Number of figures to be 
#define NumberOfFigures 2     // generated.
                             // 
#define PI acos(-1.0)       // Defining PI value.

////////////////////////////
// Functions prototypes. //
//////////////////////////

int ReadInput(), AreaCompare(double*);
double Area(double**, double**);
double FigureXverticiesGenerator();
double FigureYverticiesGenerator(); 
double PointsGenerator(int);
void PrintOutput(int,int,double**,double**); 

//////////////////////////
// Files declarations. //
////////////////////////

FILE* pointscoordinates;     // File conatining all generated points coordinates.
FILE* pentagons;             // File containing generated pentagons.

////////////////////////////////
// Main function of program. //  
//////////////////////////////

int main()                                 
{
    int PointsNumber, SmallestFigureID;
    double *FigureX = (double *)malloc(FVN * sizeof(double));
    double *FigureY = (double *)malloc(FVN * sizeof(double)); 
    double *FigureArea = (double *)malloc(NumberOfFigures * sizeof(double));              
    
    double **Figure = (double**)malloc(FVN * sizeof(double));
    for (int i = 0; i < DN; i++)
    {
        Figure[i] = (double *)malloc(DN * sizeof(double));
    }


    srand((unsigned)time(NULL));
    PointsNumber = ReadInput();
    double **Point = (double**)malloc(PointsNumber * sizeof(double));
    for (int Dimentsion = 0; Dimentsion < PointsNumber; Dimentsion++)
    {
        Point[Dimentsion] = (double*)malloc(DN * sizeof(double));
    }
    **Point = PointsGenerator(PointsNumber);
    for (int FigureID = 0; FigureID < NumberOfFigures; FigureID++)
    {
        for (int i = 0; i < DN; i++)
        {
            switch (i)
            {
            case 0:
                Figure[FigureID][i] = FigureXverticiesGenerator();
                break;
            case 1:
                Figure[FigureID][i] = FigureYverticiesGenerator();
                break;
            default:
                break;
            }
        }
        FigureArea[FigureID] = Area(Figure,Point);
    }
    SmallestFigureID = AreaCompare(FigureArea);

    PrintOutput(PointsNumber,SmallestFigureID,Point,Figure);
    for(int i = 0; i < FVN; i++)
    {
        free(Figure[i]);
    }
    free(Point);
    free(Figure);

    return 0;                       
}

//////////////////////////////
// Functions declarations. //
////////////////////////////

int ReadInput()                                                                     //Reading value of n - points to be generated
{
    int Num = 0;                                //Number of points which will be generated, should be set to be more than FVN.
    while (Num < FVN)
    {
        system("cls");
        printf("Type number of points to be generated on 2D cartesian space: ");
        scanf_s("%d", &Num);
        if (Num < FVN)                         //Chcecking if running program to get proper results is posible, if given conitions can be satisfied.
        {
            int Dec;                           //Decision if user wants to cointinue the program after wrong typed number of points.
            printf("Given number of points is to small to geerate %d-angled figure around it.\n Do you want to type other value? (1.Yes 2.No)", FVN);
            scanf_s("%d", &Dec);
            if(Dec != 1)
            {
                exit(0);
            }
            else
            {
                continue;
            }
        }
        else
        {
            break;
        }
    }
    
    system("cls");
    return Num;
}

int AreaCompare(double *FigureArea)
{
    int SmallestFAID = 0;
    for (int i = 0; i < NumberOfFigures; i++)
    {
        if (FigureArea[i+1] < FigureArea[i])
        {
            SmallestFAID = i + 1;
        }
        else 
        {
            continue;
        }
    }

    return SmallestFAID;
}

double Area(double **Figures,double **Points)                                          // Comparing size of areas, of earlier generater figures. 
{
    double FigureArea;                                                               // Array containing areas of figures under coresponding indexes 
        for (int i = 0; i < NumberOfFigures; i++)
        {
            double x = 0, y = 0;
            for (int Row = 0; Row < FVN; Row++)
            {
                for (int Column = 0; Column < DN; Column++)
                {
                    if(Column == 0) {
                        x += Figures[Row][Column];                                  // Finding centre of figure S(x,y) 
                    }                                                               // for further calculation
                    else                                                            // of radious R.
                    {                                                                
                        y += Figures[Row][Column];                                    
                    }                                                               
                }
            }
            x = x/(double)FVN;
            y = y/(double)FVN;                                                          // Radious R can be calculated using Pythagoras theorem
            double R = sqrt(pow((x-Points[0][0]),2.) + pow((y-Points[0][1]),2.));        // choise of point for Points array is free, R will have same value for all.
            FigureArea = 0.5 * FVN * sin(2 * PI / FVN) * pow(R,2.);       
        }

    return FigureArea;
}

double FigureXverticiesGenerator()                                                  // Generating random X value of figures which satisfies requirements. 
{
    double *FigureVertices = (double *)malloc( FVN * sizeof(double));                  // Alocating memory for
        for(int i = 0; i < FVN; i++)                                                // FVN - verticies figure.
        {
            FigureVertices[i] = rand()/(double)RAND_MAX;
        }
    


    return *FigureVertices;
}

double FigureYverticiesGenerator()                                                  // Generating random Y value of figures which satisfies requirements. 
{
    double *FigureVertices = (double *)malloc( FVN * sizeof(double));                 // Alocating memory for
        for(int i = 0; i < FVN; i++)                                               // FVN - verticies figure.
        {
            FigureVertices[i] = rand()/(double)RAND_MAX;
        }


    return *FigureVertices;
}

double PointsGenerator(int PointsNumber)                                            // Generating random coordinated points on the cartesian plane named Cplane.
{
    double **Points = (double **)malloc(PointsNumber * sizeof(double));               // Alocating memory for
        for(int Dimentsion = 0; Dimentsion < DN; Dimentsion++)                                      // n- points set.
        {
            Points[Dimentsion] = (double *)malloc(sizeof(double));
        }

    for (int PointID = 0; PointID < PointsNumber; PointID++)
    {
        for (int Dimentsion = 0; Dimentsion < DN; Dimentsion++)                         // Randomly generating n-points
        {                                                                              // The domain can be set to any number,
             Points[PointID][Dimentsion] = rand()/(double)RAND_MAX;                    // 10 is set to make graph 
        }                                                                            // and calc look better.
    }

    return **Points;
}

void PrintOutput(int PointNumber,int SmallerAreaFigureID,double **Points,double **Figure)  // Saving work results of program 
{
      
    pointscoordinates = fopen("pointscoordinates.txt", "at+");
    pentagons = fopen("pentagons.txt", "at+");
     
    for (int PointID = 0; PointID < PointNumber; PointID++)
    {
        for (int PointCoordinate = 0; PointCoordinate < DN; PointCoordinate++)
        {
            fprintf(pointscoordinates,"%0.2lf\t",Points[PointID][PointCoordinate]);
        }
        fprintf(pointscoordinates, "\n");
    }

    for(int FigureID = 0; FigureID < NumberOfFigures; FigureID++)
    {
        fprintf(pentagons,"Smaller area - Figure no. %d\n",SmallerAreaFigureID);
        fprintf(pentagons,"Figure number %d\n",FigureID+1);
        for (int FigureVerticiesX = 0; FigureVerticiesX < PointNumber; FigureVerticiesX++)
        {
            for (int FigureVerticiesY = 0; FigureVerticiesY < DN; FigureVerticiesY++)
            {
                fprintf(pentagons,"%0.2lf\t",Figure[FigureVerticiesX][FigureVerticiesY]);
            }
            fprintf(pentagons, "\n");
        }
        fprintf(pentagons, "\n");
    }
    
    fclose(pointscoordinates);
    fclose(pentagons);    
}
