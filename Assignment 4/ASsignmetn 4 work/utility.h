#ifndef UTIL_H
#define UTIL_H

typedef double (*FitnessFunction)(int, double*);

typedef struct {
    double lower_bound;
    double upper_bound;
} VariableBounds;

typedef struct {
    double *position;      // Current position
    double *velocity;      // Current velocity
    double *personal_best; // Best position found so far
    double fitness;        // Current fitness value
    double best_fitness;   // Personal best fitness value
} Particle;

double random_in_range(double min, double max);
void setup_particles(Particle *swarm, int num_particles, int dimensions,
                     VariableBounds *bounds, FitnessFunction fitness_func,
                     double *global_best_position, double *global_best_fitness);
void update_particles(Particle *swarm, int num_particles, int dimensions,
                      VariableBounds *bounds, FitnessFunction fitness_func,
                      double *global_best_position, double *global_best_fitness,
                      double inertia_weight, double cognitive_coeff, double social_coeff);
void free_particles(Particle *swarm, int num_particles);
double particle_swarm_optimize(FitnessFunction fitness_func, int dimensions, VariableBounds *bounds,
                                int num_particles, int max_iterations, double *best_position);

#endif
