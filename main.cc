
#include "util.h"

#include "color.h"
#include "surface_list.h"
#include "sphere.h"
#include "camera.h"

#include <string>
#include <iostream>
#include <mpi.h>
#include <fstream>
// Include the string library
using namespace std;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~IMAGE :~~~~~~~~~~~~~~~~~~~~~~~~~~
    //Img properties : 16:9 400 x 255 
    const double ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = (int)(image_width / ratio);
    const int echantillonsParPixel = 100;// dans un pixel on a 100 couleurs

//purple gradient for bg
color couleurRayon(const ray& r, const surface& monde) {
    contacte_rec rec;
    if (monde.contacte(r, 0, infinity, rec))
    {
        return 0.5 * (rec.normale + color(1,1,1));
    }
    vec3 dir_unitaire = unit_vector(r.dir());
    // t entre [0, 1]
    double t = 0.5*(dir_unitaire.y() + 1.0);
    // interpolation: (1-t) * startVal + t*endVal 
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5,0.2,1.0);
}

//doesn't work bu concat with concat.cpp works, why ?
void concat(int nbFiles)
{
    fstream finput, foutput;
    
    
    for(int i=nbFiles; i>=0; i--)
    {
        foutput.open("header.ppm", ios::app);
        string nfile = "proc_"+to_string(i)+".ppm";
        finput.open(nfile, ios::in);
        string str1;
        while(getline(finput, str1))
        {
            foutput << str1;
            foutput << endl;
        }
        finput.close();
        foutput.close();
    }
    

}


void calcul(int finJ, int debJ, string fname, surface_list monde, camera cam){
    cout << "Writing in file " << fname << endl;
    // for (int j = finJ; j <= debJ; ++j)
    for (int j = finJ; j >= debJ; --j)
        {    
            for (int i = 0; i < image_width; ++i) 
            {
                color pixel_color(0,0,0);
                for(int k =0; k<echantillonsParPixel; k++)
                {
                    auto u = double(i) / (image_width-1);
                    auto v = double(j) / (image_height-1);
                    ray r = cam.getRay(u, v);
                    pixel_color += couleurRayon(r, monde);
                }
                write_color(fname, pixel_color, echantillonsParPixel);            
            }
        }
}

int main(int argc, char *argv []) 
{


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~MPI :~~~~~~~~~~~~~~~~~~~~~~~~~~
    int rank, numtasks, len, rc, elemParProc, index;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    
    // initialize MPI
    MPI_Init(&argc,&argv);

    // get number of tasks
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    // get my rank
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    // this one is obvious
    MPI_Get_processor_name(hostname,&len);
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~FILES :~~~~~~~~~~~~~~~~~~~~~~~~~~
    fstream f;
    
    string name = "proc_" + to_string(numtasks) + ".ppm";
    f.open(name, ios::out);
    f<< "P3\n" << image_width << " " << image_height <<"\n255\n"<<endl;
    f.close();


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~MONDE :~~~~~~~~~~~~~~~~~~~~~~~~~~
    surface_list monde;    monde.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    monde.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
    // monde.add(make_shared<sphere>(point3(0,0,-0.5), 0.2));

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~CAMERA :~~~~~~~~~~~~~~~~~~~~~~~~~~
    camera cam;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~RENDU :~~~~~~~~~~~~~~~~~~~~~~~~~~
    double startTime = MPI_Wtime();

    if(rank==0)
    {    
		//~ double start = MPI_Wtime();
        int i, restants;
        elemParProc = image_height / numtasks;
        
        if(numtasks>1)
        {
//             p1 recois tab[n/k] a tab[2*(n/k)], 
//             p2 recois tab[2*(n/k)] a tab[3*(n/k)] etc
            for(i=1; i<numtasks-1; i++)
            {
                index = elemParProc * i;
                MPI_Send(&elemParProc, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Send(&index,    1, MPI_INT, i,          0, MPI_COMM_WORLD);

            }
//             le dernier proc recois les derniers elements
            index = elemParProc * (numtasks-1);
            restants = image_height - index;
            MPI_Send(&restants, 1, MPI_INT, numtasks-1, 0, MPI_COMM_WORLD);
            MPI_Send(&index,    1, MPI_INT, numtasks-1,          0, MPI_COMM_WORLD);
        }
        
        int position;      
            //Proc 0 does stuff
        string fname = "proc_0.ppm";
        calcul(elemParProc, 0, fname, monde, cam);
        concat(numtasks);
        // double end = MPI_Wtime();
        // cout << "Process 0 took " << end - allStart << " seconds to run." << endl;
    }
    
    else if (rank != 0)
    {
		// double start = MPI_Wtime();
        MPI_Recv(&elemParProc, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&index,       1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        string fname = "proc_" + to_string(rank) + ".ppm";
        
        int debJ = (rank+1)*elemParProc;
        calcul(debJ, index, fname, monde, cam); 
        // double end = MPI_Wtime();
        // cout << "Process " << rank << " took " << end - start << " seconds to end." << endl; 
    }

    MPI::COMM_WORLD.Barrier();
    if (rank == 0) {
        cout << "Execution time: " << MPI_Wtime() - startTime << endl;
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}
    // ~ MPI_Barrier(MPI_COMM_WORLD);
    
   // done with MPI  
       //~ double allEnd = MPI_Wtime();
     //~ cout << "RayTracing took " << allEnd - allStart << " seconds to end." << endl; 

    // MPI_Finalize();
    



