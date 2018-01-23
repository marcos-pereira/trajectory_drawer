#include <stdio.h>
#include <cmath>    // For M_PI constant
#include "Drawer.h"

int main(int argc, char **argv)
{
	Drawer2 drawer2;

	////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // --- Drawer2 ---
    Drawer2 x_trajectory_drawer2;               // Trajectory interpolator for x-axis
    Drawer2 y_trajectory_drawer2;               // Trajectory interpolator for y-axis
    Drawer2 z_trajectory_drawer2;               // Trajectory interpolator for z-axis
    std::vector<double> vec_x_interpolated_trajectory;   // x-axis interpolated trajectory
    std::vector<double> vec_y_interpolated_trajectory;   // y-axis interpolated trajectory
    std::vector<double> vec_z_interpolated_trajectory;   // z-axis interpolated trajectory
    
    double sample_time = 0.020; // trajectory sample time [s]

	// Trajectory segments
    std::vector<double> vec_desired_x;  // Store multi segment trajectory x-axis
    std::vector<double> vec_desired_y;  // Store multi segment trajectory y-axis
    std::vector<double> vec_desired_z;  // Store multi segment trajectory z-axis

    std::vector<int> vec_x_number_points;   // Store number of points of segment
    std::vector<int> vec_y_number_points;   // Store number of points of segment
    std::vector<int> vec_z_number_points;   // Store number of points of segment    

    std::vector<std::string> vecstr_x_trajectory_type;      // Trajectory type: LINEAR, SIN, COS
    std::vector<std::string> vecstr_y_trajectory_type;      // Trajectory type: LINEAR, SIN, COS
    std::vector<std::string> vecstr_z_trajectory_type;      // Trajectory type: LINEAR, SIN, COS

    std::vector<double> vecd_circular_radius_x;  // circular radius for circular segment (can be SIN or COS)
    std::vector<double> vecd_circular_radius_y;  // circular radius for circular segment (can be SIN or COS)
    std::vector<double> vecd_circular_radius_z;  // circular radius for circular segment (can be SIN or COS)

    
    // Add segment to trajectory drawer    
    vec_desired_x.push_back(0.1);
    vec_desired_y.push_back(0.1);
    vec_desired_z.push_back(0.1);
    vec_x_number_points.push_back(300);
    vec_y_number_points.push_back(300);
    vec_z_number_points.push_back(300);
    vecstr_x_trajectory_type.push_back("LINEAR");
    vecstr_y_trajectory_type.push_back("LINEAR");
    vecstr_z_trajectory_type.push_back("LINEAR");
    vecd_circular_radius_x.push_back(0.0);
    vecd_circular_radius_y.push_back(0.0);
    vecd_circular_radius_z.push_back(0.0);

    // Add segment to trajectory drawer
    vec_desired_x.push_back(0.1);
    vec_desired_y.push_back(-0.2);
    vec_desired_z.push_back(-0.1);
    vec_x_number_points.push_back(300);
    vec_y_number_points.push_back(300);
    vec_z_number_points.push_back(300);
    vecstr_x_trajectory_type.push_back("LINEAR");
    vecstr_y_trajectory_type.push_back("LINEAR");
    vecstr_z_trajectory_type.push_back("LINEAR");
    vecd_circular_radius_x.push_back(0.0);
    vecd_circular_radius_y.push_back(0.0);
    vecd_circular_radius_z.push_back(0.0);

    // Add segment to trajectory drawer
    vec_desired_x.push_back(2*M_PI);
    vec_desired_y.push_back(2*M_PI);
    vec_desired_z.push_back(0.0);
    vec_x_number_points.push_back(300);
    vec_y_number_points.push_back(300);
    vec_z_number_points.push_back(300);
    vecstr_x_trajectory_type.push_back("SIN");
    vecstr_y_trajectory_type.push_back("COS");
    vecstr_z_trajectory_type.push_back("LINEAR");
    vecd_circular_radius_x.push_back(0.1);
    vecd_circular_radius_y.push_back(0.1);
    vecd_circular_radius_z.push_back(0.0);

    // Add segment to trajectory drawer
    vec_desired_x.push_back(-0.1);
    vec_desired_y.push_back(0.0);
    vec_desired_z.push_back(-0.1);
    vec_x_number_points.push_back(300);
    vec_y_number_points.push_back(300);
    vec_z_number_points.push_back(300);
    vecstr_x_trajectory_type.push_back("LINEAR");
    vecstr_y_trajectory_type.push_back("LINEAR");
    vecstr_z_trajectory_type.push_back("LINEAR");
    vecd_circular_radius_x.push_back(0.0);
    vecd_circular_radius_y.push_back(0.0);
    vecd_circular_radius_z.push_back(0.0);

    // Interpolate trajectory with multiple segments and print trajectory to .txt file    
    vec_x_interpolated_trajectory = x_trajectory_drawer2.GenerateTrajectoryWithMultipleSegments(vec_desired_x, 
                                                                                                sample_time, 
                                                                                                vec_x_number_points,
                                                                                                vecstr_x_trajectory_type,
                                                                                                vecd_circular_radius_x);
    x_trajectory_drawer2.PrintTrajectoryToFile(__FILE__,"","x_trajectory_file.txt");    // Print trajectory to file to debug it with python or matlab    

    vec_y_interpolated_trajectory = y_trajectory_drawer2.GenerateTrajectoryWithMultipleSegments(vec_desired_y, 
                                                                                                sample_time, 
                                                                                                vec_y_number_points,
                                                                                                vecstr_y_trajectory_type,
                                                                                                vecd_circular_radius_y);
    y_trajectory_drawer2.PrintTrajectoryToFile(__FILE__,"","y_trajectory_file.txt");    // Print trajectory to file to debug it with python or matlab    

    vec_z_interpolated_trajectory = z_trajectory_drawer2.GenerateTrajectoryWithMultipleSegments(vec_desired_z, 
                                                                                                sample_time, 
                                                                                                vec_z_number_points,
                                                                                                vecstr_z_trajectory_type,
                                                                                                vecd_circular_radius_z);
    z_trajectory_drawer2.PrintTrajectoryToFile(__FILE__,"","z_trajectory_file.txt");    // Print trajectory to file to debug it with python or matlab
    
    std::cout << "x-trajectory size = " << x_trajectory_drawer2.GetAccumulatedTrajectorySize(vec_x_number_points) << std::endl;
    std::cout << "y-trajectory size = " << y_trajectory_drawer2.GetAccumulatedTrajectorySize(vec_y_number_points) << std::endl;
    std::cout << "z-trajectory size = " << z_trajectory_drawer2.GetAccumulatedTrajectorySize(vec_z_number_points) << std::endl;

    while(x_trajectory_drawer2.GetTrajectoryCounter() < x_trajectory_drawer2.GetAccumulatedTrajectorySize(vec_x_number_points))
    {
    	// Increase trajectory counter to get trajectory point of trajectory vector                
        x_trajectory_drawer2.IncreaseMultiSegmentTrajectoryCounter();
        y_trajectory_drawer2.IncreaseMultiSegmentTrajectoryCounter();
        z_trajectory_drawer2.IncreaseMultiSegmentTrajectoryCounter();

        //-----------------------------------------------------------------------------------------
	    // Uncomment this to debug the interpolated trajectory
	    //-----------------------------------------------------------------------------------------   
	    // Print the actual x, y and z trajectory points to check which points are being sent to pose controller
	    // std::cerr << "vec_x[" << x_trajectory_drawer2.GetTrajectoryCounter() << "] = " << vec_x_interpolated_trajectory[x_trajectory_drawer2.GetTrajectoryCounter()] << std::endl;
	    // std::cerr << "vec_y[" << y_trajectory_drawer2.GetTrajectoryCounter() << "] = " << vec_y_interpolated_trajectory[y_trajectory_drawer2.GetTrajectoryCounter()] << std::endl;
	    // std::cerr << "vec_z[" << z_trajectory_drawer2.GetTrajectoryCounter() << "] = " << vec_z_interpolated_trajectory[z_trajectory_drawer2.GetTrajectoryCounter()] << std::endl;
 
    }


	return 0;
}