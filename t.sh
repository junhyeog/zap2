docker rm -f `docker ps | grep zap | awk '{ print $1 }'` 2> /dev/null 1> /dev/null
docker rmi -f zap 2> /dev/null 1> /dev/null
docker build . -t zap -f ./Dockerfile 1> /dev/null
docker run --cap-add=SYS_TIME -dit zap
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` expect /zap/t.exp 1> /dev/null

echo "+--------- check utmp before run zap -----------+"
echo "[+] Run: w"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` w
echo ""
echo "[+] Run: who -all"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` who -all
echo ""

echo "+---------- check wtmp before run zap ----------+"
echo "[+] Run: last"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` last
echo ""

echo "+---------- check lastlog before run zap ----------+"
echo "[+] Run: lastlog"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` lastlog
echo ""

echo "+---------- run zap $@ ----------+"
echo "[+] Run: ./zap $@"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` ./zap $@
echo ""

echo "+--------- check utmp after run zap -----------+"
echo "[+] Run: w"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` w
echo ""
echo "[+] Run: who -all"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` who -all
echo ""

echo "+---------- check wtmp after run zap ----------+"
echo "[+] Run: last"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` last
echo ""

echo "+---------- check lastlog before run zap ----------+"
echo "[+] Run: lastlog"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` lastlog
echo ""

echo "+---------- check rootkit ----------+"

echo "[+] Run: chkwtmp"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` chkwtmp
echo ""

echo "[+] Run: chklastlog"
docker exec -i `docker ps | grep zap | awk '{ print $1 }'` chklastlog
echo ""

docker exec -i `docker ps | grep zap | awk '{ print $1 }'` /bin/sh
