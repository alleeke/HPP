#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include <string.h>
#include <math.h>
#include <pthread.h>

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

typedef struct {
    particle_t **galaxy;
    int N;
    int nsteps;
    double dt;
    int nthreads;
    double G;
    double epsilon;
    double (*F)[2];
    int thread_id;
} thread_data_t;

void simulate(particle_t **, int N,int nsteps,double dt);
void simulate_with_graphics(particle_t **, int N,int nsteps,double dt,char **argv); 
void read_data(particle_t **galaxy, int N, const char *filename);
void save_results(particle_t *, int, int, const char*);
void* thread_func(void *arg);

int nthreads = 1; 

int main (int argc, char const *argv[]){

    // Trivial check for input data 
    if(argc != 7) {
        printf("ERROR: Incorrect input data. Call as follows \"%s N filename nsteps delta_t graphics nthreads\" \n",argv[0]);
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
    nthreads = atoi(argv[6]);

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

void *thread_func(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    int start = (data->N / data->nthreads) * data->thread_id;
    int end = (data->N / data->nthreads) * (data->thread_id + 1);

    for (int i = start; i < end; i++) {
        particle_t *pi = &((*(data->galaxy))[i]);
        double Fx = 0, Fy = 0;  
        double rx,ry,r,factor;

        // Inner Loop (part1) to compute forces on each particle 
        for (int j = 0; j < i; j++){
            particle_t *pj = &((*(data->galaxy))[j]);
            rx = pi->x-pj->x; // Relative x distance 
            ry = pi->y-pj->y; // Relative y distance
            r = sqrt(rx*rx + ry*ry); // Magnitude of relative distance

            factor = pj->m/((r+data->epsilon)*(r+data->epsilon)*(r+data->epsilon));
            Fx += factor*rx;
            Fy += factor*ry; 
            }

        // Inner Loop (part2) to compute forces on each particle 
        for (int j = i+1; j < data->N; j++){
            particle_t *pj = &((*(data->galaxy))[j]);
            rx = pi->x-pj->x; // Relative x distance 
            ry = pi->y-pj->y; // Relative y distance
            r = sqrt(rx*rx + ry*ry); // Magnitude of relative distance

            factor = pj->m/((r+data->epsilon)*(r+data->epsilon)*(r+data->epsilon));
            Fx += factor*rx;
            Fy += factor*ry; 
        }
        Fx *= -data->G*pi->m; 
        Fy *= -data->G*pi->m; 

        (data->F)[i][0] = Fx;
        (data->F)[i][1] = Fy; 
    }

    return NULL;
}

void simulate(particle_t ** galaxy, int N,int nsteps,double dt){
    printf("Starting simulation (%s)... ",__func__);
    double G = 100/N; // Gravity 
    double epsilon = 1e-3; 

    pthread_t threads[nthreads];
    thread_data_t thread_data[nthreads];

    // Define and init 2D array to store forces (Fx, Fy) for each particle
    double F[N][2]; 

    // Loop over timesteps
    for (int t = 0; t < nsteps; t++){ 
        for (int i = 0; i < nthreads; i++) {
        thread_data[i].galaxy = galaxy;
        thread_data[i].N = N;
        thread_data[i].nsteps = nsteps;
        thread_data[i].dt = dt;
        thread_data[i].nthreads = nthreads;
        thread_data[i].G = G;
        thread_data[i].epsilon = epsilon;
        thread_data[i].F = malloc(N * sizeof(double[2])); // Allocate memory for forces
        thread_data[i].thread_id = i;
       
        pthread_create(&threads[i], NULL, thread_func, (void *)&thread_data[i]);
    }
    
        for (int i = 0; i < nthreads; i++) {
            pthread_join(threads[i], NULL);

        int start = (thread_data[i].N / thread_data[i].nthreads) * thread_data[i].thread_id;
        int end = (thread_data[i].N / thread_data[i].nthreads) * (thread_data[i].thread_id + 1);
            for (int k = start; k < end; k++)
            {
                F[k][0] = thread_data[i].F[k][0];
                F[k][1] = thread_data[i].F[k][1];
            } 
            free(thread_data[i].F); // Free memory allocated for forces
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
    }

    printf("Completed simulation\n");
    
}

void simulate_with_graphics(particle_t ** galaxy, int N,int nsteps,double dt, char **argv){
    printf("Starting simulation (%s)...",__func__);
    double G = 100/N; // Gravity 
    double epsilon = 1e-3; 
    double F[N][2];

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
     
    /* char filepath[100]; 
    strcpy(filepath,"output_data/");
    strcat(filepath, filename); // Concatenate contents of b onto c */

    char *filepath = "result.gal";
   
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
