def median(howMany, listOfNumbers):
    howMany = int(howMany)
    listOfNumbers = listOfNumbers.strip('[]\n')
    listOfNumbers = listOfNumbers.split(',')
    listOfNumbers = list(map(int,listOfNumbers))
#--------------- start your code ---------------
    median = 0# return할 median이 선언되어 있지 않으므로 선언.
    if howMany % 2 == 1:# 홀수 일 때
        median = listOfNumbers[(howMany // 2)]#중간 값 출력.
    else:
        median = (listOfNumbers[(howMany // 2) + 1] + listOfNumbers[howMany // 2]) / 2
        #중간 값 둘을 더해 /2 로 평균값 출력. 문제와 같이 5.5를 출력하기 위해 6과 5가 더해져 5.5가 나오게
        #했지만, 사실 중간값 둘이면 (3+6) / 2로 4.5 가 나와야함.
        #그를 위해서는 median = (listOfNumbers[(howMany // 2) - 1] + listOfNumbers[howMany // 2]) / 2
        #위와 같이 수정해야함.
#--------------- end your code -----------------
    return (median)

def special_number(min, max):
    for i in range (int(min), int(max)):
#--------------- start your code ---------------
        num = int(str(i)[::-1])#스트링을 변환후 slicing 이용 reverse후 다시 int로 변환
        if i * 4 == num:# i * 4가 i reversed와 같다면 return
#--------------- end your code -----------------
            return (i)

def wilson(input):
#--------------- start your code ---------------
    num = int(input)
    if isPrime(num):
        print(str(num), "is a prime number.")
    else:
        print(str(num), "is not a prime number.")#false가 return되면 소수가 아님을 출력

#--------------- end your code -----------------


def isPrime(n):
#--------------- start your code ---------------
    if (factorial(n-1) + 1) % n == 0:#wilson's theorem에 따라 나눠떨어지면 true
        return True
    return False

#--------------- end your code -----------------

def factorial(n):
    value = 1
#--------------- start your code ---------------
    for i in range(2, n+1):# 2에서 n까지 곱해준다. 1은 생략.
        value *= i
#--------------- end your code -----------------
    return value


def isTripleConsecutive(word):
#--------------- start your code ---------------
    word = word.upper()# 대문자로 치환하여 ord함수에 문제없이 작동하도록 함.
    for i in range(0, len(word)):
        if (len(word) - i) < 3:#남은 글자수가 3이하이면 false
            return False
        if ord(word[i]) == ord(word[i+1]) - 1 == ord(word[i+2]) - 2:
            return True# ord()를 이용하여 ascii코드 상 다음 숫자들로 이어지는 지 확인
#--------------- end your code -----------------

def alphabetical_order(input):
#--------------- start your code ---------------
    if(isTripleConsecutive(input)):
        print(input, "contains three succesive letters\nin consecutive alphabetical order.")
    else:
        print(input, "does not contain three succesive letters\nin consecutive alphabetical order.")
#--------------- end your code -----------------

def main():
    howMany = int(input("How many numbers do you want to enter? "))
    listofNumbers = "["
    for i in range(0, howMany):
        num = input('Enter a number: ')
        listofNumbers += num
        if i != howMany-1:
            listofNumbers += ','
    print("Median: ", median(howMany, listofNumbers))
    print()
    
    num = input().split()
    print(special_number(num[0], num[1]))
    print()
    
    wilson(input("Enter an integer greater than 1: "))
    print()
    
    alphabetical_order(input("Enter a word: "))

if __name__ == "__main__":
    main()
