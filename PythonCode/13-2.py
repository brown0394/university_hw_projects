##n = 0
##
##def incr(gamma = 1, delta = 1):#overload
##    global n
##    n = n * gamma + delta
##    return n
##
##if __name__ == "__main__":
##    print(n)
##    print(incr())
##    print(incr(2))
##    print(incr(1,2))
##    print(incr(delta = 2))
##

from tkinter import *
def click():
    return

##if __name__ == "__main__":
##    win = Tk()
##    win.title('Python')
##    frm1 = Frame(win)
##    frm1.pack()
##    frm2 = Frame(win, borderwidth = 4, relief = GROOVE)
##    frm2.pack()
##    lbl1 = Label(frm1, text = "First Label")
##    lbl1.pack()
##    btn = Button(frm2, text = "Click", command = click)
##    btn.pack()
##    lbl2 = Label(frm2, text = "Second Label")
##    lbl2.pack()
##    win.mainloop()

##if __name__ == "__main__":
##    win = Tk()
##    win.title('Python')
##    frm1 = Frame(win)
##    frm1.pack()
##    frm2 = Frame(win, borderwidth = 4, relief = GROOVE)
##    frm2.pack(side = LEFT)
##    frm3 = Frame(win, borderwidth = 4, relief = GROOVE)
##    frm3.pack(side = RIGHT)
##    lbl1 = Label(frm1, text = "First Label")
##    lbl1.pack()
##    btn = Button(frm2, text = "Click", command = click)
##    btn.pack()
##    lbl2 = Label(frm2, text = "Second Label")
##    lbl2.pack()
##    lbl3 = Label(frm3, text = "Third Lable")
##    lbl3.pack()
##    win.mainloop()

##if __name__ == "__main__":
##    win = Tk()
##    win.title('Grid Layout')
##    frm1 = Frame(win, borderwidth = 10, relief = RAISED)
##    frm1.pack()
##    btn1 = Button(frm1, text = "Click1")
##    btn1.grid(row = 0, column = 0)
##    btn2 = Button(frm1, text = "Click2")
##    btn2.grid(row = 1, column = 1)
##    btn3 = Button(frm1, text = "Click3")
##    btn3.grid(row = 0, column = 1)
##    btn3 = Button(frm1, text = "Click4")
##    btn3.grid(row = 1, column = 0)
##    win.mainloop()

##if __name__ == "__main__":
##    win = Tk()
##    win.title('Absolute Layout')
##    win.geometry("250x200+300+30")##axb 창 가로 x 세로. 부모 윈도우 좌측 상단 300 30거리.
##    btn1 = Button(win, text = "Click1", font = ('Courier', 14, 'bold'))
##    btn1.place(x = 20, y = 20)
##    btn2 = Button(win, text = "Click2", bg = 'green', fg = 'blue')
##    btn2.place(x = 50, y = 100)
##    btn3 = Button(win, text = "Click3")
##    btn3.place(x = 110, y = 40)
##    win.mainloop()

if __name__ == "__main__":
    print(eval("2 * 3 + 1"))
    print(eval("[1, 2 + 3, 2 * 3, 3 + 1]"))
    print(eval("list('abc')"))
    print(eval("0o10"))
    print(eval("0x10"))
