FROM ubuntu:18.04

RUN apt-get update
RUN apt-get install gcc make -y
RUN apt-get install tzdata -y
RUN apt-get install expect -y
RUN apt-get install chkrootkit -y

RUN groupadd -g 9999 user
RUN useradd -r -u 9999 -g user user
RUN useradd -r -u 8888 -g user user2
RUN useradd -r -u 7777 -g user attacker

RUN echo "d\nd" | passwd user
RUN echo "d\nd" | passwd user2
RUN echo "d\nd" | passwd attacker


COPY . /zap

WORKDIR /zap
RUN make
