запуск

$ docker image build -t task6 . 
$ docker run --net=host --env="DISPLAY" --volume="$HOME/.Xauthority:/root/.Xauthority:rw" task6

$ tmux
$ mosquitto -v -p 1880
$ mosquitto_sub -t test/tl -p 1880

$ cd ./project
$ cmake CMakeLists.txt
$ make
$ ./make

полезные комады
==================
$ cmake CMakeList.txt

$ make

=====
$gcc main.c -o mqtt_pub -lmosquitto
$mosquitto_sub -t  test/tl -p 1880
$mosquitto -v -p 1880



