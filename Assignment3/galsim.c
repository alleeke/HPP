#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include <string.h>
#include <math.h>

struct particle
{
    double x; // position x
    double y; // position y
    double m; // mass
    double vx; // velocity x
    double vy; // velocity y
    double brigthness; 
};
typedef struct particle particle_t;

void simulate(particle_t **, int N,int nsteps,double dt);
void simulate_with_graphics(particle_t **, int N,int nsteps,double dt,char **argv); 
void read_data(particle_t **galaxy, int N, const char *filename);
void save_results(particle_t *, int, int, const char*);

int main (int argc, char const *argv[]){

    // Trivial check for input data 
    if(argc != 6) {
        printf("ERROR: Incorrect input data. Call as follows \"%s N filename nsteps delta_t graphics\" \n",argv[0]);
        return -1; 
    }
    else printf("Correct number of input data\n");

    
     // Declare input data variables 
    int N, nsteps, graphics; // number of particles, number of timesteps, graphics on or off
    double delta_t; // timestep
    const char *filename; 
   

    // Read input data 
    N = atoi(argv[1]); 
    nsteps = atoi(argv[3]);
    graphics = atoi(argv[5]);
    delta_t = atof(argv[4]);
    filename = argv[2];

    printf("N = %d\n", N);
    printf("nsteps = %d\n", nsteps);
    printf("dt = %f\n", delta_t);
    printf("filename = %s\n", filename);
    printf("Done reading input data\n");

    
    particle_t *galaxy; 
    galaxy = (particle_t*)malloc(N*sizeof(particle_t)); 
 
    // Read input data from file 
    read_data(&galaxy,N,filename);

    // Simulate
    if(graphics)simulate_with_graphics(&galaxy, N,nsteps,delta_t,argv);
    else simulate(&galaxy, N,nsteps,delta_t); 

    // Save results and free pointer
    save_results(galaxy,N,nsteps,filename); 
    free(galaxy); 
    

    return 0; 
}

void simulate(particle_t ** galaxy, int N,int nsteps,double dt){
    printf("Starting simulation (%s)... ",__func__);
    double G = 100/N; // Gravity 
    double epsilon = 1e-3; 

    // Define and init 2D array to store forces (Fx, Fy) for each particle
    double F[N][2];  


    // Loop over timesteps
    for (int t = 0; t < nsteps; t++){ 

        // Outer Loop to compute forces on each particle 
        for (int i = 0; i < N; i++){ 
            particle_t *pi = &((*galaxy)[i]);
            double Fx = 0, Fy = 0;  
            double rx,ry,r,factor;

            // Inner Loop (part1) to compute forces on each particle 
            for (int j = 0; j < i; j++){
                particle_t *pj = &((*galaxy)[j]);
                rx = pi->x-pj->x; // Relative x distance 
                ry = pi->y-pj->y; // Relative y distance
                r = sqrt(rx*rx + ry*ry); // Magnitude of relative distance

                factor = pj->m/((r+epsilon)*(r+epsilon)*(r+epsilon));
                Fx += factor*rx;
                Fy += factor*ry; 
            }

            // Inner Loop (part2) to compute forces on each particle 
            for (int j = i+1; j < N; j++){
                particle_t *pj = &((*galaxy)[j]);
                rx = pi->x-pj->x; // Relative x distance 
                ry = pi->y-pj->y; // Relative y distance
                r = sqrt(rx*rx + ry*ry); // Magnitude of relative distance

                factor = pj->m/((r+epsilon)*(r+epsilon)*(r+epsilon));
                Fx += factor*rx;
                Fy += factor*ry; 
            }
            Fx *= -G*pi->m; 
            Fy *= -G*pi->m; 

            F[i][0] = Fx;
            F[i][1] = Fy; 
        }

        // Step each particle with Sympletic euler 
        for (int i = 0; i < N; i++)
        {
            particle_t *pi = &((*galaxy)[i]);
            double ax = F[i][0]/pi->m; // a=F/m
            double ay = F[i][1]/pi->m; // a=F/m

            pi->vx += ax*dt;  // u_n+1 = u_n + dt*a
            pi->vy += ay*dt;  

            pi->x += pi->vx*dt; // x_n+1 = x_n + dt*u_n+1
            pi->y += pi->vy*dt; 
        }
        

/*         // Step with Sympletic euler 
        double ax = Fx/pi->m; // a=F/m
        double ay = Fy/pi->m; // a=F/m

        pi->vx += ax*dt;  // u_n+1 = u_n + dt*a
        pi->vy += ay*dt;  

        pi->x += pi->vx*dt; // x_n+1 = x_n + dt*u_n+1
        pi->y += pi->vy*dt; */ 

    }

    printf("Completed simulation\n");
    
}

