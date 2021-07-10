FROM ubuntu:18.04
RUN apt update
RUN apt install python3-opencv -y && apt-get install -y wget

RUN apt install -y build-essential cmake git pkg-config libgtk-3-dev \
    libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev \
    gfortran openexr libatlas-base-dev python3-dev python3-numpy \
    libtbb2 libtbb-dev libdc1394-22-dev

#RUN apt-get install -y default-jre openjdk-11-jre-headless openjdk-13-jre-headless openjdk-14-jre-headless openjdk-8-jre-headless 
RUN apt-get install -y default-jre

RUN apt install -y curl
RUN echo "1\n 1\n \n\n\n\n\n y\n" | adduser kafka \
    && adduser kafka sudo \
    && su -l kafka\
    && mkdir ~/Downloads\
    && curl "https://downloads.apache.org/kafka/2.6.2/kafka_2.13-2.6.2.tgz" -o ~/Downloads/kafka.tgz\
    && mkdir ~/kafka && cd ~/kafka\
    && tar -xvzf ~/Downloads/kafka.tgz --strip 1\
    && echo "delete.topic.enable = true \n log.dirs=/home/kafka/logs" >> ~/kafka/config/server.properties
RUN echo "[Unit] \n Requires=network.target remote-fs.target \n After=network.target remote-fs.target\ \n [Service] \n Type=simple \n User=kafka \n ExecStart=/home/kafka/kafka/bin/zookeeper-server-start.sh /home/kafka/kafka/config/zookeeper.properties \nExecStop=/home/kafka/kafka/bin/zookeeper-server-stop.sh \nRestart=on-abnormal \n[Install] \nWantedBy=multi-user.target" >> /etc/systemd/system/zookeeper.service\
    && echo "[Unit] \n Requires=zookeeper.service \n After=zookeeper.service \n \n [Service] \n Type=simple \n User=kafka \nExecStart=/bin/sh -c '/home/kafka/kafka/bin/kafka-server-start.sh /home/kafka/kafka/config/server.properties > /home/kafka/kafka/kafka.log 2>&1' \nExecStop=/home/kafka/kafka/bin/kafka-server-stop.sh \nRestart=on-abnormal \n\n[Install] \nWantedBy=multi-user.target" >> /etc/systemd/system/kafka.service
#    && systemctl start kafka

CMD bash

