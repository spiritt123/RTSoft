sudo xhost +local:root
sudo docker build -t new_firefox_docker .
sudo docker run -it --net=host --env="DISPLAY" new_firefox_docker