void simulate_with_graphics(particle_t ** galaxy, int N,int nsteps,double dt, char **argv){
    printf("Starting simulation (%s)...",__func__);
    double G = 100/N; // Gravity 
    double epsilon = 1e-3; 
    double F[N][2]; // Fx, Fy forces for each particle 

    const float circleRadius=0.01, circleColor=0;
    const int windowWidth=800;
    const float L=1, W=1;

    InitializeGraphics(argv[0],windowWidth,windowWidth);
    SetCAxes(0,1);

    printf("Hit q to quit.\n");

    for (int t = 0; t < nsteps; t++){ // Loop over timesteps
        ClearScreen();
        for (int i = 0; i < N; i++){ 
            particle_t *pi = &((*galaxy)[i]);
            double Fx = 0, Fy = 0;  
            double rx,ry,r,factor;

            for (int j = 0; j < i; j++){
                particle_t *pj = &((*galaxy)[j]);
                rx = pi->x-pj->x; // Relative x distance 
                ry = pi->y-pj->y; // Relative y distance
                r = sqrt(rx*rx + ry*ry); // Magnitude of relative distance

                factor = pj->m/((r+epsilon)*(r+epsilon)*(r+epsilon));
                Fx += factor*rx;
                Fy += factor*ry; 
            }

            for (int j = i+1; j < N; j++){
                particle_t *pj = &((*galaxy)[j]);
                rx = pi->x-pj->x; // Relative x distance 
                ry = pi->y-pj->y; // Relative y distance
                r = sqrt(rx*rx + ry*ry); // Magnitude of relative distance

                factor = pj->m/((r+epsilon)*(r+epsilon)*(r+epsilon));
                Fx += factor*rx;
                Fy += factor*ry; 
            }
            Fx *= -G*pi->m; 
            Fy *= -G*pi->m; 

            F[i][0] = Fx;
            F[i][1] = Fy; 

            
            
        }
        

        // Step each particle with Sympletic euler 
        for (int i = 0; i < N; i++)
        {

            particle_t *pi = &((*galaxy)[i]);
            
            double ax = F[i][0]/pi->m; // a=F/m
            double ay = F[i][1]/pi->m; // a=F/m

            pi->vx += ax*dt;  // u_n+1 = u_n + dt*a
            pi->vy += ay*dt;  

            pi->x += pi->vx*dt; // x_n+1 = x_n + dt*u_n+1
            pi->y += pi->vy*dt; 
 
            DrawCircle(pi->x,pi->y,L,W,circleRadius,circleColor);
        }
        
        Refresh();
        // Sleep a short while to avoid screen flickering. 
        usleep(3000);
    }
        
    FlushDisplay();
    CloseDisplay(); 
    
}

void save_results(particle_t * galaxy, int N, int nsteps, const char *filename){
    printf("Saving results (%s)...\n", __func__);
     
    char filepath[100]; 
    strcpy(filepath,"output_data/");
    strcat(filepath, filename); // Concatenate contents of b onto c
   
    FILE *myFile = fopen(filepath, "wb");

    if (myFile == NULL) {
        perror("Error opening file");
        return; // or handle the error in your preferred way
    }

    // Write data to the file
    for (int i = 0; i < N; i++)
    {
        particle_t p = galaxy[i]; 

        fwrite(&p.x, sizeof(double),1,myFile); 
        fwrite(&p.y, sizeof(double),1,myFile); 
        fwrite(&p.m, sizeof(double),1,myFile); 
        fwrite(&p.vx, sizeof(double),1,myFile); 
        fwrite(&p.vy, sizeof(double),1,myFile); 
        fwrite(&p.brigthness, sizeof(double),1,myFile); 
    
    }
    
    // Close the file
    fclose(myFile);

    printf("Data written to output file successfully!\n");

}

void read_data(particle_t **galaxy,int N,const char *filename){
    printf("Reading file (%s)...\n", __func__);

    // Read file
    char filepath[100];
    strcpy(filepath,"input_data/"); 
    strcat(filepath, filename); // Concatenate contents of b onto c
    printf("Done defining filepath: %s\n", filepath);

    FILE * myFile = fopen(filepath,"r"); // open file, r- read only option

    if (myFile == NULL) {
        perror("Error opening file");
        return; // or handle the error in your preferred way
    }
    for (int i = 0; i < N; i++)
    {   
        
    particle_t p; 
    fread(&p.x,sizeof(double),1,myFile); // x
    fread(&p.y,sizeof(double),1,myFile); // y
    fread(&p.m,sizeof(double),1,myFile); // mass
    fread(&p.vx,sizeof(double),1,myFile); // velocity x
    fread(&p.vy,sizeof(double),1,myFile); // velocity y
    fread(&p.brigthness,sizeof(double),1,myFile); // brigthness

    (*galaxy)[i] = p; // Add particle to array 
    } 

    printf("Done reading input file, closing file\n");
    fclose(myFile);
}
