build/bin/unittests
lcov --directory  ./oss_sdk/CMakeFiles/osssdkcpp.dir   --capture --output-file app.info  -b oss_sdk/  --no-external
genhtml  -o  results  app.info