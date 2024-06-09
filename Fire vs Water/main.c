/*-------------------------------------------
Program 1: fire vs water
Course: CS 211, Spring 2024, UIC
System: Advanced zyLab
Author: Manav Malik
------------------------------------------- */



// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and
// distribution of this work, including posting or sharing through any medium,
// is explicitly prohibited by law, and also violates UIC's Student
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3.
// Participation in Academically Dishonest Activities: Material Distribution).

// Given includes - DO NOT include anything else
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "project_utils.h"

// Prototypes for given functions (given as stubs)
void displayGrid(int rows, int cols,const int g[][cols]);
void spread(int ro, int co, int g[][co], int spreadWhat);
bool wall(int row ,int col,int x,int y){
   if (x < 0 || x>=row){
       return false;
   }



   if (y<0 || y>=col){
       return false;
   }
    
    return true;
};
void store(int rows, int cols,const int g[][cols],int g2[][2],int what){
    int l=0;
    for(int i =0;i<rows;i++){
        for(int j =0;j<cols;j++){
            
            if ( g[i][j] == what){
                g2[l][0]=i;
                g2[l][1]=j;
                l++;
            }
        };
    };
};


int coun(int rows,int cols,int grid[][cols],int what){
    int c=0;
    for(int i =0;i<rows;i++){
        for(int j =0;j<cols;j++){
            if (grid[i][j]==what){
                
                //printf("index x %d y %d\n",i,j );
                
                c++;
            }
        };
    };
    //printf("%d count %d \n",what,c);
    return c;
};



bool check(int x,int y,int num_change, int stor_change[num_change][2] ){
    
    for (int i=0;i<num_change+1;i++){
        if (stor_change[i][0]==x && stor_change[i][1]==y ){
            return false;
        }
    }
    return true;
};


int main(void)
{
    // set up random number generator based on project settings
    srand(RAND_SEED);

    // Acquire the simulation count from input
    int simCount = 0;
    
    // Acquire the simulation count from input
    scanf("%d", &simCount);
    
    // grid setup
    int rows = -1;
    int cols = -1;
    

    // initialize grid size based on input values
    scanf("%d %d", &rows, &cols);
    
    
    
    int grid[rows][cols];
    
    

    // TODO: Initialize the 2D grid
    for(int i =0;i<rows;i++){
        for(int j =0;j<cols;j++){
            scanf("%d", &grid[i][j]);
        };
    };
        
    // Output initial program details
    printf("Fire vs Water - %d Simulations!\n", simCount);

    
    
    //if (simCount==0) {   // output the initial grid
        displayGrid(rows, cols, grid);
        
        
        animate();
   // };


    
    
    
    
    
    

    for(int count=0; count!=simCount ; count++){
        
        int fire=3;
        int water =4;
         spread( rows,  cols,  grid,  fire);
         spread( rows,  cols,  grid,  water);
        
        
            
//            displayGrid(rows, cols, grid);
//
//            //pause for animation
//            animate();
        
        
        
        
        
        displayGrid(rows, cols, grid);
        
        // pause for animation
        animate();
        
        
    }
    
    
    printf("\nFire vs Water - Stats After %d Simulations!\n",simCount);
    printf("Total Cells: %d\n",rows*cols);
    printf("Cells Containing Nothing: %d\n",coun(rows, cols, grid, 0));
    printf("Cells Containing Grass: %d\n",coun(rows, cols, grid, 2));
    printf("Cells Containing Water: %d\n",coun(rows, cols, grid, 4));
    printf("Cells Containing Fire: %d\n",coun(rows, cols, grid, 3));
    
    return 0;
}












void displayGrid(int rows, int cols,const int grid[][cols])
{
     clearScreen();

    for(int i =0;i<rows;i++){
        for(int j =0;j<cols;j++){
            printCell(grid[i][j]);
        };
        printf("\n");
    };
    //printf("\n");

};

















