#coding : utf-8

def main():
    val = list(input())
    valsum = 0

    loopcount = 1

    while True:
        count = 0
        while True:
            valsum += int(val[count]) **2
            if count < len(val) -1:
                count += 1
                continue
            val = str(valsum)
            valsum = 0
            loopcount += 1
            break
        if val != "1" and loopcount < 100: continue
        break

    if loopcount == 100:
        loopcount = -1
    print(loopcount)
    

if __name__ == "__main__":
    main()
