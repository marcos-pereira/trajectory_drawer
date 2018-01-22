# trajectory_drawer
This repository will contain an [in development] trajectory drawer interpolator. If desired you can ask to contribute to it.

# What is the Drawer?
The Drawer is a class used to generate and interpolate trajectory points based on the sample time specified. For example, it is possible to interpolate a trajectory from 0.0 to 0.1 with 300 points. The points between 0.0 and 0.1 will be interpolated with the sample time specified.

# How to test the Drawer
Clone the repository, use cmake to generate a makefile. Here it will generate a Unix Makefile, but cmake can also create projects and makefiles to IDEs (cmake -h).
```
git clone https://github.com/marcos-pereira/trajectory_drawer.git
cmake -G "Unix Makefiles" 
make
./Draw
```
Use the Drawer plotter to plot the generated trajectory
```
python DrawerPlotter2.py x_trajectory_file.txt y_trajectory_file.txt z_trajectory_file.txt 
```
The trajectory is plotted on the coordinate axes x, y and z and can be seen in the file x_trajectory_file.txt.pdf

# How to use the Drawer
1. Declare a Drawer2 object and a desired sample time
```
Drawer2 trajectory_drawer;
double sample_time = 0.020	// 20 ms 
```

2. Declare a vector of doubles which will store the interpolated trajectory
```
std::vector<double> vec_interpolated_trajectory;
```

3. Declare a vector to store the trajectory segments and a vector to store the trajectory number of points
```
std::vector<double> vec_desired_x;
std::vector<int> vec_x_number_points;
```

4. Add segments to the trajectory drawer and how many points the segment will have. In other words, how many points (300 in this case) will be interpolated from 0.0 to the desired point (0.1 in this case)
```
vec_desired_x.push_back(0.1); 
vec_x_number_points(300);
```

5. Generate the trajectory with the generation method. 
```
vec_interpolated_trajectory = trajectory_drawer.GenerateTrajectoryWithMultipleSegments(vec_desired_x, sample time, vec_x_number_points)
```
It is also possible to print the trajectory on a .txt file to be later read or plotted.
```
trajectory_drawer.PrintTrajectoryToFile(__FILE__,"","trajectory_file.txt");
```
