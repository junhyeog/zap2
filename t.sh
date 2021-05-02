docker rm -f `docker ps | grep zap | awk '{ print $1 }'` 2>/dev/null
docker rmi -f zap 2>/dev/null
docker build . -t zap -f ./Dockerfile 1>/dev/null
docker run --cap-add=SYS_TIME -dit zap
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` expect /zap/t.exp 1>/dev/null
echo "------------------------------------------------------------"
echo "[ last before ]"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` last
echo "[ lastlog before ]"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` lastlog
echo "------------------------------------------------------------"
echo "[ run ./zap $@ ]"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` ./zap $@
echo "------------------------------------------------------------"
echo "[ last after ]"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` last
echo "[ lastlog after ]"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` lastlog
echo "------------------------------------------------------------"
echo "[ chkwtmp ]"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` chkwtmp
echo "[ chklastlog ]"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` chklastlog
# docker exec -i `docker ps | grep zap | awk '{ print $1 }'` /bin/sh
