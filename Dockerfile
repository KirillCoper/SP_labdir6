FROM ubuntu
COPY finder_syn.cpp ./
COPY TEXT ./
RUN apt-get update
RUN apt-get install -y apt-file
RUN apt-get install -y vim
RUN apt-get install -y build-essential
RUN apt-get install -y gdb
