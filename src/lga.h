#ifndef LGA_CU
#define LGA_CU

#include <iostream>
#include <cuda_runtime.h>

// If there is a particle in the same node with the opposite direction.
__device__ bool isColliding(int *cells, int cell_index, int particle_dir){
   int opposite_dir = (particle_dir + 2)%4;
    if ((cells[cell_index + opposite_dir] >= 1) ){
            return true;
        }
    return false;
}


__device__ bool isBouncing(int *cells, int x, int y, int size_x, int size_y){
    // If is outside
    if(x >= size_x || x < 0){
        return true;
    }
    if(y >= size_y || y < 0){
        return true;
    }
    // If next position is obstacle
    int next_cell = (x + y*size_x)*4;
    if (cells[next_cell] == -1){
        return true;
    }
    return false;
}


__global__ void computeNextStep(int *nodes_in, int size_x, int size_y, int *out_grid){
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    if (index < size_x*size_y){
        int x = index % size_x;
        int y = index / size_x;
        if (nodes_in[index*4] != -1) { // If is not obstacle
            for (int dir = 0; dir < 4; dir++){
                if (nodes_in[index*4 + dir] == 1) { // If has particle
                    int next_dir = dir;
                    if ( isColliding(nodes_in, index*4, next_dir) ){ 
                        next_dir = (dir + 1) % 4; // Turn 90 degrees
                    }
                    // Streaming
                    int next_x = x;
                    int next_y = y;
                    switch (next_dir){
                        case 0:{ // right
                            next_x += 1;
                            break;
                        }
                        case 1:{ // up
                            next_y -= 1;
                            break;
                        }
                        case 2:{ // left
                            next_x -= 1;
                            break;
                        }
                        case 3:{ // down
                            next_y += 1;
                            break;
                        }
                    }
                    int next_cell = next_x + next_y*size_x;
                    if( isBouncing( nodes_in, next_x, next_y, size_x, size_y ) ){
                        next_dir = (dir + 2) % 4; // Turn 180 degrees
                        out_grid[index*4 + next_dir] = 1;
                    }else{
                        out_grid[next_cell*4 + next_dir] = 1;
                    }
                    
                }
            }
        }
    }
}

void nextStep(int *grid, int size_x, int size_y){
    // Copy input grid to device
    int *d_grid;
    cudaMalloc((void **)&d_grid, size_x * size_y * sizeof(int) * 4);
    cudaMemcpy(d_grid, grid, size_x * size_y * sizeof(int) * 4, cudaMemcpyHostToDevice);

    // Malloc output grid in device
    int *out_grid =  (int*) malloc( sizeof(int)*size_x*size_y*4 );
    for(int i = 0; i < size_x*size_y*4; i++){
        out_grid[i] = 0; 
        if(grid[i] == -1) out_grid[i] = -1; // Copy obstacles
    }

    int *d_out_grid;
    cudaMalloc((void **)&d_out_grid, size_x * size_y * sizeof(int) * 4);
    cudaMemcpy(d_out_grid, out_grid, size_x * size_y * sizeof(int) * 4, cudaMemcpyHostToDevice);
    free(out_grid);

    computeNextStep<<<400, 400>>>(d_grid, size_x, size_y, d_out_grid);

    cudaDeviceSynchronize();
    // Copy output grid to host
    free(grid);
    grid = (int *)malloc(size_x * size_y * sizeof(int) * 4);
    cudaMemcpy(grid, d_out_grid, size_x * size_y * sizeof(int) * 4, cudaMemcpyDeviceToHost);

    cudaFree(d_out_grid);
    cudaFree(d_grid);
}
#endif