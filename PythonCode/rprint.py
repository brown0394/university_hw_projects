#coding: utf-8

def rprint(s):
    ls = list(s)
    ls.reverse()
    print("".join(ls))

def reverse_str(s):
    ls = list(s)
    ls.reverse()
    return "".join(ls)

def reverse_str2(s):
    return s[::-1]
    
if __name__ == "__main__":
    myword = "hello"
    print(myword)
    reverseword = reverse_str2(myword)
    print(reverseword)
