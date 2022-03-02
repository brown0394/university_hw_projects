class DataError(Exception):
    def __init__(self, data, msg="not convertible to int"):
        super().__init__(msg)
        self.data = data
    def cause(self):
        return self.data
        

def robust_sum(xs):
    total = 0
    for x in xs:
        try:
            total += int(x)
        except ValueError:
            raise DataError(x)
    return total



if __name__ == "__main__":
    xs = [10, 21, "thrity", 40, 5]
    ys = [10, 21, 31, 40, 5]
    for ls in [xs, ys]:      
        try:
            print(robust_sum(ls))
        except DataError as e:
            print(f"Error: negelcting '{e.cause()}'")
