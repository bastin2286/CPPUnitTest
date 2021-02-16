FROM ubuntu:groovy

RUN apt-get update && \
	apt-get install -y build-essential git cmake autoconf libtool pkg-config

#RUN apt-get install git

#RUN apt-get purge -y cmake

#RUN apt-get install wget

#RUN wget https://github.com/Kitware/CMake/releases/download/v3.15.2/cmake-3.15.2.tar.gz

##RUN tar -zxvf cmake-3.15.2.tar.gz

#RUN wget -qO- "https://cmake.org/files/v3.18/cmake-3.18.4-Linux-x86_64.tar.gz" | tar --strip-components=1 -xz -C /usr/local

#RUN pwd

#RUN apt-get install libstdc++6

RUN apt-get install -y default-jre

RUN apt-get install -y apt-utils

COPY eProsima_Fast-DDS-2.0.0-Linux.tgz .

RUN tar -xvf eProsima_Fast-DDS-2.0.0-Linux.tgz

RUN chmod 755 install.sh

RUN ./install.sh

COPY ApiTestCase.csv .

RUN cat ApiTestCase.csv

RUN strings /usr/lib/x86_64-linux-gnu/libstdc++.so.6 | grep GLIBC

#WORKDIR /src/UnitTesting/TestEnvironment/AUTRunner/

WORKDIR /src/UnitTesting/TestRunner/


#RUN sleep 100
#RUN ./Gtest_Exec ApiTestCase.csv

#CMD ["./AUT_Exec"]
CMD ["./Gtest_Exec","ApiTestCase.csv"]
