cppCompilerConfig = mex.getCompilerConfigurations('C++');
pathToCompilerDirectory = cppCompilerConfig.Location;

mex sfun_hmInitialize.cpp -lHapticAPI2