#coding : utf-8

def main():
    line = input().lower()
    jewel = dict()
    keys = set(line.split())
    
    count = 0
    for n in keys:
        jewel.update({n:line.count(n)})
    
    often = float(max(jewel.values()))
    often = often / len(line.split())
    print(max(jewel.values()))
    print(f"{often :.2f}")

if __name__ == "__main__":
    main()
