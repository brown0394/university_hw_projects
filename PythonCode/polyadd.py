class Polynom:
    def __init__(self, polist):
        self.polist = list(polist)
    def __str__(self):
        self.polist.reverse()##여기서 reverse해주는 이유는 계산
        ##편의를 위해서 지수가 작을 수록 좌측에 위치하다록 해두었기 때문에
##다시 지수가 클수록 좌측에 위치하도록 reverse 시켜주는 것입니다.
        newstr = "" ##출력을 위한 새로운 문자열
        first = True;##첫자리인지 검사해줄 부울 변수
        for (i, n) in self.polist:##i 자릿수 n 계수
            if(n < 0):##계수가 음수라면
                n *= -1## -1을 곱해서 양수로 변환
                if(first == True):##첫자리이면
                    newstr += "-"##띄어쓰기 없이 -부호를 붙여줌
                    first = False
                else:
                    if 0 == i and n:##지수가 0, 계수가 0이면 부호 붙이지 말고 생략
                        break
                    newstr += " - "##첫자리 아니면 앞의 수도 있으니 " - "
            elif(n > 0):##계수가 양수라면
                if(first == True):
                    first = False##양수 첫자리는 부호를 생략
                else:
                    if 0 == i and n:
                        break
                    newstr += " + "##첫자리가 아니면 " + "
            if n > 1:##계수가 1보다 크면
                if i > 1:
                    newstr += f"{n}x^{i}"##예 3x^2
                elif i == 1:##지수가 1이면 지수부 생략
                    newstr += f"{n}x"##예 3x
            elif n == 1:##계수가 1이면
                if i > 1:##지수가 1보다 크면 계수는 1이니까 생략 지수출력
                    newstr += f"x^{i}"##예 x^2
                elif i == 1:##지수 계수 둘 다 1인 경우
                    newstr += "x"##x
        if n != 0:##상수항이 0이면 출력 안함.
            newstr += str(n)##지수가 0일때 위에서 음수 양수 확인해서 " + " 혹은 반대 붙여주고
        ##지수가 0일때는 계수가 1인지 아닌지 상관없으므로 계수 출력
        return newstr
    def __repr__(self):
        return f"Polynom({self.polist})"
    def __add__(self, q):
        vals1 = []##더하기를 할 때 지수부를 이용하지 않으려 계수부만 리스트로 뽑아냅니다.
        vals2 = []
        for (i, n) in self.polist:
            vals1.append(n)
        for (i, n) in q.polist:
            vals2.append(n)
        count = 0
        length = 0
        if(len(vals1) > len(vals2)):
            length = len(vals1)
            diffrence = len(vals1) - len(vals2)##두 수의 자릿수 차이를 검사해서 차이나는 만큼 작은 리스트에 0을 추가해줍니다.
            while(diffrence > 0):
                vals2.append(0)
                diffrence -= 1
        elif(len(vals1) < len(vals2)):
            length = len(vals2)
            diffrence = len(vals2) - len(vals1)
            while(diffrence > 0):
                vals1.append(0)
                diffrence -= 1
        else:
            length = len(vals2)
        while(count < length):
            vals1[count] += vals2[count]##이제 두 리스트의 길이가 같기 때문에 같은 인데스의 계수들을 더해줍니다.
            count += 1
        return Polynom(list(enumerate(vals1)))##enumerate 통해서 다시 지수를 넣어주고 Polynom클래스 객체로 변환해서 반환
##위 방법 말고 오히려 지수를 이용해, 지수가 같으면 더하고 하는 형식을 사용해도 좋습니다.    


def poly (p_list):
    p_list.reverse()##뒤집어 주는 이유는 zip이나 enumerate가 좌측부터 0을 넣어주기 때문에, 지수가 가장 낮은 부분을 좌측으로 보내는 겁니다.
    newvalist = []
    newvalist = [(x, y) for (x,y) in zip(range(len(p_list)), p_list)]##zip부분은 사실 enumerate(p_list)랑 똑같은 역할을 합니다. 그냥 연습용으로 해봤어요.
    return newvalist

def main():
    val1 = input().split()
    val1 = list(map(int, val1))
    val1 = poly(val1)

    val2 = input().split()
    val2 = list(map(int, val2))
    val2 = poly(val2)

    poly1 = Polynom(val1)
    poly2 = Polynom(val2)

    poly1 = poly1 + poly2
    print(poly1)




if __name__ == "__main__":
    main()
