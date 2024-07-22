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
- Visual Studio 2022
- vcpkg (for managing OpenCV dependency)

## Build Instructions
1. Clone this repository:
   ```
   git clone https://github.com/your-username/circleDetection.git
   ```

2. Open the cloned folder in Visual Studio 2022.

3. Ensure that your `CMakePresets.json` file is correctly configured. The file should already contain the necessary settings, including the `CMAKE_TOOLCHAIN_FILE` for vcpkg. Here's an example of what your `CMakePresets.json` might look like:

   ```json
   {
     "version": 3,
     "configurePresets": [
       {
         "name": "windows-base",
         "description": "Target Windows with the Visual Studio development environment.",
         "hidden": true,
         "generator": "Ninja",
         "binaryDir": "${sourceDir}/out/build/${presetName}",
         "installDir": "${sourceDir}/out/install/${presetName}",
         "cacheVariables": {
           "CMAKE_C_COMPILER": "cl.exe",
           "CMAKE_CXX_COMPILER": "cl.exe",
           "CMAKE_TOOLCHAIN_FILE": {
             "value": "C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake",
             "type": "FILEPATH"
           }
         },
         "condition": {
           "type": "equals",
           "lhs": "${hostSystemName}",
           "rhs": "Windows"
         }
       },
       {
         "name": "x64-debug",
         "displayName": "x64 Debug",
         "description": "Target Windows (64-bit) with the Visual Studio development environment. (Debug)",
         "inherits": "windows-base",
         "architecture": {
           "value": "x64",
           "strategy": "external"
         },
         "cacheVariables": { "CMAKE_BUILD_TYPE": "Debug" }
       },
       {
         "name": "x64-release",
         "displayName": "x64 Release",
         "description": "Target Windows (64-bit) with the Visual Studio development environment. (RelWithDebInfo)",
         "inherits": "windows-base",
         "architecture": {
           "value": "x64",
           "strategy": "external"
         },
         "cacheVariables": { "CMAKE_BUILD_TYPE": "Release" }
       }
     ]
   }
   ```

   Make sure the `CMAKE_TOOLCHAIN_FILE` path points to your vcpkg installation. If needed, adjust the path to match your system configuration.

4. In Visual Studio 2022, you can now select either the "x64-debug" or "x64-release" configuration from the configuration dropdown.

5. Build the project by clicking on "Build" in the Visual Studio menu.

6. Once built, you can run and debug the project directly from Visual Studio 2022.