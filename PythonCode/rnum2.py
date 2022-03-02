#coding : utf-8

def roman_num(p_line, p_rdict, p_count, p_total):
    if p_count < len(p_line):
        if (p_line[p_count] == 'I' or 'X' or 'C') and (p_count + 1) < len(p_line):
            temp = p_line[p_count] + p_line[p_count + 1]
            if temp in p_rdict.keys():
                p_total += p_rdict[temp]
                p_count += 2
            else:
                p_total += p_rdict[p_line[p_count]]
                p_count += 1
        else:
            p_total += p_rdict[p_line[p_count]]
            p_count += 1
        return roman_num(p_line, p_rdict, p_count, p_total)
    else:
        return p_total
    
def main():
    line = input().upper()
    rnumbers = {'I' : 1, 'V' : 5, 'IV' : 4, 'IX' : 9, 'X' : 10, 'XL' : 40, 'L' : 50, 'XC': 90, 'C' : 100, 'CD' : 400, 'D' : 500, 'CM' : 900, 'M' : 1000}
    num = 0
    result = 0
    num = roman_num(line, rnumbers, num, result)
    print(num)

    

if __name__ == "__main__":
    main()
