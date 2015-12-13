build/bin/unittests
lcov --directory  ./oss_sdk_cpp/CMakeFiles/osssdkcpp.dir   --capture --output-file app.info  -b oss_sdk_cpp/  --no-external
genhtml  -o  results  app.info