void spread(int rows, int cols, int grid[][cols], int spreadWhat){
    if (spreadWhat ==3 ){

        int no_fire=0;
        no_fire = coun(rows, cols, grid, 3);
        
        int storage_fire[no_fire][2];
        
        
        
        
        int stor_fire[no_fire][2];
        
        for (int i=0;i<no_fire;i++){stor_fire[no_fire][0]=-1;stor_fire[no_fire][1]=-1 ;};
       // for (int i=0;i<no_fire;i++){printf("%d    %d\n",stor_fire[no_fire][0]=-1,stor_fire[no_fire][1]=-1 );};
        

        int num_fire=-1;
        
        
        
        
        
        store( rows,  cols, grid, storage_fire, 3);
        
        
        //for (int i=0;i<no_fire;i++){            printf("%d %d \n",storage_fire[i][0],storage_fire[i][1]);        };
        
        
        
        
        
        
        
        
        
        for (int g=0;g<no_fire;g++){
            
             //spread( storage_fire[g][1], storage_fire[g][0], grid , 3);
            
            int a = 0,b = 0,box1,box2,box3,box4;
            //bool rand_res=false;
            
            int direction =0;
            direction=(rand()%4);
            //printf ("%d\n",direction);
            if (direction==0){
                 a = -1;
                 b = 0;
            }else if (direction==1){
                 a = 1;
                 b = 0;
            }else if (direction==2){
                 a = 0;
                 b = 1;
            }else if (direction ==3){
                 a = 0;
                 b = -1;
            }else{printf("error");};
            
            
            if (spreadWhat==3){
                box1=2;
                box2=3;
                
                box3=4;
                box4=0;
            
            }

                    
            int x=storage_fire[g][0];
            int y=storage_fire[g][1];

            
            if (grid[ x +a ][  y  +b  ] == box1 && check(x+a, y+b,  num_fire, stor_fire ) && wall( rows , cols, x+a, y+b)){
                grid[x+a][y+b] = box2;
                num_fire++;
                 stor_fire[num_fire][0]=x +a;
                 stor_fire[num_fire][1]=y +b;
                
            
            }else if(grid[x+a][y+b] == box3 && check(x+a, y+b,  num_fire, stor_fire) && wall( rows , cols, x+a, y+b)){
                grid[x+a][y+b] = box4;
                num_fire++;
                 stor_fire[num_fire][0]=x +a;
                 stor_fire[num_fire][1]=y +b;
                
            }else if(grid[x-1][y] == box1 && check(x-1, y,  num_fire, stor_fire) && wall( rows , cols, x-1, y) ){
                grid[x-1][y] = box2;
                num_fire++;
                 stor_fire[num_fire][0]=x -1;
                 stor_fire[num_fire][1]=y ;
                
            }else if(grid[x-1][y] == box3 && check(x-1, y,  num_fire, stor_fire) && wall( rows , cols, x-1, y) ){
                grid[x-1][y] = box4;
                num_fire++;
                 stor_fire[num_fire][0]=x -1;
                 stor_fire[num_fire][1]=y ;
                
                
                
                
            }else if(grid[x+1][y] == box1 && check(x+1, y,  num_fire, stor_fire) && wall( rows , cols, x+1, y) ){
                grid[x+1][y] = box2;
                num_fire++;
                 stor_fire[num_fire][0]=x +1;
                 stor_fire[num_fire][1]=y ;
                
            }else if(grid[x+1][y] == box3 && check(x+1, y,  num_fire, stor_fire)  && wall( rows , cols, x+1, y) ){
                grid[x+1][y] = box4;
                num_fire++;
                 stor_fire[num_fire][0]=x +1;
                 stor_fire[num_fire][1]=y ;
                
                
                
                
                
            }else if(grid[x][y+1] == box1 && check(x, y+1,  num_fire, stor_fire)  && wall( rows , cols, x, y+1)  ){
                grid[x][y+1] = box2;
                num_fire++;
                 stor_fire[num_fire][0]=x ;
                 stor_fire[num_fire][1]=y +1;
                
            }else if(grid[x][y+1] == box3 && check(x, y+1,  num_fire, stor_fire) && wall( rows , cols, x, y+1) ){
                grid[x][y+1] = box4;
                num_fire++;
                 stor_fire[num_fire][0]=x ;
                 stor_fire[num_fire][1]=y +1;
                
                
                
                
                
            }else if(grid[x][y-1] == box1 && check(x, y-1,  num_fire, stor_fire) && wall( rows , cols, x, y-1) ){
                grid[x][y-1] = box2;
                num_fire++;
                 stor_fire[num_fire][0]=x ;
                 stor_fire[num_fire][1]=y -1;
                
            }else if(grid[x][y-1] == box3 && check(x, y-1,  num_fire, stor_fire) && wall( rows , cols, x, y-1) ){
                grid[x][y-1] = box4;
                num_fire++;
                 stor_fire[num_fire][0]=x ;
                 stor_fire[num_fire][1]=y -1;
                
            }
            

        }
    }else if(spreadWhat == 4) {
        int no_water=coun(rows, cols, grid, 4);
        
        int storage_water[no_water][2];
        
        
        int stor_water[no_water][2];
        for (int i=0;i<no_water;i++){stor_water[no_water][0]=rows;stor_water[no_water][1]=cols ;};
        
        
        int num_water=-1;
        
        
        store( rows,  cols, grid, storage_water, 4);
        
        
        //        for (int i=0;i<no_water;i++){            printf("%d %d \n",storage_water[i][0],storage_water[i][1]);        };
        
        
        for (int g=0;g<no_water;g++){
            
            //spread( storage_water[g][1], storage_water[g][0], grid , 4);
            
            int a = 0,b = 0,box1,box2,box3,box4;
            //bool rand_res=false;
            
            int direction =0;
            direction=(rand()%4);
            //printf ("%d\n",direction);
            if (direction==0){
                 a = -1;
                 b = 0;
            }else if (direction==1){
                 a = 1;
                 b = 0;
            }else if (direction==2){
                 a = 0;
                 b = 1;
            }else if (direction ==3){
                 a = 0;
                 b = -1;
            }else{printf("error");};
            
            
            
            box1=0;
            box2=4;
    
            box3=3;
            box4=0;
            
            
            int x=storage_water[g][0];
            int y=storage_water[g][1];
            
            if (grid[ x +a ][  y  +b  ] == box1 && check(x+a, y+b,  num_water, stor_water) && wall( rows , cols, x+a, y+b)){
                grid[x+a][y+b] = box2;
                num_water=num_water+1;
                stor_water[num_water][0]=x +a;
                stor_water[num_water][1]=y +b;
                
            
            }else if(grid[x+a][y+b] == box3 && check(x+a, y+b,  num_water, stor_water) && wall( rows , cols, x+a, y+b)){
                grid[x+a][y+b] = box4;
                num_water=num_water+1;
                stor_water[num_water][0]=x +a;
                stor_water[num_water][1]=y +b;
                
                
                
            }else if(grid[x-1][y] == box1 && check(x-1, y,  num_water, stor_water) && wall( rows , cols, x-1, y)){
                grid[x-1][y] = box2;
                num_water=num_water+1;
                stor_water[num_water][0]=x -1;
                stor_water[num_water][1]=y ;
                
            }else if(grid[x-1][y] == box3 && check(x-1, y,  num_water, stor_water) && wall( rows , cols, x-1, y) ){
                grid[x-1][y] = box4;
                num_water=num_water+1;
                stor_water[num_water][0]=x -1;
                stor_water[num_water][1]=y ;
                
                
                
                
                
            }else if(grid[x+1][y] == box1 && check(x+1, y,  num_water, stor_water) && wall( rows , cols, x+1, y) ){
                grid[x+1][y] = box2;
                num_water=num_water+1;
                stor_water[num_water][0]=x +1;
                stor_water[num_water][1]=y ;
                
            }else if(grid[x+1][y] == box3 && check(x+1, y,  num_water, stor_water) && wall( rows , cols, x+1, y) ){
                grid[x+1][y] = box4;
                num_water=num_water+1;
                stor_water[num_water][0]=x +1;
                stor_water[num_water][1]=y ;
                
                
                
                
            }else if(grid[x][y+1] == box1 && check(x, y+1,  num_water, stor_water) && wall( rows , cols, x, y+1) ){
                grid[x][y+1] = box2;
                num_water=num_water+1;
                stor_water[num_water][0]=x ;
                stor_water[num_water][1]=y +1;
                
            }else if(grid[x][y+1] == box3 && check(x, y+1,  num_water, stor_water) && wall( rows , cols, x, y+1) ){
                grid[x][y+1] = box4;
                num_water=num_water+1;
                stor_water[num_water][0]=x ;
                stor_water[num_water][1]=y +1;
                
                
                
            }else if(grid[x][y-1] == box1 && check(x, y-1,  num_water, stor_water) && wall( rows , cols, x, y-1) ){
                grid[x][y-1] = box2;
                num_water=num_water+1;
                stor_water[num_water][0]=x ;
                stor_water[num_water][1]=y -1;
                
                
            }else if(grid[x][y-1] == box3 && check(x, y-1,  num_water, stor_water)  && wall( rows , cols, x, y-1) ){
                grid[x][y-1] = box4;
                num_water=num_water+1;
                stor_water[num_water][0]=x ;
                stor_water[num_water][1]=y -1;
                
                
            }
        }
    }
    
};
