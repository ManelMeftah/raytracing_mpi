CC=mpic++
CFLAGS =-lm
DEPS = vec3.h util.h  camera.h color.h ray.h sphere.h surface.h surface_list.h 
OBJ = camera.o color.o ray.o sphere.o surface.o surface_list.o util.o vec3.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
raytracing_mpi: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
