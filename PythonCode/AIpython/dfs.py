def name_5_1_46():
#--------------- start your code ---------------
    name = input("Enter a first name to be included: ").title()
    #텍스트 파일과 형식이 다르게 이름을 입력할시 통일성 유지 위해 .title() 사용
    file1 = "Names.txt"
    try:
        infile = open(file1, 'r')
    except FileNotFoundError:
        print(file1, "does not exist")#파일 존재여부 확인
    namelist = set()#이름들을 저장할 set 선언
    for line in infile:
        if line == name + '\n':#읽어오는 값들이 \n을 포함하고 있기에, 검사를 위해 추가.
            print(name, "aleready exist in file")
            infile.close()#이름이 존재하면 파일을 닫고 함수 탈출
            return None
        namelist.add(line.strip())#이름이 존재하지 않으면 set에 추가
    namelist.add(name)#여기가 실행되면 이름이 존재하지 않음을 의미하므로 추가
    namelist = sorted(namelist)#추가된 이름을 순서에 맞게 정렬
    infile.close()#읽어오는 것은 종료
    outfile = open(file1, 'w')
    for line in namelist:
        outfile.write(line + '\n')#개행문자 추가후 write
    outfile.close()
    print(name, "is added in", file1)
#--------------- end your code -----------------



def number_6_1_31():
#--------------- start your code ---------------
    try:
        num = int(input("Enter an integer from 1 to 100: "))
        if 0 > num or num > 100:
            raise Exception()#입력 범위 벗어났을 때 에러 발생시키기.
    except ValueError:
        print("You did not enter an integer.")
    except Exception:
        print("Your number was not between 1 and 100")
    else:
        print("Your number is", num)#문제 없으면 출력 후 종료
#--------------- end your code -----------------



def alphabet_6_2_9():
#--------------- start your code ---------------
    import random as rand
    alpha = [chr(word) for word in range(97, 123)]
    #ascii코드 이용 알파벳 리스트 생성
    for letter in rand.sample(alpha, 3):#sample 메소드 이용 문자 뽑아옴.
        print(letter, end=" ")#일열로 출력
#--------------- end your code -----------------



if __name__ == '__main__':
    name_5_1_46()
    number_6_1_31()
    alphabet_6_2_9()
