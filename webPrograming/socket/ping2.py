from ping3 import ping
from socket import gethostbyname

SIZE=32
PingXTimes=4
MAXTTL=225
pingTo = input()
ip = gethostbyname(pingTo)

step = int(MAXTTL / 10)

maxTTLReached = False
minVal = 10000000
maxVal = 0
avg = 0
recvd = 0

print("Ping", end=' ')
if pingTo.split('.')[0].isdigit() :
    print(ip, end=' ')
else :
    print(pingTo, '['+ip+']', end=' ')
print(str(SIZE)+"바이트 데이터 사용:")

for i in range(0,PingXTimes):
    result = None
    count = 1
    lastStep = 0
    incr = True
    while(True):
        result = ping(pingTo, size=SIZE, ttl=count, timeout=0.3)
        if incr:
            if result != None:
                last = count
                incr = False
                count -= 1
            if count >= MAXTTL:
                maxTTLReached = True
                break
            count += step
        else :
            if result == None:
                count = last
                break
            last = count
            count -= 1
    if maxTTLReached:
        result = ping(pingTo, size=SIZE, ttl=MAXTTL)
        if result != None:
            maxTTLReached = False
            count = MAXTTL
    if not maxTTLReached:
        result = ping(pingTo, size=SIZE, ttl=count)
        if result == None:
            print('요청 시간이 만료되었습니다.')
        else:
            result = int(result*1000)
            if result > maxVal :
                maxVal = result
            if result < minVal :
                minVal = result
            avg += result
            recvd += 1
            print(str(ip)+'의 응답: 바이트='+str(SIZE), 
            "시간", str(result)+"ms", "TTL="+str(count))
    else :
        print('요청 시간이 만료되었습니다.')

print()

print(ip+"에 대한 통계 Ping 통계:")
print("\t패킷: 보냄 =", PingXTimes, "받음 =", recvd, "손실 =", 
PingXTimes - recvd, "("+str(int(((PingXTimes-recvd) / PingXTimes) * 100))+"% 손실),")
if recvd > 0 :
    print("왕복 시간(밀리초):")
    print("\t최소 =", str(minVal)+"ms,", "최대 =", str(maxVal)+"ms,", "평균 =", str(int(avg/PingXTimes))+"ms")
print()