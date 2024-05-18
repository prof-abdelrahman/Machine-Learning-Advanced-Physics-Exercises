// // Perform the simulation for lattice size L, probability p, and realization number realization
// void performSimulation(int L, double p, int realization) {
//   // Initialize the system
//   int N = L * L; // number of sites
//   int cluster_ID = 1; // ID of the cluster which is tested
//   int x_length = L; // length of system in x direction
//   int cluster[L][L]; // cluster array

//   // Generate the cluster array with occupied sites based on probability p
//   for (int i = 0; i < L; i++) {
//     for (int j = 0; j < L; j++) {
//       double random = (double)rand() / RAND_MAX; // generate a random number between 0 and 1
//       cluster[i][j] = (random < p) ? 1 : 0; // set the site as occupied if random < p, otherwise empty
//     }
//   }

//   // Call the percol_spanning function
//   int spanning = percol_spanning(N, (int *)cluster, cluster_ID, x_length);

//   // Print the result
//   printf("Lattice size: %d, Probability: %.2f, Realization: %d, Spanning: %d\n", L, p, realization, spanning);
// }

// // Perform simulations for different lattice sizes and probabilities
// void performSimulations() {
//   int num_realizations = 1000; // number of realizations of the disorder
//   double p; // probability value

//   // Perform simulations for different lattice sizes
//   for (int L = 12; L <= 48; L += 12) {
//     // Open file for writing
//     char filename[MAX_FILENAME_LENGTH];

//     // Write output to file
//     sprintf(filename, "max_%d.out", L);
//     FILE *output_file = fopen(filename, "w");

//     // Close the file
//     fclose(fptr);
//     sprintf(fptr, "max_%d.out", L);
//     // Perform simulations for different values of p
//     for (p = 0.55; p <= 0.63; p += 0.01) {
//       // Perform num_realizations realizations of the disorder
//       for (int realization = 1; realization <= num_realizations; realization++) {
//         // Perform the simulation for lattice size L, probability p, and realization number realization
//         performSimulation(L, p, realization);
//       }
//     }
//   }
// }



// // Open file for writing
  // char filename[MAX_FILENAME_LENGTH];
  // sprintf(filename, "%d.out", l[0]);
  // FILE *output_file = fopen(filename, "w");
  // if (output_file == NULL) {
  //       fprintf(stderr, "Error opening file.\n");
  //       return 1;
  //   }
  // fprintf(output_file, "%f %f %d \n", prob, mean, l[0]);

