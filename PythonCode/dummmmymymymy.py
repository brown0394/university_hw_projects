class DataError(Exception):
    def __init__(self, msg):
         
        self.msg = msg
    def __str__(self):
        return self.msg
def robust():
   
    cnt=0
    sum=0
    while 1:

        
        try:
            alist = input().split()
            if alist==[]:
                raise DataError(alist)
            for i in range(len(alist)):
                sum += int(alist[i])
        except ValueError:#ValueError             
            print(f"({sum})")
        else:
            print(sum)
        
if __name__=="__main__":
    robust()
