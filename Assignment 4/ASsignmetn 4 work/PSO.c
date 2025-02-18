#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdio.h>
#include "utility.h"

// Generate a random value within a range
double random_in_range(double min, double max) {
    return min + (max - min) * ((double)rand() / RAND_MAX);
}

// Initialize the particle swarm with random positions and velocities
void setup_particles(Particle *swarm, int num_particles, int dimensions,
                     VariableBounds *bounds, FitnessFunction fitness_func,
                     double *global_best_position, double *global_best_fitness) {
    int i = 0; // Using while loop for initialization
    while (i < num_particles) {
        swarm[i].position = malloc(dimensions * sizeof(double));
        swarm[i].velocity = malloc(dimensions * sizeof(double));
        swarm[i].personal_best = malloc(dimensions * sizeof(double));
        swarm[i].best_fitness = DBL_MAX;

        for (int j = 0; j < dimensions; j++) {
            swarm[i].position[j] = random_in_range(bounds[j].lower_bound, bounds[j].upper_bound);
            swarm[i].velocity[j] = random_in_range(-1.0, 1.0);
            swarm[i].personal_best[j] = swarm[i].position[j];
        }

        swarm[i].fitness = fitness_func(dimensions, swarm[i].position);

        if (swarm[i].fitness < *global_best_fitness) {
            *global_best_fitness = swarm[i].fitness;
            for (int j = 0; j < dimensions; j++) {
                global_best_position[j] = swarm[i].position[j];
            }
        }

        i++; // Increment in while loop
    }
}

// Update the velocities and positions of the particles
void update_particles(Particle *swarm, int num_particles, int dimensions,
                      VariableBounds *bounds, FitnessFunction fitness_func,
                      double *global_best_position, double *global_best_fitness,
                      double inertia_weight, double cognitive_coeff, double social_coeff) {
    for (int i = 0; i < num_particles; i++) {
        for (int j = 0; j < dimensions; j++) {
            double rand_cognitive = random_in_range(0.0, 1.0);
            double rand_social = random_in_range(0.0, 1.0);

            swarm[i].velocity[j] = inertia_weight * swarm[i].velocity[j]
                + cognitive_coeff * rand_cognitive * (swarm[i].personal_best[j] - swarm[i].position[j])
                + social_coeff * rand_social * (global_best_position[j] - swarm[i].position[j]);

            // Clamp velocity to a maximum limit
            double max_velocity = (bounds[j].upper_bound - bounds[j].lower_bound) * 0.2;
            if (swarm[i].velocity[j] > max_velocity) swarm[i].velocity[j] = max_velocity;
            if (swarm[i].velocity[j] < -max_velocity) swarm[i].velocity[j] = -max_velocity;

            // Update position
            swarm[i].position[j] += swarm[i].velocity[j];

            // Handle boundaries with reflection
            if (swarm[i].position[j] < bounds[j].lower_bound) {
                swarm[i].position[j] = bounds[j].lower_bound + (bounds[j].lower_bound - swarm[i].position[j]);
                swarm[i].velocity[j] *= -1;
            }
            if (swarm[i].position[j] > bounds[j].upper_bound) {
                swarm[i].position[j] = bounds[j].upper_bound - (swarm[i].position[j] - bounds[j].upper_bound);
                swarm[i].velocity[j] *= -1;
            }
        }

        // Update fitness
        swarm[i].fitness = fitness_func(dimensions, swarm[i].position);

        // Update personal best
        if (swarm[i].fitness < swarm[i].best_fitness) {
            swarm[i].best_fitness = swarm[i].fitness;
            for (int j = 0; j < dimensions; j++) {
                swarm[i].personal_best[j] = swarm[i].position[j];
            }
        }

        // Update global best
        if (swarm[i].fitness < *global_best_fitness) {
            *global_best_fitness = swarm[i].fitness;
            for (int j = 0; j < dimensions; j++) {
                global_best_position[j] = swarm[i].position[j];
            }
        }
    }
}

// Free dynamically allocated memory for the swarm
void free_particles(Particle *swarm, int num_particles) {
    for (int i = 0; i < num_particles; i++) {
        free(swarm[i].position);
        free(swarm[i].velocity);
        free(swarm[i].personal_best);
    }
}

// Perform Particle Swarm Optimization
double particle_swarm_optimize(FitnessFunction fitness_func, int dimensions, VariableBounds *bounds,
                                int num_particles, int max_iterations, double *best_position) {
    Particle *swarm = malloc(num_particles * sizeof(Particle));
    double global_best_fitness = DBL_MAX;
    double *global_best_position = malloc(dimensions * sizeof(double));

    setup_particles(swarm, num_particles, dimensions, bounds, fitness_func,
                    global_best_position, &global_best_fitness);

    double inertia = 0.7, cognitive = 1.5, social = 1.5;
    int patience = 50, no_improvement = 0, iteration = 0;

    while (iteration < max_iterations) {
        update_particles(swarm, num_particles, dimensions, bounds, fitness_func,
                         global_best_position, &global_best_fitness, inertia, cognitive, social);

        if (global_best_fitness < 1e-13) {
            no_improvement++;
            if (no_improvement >= patience) break;
        } else {
            no_improvement = 0;
        }
        iteration++;
    }

    for (int i = 0; i < dimensions; i++) {
        best_position[i] = global_best_position[i];
    }

    free_particles(swarm, num_particles);
    free(swarm);
    free(global_best_position);

    return global_best_fitness;
}
