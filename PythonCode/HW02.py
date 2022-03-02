MILLION = 1000000 #상수로 선언
def TotalSum():
    total_sum = 0
    for i in range(0, 10):#0에서 9까지의 합
        total_sum += i
    total_sum = total_sum * (len(str(MILLION)) - 1) * (MILLION // 10) + 1
    #45가 len("1000000") - 1자리에서 1000000 / 10번 반복되고 +1 이루어짐.
    #소수점이 나올 이유가 없기에 // 연산자 사용
    print('The sum of the digits in the numbers from 1 to one million is {0}'.format(total_sum))



def PigLatin():
    word = input("Enter word to translate : ")
    og_word = word
    vowels = ('a', 'e', 'i', 'o', 'u')#변경 불가하도록 튜플 선언
    index = len(word) + 1 #처음 나오는 모음이 몇번째인지 저장할 변수.
    isWay = False #첫 글자가 모음인지 확인하는 부울변수
    #모음이 없는 단어(예. try)를 체크하기 위해 word길이 보다 1 크게 선언
    for char in vowels:
        if word[0] == char:# 첫 자리에 모음이 발견되면 단어에 way 붙이고 for문 탈출
            word += 'way'
            isWay = True
            break
        a = word.find(char)
        if a < index and a != -1: #저장된 index보다 더 앞선 자리에서 발견되면 가장 앞선 자리 저장
            index = a  
    if not isWay and 1 < index < len(word) + 1:
        #첫자리 모음이면 if문 생략. 첫자리만 자음이거나 모음이 없는 단어이면 원형 출력.
        word = og_word[index:]#첫 모음부터 끝까지.
        word += og_word[:index]#첫 자리부터 첫모음 전까지.
        word += 'ay'
    return [og_word, word]

def Bounce():
    r   = eval(input('Enter coefficient of restituion: '))
    h_i = eval(input('Enter initial height in meters: '))
    meters = 0.0
    bounces = 0
    height = h_i
    
    while True:
        meters += height# 떨어진 거리 가산.
        bounces += 1# 튕겨오른 횟수
        height *= r
        if height < 0.1:#10cm보다 적게 튀어오르면 와일문 탈출
            break
        meters += height# 튕겨져서 올라간 거리 가산.
    meters = round(meters, 2)
    print(f'Number of bounces: {bounces}')
    print('Meters traveled:   {:.2f}'.format(meters))


def main():
    #print(PigLatin())
    #Bounce()
    TotalSum()

if __name__ == '__main__':
    main()
