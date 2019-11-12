# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        common_audio/ring_buffer.c
        common_audio/spl_sqrt_floor.c
        common_audio/delay_estimator.cc
        common_audio/delay_estimator_wrapper.cc
        common_audio/dot_product_with_scale.cc
        common_audio/real_fft.c
        common_audio/fft4g.c
        common_audio/complex_fft.c
        common_audio/complex_bit_reverse.c
        common_audio/vector_scaling_operations.c
        common_audio/energy.c
        common_audio/sqrt_of_one_minus_x_squared.c
        common_audio/division_operations.c
        common_audio/min_max_operations.c
        common_audio/spl_sqrt.c
        common_audio/resample_by_2.c
        common_audio/copy_set_operations.c
        common_audio/get_scaling_square.c
        common_audio/randomization_functions.c

        aecm/aecm_core.cc
        aecm/aecm_core_c.cc
        aecm/echo_control_mobile.cc

        ns/noise_suppression.c
        ns/noise_suppression_x.c
        ns/ns_core.c
        ns/nsx_core.c
        ns/nsx_core_c.c

        agc/analog_agc.c
        agc/digital_agc.c

        native-lib.cpp)

include_directories(aecm/)
include_directories(ns/)
include_directories(agc/)
include_directories(common_audio/)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})