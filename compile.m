cppCompilerConfig = mex.getCompilerConfigurations('C++');
pathToCompilerDirectory = cppCompilerConfig.Location;

mex sfun_hmInitialize.cpp -lHapticAPI2
mex sfun_positionControl.cpp -lHapticAPI2