def stirling(val1, val2):
    if val1 == val2 or val2 == 1 :
        return 1

    return val2 * stirling(val1 - 1, val2) + stirling(val1-1, val2-1)
    
def main():
    val1 = int(input())
    val2 = int(input())
    result = stirling(val1, val2)

    print(result)


if __name__ == "__main__":
    main()
