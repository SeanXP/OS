set JARDIR1=..\jars
set JARDIR2=.
set CLASSPATH=.;%JARDIR1%\Ring.jar;%JARDIR1%\Jeli.jar;%JARDIR2%\Ring.jar;%JARDIR2%\Jeli.jar
echo %CLASSPATH%
java -mx64m RingDriver
