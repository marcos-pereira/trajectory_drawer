#include "Drawer.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>    // std::remove_if, std::transform
#include <cctype>
#include <istream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <exception>
#include <locale>         // std::locale, std::isdigit

//----------------------------------------------------------------------------
Drawer2::Drawer2()
{
    i_trajectory_counter_ = 0;
}

//----------------------------------------------------------------------------
Drawer2::~Drawer2()
{
}

//----------------------------------------------------------------------------
std::vector<double> Drawer2::GenerateTrajectory(double d_xd, 
                                                double d_sample_time, 
                                                int i_num_points 
                                                )
{
    // Interpolate the trajectory from 0 to x desired

    i_trajectory_size_ = i_num_points;

    int i_step_counter = 0;

    double d_time_m = 0.0;    // Trajectory time increased until trajectory total time

    double d_xd_trajectory;                   // Interpolated trajectory value
    std::vector<double> vec_xd_trajectory;    // Interpolated trajectory vector which receives the interpolated values
    while(i_step_counter <= i_num_points)  // While the trajectory step counter has not reached the traj. number of points yet, get the next point
    {        
        // The trajectory point is calculated based on a fraction of the trajectory total time (sample_time*number_of_points)
        d_xd_trajectory = d_xd * (d_time_m / (d_sample_time * i_num_points));          
        d_time_m += d_sample_time;  // Increase the trajectory time
        i_step_counter++;           // Increase the trajectory step
        vec_xd_trajectory.push_back(d_xd_trajectory);
    }
    vecd_x_trajectory_ = vec_xd_trajectory;     // Store the trajectory on the Drawer2 object
    return(vec_xd_trajectory);
}

//----------------------------------------------------------------------------
std::vector<double> Drawer2::GenerateTrajectoryWithMultipleSegments(std::vector<double> d_xd, 
                                                                    double d_sample_time, 
                                                                    std::vector<int> i_num_points
                                                                    )
{

    // Interpolate the trajectory from 0 to x desired
    int i_step_counter = 0;    

    double d_time_m = 0.0;    // Trajectory time increased until trajectory total time

    double d_xd_trajectory;                   // Interpolated trajectory value
    std::vector<double> vec_xd_trajectory;    // Interpolated trajectory vector which receives the interpolated values

    double last_segment = 0.0;                // Store the last segment value, the next segment will start from the end of the last one
    
    // Iterate through the d_xd trajectory segments and interpolate trajectory value
    for(int ii = 0; ii < d_xd.size(); ii++)
    { 
      while(i_step_counter <= i_num_points[ii])     
      {
        // The trajectory point is calculated based on a fraction of the trajectory total time (sample_time*number_of_points)
        d_xd_trajectory = last_segment + d_xd[ii] * (d_time_m/(d_sample_time * i_num_points[ii]));
        vec_xd_trajectory.push_back(d_xd_trajectory);
        i_step_counter++;          // Increase the trajectory step
        d_time_m += d_sample_time; // Increase the trajectory time
      }
      last_segment = d_xd[ii];     // Store the last segment value, the next segment will start from this value
      i_step_counter = 0;          // Reset counter for the next segment
      d_time_m = 0;                // Reset time counter for the next segment
    } 
    vecd_multi_segment_trajectory_ = vec_xd_trajectory; // Store interpolated trajectory to get size as limit to increase counter
    return(vec_xd_trajectory);
}

//----------------------------------------------------------------------------
void Drawer2::PrintVector(std::vector<double> vec_vector)
{
    for(int ii=0; ii < vec_vector.size(); ii++)
    {
        std::cerr << "vec_vector[" << ii << "]" << " = " << vec_vector[ii] << std::endl;
    }
}

//----------------------------------------------------------------------------
void Drawer2::IncreaseTrajectoryCounter()
{ 
    // Instead of creating a counter in the program, increase a counter from the Drawer
    // Avoid needing to add more counters to the program itself    
    if(i_trajectory_counter_ <  vecd_x_trajectory_.size()-1)
    {
        i_trajectory_counter_++;
    }    
}

//----------------------------------------------------------------------------
void Drawer2::IncreaseMultiSegmentTrajectoryCounter()
{ 
    // Instead of creating a counter in the program, increase a counter from the Drawer
    // Avoid needing to add more counters to the program itself    
    if(i_trajectory_counter_ < vecd_multi_segment_trajectory_.size()-1)
    {
        i_trajectory_counter_++;
    }    
}

//----------------------------------------------------------------------------
int Drawer2::GetTrajectoryCounter()
{
    // This counter is used to deploy each interpolated trajectory point to the program
    return i_trajectory_counter_;
}

//----------------------------------------------------------------------------
void Drawer2::PrintTrajectoryToFile(std::string output_dir, std::string subfolders, std::string output_file_name)
{
  std::ofstream oftstream_vecd_x_trajectory;

  // Write path to trajectory file 
  std::size_t slash = output_dir.find_last_of("/");
  output_dir.erase(slash,output_dir.length());
  std::string trajectory_output_file_path;    
  std::string subfolders_path;
  // Check if the trajectory file is inside a subfolder
  if(!subfolders.empty())
  {
    subfolders_path = "/" + subfolders;
  }  
  trajectory_output_file_path = output_dir + subfolders_path + "/" + output_file_name;  

  oftstream_vecd_x_trajectory.open(trajectory_output_file_path.c_str(), std::ios::out);

  std::cerr << "\n\nPrinting current trajectory to file...\n";
  std::cerr << trajectory_output_file_path << std::endl;


  // // Check trajectory size
  // if(vecd_x_trajectory_.size()-1 != i_trajectory_size_)
  // {
  //   std::cerr << "\n\nThere is some error in the trajectory dimensions vector. \nThe vector dimension is different than the trajectory number of points." << std::endl;
  //   std::cerr << "Both must have the same number of points!\n";
  //   std::cerr << "Trajectory vector size = " << vecd_x_trajectory_.size();
  //   std::cerr << "Trajectory number of points = " <<  i_trajectory_size_ << std::endl;    
  //   throw std::exception();
  // }

  for(int ii = 0; ii < vecd_multi_segment_trajectory_.size(); ii++)
  {
    // Print to file as a vector N, where N is the number of trajectory points
    // E.g.:  
    // 0.1
    // 0.2 
    oftstream_vecd_x_trajectory << vecd_multi_segment_trajectory_[ii] << std::endl;
  }

  oftstream_vecd_x_trajectory.close();
}

//----------------------------------------------------------------------------
int Drawer2::GetTrajectorySize()
{
  return i_trajectory_size_;
}

//----------------------------------------------------------------------------
int Drawer2::GetAccumulatedTrajectorySize(std::vector<int> i_num_points)
{
  int trajectory_steps = std::accumulate(i_num_points.begin(), i_num_points.end(), 0.0);  
  return(trajectory_steps);
}