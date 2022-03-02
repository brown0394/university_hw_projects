from tkinter import *

##def click():#handler
##    counter.set(counter.get() + 1)
##
##
##if __name__ == "__main__":
##    win = Tk()
##    win.title('Tkinter test')
##    ##lbl = Label(win, text="This is my first label"*2)
##    ##lbl.pack()
##    counter = IntVar()
##    counter.set(0)
##    lbl = Label(win, textvariable=counter)
##    lbl.pack()
##    btn = Button(win, text="Click this", command=click)
##    btn.pack()
##    win.mainloop()
##    ##import tkinter
##    ##win = tkinter.Tk()

class Myint:
    def __init__(self, val):
        self.val = val
    def __set__(self, newval):
        self.val = newval
        

def fun():
    n = 5
    return n

def cl(inc):
    counter.set(counter.get() + inc)


if __name__ == "__main__":
    n = Myint(0)
    print(fun())
##    win = Tk()
##    win.title('Tkinter test')
##    ##lbl = Label(win, text="This is my first label"*2)
##    ##lbl.pack()
##    counter = IntVar()
##    counter.set(0)
##    click = lambda x: counter.set(counter.get() + x)
##    lbl = Label(win, textvariable=counter)
##    lbl.pack()
##    btn = Button(win, text="Up", command=lambda: cl(1))
##    btn.pack()
##    btn = Button(win, text="Down", command=lambda: cl(-1))
##    btn.pack()
##    win.mainloop()






##n = 0
##def func():
##    global n
##    n += 1
