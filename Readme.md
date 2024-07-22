# circleDetection

This project is an OpenCV-based circle detection program that identifies circles in images and performs related calculations and drawings.

## Features

- Detect all circles in an image
- Sort circles by radius
- Draw detected circles on the image
- Calculate distances between small circles and the largest circle
- Draw connections between circles
- Calculate and display the perimeter of the largest circle

## Dependencies

- C++20
- OpenCV
- CMake (version >= 3.8)

## Build Instructions

1. Ensure you have OpenCV and CMake installed on your system.

2. Clone this repository:
   ```
   git clone https://github.com/your-username/circleDetection.git
   cd circleDetection
   ```

3. Create and enter the build directory:
   ```
   mkdir build
   cd build
   ```

4. Run CMake and build:
   ```
   cmake ..
   cmake --build .
   ```

## Usage

1. Place your input image in the `Image` directory and update the `filename` variable in the code.

2. Run the compiled executable:
   ```
   ./detect-circle
   ```

3. The program will process the image and display the result. The processed image will be saved as `the_result.png`.

## File Structure

- `circleDetection.cpp`: Main program file
- `util.h` and `util.cpp`: Declaration and implementation of utility functions
- `CMakeLists.txt`: CMake configuration file
- `Image/`: Directory for input images

## Notes

- Ensure your OpenCV installation path is correctly set in your system environment variables.
- For MSVC compilers, the appropriate C++20 flag is already set in the CMakeLists.txt.

## License

[Add your license information here]