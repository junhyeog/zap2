groupadd -g 9999 user
useradd -r -u 9999 -g user user
useradd -r -u 8888 -g user user2
useradd -r -u 7777 -g user attacker

passwd user
# 1234
# 1234
passwd user2
passwd attacker



date -s "1 Apr 2021 18:00:00"
login user
exit

exec date -s "2 Apr 2021 18:00:00"
spawn login user
expect "Password*"
send "d\r"
expect "*\$*"
send "exit"

exec date -s "3 Apr 2021 18:00:00"
spawn login user2
expect "Password*"
send "d\r"
expect "*\$*"
send "exit"

exec date -s "5 Apr 2021 18:00:00"
spawn login attacker
expect "Password*"
send "d\r"
expect "*\$*"
send "exit"

exec date -s "6 Apr 2021 18:00:00"
spawn login user2
expect "Password*"
send "d\r"
expect "*\$*"
send "exit"

exec date -s "7 Apr 2021 18:00:00"
spawn login attacker
expect "Password*"
send "d\r"
expect "*\$*"
send "exit"
