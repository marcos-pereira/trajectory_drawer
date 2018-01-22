//C++ libs
#include<cmath>
#include<signal.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>    // std::remove_if, std::transform
#include <cctype>
#include <istream>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <numeric> // std::accumulate

//Eigen
#include <Eigen/Dense>


// using namespace DQ_robotics;
using namespace Eigen;


class Drawer2
{

    public:        

        enum trajectory_type_t {zero_traj_type_t, LINEAR_t, CIRCULAR_t};
        
        Drawer2();        
        ~Drawer2();

        std::vector<double> GenerateTrajectoryWithMultipleSegments(std::vector<double> d_xd,      // Desired trajectory point
                                                                   double d_sample_time,          // Sample time of control loop
                                                                   std::vector<int> i_num_points // Number of points of desired trajectory
                                                                   );


        void PrintVector(std::vector<double> vec_vector);   // Print the chosen vector parameter

        int GetTrajectoryCounter();                         // Get the actual trajectory counter

        void IncreaseMultiSegmentTrajectoryCounter();        // Increase trajectory counter of trajectory with multiple segments

        void PrintTrajectoryToFile(std::string output_dir = __FILE__,                   // Print trajectory to file as a vector of doubles
                                   std::string subfolders = "", 
                                   std::string output_file_name = "trajectory_file.txt");

        int GetAccumulatedTrajectorySize(std::vector<int> i_num_points); // Get the trajectory size with all the segments points
    private:
        std::vector<double> vecd_x_trajectory_; // Interpolated trajectory for single point
        int i_trajectory_counter_;              // Trajectory counter used to access each trajectory point
        int i_trajectory_size_;                 // Size of single segment trajectory
        std::vector<double> vecd_multi_segment_trajectory_;   // Interpolated trajectory for multiple points

};