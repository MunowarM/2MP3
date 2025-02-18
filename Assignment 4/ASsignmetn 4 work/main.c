#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "OF_lib.h" // Include for objective function prototypes

int main(int argc, char **argv) {
    // Validate the number of command-line arguments
    if (argc != 7) {
        fprintf(stderr, "Usage: %s <ObjectiveFunction> <Dimensions> <LowerBound> <UpperBound> <ParticleCount> <MaxIterations>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Parse the command-line arguments
    char *function_name = argv[1];
    int dimensions = atoi(argv[2]);       // Dimensionality of the problem
    double lower_bound = atof(argv[3]);   // Lower limit for variables
    double upper_bound = atof(argv[4]);   // Upper limit for variables
    int particle_count = atoi(argv[5]);   // Number of particles
    int max_iterations = atoi(argv[6]);  // Maximum number of iterations

    // Map the function name to the corresponding objective function
    FitnessFunction selected_function = NULL;
    if (strcmp(function_name, "griewank") == 0) {
        selected_function = griewank;
    } else if (strcmp(function_name, "levy") == 0) {
        selected_function = levy;
    } else if (strcmp(function_name, "rastrigin") == 0) {
        selected_function = rastrigin;
    } else if (strcmp(function_name, "rosenbrock") == 0) {
        selected_function = rosenbrock;
    } else if (strcmp(function_name, "schwefel") == 0) {
        selected_function = schwefel;
    } else if (strcmp(function_name, "dixon_price") == 0) {
        selected_function = dixon_price;
    } else if (strcmp(function_name, "michalewicz") == 0) {
        selected_function = michalewicz;
    } else if (strcmp(function_name, "styblinski_tang") == 0) {
        selected_function = styblinski_tang;
    } else {
        fprintf(stderr, "Error: Unrecognized function '%s'\n", function_name);
        return EXIT_FAILURE;
    }

    // Print the parsed inputs
    printf("Selected Function: %s\n", function_name);
    printf("Dimensions: %d\n", dimensions);
    printf("Bounds: [%lf, %lf]\n", lower_bound, upper_bound);
    printf("Particles: %d\n", particle_count);
    printf("Max Iterations: %d\n", max_iterations);

    // Allocate memory for the bounds
    VariableBounds *bounds = malloc(dimensions * sizeof(VariableBounds));
    if (!bounds) {
        fprintf(stderr, "Error: Failed to allocate memory for bounds.\n");
        return EXIT_FAILURE;
    }

    // Initialize bounds
    for (int i = 0; i < dimensions; i++) {
        bounds[i].lower_bound = lower_bound;
        bounds[i].upper_bound = upper_bound;
    }

    // Allocate memory for the best solution
    double *best_solution = malloc(dimensions * sizeof(double));
    if (!best_solution) {
        fprintf(stderr, "Error: Failed to allocate memory for the best solution.\n");
        free(bounds);
        return EXIT_FAILURE;
    }

    // Perform the optimization
    printf("Starting optimization...\n");
    double best_fitness = particle_swarm_optimize(
        selected_function, dimensions, bounds, particle_count, max_iterations, best_solution
    );

    // Print the results
    printf("Optimal Fitness: %lf\n", best_fitness);
    printf("Optimal Position: ");
    for (int i = 0; i < dimensions; i++) {
        printf("%lf ", best_solution[i]);
    }
    printf("\n");

    // Clean up
    free(bounds);
    free(best_solution);

    return EXIT_SUCCESS;
}
