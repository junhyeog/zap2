FROM ubuntu:18.04

RUN apt-get update
RUN apt-get install gcc make chkrootkit expect tzdata -y
RUN groupadd -g 9999 u1
RUN useradd -r -u 9999 -g u1 u1
RUN useradd -r -u 8888 -g u1 u2
RUN useradd -r -u 7777 -g u1 a
RUN echo "1234\n1234" | passwd u1
RUN echo "1234\n1234" | passwd u2
RUN echo "1234\n1234" | passwd a


COPY . /zap
WORKDIR /zap
RUN make
