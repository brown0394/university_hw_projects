def Projectile():#Projectile Motion
    ivelocity = 50 #initial velocity
    iheight = 5 #initial height
    time = 3 #3 seconds
    fheight = (-16 * (time ** 2)) + (ivelocity * time) + iheight #height after 3 seconds
    return fheight

def Population():
    ipopulation = 845 #initial population
    growth = 6.5 #growth rate
    fpopulation = ipopulation * (1 + growth / 100)#present population
    return round(fpopulation)#0.5인이란 존재하지 않으므로 반올림

def Calories():
    ft3_calorie = 48600 #calorie per cubic foot
    mi3 = 5280 ** 3 #5280피트의 3제곱
    mi3_calorie = mi3 * 48600 #calorie per cubic mile
    return mi3_calorie

def MarketingTerm():
    purPrice = eval(input("Enter purchase price: "))#소수점 입력 대비 eval 사용
    sellPrice = eval(input("Enter the selling price: "))
    markup = float(sellPrice) - purPrice
    #양자 모두 int이면 소수점 출력이 안되므로 변수 하나를 float으로 형변환 
    per_markup = markup / purPrice * 100
    pro_margin = markup / sellPrice * 100
    print("Markup: $", markup, sep="") #sep이용 쉼표후 공백 생략
    print("Percentage markup: ", per_markup, '%', sep='')
    print("Profit margin: ", round(pro_margin, 2), '%', sep='')
    #round()이용 소수점 2자리 이하 반올림

def WordReplace():
    string = input("Enter a sentence: ")
    while(True): #문장에 포함되지 않은 단어 입력시 루프 
        replaceKey = input("Enter word to replace: ")
        if string.find(replaceKey) == -1: #.find()가 -1 반환시 해당 단어 없으므로 루프
            print("couldnt find", replaceKey, "from your sentence")
        else:
            break #-1이외의 숫자 반환시 루프 탈출
    newWord = input("Enter replacement word: ")
    newString = string.replace(replaceKey, newWord) #해당 단어를 교체한 새로운 스트링 생성
    print(newString)

def SalaryRaise():
    change = salary = eval(input("Enter the beginning salary: "))
    for i in range(0,3):#5%식 인상 3회 적용
        change = change * (1 + 5 / 100)
    print("New salary: ${0:,.2f}".format(change))#포맷 이용 자릿수 쉼표와 소수점 표기 지정
    print("Change: {0:.2%}".format((change / salary - 1)))#소수점 표기 지정과 %명시

def PresentVal():
    futureVal = eval(input("Enter future value: "))#f
    interestr = eval(input("Enter interest rate (as %): "))#r
    years = eval(input("Enter number of years: "))#n
    pre_val = futureVal / (1 + interestr / 100) ** years #f/(1 + (r / 100)**n)
    print("${0:,.2f}".format(pre_val))

def main():
    print("Projectile Motion")
    print("answer =", Projectile())
    print('\n')
    
    print("Population Increase")
    print("answer =", Population())
    print('\n')
    
    print("Calories")
    print("answer =", Calories())
    print('\n') 

    print("Marketing Terms")
    MarketingTerm()
    print('\n')

    print("Word Replacement")
    WordReplace()
    print('\n')

    print("Change in Salary")
    SalaryRaise()
    print('\n')

    print("Present Value")
    PresentVal()

if __name__ == "__main__":
    main()

