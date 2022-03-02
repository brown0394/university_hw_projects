#coding : utf-8

def roman_num(p_line, count, total):
    changed = False
    if count < len(p_line):
        if p_line[count] == 'I' and (count + 1) < len(p_line):
            if p_line[count+1] == 'V':
                total += 4
                count += 1
                changed = True
            elif p_line[count+1] == 'X':
                total += 9
                count += 1
                changed = True
            else:
                total += 1
                changed = True
        if p_line[count] == 'I' and changed == False:
            total += 1
        elif p_line[count] == 'V' and changed == False:
            total += 5

        if p_line[count] == 'X' and (count + 1) < len(p_line) and changed == False:
            if p_line[count+1] == 'L':
                total += 40
                count += 1
                changed = True
            elif p_line[count+1] == 'C':
                total += 90
                count += 1
                changed = True
            else:
                total += 10
                changed = True
        elif p_line[count] == 'X' and changed == False:
            total += 10
        elif p_line[count] == 'L' and changed == False:
            total += 50

        if p_line[count] == 'C' and (count + 1) < len(p_line) and changed == False:
            if p_line[count+1] == 'D':
                total += 400
                count += 1
                changed = True
            elif p_line[count+1] == 'M':
                total += 900
                count += 1
                changed = True
            else:
                total += 100
                changed = True
        elif p_line[count] == 'C' and changed == False:
            total += 100
        elif p_line[count] == 'D' and changed == False:
            total += 500
        elif p_line[count] == 'M' and changed == False:
            total += 1000

        count += 1
        return roman_num(p_line, count, total)

    else:
        return total

def main():
    line = input().upper()
    num = 0
    result = 0
    num = roman_num(line, num, result)
    print(num)

    

if __name__ == "__main__":
    main()
