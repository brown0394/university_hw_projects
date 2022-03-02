class DataError(Exception):
    def __init__(self, data, msg="not convertible to int"):
        super().__init__(msg)
        self.data = data
    def cause(self):
        return "(" + f"{self.data}" + ")"

class LineError(Exception):
    def __init__(self, data, msg="this list is empty"):
        super().__init__(msg)
        self.data = data

def RobustSum(p_line):
    total = 0
    if p_line == []:
        raise LineError(p_line)
    for n in p_line:
        try:
            total += int(n)
        except ValueError:
            raise DataError(total)
    return total

def main():
    exitor = True
    while True:
        line = input().split()
        if exitor:
            try:
                print(RobustSum(line))
            except DataError as e:
                print(f"{e.cause()}")
            except LineError as e:
                exitor = False


if __name__ == "__main__":
    main()
